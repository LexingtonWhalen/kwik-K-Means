/*
kMeansCalculator.
This program takes in data and clusters it.
See all the possible arguments to pass into the kMeansObject.
For instance, can pass in the number of clusters to create, the number 
of iterations, the threshold to stop at, and the number of random seeds.

The program will output summaries related to points / centroids. It can
also output a text file.
*/
#ifndef MY_VECTOR_CPP
#define MY_VECTOR_CPP

#include "./myVector.h"

// default ctor
template <class T>
myVector<T>::myVector(){
    /*
    Inputs:
    void
    Outputs:
    void
    Utility:
    Create vector, set size to 0 and point to null.
    */
    this->intSize = 0;
    this->ptrTData = nullptr;
}
// param 
template <class T>
myVector<T>::myVector(const int &intSize){
    /*
    Inputs:
    int
    Outputs:
    void
    Utility:
    Create vector, set size.
    */
    this->intSize = intSize;
    this->ptrTData = new T[intSize];
}

template <class T>
myVector<T>::myVector(const int &intSize, const T &tFiller){
    /*
    Inputs:
    int, T, size of the vector, filler value for each item in the vector to be set to
    Outputs:
    void
    Utility:
    Create vector, set size and fill.
    */
    this->intSize = intSize;
    this->ptrTData = new T[intSize];
    for(int i=0;i<intSize;++i){
        this->ptrTData[i] = tFiller;
    }
}

template <class T>
myVector<T>::myVector(const T arrT[],const int &intSize){
    /*
    Inputs:
    T [], int, Array holding the data for the vector to be filled with, size of the vector
    Outputs:
    void
    Utility:
    Create vector based on array, set size
    */
    this->intSize = intSize;
    this->ptrTData = new T[intSize];
    for(int i=0;i<this->intSize;++i){
        this->ptrTData[i] = arrT[i];
    }
}
template <class T>
myVector<T>::myVector(const myVector<T>&rhs){
    /*
    Inputs:
    myVector<T>, myVector to be copied
    Outputs:
    void
    Utility:
    Create vector in image of rhs
    */
    this->intSize = rhs.intLength();
    this->ptrTData = new T [this->intSize];
    voidBiject(rhs);
}

template <class T>
myVector<T>::~myVector(){
    /*
    Inputs:
    void
    Outputs:
    void
    Utility:
    Destructor.
    */
    voidClear();
    this->ptrTData = nullptr;
}

template <class T>
T myVector<T>::tAt(const int &intIndex) const{
    /*
    Inputs:
    int, index to have the object returned from
    Outputs:
    T, object being returned from the vector
    Utility:
    Return value found at index
    */
    if(boolCheckIndexBounds(intIndex)){
        return this->ptrTData[intIndex];
    }else{
        std::cout << "ERROR: myVector: tAt\nBad index " << intIndex << " for size: " << this->intSize << "\n";
        exit(1);
        return this->ptrTData[0];
    }
}

template <class T>
T& myVector<T>::tGetByReference(const int &index) const{
    /*
    Inputs:
    int, index to have the data returned from
    Outputs:
    T, Reference to the data at the index
    Utility:
    Explicitly get by reference the data at index
    */
    if(boolCheckIndexBounds(index)){
        return this->ptrTData[index];
    }
    else{
        voidPrintBadIndex(index);
        exit(1);
        return this->ptrTData[0];
    }
}

template <class T>
int myVector<T>::intLength() const{
    /*
    Inputs:
    void
    Outputs:
    int
    Utility:
    Get the length / size of vector
    */
    return this->intSize;
}

template <class T>
int myVector<T>::intFindIndexOf(const T&aData) const{
    /*
    Inputs:
    T, data to be found
    Outputs:
    int, index that data was found at, -1 if not found
    Utility:
    Find index of data in vector
    */
    if(this->intSize <= 0){
        return this->INT_BAD_FIND;
    }
    // loop thru, find first instance
    for(int i=0;i<this->intSize;++i){
        if(this->ptrTData[i] == aData){
            return i;
        }
    }
    return -1;
}

