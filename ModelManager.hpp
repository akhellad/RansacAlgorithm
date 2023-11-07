#pragma once

#include "GeometryModel.hpp"
#include <vector>

class ModelManager {
private:
    std::vector<std::shared_ptr<GeometryModel>> models;

public:
    ModelManager() : models() {}  // Initialisation de models dans le constructeur

    void AddModel(std::shared_ptr<GeometryModel> model);
    bool RANSACFit(std::vector<Point3D>& data, int numIterations, double inlierThreshold, int minInliers);
};

