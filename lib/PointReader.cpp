/*
kMeansCalculator.
This program takes in data and clusters it.
See all the possible arguments to pass into the kMeansObject.
For instance, can pass in the number of clusters to create, the number 
of iterations, the threshold to stop at, and the number of random seeds.

The program will output summaries related to points / centroids. It can
also output a text file.
*/
#ifndef POINT_READER_CPP
#define POINT_READER_CPP

#include "./PointReader.h"

/*

PointReader class.

This is the implementation of the point reader class.
The point reader class is designed to read points for the kMeansCalc and return vectors
of the points and their stats.

*/


/*
**************************
CTOR, DTORS
**************************
*/
// default ctor
template <class T>
PointReader<T>::PointReader(){
    /*
    Inputs:
    void
    Outputs:
    void
    Utility:
    Create reader, set point dim to 0
    */
    this->intPointDimensions = 0;
}
// param ctor that accepts dim size
template <class T>
PointReader<T>::PointReader(const int &dimSize){
    this->intPointDimensions = dimSize;
}

// copy ctor
template <class T>
PointReader<T>::PointReader(const PointReader<T> &reader){
    /*
    Inputs:
    PointReader, PointReader being copied
    Outputs:
    void
    Utility:
    Create point reader in image of reader
    */
    this->myvectorPoints.voidSetEqualLhsRhs(reader.myvectorGetPoints());
    this->intPointDimensions = reader.intGetPointDimensions();
    this->myvectorStdDevs.voidSetEqualLhsRhs(reader.myvectorGetStdDevs());
    this->myvectorAvgs.voidSetEqualLhsRhs(reader.myvectorGetAvgs());
    this->myvectorMins.voidSetEqualLhsRhs(reader.myvectorGetMins());
    this->myvectorMaxes.voidSetEqualLhsRhs(reader.myvectorGetMaxes());
}

// param ctor that accepts 2d arr
template <class T>
PointReader<T>::PointReader(T **data, const int&rows, const int &cols){
    /*
    Inputs:
    T**, int, int, double pointer to data to be taken in, number of rows, number of columns
    Outputs:
    void
    Utility:
    Creates the points based on a double array.

    NOTE: 

    This assumes that the user properly manages their own memory! We do not
    do any news or deletes here, just word with the passed in data.
    You manage your own memory!
    */
   myVector<Point<T>> points {rows};
   this->intPointDimensions = cols;


    // vectors to hold each needed property
    myVector<double> stddevs {this->intPointDimensions,0};
    myVector<double> avgs {this->intPointDimensions,0};
    myVector<double> mins {this->intPointDimensions,__DBL_MAX__};
    myVector<double> maxes {this->intPointDimensions,__DBL_MIN__};

   for(int i=0;i<rows;++i){
       // loop through point counts then point dims
       Point<T> newPoint{cols};
       for(int j=0;j<cols;++j){
           double val = data[i][j];
           // assign point its dim
           newPoint[j] = val;

           if(val >= maxes.tGetByReference(j)){
               maxes[j] = val;
           }
           if(val <= mins.tGetByReference(j)){
               mins[j] = val;
           }
           // add to avgs, later divide by num points
           avgs[j] += val;
       }
       // now put point in vector
       points[i] = newPoint;
   }
   // assign object's point vector to points
   this->myvectorPoints.voidSetEqualLhsRhs(points);
   // divide sums by count of points to get avgs
   int pointCount = points.intLength();
   for(int i=0;i<this->intPointDimensions;++i){
       avgs[i] /= pointCount;
   }
   // calc stddev
   // population stddev
   double diff = 0;
   for(int i=0;i<pointCount;++i){
       for(int j=0;j<this->intPointDimensions;++j){
           diff = this->myvectorPoints.tGetByReference(i).tGetValAtDimNByReference(j) - avgs[j];
           diff = (diff * diff);
           stddevs[j] += diff;
       }
   }
   // now divide by num points and sqrt
   for(int i=0;i<this->intPointDimensions;++i){
       stddevs[i] = std::sqrt((stddevs.tGetByReference(i)/(pointCount)));
   }
    // now assign vectors
    this->myvectorStdDevs.voidSetEqualLhsRhs(stddevs);
    this->myvectorAvgs.voidSetEqualLhsRhs(avgs);
    this->myvectorMins.voidSetEqualLhsRhs(mins);
    this->myvectorMaxes.voidSetEqualLhsRhs(maxes);
}

