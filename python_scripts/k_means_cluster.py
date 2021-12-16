# This is a sample Python script.
import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
from sklearn.cluster import KMeans
from sklearn.neighbors import NearestNeighbors

# Press the green button in the gutter to run the script.
if __name__ == '__main__':

# Read the data
    myData = pd.read_csv("data/1mill_2c.txt", sep='\t')
# Perform K-Means Cluster analysis with only 2 clusters. 
    kmeans = KMeans(n_clusters=2, init='random', n_init=1, max_iter=100, tol=0.0001, verbose=0)
    kmeans.fit(myData)
    print("Fitness: ", kmeans.inertia_)
    print("Membership: ")
    print(kmeans.labels_)
# Example of how to write data to a file
    # kmeans.labels_.tofile("Labels.csv", format='str')
    # np.savetxt("Labels.csv", kmeans.labels_)
    # print("Centroids: ")
    print(kmeans.cluster_centers_)


# clusters = []
# scores = []
# for c in range(1, 10, 1):
#     kmeans = KMeans(n_clusters=c, init='random', n_init=1, max_iter=100, tol=0.0001, verbose=0)
#     kmeans.fit(myData)
#     clusters.append(c)
#     scores.append(kmeans.inertia_)
#     print(kmeans.inertia_)
#     print(type(kmeans.labels_))
#     plt.scatter(myData[:,0], myData[:,1], c=kmeans.labels_)
#     plt.scatter(kmeans.cluster_centers_[:, 0], kmeans.cluster_centers_[:, 1], s=50, c='red')
# print(clusters)
# print(scores)
# plt.plot(clusters, scores, marker='x')
# plt.show()

