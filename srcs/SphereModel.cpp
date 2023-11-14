#include "../includes/SphereModel.hpp"
#include <iostream>
#include <fstream>

void SphereModel::DisplayResults(const std::vector<Point3D>& inliers, 
                                 const std::vector<Point3D>& outliers, 
                                 const std::string& filename, 
                                 const std::string& dataType) const {
    // Enregistrement des paramètres de la sphère
    std::ofstream file_params(filename + "_sphere_params.csv");
    file_params << "Parameter,Value\n";
    file_params << "CenterX," << centerX << "\n";
    file_params << "CenterY," << centerY << "\n";
    file_params << "CenterZ," << centerZ << "\n";
    file_params << "Radius," << radius << "\n";
    file_params.close();

    // Enregistrement des inliers
    std::ofstream file_inliers(filename + "_sphere_inliers.csv");
    for (const auto& point : inliers) {
        file_inliers << point.x << "," << point.y << "," << point.z << "\n";
    }
    file_inliers.close();

    // Enregistrement des outliers
    std::ofstream file_outliers(filename + "_sphere_outliers.csv");
    for (const auto& point : outliers) {
        file_outliers << point.x << "," << point.y << "," << point.z << "\n";
    }
    file_outliers.close();
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
