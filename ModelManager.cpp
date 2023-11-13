#include "ModelManager.hpp"
#include "PlaneModel.hpp"
#include "SphereModel.hpp"
#include <iostream>
#include <set>
#include <algorithm>

std::vector<Point3D> ModelManager::getInliers(const std::shared_ptr<GeometryModel>& model, 
                                              const std::vector<Point3D>& data, 
                                              double threshold) const {
    std::vector<Point3D> inliers;

    for (const auto& point : data) {
        if (model->CalculateDistance(point) <= threshold) {
            inliers.push_back(point);
        }
    }

    return inliers;
}

std::vector<Point3D> ModelManager::getOutliers(const std::shared_ptr<GeometryModel>& model, 
                                               const std::vector<Point3D>& data, 
                                               double threshold) const {
    std::vector<Point3D> outliers;

    for (const auto& point : data) {
        if (model->CalculateDistance(point) > threshold) {
            outliers.push_back(point);
        }
    }

    return outliers;
}

bool ModelManager::RANSACFit(const std::shared_ptr<GeometryModel>& model, const std::vector<Point3D>& data, int nIterations, double inlierThreshold, int minInliers) {
    if (!model || data.empty()) {
        return false;
    }

    bool modelFound = false;
    int maxInliersCount = 0;
    std::vector<Point3D> ResultsInliers;

    for (int iteration = 0; iteration < nIterations; ++iteration) {
        std::set<int> indices;
        while (indices.size() < model->NumParametersRequired()) {
            indices.insert(rand() % data.size());
        }

        std::vector<Point3D> maybeInliers;
        for (int idx : indices) {
            maybeInliers.push_back(data[idx]);
        }
        if (!model->FitModel(maybeInliers)) {
            continue; // Échantillon invalide, réessayez
        }

        std::vector<Point3D> confirmedInliers;
        for (const Point3D& point : data) {
            if (model->CalculateDistance(point) < inlierThreshold) {
                confirmedInliers.push_back(point);
                ResultsInliers.push_back(point);
            }
        }

        if (confirmedInliers.size() >= minInliers && confirmedInliers.size() > maxInliersCount) {
            maxInliersCount = confirmedInliers.size();
            modelFound = true;
        }
    }

    if (modelFound) {
        std::cout << "Best model found with " << maxInliersCount << " inliers." << std::endl;
        // Vous pourriez également retourner le meilleur modèle ici si nécessaire
        std::vector<Point3D> inliers = getInliers(model, data, inlierThreshold);
        std::vector<Point3D> outliers = getOutliers(model, data, inlierThreshold);
        std::string filename = "results.txt";
        model->DisplayResults(inliers, outliers, filename);
    } else {
        std::cout << "No model found." << std::endl;
    }

    return modelFound;
}

