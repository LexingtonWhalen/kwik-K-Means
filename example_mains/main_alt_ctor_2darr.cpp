#include "./lib/PointReader.cpp"
#include "./lib/kMeansCalc.cpp"

/*
This is the 2d array constructor for the kMeans object.
Here is a main.cpp file to show how it works.
*/

int main(int argc, char **argv){
    /*
    NOTE: 

    It is expected that the user manages their own double array memory.
    The program only works with it. No memory leaks will occur from this program, unless
    the user creates one!
    */

    double **arr;
    int cols = 2;
    int rows = 20;
    arr = new double *[rows];
    for(int i=0;i<rows;i++){
        arr[i] = new double[cols];
        for(int j=0;j<cols;++j){
            arr[i][j] = (i+j);
        }
    }
    kMeansCalc<double> k(arr,rows,cols);
    for(int i=0;i<rows;i++){
        delete [] arr[i];
    }
    delete [] arr;
    /*
    Print avg fitness
    */
    std::cout << "Avg fitness: " << k.doubleFindOptimalClusters(2,100,0.001,10) << "\n";
    // write points to file
    k.voidWritePointsToFile("out.txt");
    // print summaries
    k.voidPrintSummary();
    k.voidPrintClusterSummary();

    return 0;
}
