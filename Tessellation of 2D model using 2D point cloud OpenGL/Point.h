#pragma once
using namespace std;

class Point
{
public:
	double x, y;


	Point(double my_x, double my_y);   //constructor
	Point(); // again, different contructor - empty member variables
	~Point(); //destructor

};

Point::Point(double my_x, double my_y)
	:x(my_x), y(my_y)
{}

Point::Point()
{}
Point:: ~Point()
{}


