# RANSAC Algorithm Project

## Description
Ce projet implémente l'algorithme RANSAC (RANdom SAmple Consensus) en C++ pour ajuster des modèles géométriques (sphère, plan, cylindre) à des ensembles de données 3D. Un script Python est également fourni pour visualiser les résultats.

## Prérequis
Pour exécuter ce projet, vous aurez besoin des éléments suivants :
- Un compilateur C++ prenant en charge le standard C++11 (par exemple, GCC)
- Bibliothèque Armadillo pour les opérations matricielles
- Bibliothèque Eigen pour les calculs de vecteurs et de matrices
- Python 3.x pour exécuter le script de visualisation
- Bibliothèques Python : matplotlib, numpy

## Installation des bibliothèques

### Armadillo
Sous Ubuntu, vous pouvez installer Armadillo en utilisant :
```bash
sudo apt-get install libarmadillo-dev
```

### Eigen
Sous Ubuntu, installez Eigen avec :
```bash
sudo apt-get install libeigen3-dev
```

### Bibliothèques Python
Installez les bibliothèques Python nécessaires avec pip :
```bash
pip install matplotlib numpy
```

## Compilation du programme
Le projet utilise un Makefile pour la compilation. Pour compiler le programme, exécutez :
```bash
make
```

## Exécution du programme
Pour exécuter le programme, utilisez :
```bash
./Ransac
```
Ce programme lira les ensembles de données (fichiers .csv), appliquera l'algorithme RANSAC et stockera les résultats dans des fichiers de sortie.
Visualisation des résultats
Le script Python fourni peut être utilisé pour visualiser les résultats. Exécutez le script en passant le chemin des fichiers de sortie générés par le programme C++ :
```bash
python visualize_results.py <chemin_vers_les_fichiers_de_sortie>
```