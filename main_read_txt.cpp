#include "./lib/kMeansCalc.cpp"

/*
Here is an example of the primary way to use the kMeansCalc object;
with a text file.
Here is a main.cpp file to show how it works.
*/

int main(int argc, char **argv){
    int dimSize = 2;
    int clusterCount = 20;
    int iterationCount = 1;
    // optional parameter at end
    // int numStart = 1;
    double threshold = 1;
    kMeansCalc<double> k {"./data/16mill_2c_2d.txt",dimSize};
    std::cout << "Avg fitness: " << k.doubleFindOptimalClusters(clusterCount,iterationCount,threshold,1) << "\n";

    k.voidWritePointsToFile("out.txt");
    k.voidPrintSummary();
    k.voidPrintClusterSummary();


    return 0;
}
