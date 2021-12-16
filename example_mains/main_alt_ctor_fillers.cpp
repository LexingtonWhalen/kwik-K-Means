#include "./lib/PointReader.cpp"
#include "./lib/kMeansCalc.cpp"

/*
This is the alternative constructor that accepts the size of data
and some value to fill it with.
Here is a main.cpp file to show how it works.
*/

int main(int argc, char **argv){

    int numPoints = 20;
    int dimSize = 2;
    double filler = 0.0;

    /*
    Testing with default argument of filler to 0
    */
    kMeansCalc<double> k {numPoints,dimSize,filler};
    kMeansCalc<double> k2 {numPoints,dimSize,0.0};

    // at this point, k should == k2. Later may be different due to slight differents in centroid locations
    std::cout << "k == k2?: " << (k == k2) << "\n";

    std::cout << "Avg fitness: " << k.doubleFindOptimalClusters(1,10,1) << "\n";

    k.voidWritePointsToFile("out.txt");
    k.voidPrintSummary();
    k.voidPrintClusterSummary();

    std::cout << "Avg fitness: " << k2.doubleFindOptimalClusters(1,10,1) << "\n";

    k2.voidWritePointsToFile("out.txt");
    k2.voidPrintSummary();
    k2.voidPrintClusterSummary();



    return 0;
}
