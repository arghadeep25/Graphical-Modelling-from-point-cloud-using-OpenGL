#pragma once
#include"Point.h"
#include<vector> 
#include"Contour.h"

using namespace std;

class Poly
{
public:

	Contour outer_contour;
	vector<Contour> inner_contour;

	Poly();
	~Poly();
};

Poly::Poly()
{}

Poly:: ~Poly()
{}


