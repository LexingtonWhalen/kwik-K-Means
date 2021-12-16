/*
kMeansCalculator.
This program takes in data and clusters it.
See all the possible arguments to pass into the kMeansObject.
For instance, can pass in the number of clusters to create, the number 
of iterations, the threshold to stop at, and the number of random seeds.

The program will output summaries related to points / centroids. It can
also output a text file.
*/

#ifndef K_MEANS_CALC_CPP
#define K_MEANS_CALC_CPP


#include "./kMeansCalc.h"

/*
 * ***************************
 * Ctors, dtors
 * ***************************
 */

template <class T>
kMeansCalc<T>::kMeansCalc(){
    /*
    Inputs:
    void
    Outputs:
    void
    Utility:
    Default ctor:
    myVector size = 0, each pointer to null
    Members initialized.

    Note that due to the nature of how the code is encapsulated, certain attributes need not
    be defined in the default constructor. For example, the myVector class already has a default constructor
    that will be called, so this is hidden in any classes that use it.
    */
   this->intClusterCount = 0;
   this->intPointCount = 0;
   this->intDimSize = 0;

}

/*
Ctor using file name.
*/
template<class T>
kMeansCalc<T>::kMeansCalc(const std::string &strInputFile, const int &pointDims){
    /*
    Inputs: 
    input file name as a string
    number of dimensions each point has
    Outputs: 
    void
    Utility:
    Takes in the name of a file and the dimensions of the file and populates the vectors with points from the file
    */

    // create point reader object, read the file
    PointReader<T> pointreaderReader {strInputFile,pointDims};
    this->intClusterCount = 0;
    this->intDimSize = pointDims;
    // get the point vector from the PointReader object
    this->myvectorPoints.voidSetEqualLhsRhs(pointreaderReader.myvectorGetPoints());
    this->intPointCount = this->myvectorPoints.intLength();

    // get the vectors of statistics from the PointReader object
    this->myvectorStdDevs.voidSetEqualLhsRhs(pointreaderReader.myvectorGetStdDevs());
    this->myvectorAvgs.voidSetEqualLhsRhs(pointreaderReader.myvectorGetAvgs());
    this->myvectorMins.voidSetEqualLhsRhs(pointreaderReader.myvectorGetMins());
    this->myvectorMaxes.voidSetEqualLhsRhs(pointreaderReader.myvectorGetMaxes());
}

template <class T>
kMeansCalc<T>::kMeansCalc(T **data, const int &rows, const int &cols){
    /*
    Inputs:
    double pointer to data
    Outputs:
    void
    Utility:
    Creates the points based on a double array.
    Alt const that accepts a two d primitive arr

    NOTE: 

    This assumes that the user properly manages their own memory! We do not
    do any news or deletes here, just word with the passed in data.
    You manage your own memory!
    */
    this->intClusterCount = 0;
    // read the 2d array using PointReader
    PointReader<T> pointreaderReader {data,rows,cols};
    // get the points from PointReader
    this->myvectorPoints.voidSetEqualLhsRhs(pointreaderReader.myvectorGetPoints());
    // set the attributes
    this->intDimSize = cols;
    this->intPointCount = rows;
    // get the vectors of the stats from PointReader
    this->myvectorStdDevs.voidSetEqualLhsRhs(pointreaderReader.myvectorGetStdDevs());
    this->myvectorMins.voidSetEqualLhsRhs(pointreaderReader.myvectorGetMins());
    this->myvectorMaxes.voidSetEqualLhsRhs(pointreaderReader.myvectorGetMaxes());
    this->myvectorAvgs.voidSetEqualLhsRhs(pointreaderReader.myvectorGetAvgs());
}

template <class T>
kMeansCalc<T>::kMeansCalc(const int &numPoints, const int &dimSize, const T&fillerVal){
    /*
    Inputs: 
    number of points to be created
    number of dimensions each point has
    a filler value for each point to be set to
    Outputs: 
    null
    Utility: 
    Creates a kMean calculator with the desired number of points, dimensions and filler value
    Alt ctor that takes in the number of points, dimensions, and a filler value for all points
    */
    
    /*
    Rows are num points, cols are dim size

    IMPORTANT NOTE!
    The user is expected to know that this constructor only really can have one centroid.
    Attempting to do more than one centroid will give 1 actual centroid and everything else nans by design.
    This is to indicate that only one centroid is possible, since there is only one unique point!
    */
    this->intClusterCount = 0;
    this->intDimSize = dimSize;
    this->intPointCount = numPoints;
    // create a basic point object, fill the point vector with it.
    // basic point has unitialized cluster id
    Point<T> pointFillerPoint {dimSize,fillerVal,-1};
    myVector<Point<T>> points {numPoints,pointFillerPoint};
    this->myvectorPoints.voidSetEqualLhsRhs(points);

    // calculate min, max (note that it is just the fillervalue) since it is all same
    myVector<double> minsAndMaxes {dimSize,fillerVal};
    this->myvectorMins.voidSetEqualLhsRhs(minsAndMaxes);
    this->myvectorMaxes.voidSetEqualLhsRhs(minsAndMaxes);
    this->myvectorAvgs.voidSetEqualLhsRhs(minsAndMaxes);
    // note standard deviation is just zero since there is no deviation!
    myVector<double> stds {dimSize,0};
    this->myvectorStdDevs.voidSetEqualLhsRhs(stds);
}

