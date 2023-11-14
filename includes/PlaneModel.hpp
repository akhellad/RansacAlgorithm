#ifndef PLANEMODEL_HPP
#define PLANEMODEL_HPP

#include "GeometryModel.hpp"
#include <vector>

class PlaneModel : public GeometryModel {
private:
    double A, B, C, D; // Paramètres du plan : Ax + By + Cz + D = 0
public:
    PlaneModel() : A(0), B(0), C(0), D(0) {}

    bool FitModel(const std::vector<Point3D>& data) override;
    double CalculateDistance(const Point3D& point) const override;
    int NumParametersRequired() const override { return 3; } // 3 points nécessaires pour définir un plan
    void DisplayResults(const std::vector<Point3D>& inliers, const std::vector<Point3D>& outliers, const std::string& filename, const std::string& dataType) const override;
};

#endif

