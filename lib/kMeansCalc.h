/*
kMeansCalculator.
This program takes in data and clusters it.
See all the possible arguments to pass into the kMeansObject.
For instance, can pass in the number of clusters to create, the number 
of iterations, the threshold to stop at, and the number of random seeds.

The program will output summaries related to points / centroids. It can
also output a text file.
*/
#ifndef K_MEANS_CALC_H
#define K_MEANS_CALC_H

// for std::in / std::out
#include <iostream>
// for files
#include <fstream>
// for file names
#include <string>
// for random centroid gen
#include <random>
// for square root
#include <cmath>

#include "./Point.cpp"
#include "./Centroid.cpp"
#include "./myVector.cpp"
#include "./PointReader.cpp"

/*
This class performs all calculations for the k-means algorithm.
*/

template <class T>
class kMeansCalc{
    public:
        /*
        Ctor using file name.
        */
        kMeansCalc(const std::string &strInputFile, const int &pointDims);

        /*
        Default ctor:
        myVector size = 0, each pointer to null
        Members initialized.
        */
        kMeansCalc();
        /*
        Alternative const that accepts a primitive two d arr to init contents
        */
        kMeansCalc(T **data, const int &rows, const int &cols);
        /*
        Alternative constructor that accepts size of data (rows and cols, 
        aka #points and #dimensions) and a value to populate the data (aka
        populate the dims of the points with this value)
        */
        kMeansCalc(const int &numPoints, const int &numDim, const T &fillerVal= 0);

        /*
        Alternative constructor that accepts a point reader object and populates the 
        data using the already populated reader.
        */
        kMeansCalc(const PointReader<T>&reader);

        // copy ctor
        kMeansCalc(const kMeansCalc<T> &rhs);
        // dtor
        ~kMeansCalc();


        /*
         * ****************************
         * double returning functions
         * ****************************
         */
        // finds optimal clusterings, returns the average fitness of clusters
        double doubleFindOptimalClusters(const int &clusterCount, const int &iterations,const double& tolerance,const int &nstart=1);
        // finds a cluster average entropy (same thing as fitness, however the fitness function recalculates the entropies from scratch, thus this function faster)
        double doubleGetClusterAvgEntropy(const int &clusterId)const;
        // finds cluster avg fitness from scratch (slower, used to check the validity of doubleGetClusterAvgEntropy)
        double doubleGetClusterAvgFitness(const int &clusterId) const;

        /*
         * ****************************
         * Int returning functions
         * ****************************
         */
        // get the number of clusters passed
        int intGetClusterCount() const;
        // get the number of dimensions of an observation
        int intGetDimSize() const;
        // get the number of observations
        int intGetPointCount() const;
        // get the number of observations that fall under cluster
        int intGetPointCountForCluster(const int &clusterId) const;

        /*
         * ****************************
         * myVector returning functions
         * ****************************
         */
        // get the vector of points
        myVector<Point<T>> myvectorGetPoints() const;
        // get the vector of centroids
        myVector<Centroid<T>> myvectorGetCentroids() const;
        // a vector of doubles in order of cluster id
        myVector<double> myvectorGetClusterEntropies() const;
        // return the stats on the points
        // get the std devs of the observations, per dimension
        myVector<double> myvectorGetStdDevs()const;
        // get the avgs of the observations, per dimension
        myVector<double> myvectorGetAvgs()const;
        // get the maxes of the observations, per dimension
        myVector<double> myvectorGetMaxes()const;
        // get the mins of the observations, per dimension
        myVector<double> myvectorGetMins()const;

        /*
         * ****************************
         * void returning functions
         * ****************************
         */
        // print summary of observations
        void voidPrintSummary() const;
        // print summary of clusters
        void voidPrintClusterSummary() const;
        // write the points to file (done after assignment of membership)
        void voidWritePointsToFile(const std::string &fileName) const;
        // set the stddev vector
        void voidSetStdDevVector(const myVector<double>& stdDevs);
        // set the avgs vector
        void voidSetAvgsVector(const myVector<double>& avgs);
        // set the mins vector
        void voidSetMinsVector(const myVector<double>& mins);
        // set the maxes vector
        void voidSetMaxesVector(const myVector<double>& maxes);
        // set the points vector
        void voidSetPointsVector(const myVector<Point<T>>&points);
        // set the dim size
        void voidSetDimSize(const int&dimSize);
        // set the number of points
        void voidSetPointCount(const int &pointCount);

        /*
         * ****************************
         * operators
         * ****************************
        */
        // equality
        bool operator == (const kMeansCalc<T>&aKMeansCalc) const;
        // inequality
        bool operator != (const kMeansCalc<T>&aKMeansCalc) const;
        // assignment
        const kMeansCalc<T>& operator = (const kMeansCalc<T>&rhs);

        // add the two point vectors, NOT the centroid vectors, and return obj
        const kMeansCalc<T> operator + (const kMeansCalc<T> &aKMeansCalc) const;

        // get a point's membership
        int operator [](const int &intIndex) const;
        // set a point's membership
        int& operator[](const int &intIndex);


        // stream extraction, stream insertion
        template <class U>
        friend std::ostream &operator << (std::ostream & os, const kMeansCalc<U> &aKMeansCalc);

        template <class U>
        friend std::istream &operator >> (std::istream & input, kMeansCalc<U> &aKMeansCalc);

        /*
         * ****************************
         * Point returning functions
         * ****************************
         */
        // get point at index
        Point<T> pointGetPoint(const int &index) const;
        // get cluster centroid
        Centroid<T> pointGetCentroidPoint(const int&clusterIndex) const;

    private:
        // vector of cluster centroids
        myVector<Centroid<T>> myvectorCentroidPoints;
        // vector of observations
        myVector<Point<T>> myvectorPoints;
        // vector of cluster entropies (same thing as fitness)
        myVector<double> myvectorClusterEntropies;
        // vector of observation standard deviations, per dim
        myVector<double> myvectorStdDevs;
        // vector of observation avgs, per dim
        myVector<double> myvectorAvgs;
        // vector of observation mins, per dim
        myVector<double> myvectorMins;
        // vector of observation maxes, per dim
        myVector<double> myvectorMaxes;

        // check if index in bounds, used for check if index matches bounds for observation vector this->myvectorPoints
        bool boolCheckIndexBounds(const int &index) const;

        // number of clusters
        int intClusterCount {-1};
        // number of observations
        int intPointCount {-1};
        // number of dimensions of observation
        int intDimSize {-1};

        // reset and clear cluster vector this->myvectorCentroidPoints
        void voidClearClusters();
        // seed the first round of clusters (completely "random")
        void voidGenRandCentroids();
        // update the cluster centroids based on their members
        void voidUpdateClusterCentroids();
        // update the membership of points (assign membership) 
        void voidAssignPoints();
        // find the optimal clustering on the current random seed of clusters
        void voidFindOptimalClustersCurrentSeed(const int &intIterations,const double &tolerance);
        // get the total average entropy (fitness) of clusters
        double doubleGetTotalAvgEntropy() const;
};

#endif