template <class T>
kMeansCalc<T>::kMeansCalc(const PointReader<T> &reader){
    /*
    Inputs:
    PointReader
    Outputs:
    void
    Utility:
    Creates a kMeansCalc object based on a PointReader object.
    The PointReader is expected to already have data in it; else the if user
    tries to perform kMeansCalculations the program will print an error and exit, since
    you cannot perform calculations on no points.
    */

    // get the dimensions of the points from the reader
    this->intDimSize = reader.intGetPointDimensions();
    // get the vectors of statistics from the reader
    this->myvectorAvgs.voidSetEqualLhsRhs(reader.myvectorGetAvgs());
    this->myvectorMins.voidSetEqualLhsRhs(reader.myvectorGetMins());
    this->myvectorMaxes.voidSetEqualLhsRhs(reader.myvectorGetMaxes());
    this->myvectorStdDevs.voidSetEqualLhsRhs(reader.myvectorGetStdDevs());
    this->myvectorPoints.voidSetEqualLhsRhs(reader.myvectorGetPoints());
    this->intPointCount = this->myvectorPoints.intLength();
}

// copy ctor
template <class T>
kMeansCalc<T>::kMeansCalc(const kMeansCalc<T> &rhs){
    /*
    Inputs:
    kMeansCalc to be copied
    Outputs:
    void
    Utility:
    Creates a kMeansCalc in the image of rhs.
    */
    // basically just go thru all private members
    // and set them equal to this object
    this->myvectorClusterEntropies = rhs.myvectorGetClusterEntropies();
    this->myvectorCentroidPoints.voidSetEqualLhsRhs(rhs.myvectorGetCentroids());
    this->myvectorPoints.voidSetEqualLhsRhs(rhs.myvectorGetPoints());
    this->intDimSize = rhs.intGetDimSize();
    this->intPointCount = rhs.intGetPointCount();
    this->intClusterCount = rhs.intGetClusterCount();

    // for the summary
    this->myvectorStdDevs.voidSetEqualLhsRhs(rhs.myvectorGetStdDevs());
    this->myvectorAvgs.voidSetEqualLhsRhs(rhs.myvectorGetAvgs());
    this->myvectorMins.voidSetEqualLhsRhs(rhs.myvectorGetMins());
    this->myvectorMaxes.voidSetEqualLhsRhs(rhs.myvectorGetMaxes());
}
// dtor
template <class T>
kMeansCalc<T>::~kMeansCalc(){
    /*
    Inputs:
    void
    Outputs:
    void
    Utility:
    Destructor
    Note that all dynamic allocation of mem is done in the myVector class.
    Thus we do not need to deallocate anything here.
    */
}
/********************
 * Clustering functions
 * ****************/

// gen random cluster seed
template <class T>
void kMeansCalc<T>::voidGenRandCentroids(){
    /*
    Inputs:
    void
    Outputs:
    void
    Utility:
    * This function generates the initial random clusters.
    * Note: only used once, after we adjust the centroids without using any
    * randomness
    * 
    * NOTE: Cluster centroids are inited to real points. 
    * Note: cluster centroids are completely random. At first we were
    * going to have the same seed each time, but we found that certain seeds produce 
    * bad clusterings due to the nature of the seed.
    * Thus random seeds are more accurate.
    */

    /*
    Check if there are even points. If not exit out.
    */
    if(this->intPointCount <= 0){
        std::cout << "kMeansCalc.cpp: voidGenRandCentroids\n";
        std::cout << "Point count is " << this->intPointCount << "\n";
        std::cout << "Cannot perform calculations. Exiting.\n";
        exit(1);
    }
    // create a random device that selects integers between 0 and the number of points -1
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(0, this->myvectorPoints.intLength()-1);

    int intRandIndex=0;

    for(int i =0;i<this->intClusterCount;++i){
        // get a random number
        intRandIndex = distr(gen);
        // assign cluster center to cluster
        this->myvectorPoints[intRandIndex].voidSetClusterId(i);
        // create cluster
        this->myvectorCentroidPoints[i] = this->myvectorPoints.tGetByReference(intRandIndex);
    }
}
// assign points to nearest cluster
template <class T>
void kMeansCalc<T>::voidAssignPoints(){
    /*
    Inputs:
    void
    Outputs:
    void
    Utility:
    Assigns all points to their closest clusters.
    */
    /*
     * This function calculates the closest cluster for each point.
     * Returns the cluster ID of the closest one
     */
    /*
    Check if there are even points. If not, exit
    Similarly, if no clusters need to exit as well.
    */
    // reset the cluster memberships since we are now reassigning points
    for(int i=0;i<this->intClusterCount;++i){
        this->myvectorCentroidPoints[i].voidSetNumMembership(0);
    }
    // hold the minimum distance for points
    double doubleMinDist {0};
    // hold the best centroid for the points
    int intBestCentroid {-1};

    // hold the current distance
    double doubleCurrentDist {0};

    // loop thru clusters, find closest one
    for(int i=0;i<this->intPointCount;++i){

        intBestCentroid = 0;
        doubleMinDist = __DBL_MAX__;

        for(int j = 0;j<this->intClusterCount;++j){
            // get the current distance between centroid j
            doubleCurrentDist = this->myvectorPoints.tGetByReference(i).doubleGetDistance(this->myvectorCentroidPoints.tGetByReference(j));
            
            if(doubleCurrentDist <= doubleMinDist){
                // if current distance less than minimum, assign
                // reset minimum distance, assign point the centroid j
                doubleMinDist = doubleCurrentDist;
                this->myvectorPoints[i].voidSetClusterId(j);
                intBestCentroid = j;
            }
        }
        // found min distance between a point j and centroid i
        // add that distance to the centroid's entropy
        // also add membership
        this->myvectorCentroidPoints[intBestCentroid].voidAddToEntropyAndMembership(doubleMinDist,1);
    }
}