// param ctor
template <class T>
PointReader<T>::PointReader(const std::string &fileName,const int &intPointDimensions){
    /*
    Inputs:
    string, int, File name, number of dimensions
    Outputs:
    void
    Utility:
    Reads points based on a passed in file name and sets the dimensions to the passed in dimension amount
    */
    this->intPointDimensions = intPointDimensions;
    voidReadTxt(fileName);
}

// dtor
template <class T>
PointReader<T>::~PointReader(){
    /*
    Inputs:
    void
    Outputs:
    void    
    Utility:
    PointReader destructor
    */

}

/*
**************************
GETTERS, SETTERS
**************************
*/
// get vector of stddevs
template <class T>
myVector<double> PointReader<T>::myvectorGetStdDevs() const{
    /*
    Inputs: 
    void
    Outputs: 
    myVector, vector containing the standard deviations for each dimension of the points
    Utility: 
    Getter for get the standard deviation vector for all the points in the object
    */
    return this->myvectorStdDevs;
}
// get the vector of avgs
template <class T>
myVector<double> PointReader<T>::myvectorGetAvgs() const{
    /*
    Inputs:
    void
    Outputs: 
    myVector, vector containing the averages for each dimension of the points
    Utility: 
    Getter for get the averages vector for all the points in the object
    */
    return this->myvectorAvgs;
}
// get the vector of mins
template <class T>
myVector<double> PointReader<T>::myvectorGetMins() const{
    /*
    Inputs:
    void
    Outputs: 
    myVector, vector containing the minimums for each dimension of the points
    Utility: 
    Getter for get the minimums vector for all the points in the object
    */
    return this->myvectorMins;
}
// get the vector of maxes
template <class T>
myVector<double> PointReader<T>::myvectorGetMaxes() const{
    /*
    Inputs:
    void
    Outputs: 
    myVector, vector containing the maxes for each dimension of the points
    Utility: 
    Getter for get the maxes vector for all the points in the object
    */
    return this->myvectorMaxes;
}
// get the vector of points
template <class T>
myVector<Point<T>> PointReader<T>::myvectorGetPoints() const{
    /*
    Inputs:
    void
    Outputs:
    myVector, vector containing all of the points in the object
    Utility:
    returns a vector containing all of the points in the object
    */
    return this->myvectorPoints;
}
// get point count
template <class T>
int PointReader<T>::intGetPointCount() const{
    return this->myvectorPoints.intLength();
}
// get point dimension size 
template <class T>
int PointReader<T>::intGetPointDimensions() const{
    /*
    Inputs:
    void
    Outputs:
    int, number of dimensions 
    Utility:
    Returns the number of dimensions each point has in the object
    */
    return this->intPointDimensions;
}
// get the total lines of file
template <class T>
int PointReader<T>::intGetTotalLines(const std::string &fileName){
    /*
    Inputs:
    string, file name
    Outputs:
    int, number of lines in the file
    Utility:
    Gets the total number of lines that are within the passed in file
    */
    // returns the total number of lines in file
    // used to initialize the vector size of the points
    std::ifstream ifstreamFile;

    ifstreamFile.open(fileName);
    if(!ifstreamFile){
        std::cout << "Error: file cannot be opened.\n";

        exit(1);
    }

    std::string strLine;
    int counter {0};
    if(ifstreamFile.is_open()){
        
        while(std::getline(ifstreamFile,strLine)){
            counter++;
        }
    }

    return counter;
}

