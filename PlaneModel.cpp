#include "PlaneModel.hpp"
#include <Eigen/Dense> 
#include <iostream>
#include <fstream>

void PlaneModel::DisplayResults(const std::vector<Point3D>& inliers, 
                                const std::vector<Point3D>& outliers, 
                                const std::string& filename) const {
    std::ofstream file(filename, std::ios::app); // Append mode

    file << "Plane Model Parameters:\n";
    file << "A = " << A << ", B = " << B << ", C = " << C << ", D = " << D << "\n";

    file << "Inliers:\n";
    for (const auto& point : inliers) {
        file << "Point(" << point.x << ", " << point.y << ", " << point.z << ")\n";
    }

    file << "Outliers:\n";
    for (const auto& point : outliers) {
        file << "Point(" << point.x << ", " << point.y << ", " << point.z << ")\n";
    }
    file.close();
}

#include <armadillo>

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


//afficher outlayer, parametres du plan et inliers

double PlaneModel::CalculateDistance(const Point3D& point) const {
    // Assurez-vous que A, B, C ne sont pas tous nuls pour éviter la division par zéro
    if (A == 0 && B == 0 && C == 0) return std::numeric_limits<double>::max();

    // Calculez la distance perpendiculaire du point au plan
    double numerator = std::abs(A * point.x + B * point.y + C * point.z + D);
    double denominator = std::sqrt(A * A + B * B + C * C);
    
    return numerator / denominator;
}