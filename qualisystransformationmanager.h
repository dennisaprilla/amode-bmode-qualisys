#ifndef QUALISYSTRANSFORMATIONMANAGER_H
#define QUALISYSTRANSFORMATIONMANAGER_H

#include <Eigen/Geometry>
#include <unordered_map>
#include <string>

class QualisysTransformationManager {
public:
    void addTransformation(const std::string& id, const Eigen::Isometry3d& transform);
    Eigen::Isometry3d getTransformationById(const std::string& id) const;
    std::vector<Eigen::Isometry3d> getAllTransformations() const;
    std::vector<std::string> getAllIds() const;
    void clearTransformations();

private:
    std::unordered_map<std::string, Eigen::Isometry3d> idToTransformMap;
};

#endif // QUALISYSTRANSFORMATIONMANAGER_H
