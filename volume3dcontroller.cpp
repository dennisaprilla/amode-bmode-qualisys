#include "volume3dcontroller.h"
#include <omp.h>

Volume3DController::Volume3DController(QObject *parent, Q3DScatter *scatter, MHAReader *mhareader)
    : QObject{parent}, m_scatter(scatter), myMHAReader_(mhareader)
{
    // >> You might ask why do i use Q3DScatter instead of QCustom3DVolumetric to visualize our volumetric data.
    //    I must be very stupid, did not know how to use QCustom3DVolumetric.
    // >> The reason why i am doing this, because there is a rendering problem if i use QCustom3DVolumetric,
    //    a class that is inteded to handle volumetric data.
    // >> However, our goal is also to visualize signal peak along side the volumetric data. I was planning
    //    to use simple sphere to visualize the signal peak.
    // >> The problem comes because of the fact that the spheres will be inside the volumetric data. Then the
    //    rendering started to become wonky. The sphere "always at the back" of the opaque voxels (bones). I
    //    suspect it is because the Qt has unique rendering style for volumetric. The texture for opaque
    //    voxels always on top of anything else within the volume of the data.
    // >> So we instead performing a workaround by visualize the bone voxels as a point cloud.

    gradient = *new QLinearGradient();
    gradient.setColorAt(0.0, QColor(50,50,50)); // Low values of Z
    gradient.setColorAt(1.0, QColor(255,255,255));  // High values of Z

    QSurfaceFormat format;
    format.setSamples(0);
    scatter->setFormat(format);

    // get the initial data
    myMHAHeader_ = myMHAReader_->getMHAHeader();
    myMHAVolume_ = myMHAReader_->getMHAVolume();

    // Find the max and min elements in the vector
    auto minmax = std::minmax_element(myMHAVolume_.begin(), myMHAVolume_.end());
    pixelintensity_min_ = *minmax.first;
    pixelintensity_max_ = *minmax.second;

    // add data
    initData();
}

void Volume3DController::findIndicesWithThreshold(const std::vector<unsigned char>& volume, int threshold, std::vector<int>& result) {
    #pragma omp parallel for
    for (int i = 0; i <  static_cast<int>(volume.size()); ++i)
    {
        if (volume[i] > threshold) {
            #pragma omp critical
            result.push_back(i);
        }
    }
}

void Volume3DController::findIndicesWithThreshold(const std::vector<unsigned char>& volume, std::vector<int> threshold, std::vector<int>& result) {
    if (threshold.size() >2) return;

    #pragma omp parallel for
    for (int i = 0; i <  static_cast<int>(volume.size()); ++i)
    {
        if (volume[i] >= threshold[0] && volume[i] <= threshold[0]) {
            #pragma omp critical
            result.push_back(i);
        }
    }
}

void Volume3DController::getValuesWithIndices(const std::vector<unsigned char>& volume, const std::vector<int>& myindices, std::vector<unsigned char>& result) {
    #pragma omp parallel for
    for (int index : myindices) {
        #pragma omp critical
        result.push_back(volume[index]);
    }
}

void Volume3DController::ind2sub(const std::vector<int>& indices, const std::vector<int>& dimsize, std::vector<std::vector<int>>& voxelcoordinate) {
    #pragma omp parallel for
    for (int i = 0; i < static_cast<int>(indices.size()); ++i)
    {
        // int x = indices[i] % dimsize[0];
        // int y = (indices[i]/dimsize[0]) % dimsize[1];
        // int z = indices[i] / (dimsize[0] * dimsize[1]);
        #pragma omp critical
        voxelcoordinate.push_back({(indices[i] % dimsize[0]), (indices[i] / dimsize[0]) % dimsize[1], (indices[i] / (dimsize[0] * dimsize[1]))});
    }
}

Eigen::MatrixXd Volume3DController::vectorVector2EigenMatrix(const std::vector<std::vector<int>>& voxel_coordinate) {
    // Assuming all inner vectors have the same size
    int rows = voxel_coordinate.size();
    int cols = voxel_coordinate[0].size();

    // Create a temporary vector to hold all the data
    std::vector<int> temp;
    temp.reserve(rows * cols);
    for (const auto& row : voxel_coordinate) {
        temp.insert(temp.end(), row.begin(), row.end());
    }

    // Map the data to an Eigen matrix
    Eigen::MatrixXd matrix = Eigen::Map<Eigen::Matrix<int, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>>(temp.data(), rows, cols).cast<double>();

    return matrix;
}

