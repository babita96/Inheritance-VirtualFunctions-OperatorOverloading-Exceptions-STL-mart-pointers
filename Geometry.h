#ifndef GEOMETRY_H_
#define GEOMETRY_H_
#include <iostream>
#include <memory>
#include <vector>

class Point; // forward declaration

class Shape {

public:
	// Default constructor, just to make this release version compilable.
	// If your implementation is correct this should be removed
	Shape();

	// Constructor specifying the depth of the object.
	// If d is negative, throw a std::invalid_argument exception.
	Shape(int d);

	// Set depth of object to d. If d is negative, return false and
	// do not update depth. Otherwise return true
	bool setDepth(int d);

	// Return the depth of object
	int getDepth() const;

	// Return the dimension of the object (0, 1 or 2)
	virtual int dim() const = 0;

	// Translate the object horizontally by x and vertically by y
	virtual void translate(float x, float y) = 0;

	// Rotate the object 90 degrees around its centre
	virtual void rotate() = 0;

	// Scale the object by a factor f relative to its centre.
	// If f is zero or negative, throw a std::invalid-argument exception.
	virtual void scale(float f) = 0;

	// Return true if the object contains p and false otherwise.
	// Depths are ignored for purpose of comparison
	virtual bool contains(const Point& p) const = 0;

	// the constant pi
	static constexpr double PI = 3.1415926;
	

protected:
	int dimension;
private:
	// add any protected/private member variables you need
	int depth;
};

class Point : public Shape {

public:
	// Constructor. Depth defaults to 0
	Point(float x, float y, int d=0);

	// Return basic information (see assignment page)
	float getX() const;
	float getY() const;
	int dim() const;
	void translate(float x, float y);
	void rotate();
	void scale(float f);
	bool contains(const Point& p) const;

private:
	// add any member variables you need
	float x_Coordinate;
	float y_Coordinate;
	int _dim;
};

class LineSegment : public Shape {

public:
	// Constructor.
	// If the two points have different depths, or have the same x- and
	// y-coordinate, or if the line is not axis-aligned, throw a
	// std::invalid_argument exception
	LineSegment(const Point& p, const Point& q);

	// Return basic information (see assignment page)
	float getXmin() const;
	float getXmax() const;
	float getYmin() const;
	float getYmax() const;

	// Return the length of the line segment
	float length() const;
	int dim() const;
	void translate(float x, float y);
	void rotate();
	void scale(float f);
	bool contains(const Point& p) const;

private:
	// add any member variables you need
	float x_coordinate1;
	float x_coordinate2;
	float y_coordinate1;
	float y_coordinate2;
	float depth1, depth2;
	float lengthLine;

};

class TwoDShape : public Shape {

public:
	// Default constructor.
	// Similar comment to Student default constructor applies
	TwoDShape();

	// Constructor specifying the depth d
	TwoDShape(int d);

	// Return the area of the object
	virtual float area() const = 0;

protected:
private:
	// add any protected/private member variables you need
	int depth;
};

class Rectangle : public TwoDShape {

public:
	// Constructor.
	// If the two points have different depths, or have the same x-
	// and/or y-coordinate, throw a std::invalid_argument exception
	Rectangle(const Point& p, const Point& q);

	// Return basic information (see assignment page)
	float getXmin() const;
	float getYmin() const;
	float getXmax() const;
	float getYmax() const;
	float area() const;
	void translate(float a, float b);
	void rotate();
	void scale(float f);
	bool contains(const Point& p) const;
	int dim() const;
	
private:
	// add any member variables you need
	float x_coordinate1;
	float x_coordinate2;
	float y_coordinate1;
	float y_coordinate2;
};

class Circle : public TwoDShape {

public:
	// Constructor.
	// If r is zero or negative, throw a std::invalid-argument exception.
	Circle(const Point& c, float r);

	// Return basic information (see assignment page)
	float getX() const;
	float getY() const;
	float getR() const;
	float area() const;
	void translate(float a, float b);	
	void rotate();
	void scale(float f);
	bool contains(const Point& p) const;
	int dim() const;
private:
	// add any member variables you need
	float x_coordinate;
	float y_coordinate;
	float radius;
};

class Scene {

public:
	// Constructor
	Scene();

	// Add the pointer to the collection of pointers stored
	void addObject(std::shared_ptr<Shape> ptr);

	// Set the drawing depth to d
	void setDrawDepth(int d);

	// Constants specifying the size of the drawing area
	static constexpr int WIDTH = 60;
	static constexpr int HEIGHT = 20;

private:	
	// add any member variables you need
	int finalDepth = 999;
	std::vector<std::shared_ptr<Shape>> sceneObj;

	// Draw objects as specified in the assignment page
friend std::ostream& operator<<(std::ostream& out, const Scene& s);
};

#endif /* GEOMETRY_H_ */