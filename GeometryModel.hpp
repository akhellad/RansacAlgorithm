#ifndef GEOMETRYMODEL_HPP
#define GEOMETRYMODEL_HPP

#include "Point3D.hpp"
#include <vector>
#include <string>

class GeometryModel {
public:
    virtual ~GeometryModel() = default;
    virtual bool FitModel(const std::vector<Point3D>& data) = 0;
    virtual double CalculateDistance(const Point3D& point) const = 0;
    virtual int NumParametersRequired() const = 0;
    virtual void DisplayResults(const std::vector<Point3D>& inliers, 
                                const std::vector<Point3D>& outliers, const std::string& filename) const = 0;
};

#endif // GEOMETRYMODEL_HPP

