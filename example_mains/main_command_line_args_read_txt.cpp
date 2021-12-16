#include "./lib/kMeansCalc.cpp"

/*
Here is an example of the primary way to use the kMeansCalc object;
with a text file.
Here is a main.cpp file to show how it works.
*/

int main(int argc, char **argv){
	if(argc != 3){
		std::cout << "Usage for " << argv[0] << ":\n";
		std::cout << argv[0] << " <InputFileName> \n";
		std::cout << "Usage for " << argv[1] << ":\n";
		std::cout << argv[1] << " <OutputFileName>\n";
		exit(0);
	}
	std::string strInFileName = argv[1];
	std::string strOutFileName = argv[2];

	std::cout << "Enter the number of dimensions: ";
	int intDimCount {0};
	std::cin >> intDimCount;

	std::cout << "Enter the number of centroids: ";
	int intClusterCount {0};
	std::cin >> intClusterCount;

	std::cout << "Enter the threshold value: ";
	double doubleThresh {0.0};
	std::cin >> doubleThresh;

	std::cout << "Enter the iteration count: ";
	int intIterationCount {0};
	std::cin >> intIterationCount;
	
	std::cout << "Enter the number of points: ";
	int intPointCount {0};
	std::cin >> intPointCount;

	std::cout << "********************\n";
	std::cout << "Point count: " <<intPointCount << "\n";
	std::cout << "Centroid count: " << intClusterCount << "\n";
	std::cout << "Dimension size: " << intDimCount << "\n";
	std::cout << "Threshold value: " << doubleThresh << "\n";
	std::cout << "Outfile name: " << strOutFileName<<"\n";
	std::cout << "Infile name: " << strInFileName << "\n";
	std::cout << "********************\n";

	// create a basic kMeans object,populate with dummy points
	double doubleFiller = 0.0;
	kMeansCalc<double> k {intPointCount,intDimCount,doubleFiller};

	std::ifstream fileInFile;
	fileInFile.open(strInFileName);

	fileInFile >> k;
    std::cout << "Avg fitness: " << k.doubleFindOptimalClusters(intClusterCount,intIterationCount,doubleThresh) << "\n";

    k.voidWritePointsToFile(strOutFileName);
    k.voidPrintSummary();
    k.voidPrintClusterSummary();

//	std::ofstream fileOutFile;
//	fileOutFile.open(strOutFileName);
//	fileOutFile << k;





    return 0;
}
