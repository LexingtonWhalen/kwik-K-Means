/*
kMeansCalculator.
This program takes in data and clusters it.
See all the possible arguments to pass into the kMeansObject.
For instance, can pass in the number of clusters to create, the number 
of iterations, the threshold to stop at, and the number of random seeds.

The program will output summaries related to points / centroids. It can
also output a text file.
*/
#ifndef POINT_CPP
#define POINT_CPP

#include "./Point.h"

/*
__________________________________________________________________________________
* Point class.
*
* This is the implementation of the Point class.
__________________________________________________________________________________
*/

/*
****************************
CTORS, DTORS
****************************
*/

// default ctor
template <class T>
Point<T>::Point(){
    /*
    Inputs:
    void
    Outputs:
    void
    Utility:
    Create point, set membership to -1
    */
    this->intClusterId = this->INT_UNDEF_CLUSTER;
}
// create point based on coordinates
template <class T>
Point<T>::Point(const myVector<T>&coords){
    /*
    Inputs:
    myVector, vector holding the coordinates for the point
    Outputs:
    void
    Utility:
    Create point, give coordinates
    */
    this->myvectorCoords.voidSetEqualLhsRhs(coords);
    this->intClusterId = this->INT_UNDEF_CLUSTER;
    this->intDimensions = coords.intLength();
}
// point based on dimension size
template <class T>
Point<T>::Point(const int &dimSize){
    /*
    Inputs:
    int, number of dimensions for the point
    Outputs:
    void
    Utility:
    Create point with dimension size set
    */
    myVector<T> coords {dimSize};
    this->myvectorCoords.voidSetEqualLhsRhs(coords);
    this->intDimensions = coords.intLength();
    this->intClusterId = this->INT_UNDEF_CLUSTER;
}
// point based on dimension size, fill with filler, set id
template <class T>
Point<T>::Point(const int &dimSize, const T &filler,const int &id){
    /*
    Inputs:
    int, T, int, number of dimensions, filler value to be for the point, cluster id for the point
    Outputs:
    void
    Utility:
    Create point, give dimension size and fill dimensions, set membership
    */
    myVector<T> coords {dimSize,filler};
    this->myvectorCoords.voidSetEqualLhsRhs(coords);
    this->intDimensions = coords.intLength();
    this->intClusterId = id;
}
// point based on coordinates, set id
template <class T>
Point<T>::Point(const myVector<T>&coords, const int &clusterId){
    /*
    Inputs:
    myVector, int, vector containing the coordinates for the point, cluster id for the point
    Outputs:
    void
    Utility:
    Create point, set coords and membership
    */
    this->myvectorCoords.voidSetEqualLhsRhs(coords);
    this->intClusterId = clusterId;
    this->intDimensions = coords.intLength();
}
// copy ctor
template <class T>
Point<T>::Point(const Point<T> &rhs){
    /*
    Inputs:
    Point<T>, point to be copied
    Outputs:
    void
    Utility:
    Create point in image of rhs
    NOTE:
    Always make sure that this copies every necessary attribute.
    */
    this->myvectorCoords.voidSetEqualLhsRhs(rhs.myvectorGetCoords());
    this->intClusterId = rhs.intGetClusterId();
    this->intDimensions = rhs.intGetDimensions();
}
// dtor, same used for centroids
template <class T>
Point<T>::~Point(){
    /*
    Inputs:
    void
    Outputs:
    void
    Utility:
    Destructor
    */

}

/*
****************************
T returning functions
****************************
*/
// get value at dimension
template <class T>
T Point<T>::tGetAtDimN(const int &n)const{
    /*
    Inputs:
    int, dimension number for the value to be returned from
    Outputs:
    T, data being returned from the point
    Utility:
    Get the value of dimension n of a point
    */
    return this->myvectorCoords[n];
}
// get value at dimension by reference
template <class T>
T & Point<T>::tGetValAtDimNByReference(const int &dimN) const{
    /*
    Inputs:
    int
    Outputs:
    T
    Utility:
    Gets a value at dimension N by reference
    */
    return this->myvectorCoords.tGetByReference(dimN);
}
/*
****************************
myVector returning functions
****************************
*/
// get the vector of coordinates
template <class T>
myVector<T> Point<T>::myvectorGetCoords() const{
    /*
    Inputs:
    void
    Outputs:
    myVector, vector containing the coordinates of a point
    Utility:
    Get the coordinates of a point
    */
    return this->myvectorCoords;
}

/*
****************************
int returning functions
****************************
*/
// get the cluster id
template <class T>
int Point<T>::intGetClusterId() const{
    /*
    Inputs:
    void
    Outputs:
    int, Cluster ID that the point belongs to
    Utility:
    Get the membership of a point
    */
    // gets the id of the point's cluster
    return this->intClusterId;
}