// update the cluster centroids based on the points that are members
template <class T>
void kMeansCalc<T>::voidUpdateClusterCentroids(){
    /*
    Inputs:
    void
    Outputs:
    void
    Utility:
    Using the old centroids, find better ones.
    Done by creating an "average point" from all points that are assigned to the centroid.
    */
    // update cluster centroids
    // DOES NOT ASSIGN POINTS!
    
    /*
    Check if there are even points. If not, exit
    */
    Centroid<T> pointBasePoint {this->intDimSize,0,-1};
    myVector<Centroid<T>> myvectorAvgPoints {this->intClusterCount,pointBasePoint};

    // set the ids
    for(int i=0;i<this->intClusterCount;++i){
        myvectorAvgPoints[i].voidSetClusterId(i);
        // put the same number of members as before
        myvectorAvgPoints[i].voidSetNumMembership(this->myvectorCentroidPoints.tGetByReference(i).intGetNumMembership());
    }
    // loop thru points, find the avg of each dimension
    int intClusterId  {0};
    for(int i=0;i<this->intPointCount;++i){
        // get the cluster id
        intClusterId = this->myvectorPoints.tGetByReference(i).intGetClusterId();
        // 
        myvectorAvgPoints[intClusterId].voidAddPointDirectly(this->myvectorPoints.tGetByReference(i));
    }
    // now divide points
    for(int i=0;i<this->intClusterCount;++i){
        myvectorAvgPoints[i].voidDivideDirectly(myvectorAvgPoints[i].intGetNumMembershipByReference());
    }
    // update cluster centroids
    this->myvectorCentroidPoints.voidSetEqualLhsRhs(myvectorAvgPoints);
}

// clear the clusters
template <class T>
void kMeansCalc<T>::voidClearClusters(){
    /*
    Inputs:
    void
    Outputs:
    void
    Utility:
    Clears the vector of clusters.
    */
    this->myvectorClusters.voidClear();
}
// get the optimal clusters on current seed
template <class T>
void kMeansCalc<T>::voidFindOptimalClustersCurrentSeed(const int &intMaxIterations, const double& doubleTolerance){
    /*
    Inputs:
    int
    Outputs:
    void
    Utility:
    // given the current conditions, find optimal clustering 
    // done by looping and calculating entropies given the current seed
    // compare the entropies to each other, find the smallest
    // assumes points have already been assigned from the current seed
    */

    /*
    Check if there are even points. If not exit out.
    */
    if(this->intPointCount <= 0){
        std::cout << "kMeansCalc.cpp: voidFindOptimalClustersCurrentSeed\n";
        std::cout << "Point count is " << this->intPointCount << "\n";
        std::cout << "Cannot perform calculations. Exiting.\n";
        exit(1);
    }
    // set min entropy total to inf
    double MIN_ENTROPY_TOTAL = __DBL_MAX__;
    // keep a vector of the last centroids
    myVector<Centroid<T>> myvectorLastCentroids {this->myvectorCentroidPoints};
    
    // for storing the last cluster for comparison of entropies
    int intIterationCounter =0;
    // keep track if the change in centroid values is below tolerance
    bool boolBelowToleranceFlag = false;
    // keep track if the change in centroid values is currently below tolerance
    bool boolCurrentlyBelowTolerance = false;

    // hold the current distance
    double doubleCurrentDist {0};
    // hold the current avg entropy
    double doubleCurrentAvgEntropy {0};

    while((intIterationCounter < intMaxIterations) and !boolBelowToleranceFlag){

        // update the centroids, no assign     
        this->voidUpdateClusterCentroids();
        // now assign points
        this->voidAssignPoints();
        /*
        Here we check the tolerance.
        Loop thru each dimension of the current centroids and compare to old centroids.
        If each dimension is below tolerance, exit. Else, repeat (even if a SINGLE dimension is above, repeat)
        */
        for(int i=0;i<this->intClusterCount;++i){
            // set currently below tolerance to true, if find a difference greater than tolerance then it immediately goes false
            boolCurrentlyBelowTolerance = true;

            for(int j=0;j<this->intDimSize;++j){
                doubleCurrentDist = (this->myvectorCentroidPoints.tGetByReference(i).tGetValAtDimNByReference(j) - myvectorLastCentroids.tGetByReference(i).tGetValAtDimNByReference(j));
                doubleCurrentDist = doubleCurrentDist * doubleCurrentDist;
                // if doubleCurrentDistance greater than tolerance, then need to keep going
                if(doubleCurrentDist > doubleTolerance){
                    boolCurrentlyBelowTolerance = false;
                }
            }
        }
        // check if below tolerance
        boolBelowToleranceFlag = boolCurrentlyBelowTolerance;
        // compare with last cluster
        doubleCurrentAvgEntropy = this->doubleGetTotalAvgEntropy();
        if(doubleCurrentAvgEntropy < MIN_ENTROPY_TOTAL){
            // current is better, swap out
            myvectorLastCentroids.voidSetEqualLhsRhs(this->myvectorCentroidPoints);
            MIN_ENTROPY_TOTAL = this->doubleGetTotalAvgEntropy();
        }else{
            // got worse, keep the old one
            this->myvectorCentroidPoints.voidSetEqualLhsRhs(myvectorLastCentroids);
            /*
            NOTE:
            If the algorithm gets worse, we can stop.
            This is still accurate but faster.
            */
            boolBelowToleranceFlag = true;
        }
        intIterationCounter ++;
    }
}
// finds the optimum clustering
template <class T>
double kMeansCalc<T>::doubleFindOptimalClusters(const int&intClusterCount,const int &intIterations, const double& doubleTolerance,const int& intNStart){
    /*
    Inputs:
    int, int, int, int, amount of clusters, number of iterations, minimal tolerance for termination
    Outputs:
    double, average intra cluster distance across all clusters
    Utility:
    Generates random clusters and uses kmeans calculation to determine clusters, then using iterations determines which set of clusters is the optimal version
    Adjusting cluster centroids terminates if no centroids move by the tolerance distance, or the number of iterations is reached. 
    */

    /*
    Check if there are even points. If not, exit
    */
    if(this->intPointCount <= 0){
        std::cout << "kMeansCalc.cpp: doubleFindOptimalClusters\n";
        std::cout << "Point count is " << this->intPointCount << "\n";
        std::cout << "Cannot perform calculations. Exiting.\n";
        exit(1);
    }

    // set the current cluster count
    this->intClusterCount = intClusterCount;
    // init the centroid vector

    // create a vector for centroids
    myVector<Centroid<T>> myvectorCurrentCentroids {intClusterCount};
    this->myvectorCentroidPoints.voidSetEqualLhsRhs(myvectorCurrentCentroids);
    
    // create a vector of max entropies, we compare to this to determine if a clustering is better
    // holds the optimal clusters
    myVector<Centroid<T>> myvectorOptimalCentroids {intClusterCount};
    // set min entropy to inf
    double doubleMinEntropy = __DBL_MAX__;

    // for getting current avg entropy
    double doubleCurrAvgEntropy {0};

    // loop thru number of iterations, each iteration gets a seed, then try to find best centroid from the seed
    for(int i=0;i<intNStart;++i){
        // start the seed
        voidGenRandCentroids();
        // assign points to centroids
        voidAssignPoints();
        // get the optimal clustering on this seed
        voidFindOptimalClustersCurrentSeed(intIterations,doubleTolerance);

        doubleCurrAvgEntropy = doubleGetTotalAvgEntropy();
        // compare to minimum entropies, if lower then update 
        if(doubleCurrAvgEntropy <= doubleMinEntropy){
            // update min entropy
            doubleMinEntropy = doubleCurrAvgEntropy;
            // update optimal clustering
            myvectorOptimalCentroids.voidSetEqualLhsRhs(this->myvectorCentroidPoints);
        }
    }
    /*
    Return the average of all intra-cluster distance
    */
    double doubleAvgIntraClusterDistance{0};
    for(int i=0;i<this->intClusterCount;++i){
        doubleAvgIntraClusterDistance += doubleGetClusterAvgEntropy(i);
    }
    doubleAvgIntraClusterDistance /= this->intClusterCount;
    return doubleAvgIntraClusterDistance;
}