/*
**************************
void returning functions
**************************
*/
// read txt file
template <class T>
void PointReader<T>::voidReadTxt(const std::string &fileName){
    /*
    Inputs:
    string, file name
    Outputs:
    void
    Utility:
    Reads the data from the passed in file and populates the object with points being read from the file
    */
    // reads the data, populates vector
    this->myvectorPoints.voidSetSize(intGetTotalLines(fileName));

    // for the file
    std::ifstream ifstreamFile;

    // open the file
    ifstreamFile.open(fileName);
    if(!ifstreamFile){
        // if invalid file name, exit
        std::cout << "Error: file cannot be opened.\n";
        exit(1);
    }
    // vectors to hold each needed property
    myVector<double> stddevs {this->intPointDimensions,0};
    myVector<double> avgs {this->intPointDimensions,0};
    myVector<double> mins {this->intPointDimensions,__DBL_MAX__};
    myVector<double> maxes {this->intPointDimensions,__DBL_MIN__};

    // for reading the lines
    std::string strLine;
    // for keeping count of the dimension
    int intDimCounter {0};
    // for keeping track of what line the file is on (this tells what point number it is on)
    int intLineCounter {0};
    myVector<T> myvectorTCoords {this->intPointDimensions};
    Point<T> pointNew {myvectorTCoords};
    T tReadValueAtDimN;
    // open file
    if(ifstreamFile.is_open()){
        // get lines 
        while(std::getline(ifstreamFile,strLine)){
            // set dim counter to zero
            intDimCounter = 0;

            std::stringstream ss(strLine);

            while(ss >> tReadValueAtDimN and intDimCounter != this->intPointDimensions){
                myvectorTCoords[intDimCounter] = tReadValueAtDimN;
                if(tReadValueAtDimN >= maxes.tGetByReference(intDimCounter)){
                    maxes[intDimCounter] = tReadValueAtDimN;
                }
                if(tReadValueAtDimN <= mins.tGetByReference(intDimCounter)){
                    mins[intDimCounter] = tReadValueAtDimN;
                }
                // add to avgs, later divide by num points
                avgs[intDimCounter] += tReadValueAtDimN;
                pointNew.voidSetCoordVector(myvectorTCoords);
                intDimCounter ++ ;
            }
            this->myvectorPoints[intLineCounter] = pointNew;
            intLineCounter ++;
        }
    }

    ifstreamFile.close();
    // divide by total num points to get avgs
    int pointCount = this->myvectorPoints.intLength();
    for(int i=0;i<this->intPointDimensions;++i){
        avgs[i] /= pointCount;
    }
    // s^2 = sum(xi - mean(x))^2 * (1/n): populate stddev
    // store the difference
    double doubleDiff {0};
    for(int i=0;i<pointCount;++i){
        for(int j=0;j<this->intPointDimensions;++j){
            doubleDiff = (this->myvectorPoints.tGetByReference(i).tGetValAtDimNByReference(j) - avgs.tGetByReference(j));
            doubleDiff  = (doubleDiff * doubleDiff);
            stddevs[j] += doubleDiff;
        }
    }
    // now divide by num points and sqrt
    for(int i=0;i<this->intPointDimensions;++i){
        stddevs[i] = std::sqrt((stddevs.tGetByReference(i)/(pointCount)));
    }
    // now assign vectors
    this->myvectorStdDevs.voidSetEqualLhsRhs(stddevs);
    this->myvectorAvgs.voidSetEqualLhsRhs(avgs);
    this->myvectorMins.voidSetEqualLhsRhs(mins);
    this->myvectorMaxes.voidSetEqualLhsRhs(maxes);

}
// read csv file
template <class T>
void PointReader<T>::voidReadCSV(const std::string &strFileName){
    /*
    Inputs:
    string, file name
    Outputs: 
    void
    Utility: 
    reads a csv file to populate the point reader with points
    */
    std::ifstream fIn;    
    std::string line;
    this->myvectorPoints.voidSetSize(intGetTotalLines(strFileName));

    fIn.open(strFileName);
    if(!fIn){
        std::cout << "Error: file cannot be opened.\n";
        exit(1);
    }

    std::string strLine;
    int counter;
    int intLineCounter = 0;

    myVector<double> stddevs {this->intPointDimensions,0};
    myVector<double> avgs {this->intPointDimensions,0};
    myVector<double> mins {this->intPointDimensions,__DBL_MAX__};
    myVector<double> maxes {this->intPointDimensions,__DBL_MIN__};

    while(fIn.good()){
        while(getline(fIn,strLine)){
            myVector<T> pointTCoords {this->intPointDimensions};
            counter = 0;
            std::stringstream ss(strLine);
            std::string token;
            while(getline(ss,token,',')){
                double val = std::atof(token.c_str());
                // put the val in min, max, std, etc
                if(val >= maxes.tGetByReference(counter)){
                    maxes[counter] = val;
                }
                if(val <= mins.tGetByReference(counter)){
                    mins[counter] = val;
                }
                // add to avgs, later we divide by num points
                avgs[counter] += val;
                pointTCoords[counter] = val;
                counter ++;
            }
            Point<T> newPoint {pointTCoords};
            this->myvectorPoints[intLineCounter] = newPoint;
            intLineCounter ++ ;
        }
    }

    fIn.close();
    // divide total points by num points to get avgs
    for(int i=0;i<this->intPointDimensions;++i){
        avgs[i] /= this->myvectorPoints.intLength();
    }
    // s^2 = sum(xi - mean(x))^2 * (1/(n)) pop stddev
    for(int i=0;i<this->myvectorPoints.intLength();++i){
        for(int j=0;j<this->intPointDimensions;++j){
            double diff = (this->myvectorPoints.tGetByReference(i).tGetValAtDimNByReference(j) - avgs[j]);
            diff = (diff * diff);

            stddevs[j] += diff;
        }
    }
    int pointCount = this->myvectorPoints.intLength();
    // now divide by num points (pop std) and square root
    for(int i=0;i<this->intPointDimensions;++i){
        stddevs[i] = std::sqrt((stddevs.tGetByReference(i)/(pointCount)));
    }

    // now assign vectors
    this->myvectorStdDevs = stddevs;
    this->myvectorAvgs = avgs;
    this->myvectorMins = mins;
    this->myvectorMaxes = maxes;
}
// set the point dim size
template <class T>
void PointReader<T>::voidSetIntPointDimensions(const int &dimSize){
    /*
    Inputs:
    int, number of dimension to be set to
    outputs: 
    void
    Utility: 
    Sets the number of dimensions of the point reader
    */
    this->intPointDimensions = dimSize;
}
// set vector of points
template <class T>
void PointReader<T>::voidSetMyVectorPoints(const myVector<Point<T>>&points){
    /*
    Inputs:
    myVector, points vector to be set to 
    outputs: 
    void
    Utility: 
    Sets the number of points vector to the passed in points vector
    */
    this->myvectorPoints.voidSetEqualLhsRhs(points);
}
// set vector of avgs
template <class T>
void PointReader<T>::voidSetMyVectorAvgs(const myVector<double>&points){
    /*
    Inputs:
    myVector, points vector to have the averages set to 
    outputs: 
    void
    Utility: 
    Sets the averages of the current point reader to the averages of the passed in vector
    */
    this->myvectorAvgs.voidSetEqualLhsRhs(points);
}
// set min vector
template <class T>
void PointReader<T>::voidSetMyVectorMins(const myVector<double>&points){
    /*
    Inputs:
    myVector, points vector to have the minimums set to 
    outputs: 
    void
    Utility: 
    Sets the minimums of the current point reader to the minimums of the passed in vector
    */
    this->myvectorMins.voidSetEqualLhsRhs(points);
}
// set vector of maxes
template <class T>
void PointReader<T>::voidSetMyVectorMaxes(const myVector<double>&points){
    /*
    Inputs:
    myVector, points vector to have the maximums set to 
    outputs: 
    void
    Utility: 
    Sets the maxes of the current point reader to the maxes of the passed in vector
    */
    this->myvectorMaxes.voidSetEqualLhsRhs(points);
}
// set vector of stddevs
template <class T>
void PointReader<T>::voidSetMyVectorStdDevs(const myVector<double>&points){
    /*
    Inputs:
    myVector, points vector to have the standard deviations set to 
    outputs: 
    void
    Utility: 
    Sets the standard deviations of the current point reader to the standard deviations of the passed in vector
    */
    this->myvectorStdDevs.voidSetEqualLhsRhs(points);
}
// check that a point has dimensions
template <class T>
void PointReader<T>::voidCheckHasPointDimensions() const{
    /*
    Inputs: 
    void
    Outputs: 
    void
    Utility: 
    Checks to see if point dimensions have been initialized, exits if they haven't
    */
    if(this->intPointDimensions <= 0){
        std::cout << "Error: PointReader.cpp\n";
        std::cout << "Point dimensions uninitialized. Check arguments on ctor.\n";
        exit(1);
    }
}


