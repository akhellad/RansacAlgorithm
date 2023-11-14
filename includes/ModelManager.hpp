#ifndef MODELMANAGER_HPP
#define MODELMANAGER_HPP

#include "GeometryModel.hpp"
#include <vector>
#include <memory>

class ModelManager {
private:

public:
    bool RANSACFit(const std::shared_ptr<GeometryModel>& model, const std::vector<Point3D>& data, int nIterations, double inlierThreshold, int minInliers, const std::string& dataType);
    std::vector<Point3D> getInliers(const std::shared_ptr<GeometryModel>& model, 
                                    const std::vector<Point3D>& data, 
                                    double threshold) const;
    std::vector<Point3D> getOutliers(const std::shared_ptr<GeometryModel>& model, 
                                     const std::vector<Point3D>& data, 
                                     double threshold) const;
};

#endif // MODELMANAGER_HPP



