#ifndef CYLINDERMODEL_HPP
#define CYLINDERMODEL_HPP

#include "GeometryModel.hpp"
#include <vector>
#include <memory>

class CylinderModel : public GeometryModel {
public:
    CylinderModel() : centerX(0), centerY(0), centerZ(0), radius(0), directionX(0), directionY(0), directionZ(0) {}

    bool FitModel(const std::vector<Point3D>& data) override;
    double CalculateDistance(const Point3D& point) const override;
    int NumParametersRequired() const override;
	void DisplayResults(const std::vector<Point3D>& inliers, const std::vector<Point3D>& outliers, const std::string& filename, const std::string& dataType) const override;
    // Vous pouvez ajouter d'autres méthodes spécifiques pour la gestion du cylindre

private:
    // Paramètres du modèle de cylindre
    double centerX, centerY, centerZ; // Centre du cylindre
    double radius; // Rayon du cylindre
    double directionX, directionY, directionZ; // Direction du cylindre
    // Méthodes privées pour les calculs internes
};

#endif // CYLINDERMODEL_HPP
