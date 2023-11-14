#include "../includes/Point3D.hpp"
#include "../includes/ModelManager.hpp"
#include "../includes/SphereModel.hpp"
#include "../includes/PlaneModel.hpp"
#include "../includes/CylinderModel.hpp"
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

std::vector<Point3D> ReadPointsFromCSV(const std::string& filename) {
    std::vector<Point3D> points;
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Erreur : Impossible d'ouvrir le fichier " << filename << std::endl;
        // Retourner un vecteur vide ou gérer l'erreur comme nécessaire
    }
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
    std::vector<Point3D> spherePoints = ReadPointsFromCSV("/home/akhellad/Documents/RansacAlgorithm/dataBase/sphere.csv");
    std::vector<Point3D> cylinderLowResPoints = ReadPointsFromCSV("/home/akhellad/Documents/RansacAlgorithm/dataBase/cylinder-points-low-res.csv");
    std::vector<Point3D> cylinderHighResPoints = ReadPointsFromCSV("/home/akhellad/Documents/RansacAlgorithm/dataBase/cylinder-points-high-res.csv");
    std::vector<Point3D> planePoints = ReadPointsFromCSV("/home/akhellad/Documents/RansacAlgorithm/dataBase/plane.csv");

    // Ajout de modèles à ModelManager et exécution de RANSAC sur ces données
    ModelManager modelManager;
      // Création et ajout des modèles géométriques
    std::shared_ptr<GeometryModel> sphereModel = std::make_shared<SphereModel>();
    std::shared_ptr<GeometryModel> planeModel = std::make_shared<PlaneModel>();
    std::shared_ptr<GeometryModel> cylinderLowResModel = std::make_shared<CylinderModel>();
    std::shared_ptr<GeometryModel> cylinderHighResModel = std::make_shared<CylinderModel>();

    // Paramètres RANSAC
    int numIterations = 1000;
    double planeInlierThreshold = 0.0000002;
    double sphereInlierThreshold = 0.001;
    double cylinderInlierLowResThreshold = 0.1;
    double cylinderInlierHighResThreshold = 0.005;
    int minInliers = 100;

    // Exécution de RANSAC pour chaque ensemble de données
    if (modelManager.RANSACFit(planeModel, planePoints, numIterations, planeInlierThreshold, minInliers, "Plane")) {
        std::cout << "Modèle de plan ajusté avec succès." << std::endl;
    } else {
        std::cout << "Aucun modèle de plan valide trouvé." << std::endl;
    }
    if (modelManager.RANSACFit(sphereModel, spherePoints, numIterations, sphereInlierThreshold, minInliers, "Sphere")) {
        std::cout << "Modèle de sphère ajusté avec succès." << std::endl;
    } else {
        std::cout << "Aucun modèle de sphère valide trouvé." << std::endl;
    }

    if (modelManager.RANSACFit(cylinderLowResModel, cylinderLowResPoints, numIterations, cylinderInlierLowResThreshold, minInliers, "LowRes")) {
        std::cout << "Modèle de cylindre ajusté avec succès." << std::endl;
    } else {
        std::cout << "Aucun modèle de cylindre valide trouvé." << std::endl;
    }

    if (modelManager.RANSACFit(cylinderHighResModel, cylinderHighResPoints, numIterations, cylinderInlierHighResThreshold, minInliers, "HighRes")) {
        std::cout << "Modèle de cylindre ajusté avec succès." << std::endl;
    } else {
        std::cout << "Aucun modèle de cylindre valide trouvé." << std::endl;
    }
    // Répétez le processus pour les données des cylindres

    return 0;
}
