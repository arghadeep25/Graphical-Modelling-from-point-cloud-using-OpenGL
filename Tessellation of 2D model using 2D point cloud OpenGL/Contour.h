#pragma once
#include"Point.h"
#include<vector> 

using namespace std;

class Contour
{
public:
	
	vector<Point> points;
	Contour();
	~Contour();
};

Contour::Contour()
{}

Contour:: ~Contour()
{}


