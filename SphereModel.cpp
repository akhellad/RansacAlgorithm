#include "SphereModel.hpp"
#include <iostream>
#include <fstream>

void SphereModel::DisplayResults(const std::vector<Point3D>& inliers, const std::vector<Point3D>& outliers, const std::string& filename) const {
    std::ofstream file(filename, std::ios::app);
    file << "Sphere Model Parameters:" << "\n";
    file << "CenterX = " << centerX << ", CenterY = " << centerY << ", CenterZ = " << centerZ << "\n";
    file << "Radius = " << radius << "\n";

    file << "Inliers:" << "\n";
    for (const auto& point : inliers) {
        file << "Point(" << point.x << ", " << point.y << ", " << point.z << ")" << "\n";
    }

    file << "Outliers:" << "\n";
    for (const auto& point : outliers) {
        file << "Point(" << point.x << ", " << point.y << ", " << point.z << ")" << "\n";
    }
    file.close();
}

bool SphereModel::FitModel(const std::vector<Point3D>& data) {
    if (data.size() < NumParametersRequired()) {
        return false; // Pas suffisamment de points
    }

    Eigen::MatrixXd A(data.size(), 4);
    Eigen::VectorXd b(data.size());

    for (size_t i = 0; i < data.size(); ++i) {
        double x = data[i].x, y = data[i].y, z = data[i].z;
        A(i, 0) = x * 2;
        A(i, 1) = y * 2;
        A(i, 2) = z * 2;
        A(i, 3) = -1.0;
        b(i) = x * x + y * y + z * z;
    }

    Eigen::VectorXd solution = A.colPivHouseholderQr().solve(b);

    // Les coordonnées du centre de la sphère
    centerX = solution(0);
    centerY = solution(1);
    centerZ = solution(2);

    // Calcul du rayon de la sphère
    double rSquare = solution(3) + centerX * centerX + centerY * centerY + centerZ * centerZ;
    radius = std::sqrt(std::abs(rSquare));

    return true; // Le modèle a été ajusté avec succès
}

//afficher outlayer, centre et radius de la sphere et inliers

double SphereModel::CalculateDistance(const Point3D& point) const{
    // Calculez la distance du point au modèle de sphère
    double distance = std::sqrt((point.x - centerX) * (point.x - centerX) +
                               (point.y - centerY) * (point.y - centerY) +
                               (point.z - centerZ) * (point.z - centerZ));
    // La distance est la différence entre la distance au centre de la sphère et le rayon de la sphère
    return std::abs(distance - radius);
}
