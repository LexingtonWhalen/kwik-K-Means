#include "./lib/kMeansCalc.cpp"


/*
This is the example of the copy ctor for the kMeans object.
Note that all objects have a copy ctor.
Here is a main.cpp file to show how it works.
*/

int main(int argc, char **argv){

    kMeansCalc<double> k {"./data/20p_2c_2d.txt",2};
    std::cout << "Avg fitness k1: " << k.doubleFindOptimalClusters(2,10,1) << "\n";

    k.voidWritePointsToFile("out.txt");
    k.voidPrintSummary();
    k.voidPrintClusterSummary();

    kMeansCalc<double> k2{k};
    std::cout << "k2 == k1? Expect true. May be false if run find optimal clusters due to small differences in centroids.\n";
    std::cout << (k2 == k) << "\n";
    std::cout << "k2 != k1? Expect false. May be true if run find optimal clusters due to small differences in centroids.\n";
    std::cout << (k2 != k) << "\n";
    std::cout << "Avg fitness k2: " << k.doubleFindOptimalClusters(2,10,1) << "\n";
    kMeansCalc<double> k3 {"./data/20p_2c_2d.txt",2};
    std::cout << "Avg fitness k3: " << k.doubleFindOptimalClusters(2,10,1) << "\n";
    std::cout << "k3 same as k1? Expect false\n";
    std::cout << (k3 == k) << "\n";
    std::cout << "Set k3 = k2. \n";
    k3 = k2;
    std::cout << "k2 == k3? Expect true.\n";
    std::cout << (k2 == k3) << "\n";

    return 0;
}
