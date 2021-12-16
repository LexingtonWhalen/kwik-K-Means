/*
kMeansCalculator.
This program takes in data and clusters it.
See all the possible arguments to pass into the kMeansObject.
For instance, can pass in the number of clusters to create, the number 
of iterations, the threshold to stop at, and the number of random seeds.

The program will output summaries related to points / centroids. It can
also output a text file.
*/
#ifndef POINT_H
#define POINT_H

#include <iostream>
#include "./myVector.cpp"

/*

Point Class

This class represents a point in N dimensional space.
It is used to both represent data points and centroid points.

*/

template <class T>
class Point{
    public:
        /*
        ****************************
        CTORS, DTORS
        ****************************
        */
        // default ctor
        Point();
        // param ctors
        // create point based on coordinates
        Point(const myVector<T>&coords);
        // create point based on dimension size
        Point(const int &dimSize);
        // create point based on dimensions and filler with values, also give an id
        Point(const int &dimSize, const T &filler,const int &id);
        // create point based on coordinates and give id
        Point(const myVector<T>&coords, const int &clusterId);
        // copy ctor
        Point(const Point &rhs);
        // dtor
        ~Point();

        /*
        ****************************
        SETTERS, GETTERS
        ****************************
        */
        // get val at dim
        T tGetAtDimN(const int &n)const;
        // get val at dim by ref
        T& tGetValAtDimNByReference(const int &dimN) const;
        
        // get the coords vector
        myVector<T> myvectorGetCoords() const;
        // get the cluster id of point
        int intGetClusterId() const;
        // get clutser id of point by ref
        int& intGetClusterIdByReference();
        // get dim size of point
        int intGetDimensions() const;
        
        // set cluster id
        void voidSetClusterId(const int &intClusterId);
        // set coord vector
        void voidSetCoordVector(const myVector<T>&vec);
        // set dim size of point
        void voidSetDimSize(const int &intDimSize);

        /*
        ****************************
        FUNCTIONS FOR CALCULATIONS
        ****************************
        */
        // get distance at dim n
        double doubleGetDistanceAtDimN(const Point<T> & p, const int &n) const;
        // to get around issue of returning a new point object (faster)
        void voidAddPointDirectly(const Point<T>&aPoint);
        // get around issue of returning a new point object
        void voidDivideDirectly(const T &divisor);
        // get distance between other point (Euclidean)
        double doubleGetDistance(const Point &aPoint) const;
        /*
        ****************************
        AUX FUNCTIONS, OPERATORS
        ****************************
        */
        // get
        T operator [] (const int&intIndex) const;
        // set
        T& operator[](const int &intIndex);
        
        bool operator == (const Point<T>&aPoint) const;
        bool operator != (const Point<T> &aPoint) const;

        const Point<T> operator + (const Point<T>& aPoint) const;
        const Point<T> operator - (const Point<T>& aPoint) const;

        const Point<T>& operator = (const Point<T> &rhs);

        template <class U>
        friend std::ostream& operator << (std::ostream &os, const Point<U>& aPoint);

        template <class U>
        friend std::istream &operator >>(std::istream &input, Point<U> &aPoint);

    private:
        // helper function for equality operator 
        bool boolEquals(const Point<T> &aPoint) const;
        // default cluster id
        static const int INT_UNDEF_CLUSTER {-1};
        // id of cluster it belongs to
        int intClusterId {-1};
        // vector of coords
        myVector<T> myvectorCoords {0};

        // number of dimensions of a point
        int intDimensions {-1};

};

#endif