// get cluster id by ref
template <class T>
int& Point<T>::intGetClusterIdByReference(){
    /*
    Inputs: 
    void
    Outputs: 
    int, reference to the cluster id that the point belongs to
    Utility: 
    Return by reference the id of the cluster of the current point
    */
    return this->intClusterId;
}

// get dim size (number of dimensions of point)
template <class T>
int Point<T>::intGetDimensions() const{
    /*
    Inputs:
    void
    Outputs:
    int, number of dimensions a point has
    Utility:
    Get the number of dimensions of a point
    */
    // gets the dimensions of a point
    return this->intDimensions;
}
/*
****************************
double returning functions
****************************
*/
// get distance at a dimension
template <class T>
double Point<T>::doubleGetDistanceAtDimN(const Point<T>&p ,const int&n)const{
    /*
    Inputs:
    Point, int, Point to have its distance from calculated, dimension to have the distance calculated 
    Outputs:
    double, distance between the two points
    Utility:
    Get the distance (Euclidean) of two points at dimension n
    */
    return (tGetValAtDimNByReference(n) - p.tGetValAtDimNByReference(n))*(tGetValAtDimNByReference(n)-p.tGetValAtDimNByReference(n));
}
// get distance over all dimensions
// note we do not square root here
template <class T>
double Point<T>::doubleGetDistance(const Point<T> &aPoint)const {
    /*
    Inputs:
    Point, Point to have the distance from calculated
    Outputs:
    double, distance between the points
    Utility:
    Get the total distance between two points (Euclidean)
    */
    // assumes they are of same dimension
    if(aPoint.intGetDimensions() != this->intDimensions){
        std::cout << "ERROR: Point.cpp\nBad dimensions between point: " << aPoint << " and current point: " << *this << "\n";
        std::cout << "this dim:" << this->intDimensions << " aPoint dim:" << aPoint.intGetDimensions() << "\n";
        exit(1);
    }
    double distance = 0;
    for(int i=0;i<this->intDimensions;i++){
        distance += doubleGetDistanceAtDimN(aPoint,i);
    }
    
    return distance;
}
/*
****************************
void returning functions
****************************
*/
// set the vector of coords
template <class T>
void Point<T>::voidSetCoordVector(const myVector<T> &coords){
    /*
    Inputs:
    myVector
    Outputs:
    void
    Utility:
    Sets the coordinate vector of point
    */
    this->myvectorCoords.voidSetEqualLhsRhs(coords);
}
// set the number of dimensions
template <class T>
void Point<T>::voidSetDimSize(const int &intDimSize){
    /*
    Inputs:
    int
    Outputs:
    void
    Utility:
    Sets the dimension size of vector
    */
    this->intDimensions = intDimSize;
}

// set the point cluster id
template <class T>
void Point<T>::voidSetClusterId(const int &intClusterId){
    /*
    Inputs:
    int, cluster ID to be set to
    Outputs:
    void
    Utility:
    Set membership of a point
    */
    this->intClusterId = intClusterId;
}
// add a point directly
// used over the operator so that there is not intermediate creation of point
template <class T>
void Point<T>::voidAddPointDirectly(const Point<T>&aPoint){
    /*
    Inputs:
    Point, Point being added into the currect point
    Outputs:
    void
    Utility:
    Add point directly (meaning, no returning, that is too slow)
    */
    if(aPoint.intGetDimensions() != this->intDimensions){
        std::cout << "ERROR: Point.cpp voidAddPointDirectly\nDimension mismatch of this: " << this->intDimensions << " and rhs: " << aPoint.intGetDimensions() << "\n";
        exit(1);
    }
    for(int i=0;i<this->intDimensions;++i){
        this->myvectorCoords[i] += aPoint.tGetValAtDimNByReference(i);
    }
}
// divide a point by divisor
template <class T>
void Point<T>::voidDivideDirectly(const T & divisor){
    /*
    Inputs:
    T, value to divide the dimensions by
    Outputs:
    void
    Utility:
    Divide all dimensions by divisor. Used in creating average points when updating centroid
    */
    for(int i=0;i<this->intDimensions;++i){
        this->myvectorCoords[i] /= divisor;
    }
}

/*
****************************
bool returning functions
****************************
*/
// check if two points equal
template <class T>
bool Point<T>::boolEquals(const Point<T> &aPoint) const{
    /*
    Inputs:
    Point, Point being checked for equality to the current point
    Outputs:
    boolm, true if equals, false if not
    Utility:
    Check if two points equal
    */
    if(aPoint.intGetDimensions() != this->myvectorCoords.intLength()){
        return false;
    }
    if(aPoint.intGetClusterId() != this->intClusterId){
        return false;
    }
    for(int i=0;i<this->myvectorCoords.intLength();++i){
        if(aPoint.tGetValAtDimNByReference(i) != this->myvectorCoords.tGetByReference(i)){
            return false;
        }
    }
    return true;
}
/*
 * ************************
 * Operators
 * ************************
 */
