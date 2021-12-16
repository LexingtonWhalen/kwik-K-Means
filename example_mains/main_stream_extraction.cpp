#include "./lib/PointReader.cpp"
#include "./lib/kMeansCalc.cpp"

/*
Here is an example of using the stream extraction operator on the kMeansCalc object.
NOTE: There is also an extraction operator for the PointReader class that works very similarly.
Here is a main.cpp file to show how it works.
*/

int main(int argc, char **argv){

    std::string strFileName = "./data/20p_2c_2d.txt";
    std::ifstream fileInFile;
    fileInFile.open(strFileName);

    if(!fileInFile){
        std::cout << "Error: file cannot be opened.\n";
        exit(1);
    }
    int intDimensionSize = 2;
    int intNumPoints = 4;
    double doubleFiller = 0;
    // creating a basic kMeans object and populating it with dummy points
    kMeansCalc<double> k{intNumPoints,intDimensionSize,doubleFiller};
    // reading the file into kMeans object, updating the object
    fileInFile >> k;
    k.doubleFindOptimalClusters(2,100,0.01);
    k.voidPrintSummary();
    k.voidWritePointsToFile("out.txt");


    return 0;
}