/*
**************************
operator
**************************
*/
// stream extraction
template <class T>
std::istream &operator >>(std::istream &fileInput,PointReader<T> &aReader){
    /*
    Inputs: 
    istream, PointReader, istream to have data pulled from, point reader to have data put into 
    Outputs: 
    istream
    Utility: 
    Stream extraction operator for populating a PointReader object
    */

    // first need to check if object has point dimensions.
    // if not, exit.
    aReader.voidCheckHasPointDimensions();

    // get line count
    std::string strLine;
    int intLineCounter {0};
    while(fileInput.good()){
        while(std::getline(fileInput,strLine)){
            intLineCounter ++;
        }
    }
    // reset the position at file
    fileInput.clear();
    fileInput.seekg(0,std::ios::beg);
    // set size of the point vector
    myVector<Point<T>> points {intLineCounter};

    // counter for points
    int counter;
    // reset line counter since going thru again
    intLineCounter = 0;

    int intPointDimensions = aReader.intGetPointDimensions();

    myVector<double> stddevs {intPointDimensions,0};
    myVector<double> avgs {intPointDimensions,0};
    myVector<double> mins {intPointDimensions,__DBL_MAX__};
    myVector<double> maxes {intPointDimensions,__DBL_MIN__};
    myVector<T> myvectorTCoords {intPointDimensions};
    Point<T> pointNew {myvectorTCoords};
    T tValAtDimN {0};

    while(fileInput.good()){
        while(std::getline(fileInput,strLine)){
            counter = 0;


            std::stringstream ss(strLine);

            while(ss >> tValAtDimN and counter != intPointDimensions){
                myvectorTCoords[counter] = tValAtDimN;
                if(tValAtDimN >= maxes.tGetByReference(counter)){
                    maxes[counter] = tValAtDimN;
                }
                if(tValAtDimN <= mins.tGetByReference(counter)){
                    mins[counter] = tValAtDimN;
                }
                // add to avgs, later divide by num points
                avgs[counter] += tValAtDimN;

                counter ++ ;
            }
            pointNew.voidSetCoordVector(myvectorTCoords);
            points[intLineCounter] = pointNew;
            intLineCounter ++;
        }
    }

    // divide total points by num points to get avgs
    for(int i=0;i<intPointDimensions;++i){
        avgs[i] /= points.intLength();
    }
    // s^2 = sum(xi - mean(x))^2 * (1/(n)) pop stddev
    double diff {0};
    for(int i=0;i<points.intLength();++i){
        for(int j=0;j<intPointDimensions;++j){
            diff = (points.tGetByReference(i).tGetValAtDimNByReference(j) - avgs[j]);
            diff = (diff * diff);
            stddevs[j] += diff;
        }
    }
    int pointCount = points.intLength();
    // now divide by num points (pop std) and square root
    for(int i=0;i<intPointDimensions;++i){
        stddevs[i] = std::sqrt((stddevs.tGetByReference(i)/(pointCount)));
    }
    aReader.voidSetMyVectorAvgs(avgs);
    aReader.voidSetMyVectorMaxes(maxes);
    aReader.voidSetMyVectorMins(mins);
    aReader.voidSetMyVectorStdDevs(stddevs);
    aReader.voidSetMyVectorPoints(points);

    return fileInput;
}