// get the avg entropy (fitness) of cluster
template <class T>
double kMeansCalc<T>::doubleGetClusterAvgEntropy(const int &clusterId) const{
    /*
    Inputs: 
    Cluster ID number
    Outputs: 
    The average distance of a cluster centroid to its members
    Utility: 
    Returns the value of the passed in cluster's average entropy. 
    */
   // check if correct id
   if(clusterId <0 || clusterId >= this->intClusterCount){
       std::cout << "kMeansCalc: doubleGetClusterEntropy\n";
       std::cout << "Error: bad cluster id " << clusterId << " for total clusters " << this->intClusterCount << "\n";
       exit(1);
   }
   // else, return the cluster entropy
   // note that this is already contained in the point class
   return this->myvectorCentroidPoints.tGetByReference(clusterId).doubleGetAvgEntropy();
}
// get the avg fitness of cluster (differs from entropy in that this is slower)
// used to check accuracy of doubleGetClusterAvgEntropy
template <class T>
double kMeansCalc<T>::doubleGetClusterAvgFitness(const int &clusterId) const{
    /*
    Inputs: 
    int, Cluster's ID number
    Outputs:
    double, The average fitness of a cluster 
    Utility: 
    Calculates the average fitness of a cluster, the average distance of a cluster to its members.
     */
    // loop thru points, get distance between cluster id
    double doubleAvgDistance = 0;
    int intClusterPointCounter = 0;
    for(int i=0;i<this->intPointCount;++i){
        if(this->myvectorPoints.tGetByReference(i).intGetClusterIdByReference() == clusterId){
            // calc distance
            doubleAvgDistance += (myvectorPoints.tGetByReference(i).doubleGetDistance(this->myvectorCentroidPoints[clusterId]));
            intClusterPointCounter++;
        }
    }
    return doubleAvgDistance/intClusterPointCounter;
}
// get the total avg entropy across clusters
template <class T>
double kMeansCalc<T>::doubleGetTotalAvgEntropy() const{
    /*
    Inputs:
    void
    Outputs:
    void
    Utility:
    Returns the total entropy level of the centroid points.
    Centroid points store the entropy of the entire grouping.
    Entropy is a measure of disorder among points; centroids with lower entropy (ie: having points closer to them) are more optimal.
    */
    double totalEntropy {0};
    // loop thru centroids, get their entropy value
    for(int i=0;i<this->intClusterCount;++i){
        totalEntropy += this->myvectorCentroidPoints.tGetByReference(i).doubleGetAvgEntropy();
    }
    // then divide by total entropy
    return totalEntropy / this->intClusterCount;
}


/*******************
 * int returning functions
 * ****************/
// get the cluster count of kMeans object
template <class T>
int kMeansCalc<T>::intGetClusterCount() const{
    /*
    Inputs: 
    void
    Outputs: 
    int, the number of cluster
    Utility: 
    Returns the amount of clusters within the data
    */
    return this->intClusterCount;
}
// get the dimension size of points within kMeans object
template <class T>
int kMeansCalc<T>::intGetDimSize() const{
    /*
    Inputs:
    void
    Outputs:
    int, the amount of dimensions the data contains
    Utility:
    Returns the dimension size of the data.
    */
    return this->intDimSize;
}
// get the count of points in kmeans object
template <class T>
int kMeansCalc<T>::intGetPointCount() const{
    /*
    Inputs: 
    void
    Outputs: 
    int, Total point count
    Utility: 
    Returns the total number of points within the data
    */
    return this->myvectorPoints.intLength();
}

/*
 * *************************
 * myVector returning functions
 * *************************
 */
