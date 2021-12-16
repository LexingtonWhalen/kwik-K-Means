#include "./lib/kMeansCalc.cpp"

/*
This is the addition operator for the kMeansCalc object.
Note that some other classes also have this operator, like Point.
Here is a main.cpp file to show how it works.
*/

int main(int argc, char **argv){

    kMeansCalc<double> k {"./data/40p_2c_2d.txt",2};
    kMeansCalc<double> k2 {"./data/20p_2c_2d.txt",2};

    kMeansCalc<double> k3 = k + k2;


    std::cout << "printing stats for k\n";
    std::cout << "Avg fitness: " << k.doubleFindOptimalClusters(2,100,0.001) << "\n";
    k.voidPrintSummary();
    k.voidPrintClusterSummary();


    std::cout << "printing stats for k2\n";
    std::cout << "Avg fitness: " << k2.doubleFindOptimalClusters(2,100,0.001) << "\n";
    k2.voidPrintSummary();
    k2.voidPrintClusterSummary();

    std::cout << "printing stats for k3\n";
    std::cout << "Avg fitness: " << k3.doubleFindOptimalClusters(2,100,0.001) << "\n";
    k3.voidPrintSummary();
    k3.voidPrintClusterSummary();

    // cascade
    kMeansCalc<double> k4 = k3 + k2 + k;
    std::cout << "printing stats for k4\n";
    std::cout << "Avg fitness: " << k4.doubleFindOptimalClusters(2,100,0.001) << "\n";
    k4.voidPrintSummary();
    k4.voidPrintClusterSummary();

    std::cout << "Note that addition does not modify k, k2, k3.\n";
    std::cout << "Printing all k's to show they are not modified\n";
    k.voidPrintSummary();
    k2.voidPrintSummary();
    k3.voidPrintSummary();





    return 0;
}
