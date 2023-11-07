#include "PlaneModel.hpp"

double A, B, C, D;

bool PlaneModel::FitModel(const std::vector<Point3D>& data, double inlierThreshold) {
    if (data.size() < NumParametersRequired()) {
        return false;  // Pas suffisamment de points pour ajuster le modèle
    }

    // Initialisation des sommes
    double sumX = 0.0, sumY = 0.0, sumZ = 0.0, sumXX = 0.0, sumXY = 0.0, sumXZ = 0.0, sumYY = 0.0, sumYZ = 0.0, sumZZ = 0.0;
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

    A = (n * (sumYZ * (sumXX + sumYY) - sumXY * (sumXY + sumXZ)) - sumY * (sumXZ * (sumXX + sumYY) - sumXY * (sumXY + sumYZ)) + sumZ * (sumXZ * (sumXY + sumXZ) - sumYY * (sumXY + sumYZ))) / denominator;
    B = (n * (sumXZ * (sumXX + sumYY) - sumXY * (sumXY + sumXZ)) - sumX * (sumYZ * (sumXX + sumYY) - sumXY * (sumXY + sumYZ)) + sumZ * (sumYZ * (sumXY + sumXZ) - sumXZ * (sumXY + sumYZ))) / denominator;
    C = (n * (sumXY * (sumXX + sumYY) - sumX * sumY * (sumXY + sumXZ)) - sumZ * (sumX * sumY * (sumXY + sumXZ) - sumXY * (sumXY + sumYZ)) + sumZ * (sumX * sumY * (sumXY + sumYZ) - sumYY * (sumXY + sumXZ))) / denominator;
    D = (sumZ * (sumXZ * (sumXX + sumYY) - sumXY * (sumXY + sumXZ)) - sumX * (sumYZ * (sumXX + sumYY) - sumXY * (sumXY + sumYZ)) + sumZ * (sumYZ * (sumXY + sumXZ) - sumYY * (sumXY + sumYZ))) / denominator;

    // Trouver les inliers en utilisant le modèle ajusté et un seuil
    std::vector<Point3D> inliers;
    for (const Point3D& point : data) {
        double distance = CalculateDistance(point);
        if (distance < inlierThreshold) {
            inliers.push_back(point);
        }
    }

    if (inliers.size() < NumParametersRequired()) {
        return false;  // Pas suffisamment d'inliers pour ajuster le modèle
    }

    // Réajustez le modèle en utilisant uniquement les inliers
    double sumX = 0.0, sumY = 0.0, sumZ = 0.0, sumXX = 0.0, sumXY = 0.0, sumXZ = 0.0, sumYY = 0.0, sumYZ = 0.0, sumZZ = 0.0;
    size_t n = inliers.size();

    for (const Point3D& inlier : inliers) {
        sumX += inlier.x;
        sumY += inlier.y;
        sumZ += inlier.z;
        sumXX += inlier.x * inlier.x;
        sumYY += inlier.y * inlier.y;
        sumZZ += inlier.z * inlier.z;
        sumXY += inlier.x * inlier.y;
        sumXZ += inlier.x * inlier.z;
        sumYZ += inlier.y * inlier.z;
    }

    double denominator = n * (sumXX + sumYY + sumZZ) - (sumX * sumX + sumY * sumY + sumZ * sumZ);
    if (denominator == 0) {
        return false;  // Les inliers ne permettent pas de calculer le modèle
    }

    A = (n * (sumYZ * (sumXX + sumYY) - sumXY * (sumXY + sumXZ)) - sumY * (sumXZ * (sumXX + sumYY) - sumXY * (sumXY + sumYZ)) + sumZ * (sumXZ * (sumXY + sumXZ) - sumYY * (sumXY + sumYZ))) / denominator;
    B = (n * (sumXZ * (sumXX + sumYY) - sumXY * (sumXY + sumXZ)) - sumX * (sumYZ * (sumXX + sumYY) - sumXY * (sumXY + sumYZ)) + sumZ * (sumYZ * (sumXY + sumXZ) - sumXZ * (sumXY + sumYZ))) / denominator;
    C = (n * (sumXY * (sumXX + sumYY) - sumX * sumY * (sumXY + sumXZ)) - sumZ * (sumX * sumY * (sumXY + sumXZ) - sumXY * (sumXY + sumYZ)) + sumZ * (sumX * sumY * (sumXY + sumYZ) - sumYY * (sumXY + sumXZ))) / denominator;
    D = (sumZ * (sumXZ * (sumXX + sumYY) - sumXY * (sumXY + sumXZ)) - sumX * (sumYZ * (sumXX + sumYY) - sumXY * (sumXY + sumYZ)) + sumZ * (sumYZ * (sumXY + sumXZ) - sumYY * (sumXY + sumYZ))) / denominator;

    std::cout << "Plane Model Parameters:" << std::endl;
    std::cout << "A = " << A << std::endl;
    std::cout << "B = " << B << std::endl;
    std::cout << "C = " << C << std::endl;
    std::cout << "D = " << D << std::endl;

    return true;
}

double PlaneModel::CalculateDistance(const Point3D& point) {
    // Calculez la distance du point au modèle de plan
    return std::abs(A * point.x + B * point.y + C * point.z + D) / std::sqrt(A * A + B * B + C * C);
}
int PlaneModel::NumParametersRequired() const {
    // Indiquez le nombre de paramètres requis pour le modèle de plan (4 pour Ax + By + Cz + D = 0)
    return 4;
}
