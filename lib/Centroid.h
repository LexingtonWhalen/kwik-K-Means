/*
kMeansCalculator.
This program takes in data and clusters it.
See all the possible arguments to pass into the kMeansObject.
For instance, can pass in the number of clusters to create, the number 
of iterations, the threshold to stop at, and the number of random seeds.

The program will output summaries related to points / centroids. It can
also output a text file.
*/
#ifndef CENTROID_H
#define CENTROID_H

// inherits from point
#include "Point.h"
/*
******************
* Centroids are just special points that contain members and entropy levels.
******************
*/
template <class T>
class Centroid: public Point<T>{
    public:
        /*
        *************************
        * Centroid ctors, dtors
        *************************
        */
        // default
        Centroid() : Point<T>() {};
        // fill up centroid based on vector of coordinates
        Centroid(const myVector<T>&coords) : Point<T>(coords) {};
        // ctor only set dimension size
        Centroid(const int&dimSize) : Point<T>(dimSize) {};
        // ctor set dim size, fill dimensions, give centroid id 
        Centroid(const int&dimSize, const T&filler, const int &id) : Point<T>(dimSize,filler,id) {};
        // ctor set vector of coords, give cluster id
        Centroid(const myVector<T>& coords, const int &clusterId) : Point<T>(coords,clusterId) {};
        // copy ctor
        Centroid(const Centroid &rhs);
        /*
        *************************
        * void returning functions
        *************************
        */
        // for centroids; when adding a point's entropy, you always add to membership (the point you calced the entropy for is always a new member)
        void voidAddToEntropyAndMembership(const double &doubleEntropy,const int &newMemberCount);
        // set the number of members of a centroid
        void voidSetNumMembership(const int &newMembership);
        // get the number of members by reference
        int& intGetNumMembershipByReference();
        // get the number of members
        int intGetNumMembership() const;

        /*
        *************************
        * double returning functions
        *************************
        */
        // get the avg entropy of centroid
        double doubleGetAvgEntropy() const;
        // get the total entropy level of centroid
        double doubleGetEntropyLevel() const;
        /*
        *************************
        * operator functions
        *************************
        */
        // assignment to centroid
        const Centroid<T>& operator = (const Centroid<T> &rhs);
        // assignment to point
        const Centroid<T>& operator = (const Point<T> &rhs);

        // inequality for centroid
        bool operator != (const Centroid<T>&rhs);
        // equality
        bool operator == (const Centroid<T>&rhs);

    private:

        // hold the entropy level
        double doubleEntropyLevel {0};
        // hold the number of members
        int intNumMembers {0};
};

#endif