// get the point vector of object
template <class T>
myVector<Point<T>> kMeansCalc<T>::myvectorGetPoints() const{
    /*
    Inputs:
    void
    Outputs:
    myVector<Point<T>>, Vector of all the points. 
    Utility:
    Returns the vector of points.
    */
    return this->myvectorPoints;
}
// get the std dev vector of object
template <class T>
myVector<double> kMeansCalc<T>::myvectorGetStdDevs() const{
    /*
    Inputs:
    void
    Outputs:
    myVector<double>, vector with all of the standard deviations for each dimension. 
    Utility: 
    Returns the vector containing all of the standard deviations, individual member holds the standard deviation for the values in its respective dimension
    */
    return this->myvectorStdDevs;
}
// get the avgs vector of object
template <class T>
myVector<double> kMeansCalc<T>::myvectorGetAvgs() const{
    /*
    Inputs: 
    void
    Outputs:
    myVector<double>, vector that holds the average values
    Utility: 
    Returns the vector containing all of the average values of each dimension
    */
    return this->myvectorAvgs;
}
// get the maxes vector of object
template <class T>
myVector<double> kMeansCalc<T>::myvectorGetMaxes() const{
    /*
    Inputs: 
    void
    Outputs: 
    myVector<double>, vector containing the max values
    Utility:
    Returns a vector containing the maximum value found in each dimension
    */
    return this->myvectorMaxes;
}
// get the mins vec of obj
template <class T>
myVector<double> kMeansCalc<T>::myvectorGetMins() const{
    /*
    Inputs: 
    void
    Outputs: 
    myVector<double>, vector containinig the minimum values
    Utility: 
    Returns a vector containing the minimum values in each dimension
    */ 
    return this->myvectorMins;
}
// get the centroids of obj
template <class T>
myVector<Centroid<T>> kMeansCalc<T>::myvectorGetCentroids() const{
    /*
    Inputs: 
    void
    Outputs: 
    myVector<Point<T>>, vector containing the points that are the centroids
    Utility: 
    Returns the vector that holds all of the centroid points.
    */
    return this->myvectorCentroidPoints;
}
// get the cluster entropy vector of obj
template <class T>
myVector<double> kMeansCalc<T>::myvectorGetClusterEntropies() const{
    /*
    Inptus: 
    void
    Outputs: 
    myVector<double>, vector containing the entropies for each respective cluster
    Utility:
    Returns a vector which contains the average entropy for each respective cluster.
    */
    return this->myvectorClusterEntropies;
}

/**********
 * Void returning functions
 * ********/
// print summary of points
template <class T>
void kMeansCalc<T>::voidPrintSummary() const{
    /*
    Inputs: 
    void
    Outputs: 
    void
    Utility: 
    Prints out of summary of all the points that are in the kmeans calculator
    Prints the total point count, Minimum values in each dimension, Maxes in each dimension, averages in each dimension, and standard deviation in each deminsion
    */
    /*
    Check if there are even points. If not, exit
    */
    if(this->intPointCount <= 0){
        std::cout << "kMeansCalc.cpp: voidPrintSummary\n";
        std::cout << "Point count is " << this->intPointCount << "\n";
        std::cout << "Cannot perform calculations. Exiting.\n";
        exit(1);
    }
    // now we print things
    std::cout << "************************************\n";
    std::cout << "* Total number of points | " << this->intPointCount << "\n";
        std::cout << "------------------------------------\n";
    for(int i=0;i<this->intDimSize-1;++i){
        std::cout << "* Dim #" << i << " | Min = " << this->myvectorMins.tGetByReference(i) << "\n";
        std::cout << "* Dim #" << i << " | Max = " << this->myvectorMaxes.tGetByReference(i) << "\n";
        std::cout <<"* Dim #" << i << " | Mean = " << this->myvectorAvgs.tGetByReference(i) << "\n";
        std::cout <<"* Dim #" << i << " | stddev: " << this->myvectorStdDevs.tGetByReference(i) << "\n";
        std::cout << "------------------------------------\n";
    }
    // last dim
    std::cout << "* Dim #" << this->intDimSize-1 << " | Min = " << this->myvectorMins.tGetByReference(this->intDimSize-1) << "\n";
    std::cout << "* Dim #" << this->intDimSize-1 << " | Max = " << this->myvectorMaxes.tGetByReference(this->intDimSize-1) << "\n";
    std::cout <<"* Dim #" << this->intDimSize-1 << " | Mean = " << this->myvectorAvgs.tGetByReference(this->intDimSize-1) << "\n";
    std::cout <<"* Dim #" << this->intDimSize-1 << " | stddev: " << this->myvectorStdDevs.tGetByReference(this->intDimSize-1) << "\n";
    std::cout << "************************************\n";
}

// print summary of clusters
template <class T>
void kMeansCalc<T>::voidPrintClusterSummary() const{
    /*
    Inputs: 
    void
    Outputs: 
    void
    Utility: 
    Prints a summary of the cluster information
    Prints centroid dimensions, number of members, and fitness for each cluster, and total average cluster fitness across all clusters
    */
    /*
    Check if there are even points. If not, exit.
    */
    if(this->intPointCount <= 0){
        std::cout << "kMeansCalc.cpp: voidPrintClusterSummary\n";
        std::cout << "Point count is " << this->intPointCount << "\n";
        std::cout << "Cannot perform calculations. Exiting.\n";
        exit(1);
    }

    std::cout << "************************************\n";
    double doubleAvgEntropy =0;
    for(int i=0;i<this->intClusterCount-1;++i){
        // print cluster number:
        std::cout << "* Cluster             | " << i << "\n";
        // print centroid
        std::cout << "* Centroid Dimensions | ";
        for(int j=0;j<this->intDimSize;++j){
            std::cout << this->myvectorCentroidPoints.tGetByReference(i).tGetValAtDimNByReference(j) << " ";
        }
        std::cout << "\n";
        // print num members
        std::cout << "* Num members         | " << this->myvectorCentroidPoints[i].intGetNumMembershipByReference() << "\n";
        // print avg distance from center
        std::cout << "* Cluster fitness     | " << this->myvectorCentroidPoints[i].doubleGetAvgEntropy() << "\n";
        doubleAvgEntropy += this->myvectorCentroidPoints[i].doubleGetAvgEntropy();

        std::cout << "------------------------------------\n";
    }
    int intLastIndex = this->intClusterCount-1;
    // print cluster number:
    std::cout <<     "* Cluster             | " << intLastIndex << "\n";
    // print centroid
    std::cout << "* Centroid Dimensions | ";
    for(int j=0;j<this->intDimSize;++j){
        std::cout << this->myvectorCentroidPoints.tGetByReference(intLastIndex).tGetValAtDimNByReference(j) << " ";
    }
    std::cout << "\n";
    // print num members
    std::cout <<      "* Num members         | " << this->myvectorCentroidPoints[intLastIndex].intGetNumMembershipByReference() << "\n";
    // print avg distance from center
    // print total avg fitness

    std::cout <<       "* Cluster fitness     | " << this->myvectorCentroidPoints[intLastIndex].doubleGetAvgEntropy() << "\n";
    doubleAvgEntropy += this->myvectorCentroidPoints[intLastIndex].doubleGetAvgEntropy();

    doubleAvgEntropy /= this->intClusterCount;
    std::cout << "------------------------------------\n";

    std::cout << "* Cluster average fitness | " << doubleAvgEntropy <<"\n";
    std::cout << "************************************\n";
}

