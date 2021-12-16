#include "./lib/kMeansCalc.cpp"

/*
This is an example of the stream insertion operator for the kMeansCalc object.
Note that Point and myVector also have this operator.
Here is a main.cpp file to show how it works.
*/
int main(int argc, char **argv){

    kMeansCalc<double> k {"./example_in_files/40p_2c_2d.txt",2};
    k.doubleFindOptimalClusters(2,100,0.001);
    std::cout << k << "\n";
    std::cout << "Avg fitness: " << k.doubleFindOptimalClusters(2,100,0.001) << "\n";

    k.voidWritePointsToFile("out.txt");
    // k.voidPrintSummary();
    // k.voidPrintClusterSummary();


    return 0;
}
