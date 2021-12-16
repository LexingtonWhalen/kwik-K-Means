#include "./lib/kMeansCalc.cpp"

/*
This is an example of using the bracket operator on the kMeans object.
Note that both Point and myVector also have this operator.
Here is a main.cpp file to show how it works.
*/

int main(int argc, char **argv){

    kMeansCalc<double> k {"./data/20p_2c_2d.txt",2};
    // print membership
    std::cout << k[0] << "\n";
    k[0] = 1;
    // set membership
    std::cout << k[0] << "\n";
    // std::cout << "Avg fitness: " << k.doubleFindOptimalClusters(2,10,1) << "\n";

    std::cout << "trying to get point that is not in bounds negative\n";
    std::cout << "Note that the program ends so that the programmer knows that something is amiss\n";
    std::cout << k[-1] << "\n";

    std::cout << "trying to get point that is not in bounds positive\n";
    std::cout << k[1000] << "\n";
    // k.voidWritePointsToFile("out.txt");
    // k.voidPrintSummary();
    // k.voidPrintClusterSummary();


    return 0;
}