/*
 * Write points to file
 */
// wrte points to file
template <class T>
void kMeansCalc<T>::voidWritePointsToFile(const std::string &fileName)const{
    /*
    Inputs:
    string
    Outputs:
    void
    Utility:
    Writes the points and their assignments to a file. 
    */
    /*
    Check if there are even points. If not, exit.
    */
    if(this->intPointCount <= 0){
        std::cout << "kMeansCalc.cpp: voidWritePointsToFile\n";
        std::cout << "Point count is " << this->intPointCount << "\n";
        std::cout << "Cannot perform calculations. Exiting.\n";
        exit(1);
    }
    std::ofstream ofstreamOutData; 

    ofstreamOutData.open(fileName);
        // if error, exit
        if(!ofstreamOutData){
            std::cout << "Error: kMeansCalc.cpp\nFile " << fileName << " could not be opened.\n";
            exit(1);
        }
        // else start writing points
        // note here we use the Point classes string insertion operator
        for(int i=0;i<this->intPointCount;++i){
            ofstreamOutData << myvectorPoints.tGetByReference(i) << "\n";
        }

        // now put the centroids in
        // special character * to mark they are special
        for(int i=0;i<this->intClusterCount;++i){
            for(int j = 0;j<this->intDimSize;++j){
                ofstreamOutData << this->myvectorCentroidPoints.tGetByReference(i).tGetValAtDimNByReference(j) << " ";
            }
            ofstreamOutData << " | ";
            ofstreamOutData << this->myvectorCentroidPoints.tGetByReference(i).intGetClusterIdByReference();
            ofstreamOutData << "*\n";
        }

        ofstreamOutData.close();
}
// set the vector of points
template <class T>
void kMeansCalc<T>::voidSetPointsVector(const myVector<Point<T>>&points){
    /*
    Inputs: 
    myVector, reference to a vector full of points
    Outputs: 
    void
    Sets the vector of points for the kmean calc object to the passed in set of points
    */
    this->myvectorPoints.voidSetEqualLhsRhs(points);
}
// set the vector of maxes
template <class T>
void kMeansCalc<T>::voidSetMaxesVector(const myVector<double>& maxes){
    /*
    Inputs: 
    myVector, reference to a vector full of doubles, which are the maximum values in each dimension
    Outputs: 
    void
    Sets the vector of maximums in each dimension of the data set to the passed in the vector
    */
    this->myvectorMaxes.voidSetEqualLhsRhs(maxes);
}
// set the vector of mins
template <class T>
void kMeansCalc<T>::voidSetMinsVector(const myVector<double>& mins){
    /*
    Inputs: 
    myVector, reference to a vector full of doubles, which are the minimum values in each dimension
    Outputs: 
    void
    Sets the vector of minimums in each dimension of the data set to the passed in the vector
    */
    this->myvectorMins.voidSetEqualLhsRhs(mins);
}
// set the avg vectors
template <class T>
void kMeansCalc<T>::voidSetAvgsVector(const myVector<double>& avgs){
    /*
    Inputs: 
    myVector, reference to a vector full of doubles, which are the average values in each dimension
    Outputs: 
    void
    Sets the vector of averages in each dimension of the data set to the passed in the vector
    */
    this->myvectorAvgs.voidSetEqualLhsRhs(avgs);
}
// set the vector of std devs
template <class T>
void kMeansCalc<T>::voidSetStdDevVector(const myVector<double>& stdDevs){
    /*
    Inputs: 
    myVector, reference to a vector full of doubles, which are the standard deviation values in each dimension
    Outputs: 
    void
    Utility:
    Sets the vector of standard deviations in each dimension of the data set to the passed in the vector
    */
    this->myvectorStdDevs.voidSetEqualLhsRhs(stdDevs);
}
// set the number of points / observations
template <class T>
void kMeansCalc<T>::voidSetPointCount(const int& count){
    /*
    Inputs:
    int
    Outputs:
    void
    Utility:
    sets the point count
    */
    this->intPointCount = count;
}
// set the dimension size of a point
template <class T>
void kMeansCalc<T>::voidSetDimSize(const int &dimSize){
    /*
    Inputs;
    int
    Outputs:
    void
    Utility:
    sets the dimension size
    */
    this->intDimSize=  dimSize;
}



/**************
 * Operator functions
 * ************/

