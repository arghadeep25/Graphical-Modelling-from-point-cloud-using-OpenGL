#pragma once

#include <vector>
#include "Point.h"
using namespace std;

class LineString
{
public:
	vector<Point> points;

	LineString();
	~LineString();
};

LineString::LineString()
{}

LineString:: ~LineString()
{}

