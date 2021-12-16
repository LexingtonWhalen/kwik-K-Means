#include "./lib/PointReader.cpp"
#include "./lib/kMeansCalc.cpp"

/*
This is the assignment operator for the kMeansCalc.
Note that all objects have an assignment operator.
Here is a main.cpp file to show how it works.
*/

int main(int argc, char **argv){
    int dimensionSize = 2;
    kMeansCalc<double> k {"./data/20p_2c_2d.txt",dimensionSize};
    std::cout << "Avg fitness: " << k.doubleFindOptimalClusters(2,10,1) << "\n";
    kMeansCalc<double> k2;
    k2 = k;
    std::cout << "k2 == k?: " << (k2 == k) << "\n";
    std::cout << "Avg fitness: "<<  k2.doubleFindOptimalClusters(2,10,1) << "\n";

    // cascade
    kMeansCalc<double> k3 {"./data/4p_2c_v1.txt",dimensionSize};
    k3 = k2 = k;
    std::cout << "Avg fitness: " << k3.doubleFindOptimalClusters(2,10,1) << "\n";
    std::cout << "k3 == k?: " << (k3 == k) << "\n";


    return 0;
}
