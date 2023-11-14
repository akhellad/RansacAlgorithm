#include "../includes/PlaneModel.hpp"
#include <iostream>
#include <fstream>
#include <armadillo>
#include <Eigen/Dense>

bool PlaneModel::FitModel(const std::vector<Point3D>& data) {
    if (data.size() < NumParametersRequired()) {
        return false; // Pas suffisamment de points
    }

    arma::mat matA(data.size(), 3);
    arma::vec vecB(data.size());

    for (size_t i = 0; i < data.size(); ++i) {
        matA(i, 0) = data[i].x;
        matA(i, 1) = data[i].y;
        matA(i, 2) = 1.0; // Terme constant
        vecB(i) = data[i].z;
    }

    // Résolution des moindres carrés
    arma::vec solution = arma::solve(matA, vecB);

    A = -solution(0);
    B = -solution(1);
    C = 1.0; // ou autre valeur selon votre formulation
    D = -solution(2);
    return true; // Le modèle a été ajusté avec succès
}

double PlaneModel::CalculateDistance(const Point3D& point) const {
    // Assurez-vous que A, B, C ne sont pas tous nuls pour éviter la division par zéro
    if (A == 0 && B == 0 && C == 0) return std::numeric_limits<double>::max();

    // Calculez la distance perpendiculaire du point au plan
    double numerator = std::abs(A * point.x + B * point.y + C * point.z + D);
    double denominator = std::sqrt(A * A + B * B + C * C);
    
    return numerator / denominator;
}

void PlaneModel::DisplayResults(const std::vector<Point3D>& inliers, 
                                const std::vector<Point3D>& outliers, 
                                const std::string& filename, 
                                const std::string& dataType) const {
    (void) dataType; // Pour éviter un avertissement de compilation
    // Enregistrement des paramètres du plan
    std::ofstream file_params(filename + "_plane_params.csv");
    file_params << "Parameter,Value\n";
    file_params << "NormalX," << A << "\n";
    file_params << "NormalY," << B << "\n";
    file_params << "NormalZ," << C << "\n";
    file_params << "D," << D << "\n";
    file_params.close();

    // Enregistrement des inliers
    std::ofstream file_inliers(filename + "_plane_inliers.csv");
    for (const auto& point : inliers) {
        file_inliers << point.x << "," << point.y << "," << point.z << "\n";
    }
    file_inliers.close();

    // Enregistrement des outliers
    std::ofstream file_outliers(filename + "_plane_outliers.csv");
    for (const auto& point : outliers) {
        file_outliers << point.x << "," << point.y << "," << point.z << "\n";
    }
    file_outliers.close();
}