// stream extraction
template <class T>
std::istream &operator >>(std::istream &fileInput, kMeansCalc<T>&kMeansCalcK){
    /*
    Inputs:
    istream, kMeansCalc
    Outputs:
    istream
    Utility:
    Creates a kMeansCalc object based on file input
    */
    // create a point reader object
    PointReader<T> reader {kMeansCalcK.intGetDimSize()};
    // read the points
    fileInput >> reader;
    // update the kMeansCalc object
    kMeansCalcK.voidSetAvgsVector(reader.myvectorGetAvgs());
    kMeansCalcK.voidSetMaxesVector(reader.myvectorGetMaxes());
    kMeansCalcK.voidSetMinsVector(reader.myvectorGetMins());
    kMeansCalcK.voidSetStdDevVector(reader.myvectorGetStdDevs());
    kMeansCalcK.voidSetPointsVector(reader.myvectorGetPoints());
    kMeansCalcK.voidSetDimSize(reader.intGetPointDimensions());
    kMeansCalcK.voidSetPointCount(reader.intGetPointCount());

    return fileInput;
}
// equality
template <class T>
bool kMeansCalc<T>::operator == (const kMeansCalc<T> &aKMeansCalc) const{
    /*
    Inputs: 
    kMeansCalc<T>, kMeanCalc object to be tested against the current
    Outputs:
    bool, true if the kMean objects are equal, false if they are not
    Utility: 
    equality operator for testing if two kmeans calc objects are equal
    Tests point count, dimension amounts, the points, averages, standard devations, minimums, maximums, and cluster counts
    */

    /*
    First check if they have the same num of observations
    Then check if the observations have same dim size
    Finally check the observations

    Note that internal classes already have == operator defined; we reuse those
    (ie in the myVector class)
    */
    if(this->intPointCount != aKMeansCalc.intGetPointCount()){
        return false;
    }
    if(this->intDimSize != aKMeansCalc.intGetDimSize()){
        return false;
    }
    if(this->myvectorPoints != aKMeansCalc.myvectorGetPoints()){
        return false;
    }

    /*
    If made this far, both objs have same point count, same dim size, and same points
    Now go thru each private member
    */
    if(this->myvectorAvgs != aKMeansCalc.myvectorGetAvgs()){
        return false;
    }
    if(this->myvectorStdDevs != aKMeansCalc.myvectorGetStdDevs()){
        return false;
    }
    if(this->myvectorMins != aKMeansCalc.myvectorGetMins()){
        return false;
    }
    if(this->myvectorMaxes != aKMeansCalc.myvectorGetMaxes()){
        return false;
    }
    if(this->intClusterCount != aKMeansCalc.intGetClusterCount()){
        return false;
    }

    return true;
}

// inequality 
template <class T>
bool kMeansCalc<T>::operator != (const kMeansCalc<T> &aKMeansCalc) const{
    /*
    Inputs: 
    kMeansCalc<T>, kMeansCalc object to be tested against the current object
    Outputs:
    bool, true if the objects are not equals, false if they are
    Utility: 
    Inequality operator for testing if two kMeansCalc objects are not equal
    */
    return !(*this == aKMeansCalc);
}

// assignment operator
template <class T>
const kMeansCalc<T>& kMeansCalc<T>::operator = (const kMeansCalc<T>&rhs){
    /*
    inputs:
    kMeansCalc<T>, kMeansCalc object for the current object to be set equal to
    outputs: 
    kMeansCalc<T>, reference to the input kmeanscalc object for cascadability
    Utility: 
    Sets the current Kmeans calc object to be equal to the passed in kmeans calc
    Sets the cluster entropies, cluster centroids, points, cluster count, point count, dimension amount, averages, minimums, maxes, and standard deviations
    */
    // give same cluster entropies
    this->myvectorClusterEntropies.voidSetEqualLhsRhs(rhs.myvectorGetClusterEntropies());
    // give same centroids
    this->myvectorCentroidPoints.voidSetEqualLhsRhs(rhs.myvectorGetCentroids());
    // give same points
    this->myvectorPoints.voidSetEqualLhsRhs(rhs.myvectorGetPoints());
    // give same cluster count
    this->intClusterCount = rhs.intGetClusterCount();
    // give same point count
    this->intPointCount = rhs.intGetPointCount();
    // give same dim size
    this->intDimSize = rhs.intGetDimSize();
    // give same point distribution stuff
    this->myvectorAvgs.voidSetEqualLhsRhs(rhs.myvectorGetAvgs());
    this->myvectorMins.voidSetEqualLhsRhs(rhs.myvectorGetMins());
    this->myvectorMaxes.voidSetEqualLhsRhs(rhs.myvectorGetMaxes());
    this->myvectorStdDevs.voidSetEqualLhsRhs(rhs.myvectorGetStdDevs());

    return *this;
}

