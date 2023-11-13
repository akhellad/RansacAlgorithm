#include "Point3D.hpp"
#include "ModelManager.hpp"
#include "SphereModel.hpp"
#include "PlaneModel.hpp"
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

void normalizePoints(std::vector<Point3D>& points) {
    double sumX = 0, sumY = 0, sumZ = 0;
    double sumX2 = 0, sumY2 = 0, sumZ2 = 0;
    int n = points.size();

    // Calculer les sommes et les sommes des carrés
    for (const auto& point : points) {
        sumX += point.x;
        sumY += point.y;
        sumZ += point.z;

        sumX2 += point.x * point.x;
        sumY2 += point.y * point.y;
        sumZ2 += point.z * point.z;
    }

    // Calculer la moyenne et l'écart-type
    double meanX = sumX / n;
    double meanY = sumY / n;
    double meanZ = sumZ / n;

    double stdX = std::sqrt(sumX2 / n - meanX * meanX);
    double stdY = std::sqrt(sumY2 / n - meanY * meanY);
    double stdZ = std::sqrt(sumZ2 / n - meanZ * meanZ);

    // Normaliser chaque point
    for (auto& point : points) {
        point.x = (point.x - meanX) / stdX;
        point.y = (point.y - meanY) / stdY;
        point.z = (point.z - meanZ) / stdZ;
    }
}


std::vector<Point3D> ReadPointsFromCSV(const std::string& filename) {
    std::vector<Point3D> points;
    std::ifstream file(filename);
    std::string line;

    while (std::getline(file, line)) {
        std::stringstream lineStream(line);
        std::string cell;
        std::vector<double> pointData;

        while (std::getline(lineStream, cell, ',')) {
            pointData.push_back(std::stod(cell));
        }

        if (pointData.size() >= 3) {
            points.emplace_back(pointData[0], pointData[1], pointData[2]);
        }
    }

    return points;
}

int main() {
    std::vector<Point3D> spherePoints = ReadPointsFromCSV("sphere.csv");
    std::vector<Point3D> cylinderLowResPoints = ReadPointsFromCSV("cylinder-points-low-res.csv");
    std::vector<Point3D> cylinderHighResPoints = ReadPointsFromCSV("cylinder-points-high-res.csv");
    std::vector<Point3D> planePoints = ReadPointsFromCSV("plane.csv");

    // Ajout de modèles à ModelManager et exécution de RANSAC sur ces données
    ModelManager modelManager;
      // Création et ajout des modèles géométriques
    std::shared_ptr<GeometryModel> sphereModel = std::make_shared<SphereModel>();
    std::shared_ptr<GeometryModel> planeModel = std::make_shared<PlaneModel>();
    // Ajoutez ici les modèles pour les cylindres à basse et haute résolution
    // modelManager.AddModel(cylinderLowResModel);
    // modelManager.AddModel(cylinderHighResModel);

    // Paramètres RANSAC
    int numIterations = 1000;
    double inlierThreshold = 0.001;
    int minInliers = 100;

    // Exécution de RANSAC pour chaque ensemble de données
    std::cout << "\nRANSAC sur les données du plan:" << std::endl;
    if (modelManager.RANSACFit(planeModel, planePoints, numIterations, inlierThreshold, minInliers)) {
        std::cout << "Modèle de plan ajusté avec succès." << std::endl;
    } else {
        std::cout << "Aucun modèle de plan valide trouvé." << std::endl;
    }

    std::cout << "RANSAC sur les données de la sphère:" << std::endl;
    if (modelManager.RANSACFit(sphereModel, spherePoints, numIterations, inlierThreshold, minInliers)) {
        std::cout << "Modèle de sphère ajusté avec succès." << std::endl;
    } else {
        std::cout << "Aucun modèle de sphère valide trouvé." << std::endl;
    }


    // Répétez le processus pour les données des cylindres

    return 0;
}
