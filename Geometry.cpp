#include "Geometry.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <sstream>
#include <memory>

using namespace std;
// ============ Shape class =================

Shape::Shape() {}

Shape::Shape(int d) {
	if(d<0) throw std::invalid_argument("Depth should not be negetive");
	else setDepth(d);
}

bool Shape::setDepth(int d) {
	if(d>=0){
		depth = d;
		return true;
	} else {
		return false;
	}
}

int Shape::getDepth() const {
	return depth;
}

// =============== Point class ================

Point::Point(float x, float y, int d) : Shape(d) {
	x_Coordinate = x;
	y_Coordinate = y;
	dimension = 0;
	// if(d>=0) setDepth(d);
}

float Point::getX() const {
	return x_Coordinate; 
}

float Point::getY() const {
	return y_Coordinate; 
}

int Point::dim() const {
	return dimension;
}

void Point::translate(float x, float y) {
	x_Coordinate = x_Coordinate + x;
	y_Coordinate = y_Coordinate + y;
}

bool Point::contains(const Point& p) const{
	if(x_Coordinate == p.getX() &&	y_Coordinate == p.getY()) return true;
	else return false;
}

void Point::rotate() {}

void Point::scale(float f) {
	if(f<=0) throw std::invalid_argument("Invalid scaling");
}

// =========== LineSegment class ==============

LineSegment::LineSegment(const Point& p, const Point& q) {
	x_coordinate1 = p.getX();
	x_coordinate2 = q.getX();
	y_coordinate1 = p.getY();
	y_coordinate2 = q.getY();
	depth1 = p.getDepth();
	depth2 = q.getDepth();
	dimension = 1;
	if((x_coordinate1 != x_coordinate2 && y_coordinate1 != y_coordinate2) || 
		(x_coordinate1 == x_coordinate2 && y_coordinate1 == y_coordinate2)) {
		throw std::invalid_argument("Line segment cannot be formed");
	}
	if(depth1 == depth2) {
		setDepth(depth1);
	} else {
		throw std::invalid_argument("Invalid depths");
	}
}

float LineSegment::getXmin() const {
	return std::min(x_coordinate1, x_coordinate2);
}

float LineSegment::getXmax() const {
	return std::max(x_coordinate1, x_coordinate2);
}

float LineSegment::getYmin() const {
	return std::min(y_coordinate1, y_coordinate2);
}

float LineSegment::getYmax() const {
	return std::max(y_coordinate1, y_coordinate2);
}

float LineSegment::length() const {
	int length;
	if(x_coordinate1 == x_coordinate2 || y_coordinate1 == y_coordinate2) {
		length = sqrt(pow((x_coordinate1-x_coordinate2),2) + pow((y_coordinate1-y_coordinate2),2));
	}
	return length;
}

int LineSegment::dim() const {
	return dimension;
}

void LineSegment::translate(float x, float y) {
	x_coordinate1 = x_coordinate1 + x;
	x_coordinate2 = x_coordinate2 + x;
	y_coordinate1 = y_coordinate1 + y;
	y_coordinate2 = y_coordinate2 + y;
}

void LineSegment::rotate() {
	float cx = (x_coordinate1 + x_coordinate2) /2;
	float cy = (y_coordinate1 + y_coordinate2) /2;
	float tx1 = x_coordinate1, tx2 = x_coordinate2, ty1 = y_coordinate1, ty2 = y_coordinate2;

	if(tx1 == tx2) {
		float len = length(), temp = x_coordinate1;
		x_coordinate1 = temp + (len/2);
		y_coordinate1 = cy;
		x_coordinate2 = temp - (len/2);
		y_coordinate2 = cy;
	}
	if(ty1 == ty2) {
		float len = length(), temp = y_coordinate1;
		x_coordinate1 = cx;
		y_coordinate1 = temp + (len/2);
		x_coordinate2 = cx;
		y_coordinate2 = temp - (len/2);
	}
}

bool LineSegment::contains(const Point& p) const{
	if((x_coordinate1 == x_coordinate2 && x_coordinate1 == p.getX() && (p.getY() >= getYmin()) && (p.getY() <= getYmax())) || 
		y_coordinate1 == y_coordinate2 && y_coordinate1 == p.getY() && (p.getX() >= getXmin()) && (p.getX() <= getXmax())) {
		return true;
	} else {
		return false;
	}
}

void LineSegment::scale(float f) {
	if(f<=0) {
		throw std::invalid_argument("Saling value should be greater than 0");
	} else {
		int fixedLen = length();
		float newLen = length() * f;
		float newx, newY;
		newx = (getXmin() + getXmax())/2;
		newY = (getYmin() + getYmax())/2;
		if(x_coordinate1 == x_coordinate2) {
			y_coordinate1 = newY - (newLen/2);
			y_coordinate2 = newY + (newLen/2);
		} else if(y_coordinate1 == y_coordinate2) {
			x_coordinate1 = newx - (newLen/2);
			x_coordinate2 = newx + (newLen/2);
		}
	}
}

// ============ TwoDShape class ================

TwoDShape::TwoDShape(){}

TwoDShape::TwoDShape(int d) {
	depth = d;
}

// ============== Rectangle class ================

Rectangle::Rectangle(const Point& p, const Point& q) {
	if(p.getDepth() == q.getDepth() && (p.getX() != q.getX()) && (p.getY() != q.getY())) {
		x_coordinate1 = p.getX();
		x_coordinate2 = q.getX();
		y_coordinate1 = p.getY();
		y_coordinate2 = q.getY();
		setDepth(p.getDepth());	
		dimension = 2;
	} else {
		throw std::invalid_argument("Points do not have the same depth");
	}	
}

