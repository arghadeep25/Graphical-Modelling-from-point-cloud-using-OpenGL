//Class wkTReader is defined in this header file where the functions for Reading Points, Line and Polygon from
//given text files has been declared. 
#pragma once
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>
#include "Point.h"
#include "LineString.h"
#include"Poly.h"

using namespace std;

class wktReader
{
public:	
	wktReader(); 
	~wktReader(); 

	vector<Point*> ReadPointsFile(const string path);
	vector<LineString*> ReadLineFile(const string path);
	vector<Poly*> ReadPolygonFile(const string path);

	vector<string> Split(const string &s, const string &delim);
};

wktReader::wktReader()
{}

wktReader:: ~wktReader()
{}

//Function for reading points from file has been declared
vector<Point*> wktReader::ReadPointsFile(string path)
{
	vector<Point*> result; //container for Point pointers
	double x, y; //point coordinates

	ifstream file(path, ios::in); //open file with the given path, to read-in only

	while (file && !file.eof()) //if such a file exists and till it's not the end-of-file
	{
		file.ignore(100, '(');   // ignore until bracket
		file >> x >> y; //read in double x and double y
						//cout << x << " "<< y << endl; //line not needed - only to check if reading was ok
		result.push_back(new Point(x, y)); //create a point and put it into a container
	}
	result.pop_back(); //the last line is readed twice, so you must delete the last point

	return result;
}

//Function for reading Line from file has been declared
vector<LineString*> wktReader::ReadLineFile(string path)
{
	vector<LineString*> result; //container 
	double x, y; //point coordinates
	char one;

	ifstream file(path, ios::in); //open file with the given path, to read-in only

	while (file && !file.eof()) //if such a file exists and till it's not the end-of-file
	{
		file.ignore(100, '(');   // ignore until bracket
		LineString* temp_line = new LineString;

		file >> x >> y >> one; //read in double x and double y
		temp_line->points.push_back(Point(x, y));

		while (one != ')')
		{
			file >> x >> y >> one;
			temp_line->points.push_back(Point(x, y));
		}

		result.push_back(temp_line); //push a line into a container
	}

	result.pop_back();

	return result;
}

//Function for reading polygons from file has been declared
vector<Poly*> wktReader::ReadPolygonFile(const string path)
{
	vector<Poly*> result;
	ifstream file(path, ios::in);

	while (file && !file.eof())
	{
		string polygon_line;
		getline(file, polygon_line);
		if (!polygon_line.empty())
		{
			Poly* temp_polygon = new Poly;

			polygon_line = polygon_line.substr(10, polygon_line.size() - 12);

			vector<string> contours = Split(polygon_line, "), (");


			vector<string> coordinate_pairs = Split(contours[0], ", ");
			for (int j = 0; j < coordinate_pairs.size(); j++)
			{
				vector<string> xy = Split(coordinate_pairs[j], " ");
				Point p(atof(xy[0].c_str()), atof(xy[1].c_str()));
				temp_polygon->outer_contour.points.push_back(p);
			}

			if (contours.size() > 1)
			{
				for (int i = 1; i < contours.size(); i++)
				{
					Contour temp_contour;
					vector<string> coordinate_pairs = Split(contours[i], ", ");
					for (int j = 0; j < coordinate_pairs.size(); j++)
					{
						vector<string> xy = Split(coordinate_pairs[j], " ");
						Point p(atof(xy[0].c_str()), atof(xy[1].c_str()));
						temp_contour.points.push_back(p);
					}
					temp_polygon->inner_contour.push_back(temp_contour);
				}
			}

			result.push_back(temp_polygon);
		}
	}


	return result;
}


vector<string> wktReader::Split(const string &s, const string &delim)
{
	vector<string> result;
	if (delim.empty())
	{
		result.push_back(s);
		return result;
	}
	string::const_iterator substart = s.begin(), subend;
	while (true) {
		subend = search(substart, s.end(), delim.begin(), delim.end());
		string temp(substart, subend);
		if (!temp.empty()) {
			result.push_back(temp);
		}
		if (subend == s.end()) {
			break;
		}
		substart = subend + delim.size();
	}
	return result;
}

