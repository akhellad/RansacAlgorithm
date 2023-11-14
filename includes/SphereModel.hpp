#ifndef SPHEREMODEL_HPP
#define SPHEREMODEL_HPP

#include "GeometryModel.hpp"
#include <Eigen/Dense>
#include <vector>

class SphereModel : public GeometryModel {
private:
    double centerX, centerY, centerZ, radius;
public:
    SphereModel() : centerX(0), centerY(0), centerZ(0), radius(0) {}

    bool FitModel(const std::vector<Point3D>& data) override;
    double CalculateDistance(const Point3D& point) const override;
    int NumParametersRequired() const override { return 4; } // 4 points nécessaires pour définir une sphère
    void DisplayResults(const std::vector<Point3D>& inliers, const std::vector<Point3D>& outliers, const std::string& filename, const std::string& dataType) const override;
};

#endif // SPHEREMODEL_HPP