// equality operator
template <class T>
bool PointReader<T>::operator == (const PointReader<T>&rhs) const{
    /*
    Inputs: 
    PointReader, point reader being tested for equality
    Outputs: 
    bool, true if point readers are equal, false if not
    Utility: 
    equality operator for testing if two point readers are equal
    */
    if(rhs.myvectorGetAvgs() != this->myvectorAvgs){
        return false;
    }
    if(rhs.myvectorGetMaxes() != this->myvectorMaxes){
        return false;
    }
    if(rhs.myvectorGetMins() != this->myvectorMins){
        return false;
    }
    if(rhs.myvectorGetAvgs() != this->myvectorAvgs){
        return false;
    }
    if(this->intPointDimensions != rhs.intGetPointDimensions()){
        return false;
    }
    if(this->myvectorPoints != rhs.myvectorGetPoints()){
        return false;
    }
    return true;
}
// inequality operator
template <class T>
bool PointReader<T>::operator != (const PointReader<T>&rhs)const{
    /*
    Inputs: 
    PointReader, point reader being tested for inequality
    Outputs: 
    bool, true if point readers are not equal, false if they are
    Utility: 
    inequality operator for testing if two point readers are not equal
    */
    return !(*this == rhs);
}
// assignment operator
template <class T>
const PointReader<T>& PointReader<T>::operator = (const PointReader<T> &rhs){
    /*
    Inputs: 
    PointReader, point reader to be set equal to
    Outputs: 
    PointReader, passed in point reader for cascadability
    Utility: 
    Assignment operator to set the current point reader to be equal to the passed in point reader
    */

    // set all attributes equal
    this->intPointDimensions = rhs.intGetPointDimensions();

    this->myvectorPoints.voidSetEqualLhsRhs(rhs.myvectorGetPoints());
    this->myvectorStdDevs.voidSetEqualLhsRhs(rhs.myvectorGetStdDevs());
    this->myvectorAvgs.voidSetEqualLhsRhs(rhs.myvectorGetAvgs());
    this->myvectorMins.voidSetEqualLhsRhs(rhs.myvectorGetMins());
    this->myvectorMaxes.voidSetEqualLhsRhs(rhs.myvectorGetMaxes());

    return *this;
}

#endif
