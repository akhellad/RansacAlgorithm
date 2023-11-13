import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import csv

# Lire les données depuis le fichier CSV
x_coords = []
y_coords = []
z_coords = []
with open('sphere.csv', 'r') as file:
    reader = csv.reader(file)
    for row in reader:
        x_coords.append(float(row[0]))
        y_coords.append(float(row[1]))
        z_coords.append(float(row[2]))

# Créer un graphique 3D
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

# Ajouter les points au graphique
ax.scatter(x_coords, y_coords, z_coords)

# Définir les étiquettes des axes
ax.set_xlabel('X Axis')
ax.set_ylabel('Y Axis')
ax.set_zlabel('Z Axis')

# Afficher le graphique
plt.show()