template <class T>
void myVector<T>::voidPrint() const{
    /*
    Inputs:
    void
    Outputs:
    void
    Utility:
    Prints contents of vector.
    */
    if(this->intSize == 0){
        return;
    }else{
        for(int i=0;i<this->intSize;++i){
            std::cout << this->ptrTData[i] << " ";
        }
        std::cout << "\n";
    }

}

template <class T>
void myVector<T>::voidBiject(const myVector<T>&rhs){
    /*
    Inputs:
    myVector, vector to be copied into the current vector
    Outputs:
    void
    Utility:
    copies 1-1 from rhs to this object.
    */
    if(rhs.intLength() != this->intSize){
        return;
    }else{
        for(int i=0;i<this->intSize;++i){
            this->ptrTData[i] = rhs.tGetByReference(i);
        }
    }
}

template <class T>
void myVector<T>::voidPrintBadIndex(const int &intIndex) const{
    /*
    Inputs:
    int, index that is bad
    Outputs:
    void
    Utility:
    if bad index, print error.
    */
    std::cout << "Error:\nBad index \"" << intIndex << "\" for array intSize \"" << this->intSize << "\"";
}

template <class T>
void myVector<T>::voidClear(){
    /*
    Inputs:
    void
    Outputs:
    void
    Utility:
    Clear the vector
    */
    delete [] this->ptrTData;
    this->intSize = 0;
    this->ptrTData = nullptr;
}

template <class T>
void myVector<T>::voidSetSize(const int & newSize){
    /*
    Inputs:
    int, new size of the vector
    Outputs:
    void
    Utility:
    Update the size of vector
    */
    voidClear();
    this->intSize = newSize;
    this->ptrTData = new T[newSize];
}
template <class T>
void myVector<T>::voidSetEqualLhsRhs(const myVector<T>&rhs){
    /*
    Inputs:
    myVector, vector for the current vector to be set equal to
    Outputs:
    myVector, passed in vector reference for cascadability
    Utility:
    Assignment, faster bc dont return object
    */
    if(rhs.intLength() == this->intSize){
        // just biject
        voidBiject(rhs);
        return;
    }
    // else need to clear
    voidClear();

    this->intSize = rhs.intLength();
    this->ptrTData = new T[this->intSize];
    
    voidBiject(rhs);
    return;
}

template <class T>
void myVector<T>::voidPush(const T &aData){
    /*
    Inputs:
    T, data to be added onto the end of the vector
    Outputs:
    void
    Utility:
    Push a new item to end of vector
    */
    int intOldLength = this->intSize;
    T * temp = new T[intOldLength + 1];
    for(int i=0;i<intOldLength;++i){
        temp[i] = this->ptrTData[i];
    }
    temp[intOldLength] = aData;
    delete [] this->ptrTData;
    this->ptrTData = nullptr;

    this->intSize += 1;
    this->ptrTData = temp;
}

template <class T>
void myVector<T>::voidRemove(const T&aData){
    /*
    Inputs:
    T, data to be found and removed from the vector
    Outputs:
    void
    Utility:
    Remove item from vector
    */
    if(this->intSize <= 0){
        return;
    }
    int intFoundIndex = intFindIndexOf(aData);
    if(intFoundIndex == this->INT_BAD_FIND){
        return;
    }
    voidPopAt(intFoundIndex);
}

template <class T>
void myVector<T>::voidPopAt(const int &anIndex){
    /*
    Inputs:
    int, Index to be removed 
    Outputs:
    void
    Utility:
    Remove item at index
    */
    if(this->intSize <= 0){
        return;
    }
    int intOldLength = this->intSize;
    T * temp = new T[intOldLength-1];
    // left side
    for(int i=0;i<anIndex;++i){
        temp[i] = this->ptrTData[i];
    }
    // right side
    for(int i=anIndex;i<intOldLength-1;++i){
        temp[i] = this->ptrTData[anIndex+1];
    }
    delete [] this->ptrTData;
    this->ptrTData = nullptr;

    this->intSize --;
    this->ptrTData = temp;
}

template <class T>
void myVector<T>::voidSetAt(const T &aData, const int &index){
    /*
    Inputs:
    T, int,  Data to be put at the index, index to be changed
    Outputs:
    void
    Utility:
    Set value at index
    */
    if(boolCheckIndexBounds(index)){
        this->ptrTData[index] = aData;
    }else{
        return;
    }
}

