#include "../includes/CylinderModel.hpp"
#include <iostream>
#include <set>
#include <algorithm>
#include <armadillo>
#include <Eigen/Dense>
#include <fstream>
#include <vector>


bool CylinderModel::FitModel(const std::vector<Point3D>& data) {
    if (data.size() < NumParametersRequired()) {
        std::cout << "Not enough data points to define a cylinder" << std::endl;
        return false;
    }

    // Initialisation de la matrice de points avec Eigen
    Eigen::MatrixXd points(data.size(), 3);
    for (size_t i = 0; i < data.size(); ++i) {
        points(i, 0) = data[i].x;
        points(i, 1) = data[i].y;
        points(i, 2) = data[i].z;
    }

    // Calcul de la moyenne pour chaque colonne
    Eigen::Vector3d mean = points.colwise().mean();

    // Soustraction de la moyenne de chaque ligne
    Eigen::MatrixXd centered = points.rowwise() - mean.transpose();

    // Calcul de la matrice de covariance
    Eigen::MatrixXd cov = (centered.adjoint() * centered) / double(points.rows() - 1);

    // Calcul des vecteurs propres et des valeurs propres
    Eigen::SelfAdjointEigenSolver<Eigen::MatrixXd> eig(cov);
    Eigen::Vector3d cylinder_axis = eig.eigenvectors().col(2);

    // Calcul des projections et du rayon
    Eigen::MatrixXd projections(data.size(), 3);
    double radius_sum = 0;
    for (size_t i = 0; i < data.size(); ++i) {
        Eigen::Vector3d point = points.row(i);
        Eigen::Vector3d projection = (point.dot(cylinder_axis) * cylinder_axis) + mean;
        projections.row(i) = projection;

        double distance = (point - projection).norm();
        radius_sum += distance;
    }

    // Calcul du centre et du rayon estimés
    Eigen::Vector3d center = projections.colwise().mean();
    double estimated_radius = radius_sum / data.size();

    // Affectation des valeurs calculées aux variables de la classe
    centerX = center(0);
    centerY = center(1);
    centerZ = center(2);
    radius = estimated_radius;
    directionX = cylinder_axis(0);
    directionY = cylinder_axis(1);
    directionZ = cylinder_axis(2);

    return true;
}



double CylinderModel::CalculateDistance(const Point3D& point) const {
    // Convertir les composantes du point et de l'axe en vecteurs Armadillo
    arma::vec p = {point.x, point.y, point.z};
    arma::vec center = {centerX, centerY, centerZ};
    arma::vec axis = {directionX, directionY, directionZ};

    // Calculer le vecteur allant du centre du cylindre au point
    arma::vec centerToPoint = p - center;

    // Projetons ce vecteur sur l'axe du cylindre
    arma::vec projection = dot(centerToPoint, axis) * axis;

    // Calculer le vecteur perpendiculaire à l'axe du cylindre
    arma::vec perpendicular = centerToPoint - projection;

    // La distance est la norme de ce vecteur perpendiculaire moins le rayon
    double distance = arma::norm(perpendicular) - radius;

    return std::abs(distance); // Retourner la valeur absolue de la distance
}

int CylinderModel::NumParametersRequired() const {
    return 3; // Nombre minimal de points pour définir un cylindre
}

void CylinderModel::DisplayResults(const std::vector<Point3D>& inliers, 
                                   const std::vector<Point3D>& outliers, 
                                   const std::string& filename,
                                   const std::string& dataType) const {
    // Utiliser dataType pour personnaliser les noms de fichiers
    std::string filePrefix = filename + "_" + dataType + "_cylinder";

    // Enregistrement des paramètres du cylindre
    std::ofstream file_params(filePrefix + "_params.csv");
    file_params << "Parameter,Value\n";
    file_params << "CenterX," << centerX << "\n";
    file_params << "CenterY," << centerY << "\n";
    file_params << "CenterZ," << centerZ << "\n";
    file_params << "AxisX," << directionX << "\n";
    file_params << "AxisY," << directionY << "\n";
    file_params << "AxisZ," << directionZ << "\n";
    file_params << "Radius," << radius << "\n";
    file_params.close();

    // Enregistrement des inliers
    std::ofstream file_inliers(filePrefix + "_inliers.csv");
    for (const auto& point : inliers) {
        file_inliers << point.x << "," << point.y << "," << point.z << "\n";
    }
    file_inliers.close();

    // Enregistrement des outliers
    std::ofstream file_outliers(filePrefix + "_outliers.csv");
    for (const auto& point : outliers) {
        file_outliers << point.x << "," << point.y << "," << point.z << "\n";
    }
    file_outliers.close();
}

