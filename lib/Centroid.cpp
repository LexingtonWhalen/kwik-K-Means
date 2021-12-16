/*
kMeansCalculator.
This program takes in data and clusters it.
See all the possible arguments to pass into the kMeansObject.
For instance, can pass in the number of clusters to create, the number 
of iterations, the threshold to stop at, and the number of random seeds.

The program will output summaries related to points / centroids. It can
also output a text file.
*/

#ifndef CENTROID_CPP
#define CENTROID_CPP

#include "./Centroid.h"
/*
__________________________________________________________________________________
* Centroid class.
*
* This is the implementation of the centroid class.
__________________________________________________________________________________
*/

/*
****************************
ctors
****************************
Note most are inherited from Point.
*/
// copy ctor
template <class T>
Centroid<T>::Centroid(const Centroid &rhs) : Point<T>(rhs){
    this->doubleEntropyLevel = rhs.doubleGetEntropyLevel();
    this->intNumMembers = rhs.intGetNumMembership();
}

/*
****************************
operators
****************************
*/
// assignment centroid
template <class T>
const Centroid<T>& Centroid<T>::operator = (const Centroid<T> &rhs){
    // call parent assignment
    Point<T>::operator = (rhs);
    // then do operations special to centroids
    this->intNumMembers = rhs.intGetNumMembership();
    this->doubleEntropyLevel = rhs.doubleGetEntropyLevel();
    return *this;
}
// assignment point
template <class T>
const Centroid<T>& Centroid<T>::operator = (const Point<T>&rhs){
    // call parent assignment
    Point<T>::operator = (rhs);
    return *this;
}
// equality 
template <class T>
bool Centroid<T>::operator == (const Centroid<T>&rhs){
    // call parent equality
    if(!Point<T>::operator == (rhs)){
        return false;
    }
    // check attributes special to centroids
    if(this->doubleEntropyLevel != rhs.doubleGetEntropyLevel()){
        return false;
    }
    if(this->intNumMembers != rhs.intGetNumMembership()){
        return false;
    }
    return true;
}
// inequality
template <class T>
bool Centroid<T>::operator != (const Centroid<T> &rhs){
    return !(*this == rhs);
}
/*
****************************
void returning functions
****************************
*/
// add double to entropy level and int to membership
template <class T>
void Centroid<T>::voidAddToEntropyAndMembership(const double &entropy, const int &newMemberCount){
    /*
    Inputs:
    double, int, entropy to be added, member count being added 
    Outputs:
    void
    Utility:
    Add a point's entropy and increment the current point's (centroid here) membership count.
    */
    this->doubleEntropyLevel += entropy;
    this->intNumMembers += newMemberCount;
}
// set the number of members of centroid
template <class T>
void Centroid<T>::voidSetNumMembership(const int &newMemberCount){
    /*
    Inputs:
    int, number of members for the point to be set to
    Outputs:
    void
    Utility:
    Set the number of members a point has
    */
    this->intNumMembers = newMemberCount;
}
/*
****************************
int returning functions
****************************
*/
// get the number of members
template <class T>
int Centroid<T>::intGetNumMembership() const{
    /*
    Inputs:
    void
    Outputs:
    int, number of members a point has
    Utility:
    Get the number of members of a point
    */
    return this->intNumMembers;
}
// get number of members by reference
template <class T>
int& Centroid<T>::intGetNumMembershipByReference(){
    /*
    Inputs:
    void
    Outputs:
    int
    Utility:
    Gets the number of members by reference
    */
    return this->intNumMembers;
}
/*
****************************
double returning functions
****************************
*/
// get entropy level of centroid
template <class T>
double Centroid<T>::doubleGetEntropyLevel() const{
    /*
    Inputs:
    void
    Outputs:
    double, entropy level of a point
    Utility:
    Get the entropy level of a point (only needed for centroid points)
    */
    return this->doubleEntropyLevel;
}
// get avg entropy level of centroid
template <class T>
double Centroid<T>::doubleGetAvgEntropy() const{
    /*
    Inputs:
    void
    Outputs:
    double, average entropy of a point 
    Utility:
    Get the average entropy of a point
    */
    return this->doubleEntropyLevel / intNumMembers;
}

#endif