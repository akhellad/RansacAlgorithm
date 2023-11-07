#pragma once

#include <vector>
#include <memory>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include "Point3D.hpp"

class GeometryModel {
public:
    virtual bool FitModel(const std::vector<Point3D>& data) = 0;
    virtual double CalculateDistance(const Point3D& point) = 0;
    virtual int NumParametersRequired() const = 0;
};