void Volume3DController::initData()
{
    // initial pixel intensity
    int init_threshold = pixelintensity_min_ + ((pixelintensity_max_ - pixelintensity_min_)/2);

    // Get the data
    std::vector<int> indices;
    findIndicesWithThreshold(myMHAVolume_, init_threshold, indices);
    std::vector<unsigned char> volumevalues_overthresh;
    getValuesWithIndices(myMHAVolume_, indices, volumevalues_overthresh);

    // Convert indices to subscripts
    std::vector<std::vector<int>> voxelcoordinate;
    ind2sub(indices, myMHAHeader_.DimSize, voxelcoordinate);

    // Convert std::vector to Eigen::MatrixXd, more efficient to perform calculation
    Eigen::MatrixXd voxelcoordinate_ = vectorVector2EigenMatrix(voxelcoordinate).transpose();
    Eigen::MatrixXd voxelcoordinate_homogeneous(4, voxelcoordinate_.cols());
    voxelcoordinate_homogeneous << voxelcoordinate_, Eigen::MatrixXd::Ones(1, voxelcoordinate_.cols());

    // Get the transformation value from MHAReader
    Eigen::Vector3d init_t(myMHAHeader_.Offset[0], myMHAHeader_.Offset[1], myMHAHeader_.Offset[2]);
    Eigen::Vector3d init_s(myMHAHeader_.ElementSpacing[0], myMHAHeader_.ElementSpacing[1], myMHAHeader_.ElementSpacing[2]);
    // Eigen::Matrix3d init_R = Eigen::Matrix3d::Identity();
    Eigen::Matrix3d init_R = Eigen::AngleAxisd(-M_PI / 2, Eigen::Vector3d::UnitX()).toRotationMatrix();
    Eigen::Affine3d init_A = Eigen::Affine3d::Identity();
    init_A.translate(init_t);
    init_A.linear() = init_R * init_s.asDiagonal();

    // Apply the transformation
    voxelcoordinate_homogeneous = init_A.matrix() * voxelcoordinate_homogeneous;
    voxelcoordinate_ = voxelcoordinate_homogeneous.topRows(3);

    // Create a new QScatterDataArray
    QScatterDataArray* dataArray = new QScatterDataArray;
    // Resize the array to hold all points
    dataArray->resize(voxelcoordinate_.cols());
    // Copy the points from the Eigen matrix to the QScatterDataArray
    for (int i = 0; i < voxelcoordinate_.cols(); ++i) {
        (*dataArray)[i].setPosition( QVector3D(voxelcoordinate_(0, i),voxelcoordinate_(1, i),voxelcoordinate_(2, i)));
    }

    // Create a new scatter series
    QScatter3DSeries *series = new QScatter3DSeries();
    series->setName("tissue_layers");
    series->setItemSize(0.02f);
    series->setMesh(QAbstract3DSeries::MeshPoint);
    series->setBaseGradient(gradient);
    series->setColorStyle(Q3DTheme::ColorStyleRangeGradient);
    series->dataProxy()->resetArray(dataArray);

    // add the volume to the series
    m_scatter->addSeries(series);

    // set range
    m_scatter->axisX()->setRange(myMHAHeader_.Offset[0] - 50,
                                 myMHAHeader_.Offset[0]+(myMHAHeader_.DimSize[0]*myMHAHeader_.ElementSpacing[0]) + 50);
    m_scatter->axisY()->setRange(myMHAHeader_.Offset[1],
                                 myMHAHeader_.Offset[1]+(myMHAHeader_.DimSize[1]*myMHAHeader_.ElementSpacing[1]) + 50);
    m_scatter->axisZ()->setRange(myMHAHeader_.Offset[2]-(myMHAHeader_.DimSize[2]*myMHAHeader_.ElementSpacing[2]) - 50,
                                 myMHAHeader_.Offset[2] + 50);
}

