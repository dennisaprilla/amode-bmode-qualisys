#ifndef VOLUME3DCONTROLLER_H
#define VOLUME3DCONTROLLER_H

#include <Eigen/Dense>

#include <QObject>
#include <QtDataVisualization>

#include "mhareader.h"

class Volume3DController : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief Constructor of the class
     */
    explicit Volume3DController(QObject *parent = nullptr, Q3DScatter *scatter = nullptr, MHAReader *mhareader=nullptr);

    /**
     * @brief Returns pixel intensity range (min and max)
     */
    std::array<int, 2> getPixelIntensityRange();

public slots:
    /**
     * @brief A slot where we could update the volume
     * As now i am writing this class, this function will be called when user change the threshold
     */
    void updateVolume(int value);

private:

    /**
     * @brief Returns indices from a vector (volume) that is over the threshold
     */
    void findIndicesWithThreshold(const std::vector<unsigned char>& volume, int threshold, std::vector<int>& result);

    /**
     * @brief Returns indices from a vector (volume) that is within the threshold
     */
    void findIndicesWithThreshold(const std::vector<unsigned char>& volume, std::vector<int> threshold, std::vector<int>& result);

    /**
     * @brief Returns values from a vector that is specified with indices
     */
    void getValuesWithIndices(const std::vector<unsigned char>& volume, const std::vector<int>& myindices, std::vector<unsigned char>& result);

    /**
     * @brief Converts indices into a subscript.
     * Imagine you have a long vector that it is actually a matrix. You have the indices but you want to know,
     * the position (row and column) in the matrix. This function will does that for you.
     */
    void ind2sub(const std::vector<int>& indices, const std::vector<int>& dimsize, std::vector<std::vector<int>>& voxelcoordinate);

    /**
     * @brief Convert std::vector of std::vector to an Eigen Matrix
     */
    Eigen::MatrixXd vectorVector2EigenMatrix(const std::vector<std::vector<int>>& voxel_coordinate);

    /**
     * @brief Initialize the data that will be shown in the scatter
     */
    void initData();


    // all variables related to MHA files
    Q3DScatter *m_scatter;                      //!< An object of the Q3Dscatter, initialized outside of this class
    MHAReader *myMHAReader_;                    //!< A pointer to an MHAReader object, contains the header data and the volume of MHA file
    MHAReader::MHAHeader myMHAHeader_;          //!< A pointer to an MHAHeader object, stores the header data from the MHA file
    std::vector<unsigned char> myMHAVolume_;    //!< A vector that stores the volume

    // variables for visualization only
    QLinearGradient gradient;                   //!< A gradient to color the data points in Q3DScatter

    // pixel information of the volume
    int pixelintensity_max_;                    //!< The maximum value of pixel intensity in the volume
    int pixelintensity_min_;                    //!< The minimum value of pixel intensity in the volume



signals:
};

#endif // VOLUME3DCONTROLLER_H
