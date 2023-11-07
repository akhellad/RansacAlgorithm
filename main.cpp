#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "Point3D.hpp"
#include "ModelManager.hpp"
#include "SphereModel.hpp"
#include "PlaneModel.hpp"

int main() {
    // Initialisation du générateur de nombres aléatoires
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    // Génération de points 3D aléatoires
    std::vector<Point3D> randomData;
    int numRandomPoints = 100;  // Nombre de points 3D aléatoires à générer
    for (int i = 0; i < numRandomPoints; ++i) {
        double x = static_cast<double>(std::rand()) / RAND_MAX;
        double y = static_cast<double>(std::rand()) / RAND_MAX;
        double z = static_cast<double>(std::rand()) / RAND_MAX;
        randomData.push_back(Point3D(x, y, z));
    }

    // Génération de points 3D pour une sphère
    std::vector<Point3D> sphereData;
    double sphereRadius = 1.0;  // Rayon de la sphère
    int numSpherePoints = 100;  // Nombre de points sur la sphère

    for (int i = 0; i < numSpherePoints; ++i) {
        double theta = 2 * M_PI * i / numSpherePoints;
        double phi = M_PI * i / numSpherePoints;
        double x = sphereRadius * sin(phi) * cos(theta);
        double y = sphereRadius * sin(phi) * sin(theta);
        double z = sphereRadius * cos(phi);
        sphereData.push_back(Point3D(x, y, z));
    }

    // Génération de points 3D pour un plan
    std::vector<Point3D> planeData;
    double planeNormalX = 0.0;
    double planeNormalY = 0.0;
    double planeNormalZ = 1.0;  // Normale du plan

    for (double x = -5.0; x <= 5.0; x += 1.0) {
        for (double y = -5.0; y <= 5.0; y += 1.0) {
            double z = 0.0;  // Plan z = 0
            planeData.push_back(Point3D(x, y, z));
        }
    }

    ModelManager modelManager;

    // Test de l'ajustement du modèle de sphère
    if (modelManager.RANSACFit(randomData, 1000, 0.01, 1)) {
        std::cout << "Modèle de sphère ajusté avec succès." << std::endl;
    } else {
        std::cout << "Aucun modèle de sphère valide trouvé." << std::endl;
    }

    // Test de l'ajustement du modèle de plan
    if (modelManager.RANSACFit(randomData, 1000, 0.01, 1)) {
        std::cout << "Modèle de plan ajusté avec succès." << std::endl;
    } else {
        std::cout << "Aucun modèle de plan valide trouvé." << std::endl;
    }

    return 0;
}
