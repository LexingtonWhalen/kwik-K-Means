/*
kMeansCalculator.
This program takes in data and clusters it.
See all the possible arguments to pass into the kMeansObject.
For instance, can pass in the number of clusters to create, the number 
of iterations, the threshold to stop at, and the number of random seeds.

The program will output summaries related to points / centroids. It can
also output a text file.
*/
#ifndef MY_VECTOR_H
#define MY_VECTOR_H

#include <iostream>

/*

myVector class.

This class represents a dynamically resizing vector. However, it should be used mainly as a buffed array, as resizing is a slow operation.

*/

template <class T>
class myVector{
    public:
        /*
        **************************
        CTORS, DTORS
        **************************
        */
        // default ctor
        myVector();
        // make vector with size
        myVector(const int &intSize);
        // make vector based on array and array size
        myVector(const T arrT[], const int &intSize);
        // make vector based on size, fill with filler
        myVector(const int &intSize, const T &tFiller);
        // copy ctor
        myVector(const myVector<T>& rhs);
        // dtor
        ~myVector();

        /*
        **************************
        GETTERS, SETTERS
        **************************
        */
        // get val at index
        T tAt(const int &intIndex) const;
        // return a value by reference
        T& tGetByReference(const int &index) const;
        // get length 
        int intLength() const;
        // find index of item
        int intFindIndexOf(const T &aData) const;

        /*
         * Void returning functions 
         */
        // set lhs equal rhs (faster than assignment)
        void voidSetEqualLhsRhs(const myVector<T>&rhs);
        // concat two vec
        void voidConcat(const myVector<T> &rhs);
        // push to end of vec
        void voidPush(const T &aData);
        // pop at index (remove)
        void voidPopAt(const int &anIndex);
        // set at index
        void voidSetAt(const T &aData, const int &index);
        // remove data
        void voidRemove(const T&aData);

        // copy 1-1 items
        void voidBiject(const myVector<T>& copier);
        // clear the vector
        void voidClear();
        // print the vector
        void voidPrint() const;
        // set the size of vector
        void voidSetSize(const int &newSize);

        // deep copy
        const myVector<T> myvectorMakeClone() const;

        /*
        **************************
        * Operators
        **************************
         */
        // get value
        T operator [] (const int &intIndex) const;
        // set value
        T& operator[](const int &intIndex);
        // equal
        bool operator == (const myVector<T>&rhs) const;
        bool operator != (const myVector<T> &rhs) const;

        const myVector<T>& operator = (const myVector<T>&rhs);
        const myVector<T> operator + (const myVector<T> &rhs) const;


        template <class U>
        friend std::ostream& operator <<(std::ostream &os, const myVector<U>& aVector);
    private:
        // if you get a bad find
        static const int INT_BAD_FIND = -1;
        // data pointer
        T *ptrTData = nullptr;
        // size of vector
        int intSize;
        // check bounds of vector
        bool boolCheckIndexBounds(const int &intIndex) const;
        // print bad index
        void voidPrintBadIndex(const int &indexIndex) const;
};

#endif
