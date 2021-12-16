# CPP_KMeans

How to run:

You must have each file as is shown below:

- currect directory:
  - lib:
	- kMeansCalc.cpp
	- kMeansCalc.h
	- myVector.cpp
	- myVector.h
	- Point.cpp
	- Point.h
	- PointReader.cpp
	- PointReader.h
  - main.cpp

The main.cpp file can have any name as long as `main` is the first 4 letters.

Example mains are found in `./example_mains`
For instance, dragging and droping `main_alt_ctor_2darr.cpp` provides an example main.cpp for the 2d arr constructor.

Running `make` and then `./app` will run the main file.

To clean the object files, run `make clean`.

Each `./app` run may or may not make a file (depending on user input).

In `grapher.py`, you can graph the output of the text file obtained from voidWriteToFile in kMeansCalc.h.
- This creates a file `out.png` which is a visual representation of the clustering. Note that this only really works for 2 dimensional data.

