/*
kMeansCalculator.
This program takes in data and clusters it.
See all the possible arguments to pass into the kMeansObject.
For instance, can pass in the number of clusters to create, the number 
of iterations, the threshold to stop at, and the number of random seeds.

The program will output summaries related to points / centroids. It can
also output a text file.
*/
#ifndef POINT_READER_H
#define POINT_READER_H

// for files
#include <fstream>
// for std::in/ out
#include <iostream>
// for filenames
#include <string>
// for parsing csv
#include <sstream>
// for square root
#include <cmath>

#include "./Point.cpp"
#include "./myVector.cpp"

/*

PointReader Class.

This class reads a csv file of points and creats a vector of point objects for use in other programs.

*/

template <class T>
class PointReader{
    public: 
        /*
        **************************
        CTOR, DTORS
        **************************
        */
        // default ctor
        PointReader();
        // copy ctor
        PointReader(const PointReader<T> &reader);
        // param ctor that accepts point dim size
        PointReader(const int &pointDimSize);
        // param ctor
        PointReader(const std::string &strInputFile, const int &pointDims);
        // param ctor accepts 2d arr
        PointReader(T **data,const int &rows, const int &cols);
        // dtor
        ~PointReader();
        // read txt file
        void voidReadTxt(const std::string &strInputFile);
        // read csv file
        void voidReadCSV(const std::string &strInputFile);

        /*
        **************************
        GETTERS, SETTERS
        **************************
        */
        // get the vector of read points
        myVector<Point<T>> myvectorGetPoints() const;
        // get the vector of stdevs accross dims
        myVector<double> myvectorGetStdDevs() const;
        // get the vector of avgs across dims
        myVector<double> myvectorGetAvgs() const;
        // get min and max across dims
        myVector<double> myvectorGetMins() const;
        myVector<double> myvectorGetMaxes() const;

        // get the dimensions of the points read
        int intGetPointDimensions() const;
        // get the number of points
        int intGetPointCount() const;
        // set vector points
        void voidSetMyVectorPoints(const myVector<Point<T>> &points);
        // set vector of avgs
        void voidSetMyVectorAvgs(const myVector<double> &points);
        // set vector of mins
        void voidSetMyVectorMins(const myVector<double> &points);
        // set vector of maxes
        void voidSetMyVectorMaxes(const myVector<double> &points);
        // set vector of stddevs
        void voidSetMyVectorStdDevs(const myVector<double> &points);
        // set point dim size
        void voidSetIntPointDimensions(const int& dimSize);

        /*
        Operators
        */
        bool operator == (const PointReader<T>&rhs) const;
        bool operator != (const PointReader<T>&rhs) const;

        // assignment
        const PointReader<T>& operator = (const PointReader<T>&rhs);

        template <class U>
        friend std::istream &operator >> (std::istream &input, PointReader<U> &aReader);

    private:
        void voidCheckHasPointDimensions() const;
        myVector<Point<T>> myvectorPoints;
        myVector<double> myvectorStdDevs;
        myVector<double> myvectorAvgs;
        myVector<double> myvectorMins;
        myVector<double> myvectorMaxes;

        int intGetTotalLines(const std::string &strInputFile);

        int intPointDimensions{0};
};

#endif