// get 
template <class T>
T Point<T>::operator[] (const int &index) const{
    /*
    Inputs:
    int, Index to have the coordinate returned from
    Outputs:
    T, coordinate 
    Utility:
    Bracket operator to get data at index
    */
    return tGetAtDimN(index);
}
// set
template <class T>
T& Point<T>::operator[] (const int &index){
    /*
    Inputs:
    int, index to have the coordinate changed
    Outputs:
    T, Reference to the coordinate to be changed
    Utility:
    Bracket operator to set at index
    */
    if(index < 0 || index >= this->myvectorCoords.intLength()){
        std::cout << "ERROR: Point.cpp\nBad index: " << index << " for size:" << this->intDimensions << "\n";
        exit(1);
    }
    else{
        return this->myvectorCoords[index];
    }
}
// equality
template <class T>
bool Point<T>::operator == (const Point<T> &aPoint) const{
    /*
    Inputs:
    Point, point to check for equality
    Outputs:
    bool, true if points are equals, false if not
    Utility:
    Equals operator to check if two points equal
    */
    return boolEquals(aPoint);
}
// inequality
template <class T>
bool Point<T>::operator != (const Point<T> &aPoint) const{
    /*
    Inputs:
    Point, point being tested for inequality
    Outputs:
    bool, true if points are not equal, false if they are
    Utility:
    Inequality operator to check if two points not equal
    */
    return !boolEquals(aPoint);
}
// insertion
template <class U>
std::ostream & operator << (std::ostream &os, const Point<U>&aPoint){
    /*
    Inputs:
    ostream, Point, ostream to have data inserted into, Point to have data extracted from
    Outputs:
    ostream, modified ostream
    Utility:
    Stream insertion operator for printing point to console
    */
    int dims = aPoint.intGetDimensions();
    if(dims == 0){
        return os;
    }
    else{
        for(int i=0;i<dims;i++){
            os << aPoint.tGetValAtDimNByReference(i) << " ";
        }
        os << " | " << aPoint.intGetClusterId();
    }
    return os;
}
// extraction
template <class U>
std::istream &operator >>(std::istream &input, Point<U> &aPoint){
    /*
    Inputs: 
    istream, Point, istream to get data from, Point to have data added to
    Outputs:
    istream
    Utility: 
    Stream extraction oprator for adding data from the stream to a point
    */
    for(int i=0;i<aPoint.intGetDimensions();++i){
        input >> aPoint.tGetValAtDimNByReference(i);
    }
    return input;
}
// addition
template <class T>
const Point<T> Point<T>::operator + (const Point<T>&rhs) const{
    /*
    Inputs:
    Point, point being added to the current point
    Outputs:
    Point, point containing the data of the two added points
    Utility:
    Add two points, return the add
    */
    // adds up all dimensions
    if(rhs.intGetDimensions() != this->intDimensions){
        std::cout << "ERROR: Point.cpp operator +\n";
        std::cout << "Dimension rhs:" << rhs.intGetDimensions() << " not match for this: " << this->intDimensions << "\n";
        exit(1);
    }
    Point<T> temp = rhs;
    for(int i=0;i<this->intDimensions;++i){
        temp[i] += this->myvectorCoords.tGetByReference(i);
    }
    return temp;
}
// subtraction
template <class T>
const Point<T> Point<T>::operator - (const Point<T>&rhs) const{
    /*
    Inputs:
    Point, point to be subtacted from the current
    Outputs:
    Point, Point containing the data of the subtracted points
    Utility:
    Substract two points, return the subtract
    */
    // subtract up all dimensions
    if(rhs.intGetDimensions() != this->intDimensions){
        std::cout << "ERROR: Point.cpp operator -\n";
        std::cout << "Dimension rhs:" << rhs.intGetDimensions() << " not match for this: " << this->intDimensions << "\n";
        exit(1);
    }
    Point<T> temp = rhs;
    for(int i=0;i<this->intDimensions;++i){
        temp[i] -= this->myvectorCoords.tGetByReference(i);
    }
    return temp;
}
// assignment
template <class T>
const Point<T>& Point<T>::operator = (const Point<T> &rhs){
    /*
    Inputs:
    Point, point to be set equal to
    Outputs:
    Point, point passed in for cascading
    Utility:
    assignment operator for setting one point equal to another
    */
    this->myvectorCoords.voidSetEqualLhsRhs(rhs.myvectorGetCoords());
    this->intClusterId = rhs.intGetClusterId();
    this->intDimensions = rhs.intGetDimensions();

    return *this;
}

#endif
