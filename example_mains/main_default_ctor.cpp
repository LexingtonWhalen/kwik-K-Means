#include "./lib/kMeansCalc.cpp"

/*
This is the default ctor for the kMeansCalc object.
Here is a main.cpp file to show how it works.
*/

int main(int argc, char **argv){
    /*
    IMPORTANT NOTE:

    For a default constructor, there are no points.
    So as to let programmers know that there are not any points (and thus all future analysis would be useless)
    we have chosen to print the function name that would use points and then exit.

    This is to prevent any possible errors on the user end.
    */

    kMeansCalc<double> k {};
    std::cout << "Avg fitness: " << k.doubleFindOptimalClusters(1,10,1) << "\n";

    k.voidWritePointsToFile("out.txt");
    k.voidPrintSummary();
    k.voidPrintClusterSummary();


    return 0;
}