template <class T>
bool myVector<T>::boolCheckIndexBounds(const int &intIndex) const{
    /*
    Inputs:
    int, index to be checked
    Outputs:
    bool, true if index is within bounds, false if not
    Utility:
    Check index within bounds
    */
    if(intIndex < 0 || intIndex >= this->intSize){
        return false;
    }else{
        return true;
    }
}

template <class T>
const myVector<T> myVector<T>::myvectorMakeClone() const{
    /*
    Inputs:
    void
    Outputs:
    myVector<T>, clone of the current vector object
    Utility:
    Create and return clone of current object
    */
    myVector<T> ret {this->intSize};
    for(int i=0;i<this->intSize;++i){
        ret[i] = this->ptrTData[i];
    }
    return ret;
}


/*
 * Operators
 */
template <class T>
T& myVector<T>::operator[] (const int &index){
    /*
    Inputs:
    int, index to be changed
    Outputs:
    T, Reference to the T object in the vector that will be changed
    Utility:
    Bracket operator For modifying vector values at index
    */
    if(boolCheckIndexBounds(index)){
        return this->ptrTData[index];
    }
    else{
        voidPrintBadIndex(index);
        exit(1);
        return this->ptrTData[0];
    }
}

template <class T>
T myVector<T>::operator[] (const int &index)const{
    /*
    Inputs:
    int, index for the data to be returned from
    Outputs:
    T, Returned data found at the index
    Utility:
    Bracket operator to get value at index
    */
    return tAt(index);
}

template <class T>
bool myVector<T>::operator != (const myVector<T>&rhs)const{
    /*
    Inputs:
    myVector, vector being checked for being not equal
    Outputs:
    bool, true if the vectors are not equal, false if they are
    Utility:
    Inequality operator for checking if two vectors not equal
    */
    return !(*this == rhs);
}

template<class T>
bool myVector<T>::operator == (const myVector<T>&rhs)const{
    /*
    Inputs:
    myVector, vector being checked for being equal
    Outputs:
    bool, true if the vectors are equal, false if they are not
    Utility:
    Equality operator for checking if two vectors equal
    */
    if(this->intSize != rhs.intLength()){
        return false;
    }
    else{
        for(int i=0;i<this->intSize;i++) {
            if(this->ptrTData[i] != rhs.tGetByReference(i)){
                return false;
            }
        }
    }
    return true;
}

template <class T>
const myVector<T>& myVector<T>::operator = (const myVector<T>&rhs){
    /*
    Inputs:
    myVector, vector for the current vector to be set equal to
    Outputs:
    myVector, passed in vector reference for cascadability
    Utility:
    Assignment operator for setting a vector equal to rhs
    */
    if(rhs.intLength() == this->intSize){
        // just biject
        voidBiject(rhs);
        return *this;
    }
    // else need to clear
    voidClear();

    this->intSize = rhs.intLength();
    this->ptrTData = new T[this->intSize];
    
    voidBiject(rhs);

    return *this;
}

template <class T>
const myVector<T> myVector<T>::operator +(const myVector<T> &rhs)const {
    /*
    Inputs:
    myVector, vector to be appended onto the end of the current
    Outputs:
    myVector, vector containing the current vector with the rhs vector appended to it
    Utility:
    Addition operator to concat two vectors (rhs goes to end of current obj)
    */
    if(rhs.intLength() <= 0){
        return myvectorMakeClone();
    }

    myVector<T> temp {this->intSize + rhs.intLength()};
    for(int i=0;i<this->intSize;++i){
        temp[i] = this->ptrTData[i];
    }
    for(int i=this->intSize;i<temp.intLength();++i){
        int adjIndex = i - this->intSize;
        temp[i] = rhs[adjIndex];
    }
    return temp;
}

template <class T>
std::ostream & operator << (std::ostream &os, const myVector<T> & aVector){
    /*
    Inputs:
    ostream, myVector, ostream to have data inserted, vector to have data pulled from
    Outputs:
    ostream, changed ostream
    Utility:
    Stream insertion operator for printing out a vector
    */
    for(int i=0;i<aVector.intLength();++i){
        os << aVector.tGetByReference(i) << " ";
    }
    return os;
}

#endif