// concat two sets of points, return kMeans object
template <class T>
const kMeansCalc<T> kMeansCalc<T>::operator +(const kMeansCalc<T>&rhs)const{
    /*
    Inputs: 
    kMeansCalc<T>, kMeans calc to have its points appended to the current object
    Outputs: 
    kMeansCalc<T>< kMeansCalc object to that has the objects current points, with the passed in objects points appended to them
    Utility: 
    Addition operator which appends the right hand side's points to the lefthand side's points
    */
    // check if dimensions match, else exit
    if(rhs.intGetDimSize() != this->intDimSize){
        std::cout << "Error: kMeansCalc operator + \n";
        std::cout << "Dimension mismatch between lhs " << this->intDimSize << " and rhs " << rhs.intGetDimSize() << "\n";
        exit(1);
    }
    myVector<Point<T>> temp {this->intPointCount + rhs.intGetPointCount()};
    // copy left
    for(int i=0;i<this->intPointCount;++i){
        temp[i] = this->myvectorPoints[i];
    }
    // copy right
    int intAdjIndex {0};
    for(int i=0;i<rhs.intGetPointCount();++i){
        intAdjIndex = i + this->intPointCount;
        temp[intAdjIndex] = rhs.pointGetPoint(i);
    }
    // get stats on temp
    // get all the stats
    int intPointCount = temp.intLength();
    myVector<double> stddevs {this->intDimSize,0};
    myVector<double> avgs {rhs.myvectorGetAvgs()};
    myVector<double> mins {rhs.myvectorGetMins()};
    myVector<double> maxes {rhs.myvectorGetMaxes()};

    // to get min, max, avgs, only need to compare the two vectors already
    for(int i=0;i<this->intDimSize;++i){
        if(this->myvectorMins.tGetByReference(i) <= mins.tGetByReference(i)){
            mins[i] = this->myvectorMins[i];
        }
        if(this->myvectorMaxes.tGetByReference(i) >= maxes.tGetByReference(i)){
            maxes[i] = this->myvectorMaxes[i];
        }
        // averages are just (avg 1 + avg2) /2
        avgs[i] = (avgs.tGetByReference(i) + this->myvectorAvgs.tGetByReference(i)) /2;
    }
    double doubleDifference {0};
    // stds require more work
    for(int i=0;i<intPointCount;++i){
        for(int j=0;j<this->intDimSize;++j){
            doubleDifference = (temp.tGetByReference(i).tGetValAtDimNByReference(j) - avgs.tGetByReference(j));
            doubleDifference = (doubleDifference*doubleDifference);
            stddevs[j] += doubleDifference;
        }
        // now divide by total num points and sqrt
    }
    for(int j=0;j<this->intDimSize;++j){
        stddevs[j] = std::sqrt((stddevs.tGetByReference(j)/(intPointCount)));
    }
    // now assign points and vectors to new kMeansCalc
    kMeansCalc<T> newKMeansCalc {intPointCount,this->intDimSize};
    newKMeansCalc.voidSetMaxesVector(maxes);
    newKMeansCalc.voidSetMinsVector(mins);
    newKMeansCalc.voidSetStdDevVector(stddevs);
    newKMeansCalc.voidSetAvgsVector(avgs);
    newKMeansCalc.voidSetPointsVector(temp);
    // now set temp to have all of the stats from the point vector
    return newKMeansCalc;
}

// get point membership at index
template <class T>
int kMeansCalc<T>::operator[] (const int &index) const{
    /*
    Inputs: 
    int, point's index
    Outputs: 
    int, point's cluster that it belongs to
    Utility:
    Operator use to find the cluster id that a point belongs to, the point being the point at the index value
    */
    // get point at index index 's membership
    if(!boolCheckIndexBounds(index)) {
        // index out of bounds, flash error and leave
        std::cout << "kMeansCalc operator [] (get): index " << index << " out of bounds.\n";
        std::cout << "Bounds: 0 - " << this->myVectorPoints.intLength() << "\n";
        exit(1);
    }
    // else we good
    return this->myvectorPoints[index].intGetClusterId();
}

// set point membership at index
template <class T>
int& kMeansCalc<T>::operator[] (const int &index){
    /*
    Inputs: 
    int, index of the point to be found
    Outputs: 
    The reference to the cluster ID of the point being found
    Utility: 
    Operator user to change the cluster ID of the point found at the index
    */
    // set point at index index membership
    if(!boolCheckIndexBounds(index)) {
        // index out of bounds, flash error and leave
        std::cout << "kMeansCalc operator [] (set): index " << index << " out of bounds.\n";
        std::cout << "Bounds: 0 - " << this->myvectorPoints.intLength() << "\n";
        exit(1);
    }
    // else we good
    return this->myvectorPoints[index].intGetClusterIdByReference();
}
// stream insertion
template <class T>
std::ostream & operator << (std::ostream &os, const kMeansCalc<T> &aKMeansCalc){
    /*
    Input: 
    ostream, kMeansCalc, ostream to have data inserted into, kMeansCalc to have data pulled from
    Output: 
    ostream, ostream that has been changed and passed along for cascading
    Utility: 
    Stream insertion operator, takes all of the points and the cluster they belong to and puts it into the stream
    */
    // loop thru points, print the point's dimensions and then its membership
    int pointCount = aKMeansCalc.intGetPointCount();
    int dimCount = aKMeansCalc.intGetDimSize();
    int clusterCount = aKMeansCalc.intGetClusterCount();
    os << "Points: \n";
    for(int i=0;i<pointCount;++i){
        for(int j=0;j<dimCount;++j){
            os  << aKMeansCalc.pointGetPoint(i)[j] << ", ";
        }
        // now print the membership
        os << aKMeansCalc.pointGetPoint(i).intGetClusterIdByReference() << "\n";
    }
    os << "Centroids: \n";
    for(int i=0;i<clusterCount;++i){
        os << "#" << i << ": ";
        for(int j=0;j<dimCount;++j){
            os << aKMeansCalc.pointGetCentroidPoint(i)[j] << ", ";
        }
        os << aKMeansCalc.pointGetCentroidPoint(i).intGetClusterIdByReference();
        os << "\n";
    }
    return os;
}

/************
 * Point returning functions
 * **********/
// get point at index
template <class T>
Point<T> kMeansCalc<T>::pointGetPoint(const int &index)const{
    /*
    Inputs: 
    int, index of point to be found
    Outputs: 
    Point<T>, point at the passed in index
    Utility: 
    Returns a point found at a passed in index
    */
    return this->myvectorPoints[index];
}
// get centroid point at index
template <class T>
Centroid<T> kMeansCalc<T>::pointGetCentroidPoint(const int &index)const{
    /*
    Inputs:
    int
    Outputs:
    Point
    Utility:
    gets the centroid point at index index
    */
    return this->myvectorCentroidPoints[index];
}

/*************
 * bool returning functions
 * **********/
template <class T>
bool kMeansCalc<T>::boolCheckIndexBounds(const int &index) const{
    /*
    Inputs: 
    int, index being checked
    Outputs: 
    bool, true if the index is within the bounds, false if not
    Utility: 
    Checks if the passed in index falls within the bounds of the points in the kmeans calculator
    */
   if(index < 0 || index >= this->myvectorPoints.intLength()){
       return false;
   }
   return true;
}


#endif