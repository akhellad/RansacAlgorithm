#include "SphereModel.hpp"

double centerX = 0.0 , centerY = 0.0 , centerZ = 0.0 , radius = 0.0;; 

bool SphereModel::FitModel(const std::vector<Point3D>& data) {
    if (data.size() < NumParametersRequired()) {
        return false;  // Pas suffisamment de points pour ajuster le modèle
    }

    // Initialisation des sommes
    double sumX = 0.0, sumY = 0.0, sumZ = 0.0, sumXX = 0.0, sumYY = 0.0, sumZZ = 0.0, sumXY = 0.0, sumXZ = 0.0, sumYZ = 0.0;
    size_t n = data.size();

    // Calcul des sommes
    for (const Point3D& point : data) {
        sumX += point.x;
        sumY += point.y;
        sumZ += point.z;
        sumXX += point.x * point.x;
        sumYY += point.y * point.y;
        sumZZ += point.z * point.z;
        sumXY += point.x * point.y;
        sumXZ += point.x * point.z;
        sumYZ += point.y * point.z;
    }

    // Calcul des coefficients du modèle
    double denominator = n * (sumXX + sumYY + sumZZ) - (sumX * sumX + sumY * sumY + sumZ * sumZ);
    if (denominator == 0) {
        return false;  // Les données ne permettent pas de calculer le modèle
    }

    // Calcul du centre de la sphère
    centerX = (sumY * (sumYY + sumZZ) - sumZ * (sumXY + sumXZ)) / denominator;
    centerY = (sumZ * (sumXX + sumZZ) - sumX * (sumXY + sumYZ)) / denominator;
    centerZ = (sumX * (sumXX + sumYY) - sumY * (sumXY + sumYZ)) / denominator;

    radius = std::sqrt((sumX * sumX + sumY * sumY + sumZ * sumZ - (sumXX + sumYY + sumZZ)) / n);

    std::cout << "Sphere Model Parameters:" << std::endl;
    std::cout << "CenterX = " << centerX << std::endl;
    std::cout << "CenterY = " << centerY << std::endl;
    std::cout << "CenterZ = " << centerZ << std::endl;
    std::cout << "Radius = " << radius << std::endl;

    return true;  // Le modèle a été ajusté avec succès
}


double SphereModel::CalculateDistance(const Point3D& point) {
    // Calculez la distance du point au modèle de sphère
    double distance = std::sqrt((point.x - centerX) * (point.x - centerX) +
                               (point.y - centerY) * (point.y - centerY) +
                               (point.z - centerZ) * (point.z - centerZ));

    // La distance est la différence entre la distance au centre de la sphère et le rayon de la sphère
    return std::abs(distance - radius);
}

int SphereModel::NumParametersRequired() const {
    // Indiquez le nombre de paramètres requis pour le modèle de sphère (4 pour un centre de sphère et un rayon)
    return 4;
}