void Volume3DController::updateVolume(int value)
{
    // delete all the series inside the scatter
    for (QScatter3DSeries *series : m_scatter->seriesList()) {
        if (series->name() == "tissue_layers") {
            m_scatter->removeSeries(series);
        }
    }

    // Get the data
    std::vector<int> indices;
    findIndicesWithThreshold(myMHAVolume_, value, indices);
    std::vector<unsigned char> volumevalues_overthresh;
    getValuesWithIndices(myMHAVolume_, indices, volumevalues_overthresh);

    // Convert indices to subscripts
    std::vector<std::vector<int>> voxelcoordinate;
    ind2sub(indices, myMHAHeader_.DimSize, voxelcoordinate);

    // Convert std::vector to Eigen::MatrixXd, more efficient to perform calculation
    Eigen::MatrixXd voxelcoordinate_ = vectorVector2EigenMatrix(voxelcoordinate).transpose();
    Eigen::MatrixXd voxelcoordinate_homogeneous(4, voxelcoordinate_.cols());
    voxelcoordinate_homogeneous << voxelcoordinate_, Eigen::MatrixXd::Ones(1, voxelcoordinate_.cols());

    // Get the transformation value from MHAReader
    Eigen::Vector3d init_t(myMHAHeader_.Offset[0], myMHAHeader_.Offset[1], myMHAHeader_.Offset[2]);
    Eigen::Vector3d init_s(myMHAHeader_.ElementSpacing[0], myMHAHeader_.ElementSpacing[1], myMHAHeader_.ElementSpacing[2]);
    // Eigen::Matrix3d init_R = Eigen::Matrix3d::Identity();
    Eigen::Matrix3d init_R = Eigen::AngleAxisd(-M_PI / 2, Eigen::Vector3d::UnitX()).toRotationMatrix();
    Eigen::Affine3d init_A = Eigen::Affine3d::Identity();
    init_A.translate(init_t);
    init_A.linear() = init_R * init_s.asDiagonal();

    // Apply the transformation
    voxelcoordinate_homogeneous = init_A.matrix() * voxelcoordinate_homogeneous;
    voxelcoordinate_ = voxelcoordinate_homogeneous.topRows(3);

    // Create a new QScatterDataArray
    QScatterDataArray* dataArray = new QScatterDataArray;
    // Resize the array to hold all points
    dataArray->resize(voxelcoordinate_.cols());
    // Copy the points from the Eigen matrix to the QScatterDataArray
    for (int i = 0; i < voxelcoordinate_.cols(); ++i) {
        (*dataArray)[i].setPosition( QVector3D(voxelcoordinate_(0, i),voxelcoordinate_(1, i),voxelcoordinate_(2, i)));
    }

    // Create a new scatter series
    QScatter3DSeries *series = new QScatter3DSeries();
    series->setName("tissue_layers");
    series->setItemSize(0.02f);
    series->setMesh(QAbstract3DSeries::MeshPoint);
    series->setBaseGradient(gradient);
    series->setColorStyle(Q3DTheme::ColorStyleRangeGradient);
    series->dataProxy()->resetArray(dataArray);

    // and the volume to the series
    m_scatter->addSeries(series);

    // set range
    m_scatter->axisX()->setRange(myMHAHeader_.Offset[0] - 50,
                                 myMHAHeader_.Offset[0]+(myMHAHeader_.DimSize[0]*myMHAHeader_.ElementSpacing[0]) + 50);
    m_scatter->axisY()->setRange(myMHAHeader_.Offset[1],
                                 myMHAHeader_.Offset[1]+(myMHAHeader_.DimSize[1]*myMHAHeader_.ElementSpacing[1]) + 50);
    m_scatter->axisZ()->setRange(myMHAHeader_.Offset[2]-(myMHAHeader_.DimSize[2]*myMHAHeader_.ElementSpacing[2]) - 50,
                                 myMHAHeader_.Offset[2] + 50);
}

std::array<int, 2> Volume3DController::getPixelIntensityRange() {
    std::array<int, 2> result = {pixelintensity_min_, pixelintensity_max_}; // Replace with your desired integers
    return result;
}





















