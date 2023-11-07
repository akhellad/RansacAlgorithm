#include "ModelManager.hpp"
#include <iostream>

void ModelManager::AddModel(std::shared_ptr<GeometryModel> model) {
    // Ajoutez un modèle à la liste des modèles gérés
    models.push_back(model);
}

bool ModelManager::RANSACFit(std::vector<Point3D>& data, int nIterations, double inlierThreshold, int minInliers) {
    if (models.empty() || data.empty()) {
        return false;
    }

    for (const auto& model : models) {
        for (int iteration = 0; iteration < nIterations; ++iteration) {
            // Sélectionnez un échantillon aléatoire de données
            std::vector<Point3D> maybeInliers;
            for (int i = 0; i < model->NumParametersRequired(); ++i) {
                maybeInliers.push_back(data[rand() % data.size()]);
            }

            // Estimez les paramètres du modèle à partir de l'échantillon
            if (!model->FitModel(maybeInliers)) {
                continue;  // Échantillon invalide, réessayez
            }

            std::vector<Point3D> confirmedInliers;
            for (const Point3D& point : data) {
                // Calculez la distance de chaque point au modèle
                double distance = model->CalculateDistance(point);

                // Si le point est un inlier (distance inférieure à inlierThreshold), ajoutez-le aux inliers confirmés
                if (distance < inlierThreshold) {
                    confirmedInliers.push_back(point);
                }
            }

            // Si le nombre d'inliers confirmés est supérieur ou égal à minInliers, le modèle est valide
            if (confirmedInliers.size() >= minInliers) {
                std::cout << "Model successfully fitted with " << confirmedInliers.size() << " inliers." << std::endl;
                return true;  // Vous pouvez également renvoyer le modèle estimé ici
            }
        }
    }

    std::cout << "No model found." << std::endl;
    return false;  // Aucun modèle n'a été trouvé
}