float Rectangle::getXmin() const {
	return std::min(x_coordinate1, x_coordinate2);
}

float Rectangle::getYmin() const {
	return std::min(y_coordinate1, y_coordinate2);
}

float Rectangle::getXmax() const {
	return std::max(x_coordinate1, x_coordinate2);
}

float Rectangle::getYmax() const {
	return std::max(y_coordinate1, y_coordinate2);
}

float Rectangle::area() const{
	float length, breadth, x1, x2, y1, y2;
	if(getXmin() == getXmax() || getYmin() == getYmax()) return 0;
	else {
		length = sqrt(pow((x_coordinate1-x_coordinate2),2) + pow((y_coordinate1-y_coordinate1),2));
		breadth = sqrt(pow((x_coordinate1-x_coordinate1),2) + pow((y_coordinate1-y_coordinate2),2));
	}
	return length*breadth;
}

void Rectangle::translate(float x, float y) {
	x_coordinate1 = x_coordinate1 + x;
	x_coordinate2 = x_coordinate2 + x;
	y_coordinate1 = y_coordinate1 + y;
	y_coordinate2 = y_coordinate2 + y;
}

void Rectangle::rotate() {
	float x1 = getXmin(), x2 = getXmax(), y1 = getYmin(), y2 = getYmax(), newX, newY;
	Point p1(x1, y2);
	Point p2(x2, y2);
	LineSegment top(p1,p2);
	float topLength = top.length(); 

	Point p3(x2, y1);
	LineSegment right(p2, p3);
	float rightLength = right.length();

	newX = (x1+x2)/2; 
	newY = (y1+y2)/2;

	x_coordinate1 = (newX - (rightLength/2));
	x_coordinate2 = (newX + (rightLength/2));

	y_coordinate1 = (newY - (topLength/2));
	y_coordinate2 = (newY + (topLength/2));

}

void Rectangle::scale(float f) {
	if(f<=0) {
		throw std::invalid_argument("Saling value should be greater than 0");
	} else {
		float x1 = getXmin(), x2 = getXmax(), y1 = getYmin(), y2 = getYmax();
		Point p1(x1, y2);
		Point p2(x2, y2);
		LineSegment top(p1,p2);
		top.scale(f);

		x_coordinate1 = top.getXmin(); 
		x_coordinate2 = top.getXmax();

		Point p3(x2, y1); 
		LineSegment right(p2,p3);
		right.scale(f);

		y_coordinate1 = right.getYmax();
		y_coordinate2 = right.getYmin();

	}
}

bool Rectangle::contains(const Point& p) const{
	if(getXmin() <= p.getX() && getXmax() >= p.getX() && getYmax() >= p.getY() && getYmin() <= p.getY()) {
		return true;
	}
	else return false;
}

int Rectangle::dim() const {
	return dimension;
}

// ================== Circle class ===================

Circle::Circle(const Point& c, float r) {
	if(r>0) {
		x_coordinate = c.getX();
		y_coordinate = c.getY();
		setDepth(c.getDepth());
		radius = r;
		dimension = 2;
	} else {
		throw std::invalid_argument("Invalid radius");
	}
	
}

float Circle::getX() const {
	return x_coordinate;
}

float Circle::getY() const {
	return y_coordinate;
}

float Circle::getR() const {
	return radius;
}

float Circle:: area() const {
	return PI*getR()*getR();
}

void Circle::translate(float x, float y) {
	x_coordinate = x_coordinate + x;
	y_coordinate = y_coordinate + y;
}

void Circle::scale(float f) {
	if(f<=0) throw std::invalid_argument("Saling value should be greater than 0");
	else radius = radius * f;
}

bool Circle::contains(const Point& p) const {
	if (pow((p.getX() - getX()), 2) + pow((p.getY() - getY()), 2) <= pow((getR()), 2)) {
		return true;
	}
	else return false;
}

int Circle::dim() const {
	return dimension;
}

void Circle::rotate() {}

// ================= Scene class ===================

Scene::Scene() {}

void Scene::addObject(std::shared_ptr<Shape> ptr) {	
	sceneObj.push_back(ptr);
}

void Scene::setDrawDepth(int depth) {
	finalDepth = depth;
}

std::ostream& operator<<(std::ostream& out, const Scene& s) {
	vector <Point> allPoints;
	const Scene *p = &s;
	if(p->sceneObj.size() != 0) {
		for(int i = p->HEIGHT-1 ; i >= 0; i--) {
			for(int j = 0; j <p->WIDTH; j++) {
				Point p1(j,i);
				for(int k = 0; k < p->sceneObj.size(); k++) {
					if(p->sceneObj.at(k).get()->contains(p1) && (s.finalDepth >= (p->sceneObj.at(k).get()->getDepth()))) {
						allPoints.push_back(p1);
						break;
					}
				}				
			}
		}
	}
	if(p->sceneObj.size() != 0 && allPoints.size()) {
		for(int i = p->HEIGHT-1 ; i >= 0; i--) {
			for(int j = 0; j <p->WIDTH; j++) {
				for (int k = 0; k < allPoints.size(); k++) {
					float x = allPoints[k].getX();
					float y = allPoints[k].getY();
					if(x == j && y == i) {
						out << "*"; 
						if(k != (allPoints.size()-1)) allPoints.erase( allPoints.begin() + k );		
						break;
					} else {
						out << " ";
						break;
					}
				}
			} 
			out << "\n";
		}
	} else {
		string blankline(Scene::WIDTH, ' '), blankpage_;
			for(int i=0;i<Scene::HEIGHT;i++) blankpage_ += (blankline + "\n");
		string page = blankpage_;
		out << page;
	}
	return out;
}
