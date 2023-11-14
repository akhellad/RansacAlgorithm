RANSAC Algorithm Project
Description

Ce projet implémente l'algorithme RANSAC (RANdom SAmple Consensus) pour l'ajustement de modèles géométriques tels que les plans, les sphères et les cylindres à partir de données 3D. Le programme est écrit en C++ et utilise les bibliothèques Armadillo et Eigen pour les opérations mathématiques. Un script Python est également fourni pour visualiser les résultats.
Installation
Prérequis

    Compilateur C++ (g++, clang++, etc.)
    CMake (optionnel, pour la construction)
    Bibliothèque Armadillo
    Bibliothèque Eigen
    Python 3
    Bibliothèques Python : matplotlib, numpy

Installation des bibliothèques C++
Armadillo

Sur Ubuntu/Debian :

sudo apt-get install libarmadillo-dev

Sur Fedora :

sudo dnf install armadillo-devel

Eigen

Sur Ubuntu/Debian :

sudo apt-get install libeigen3-dev

Sur Fedora :

sudo dnf install eigen3-devel

Changer chemins des fichiers .csv dans srcs/main.cpp

Installation des bibliothèques Python

pip install matplotlib numpy

Compilation du programme

Dans le répertoire principal du projet :

make

Cela générera un exécutable nommé Ransac.

Changer chemins des resultats .csv dans le script python en fonction de la visualisation souhaitée.

Executer le script Python : 

Python visualiser_points_3d.py
