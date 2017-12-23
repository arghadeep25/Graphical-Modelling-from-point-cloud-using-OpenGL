#include<iostream>
#include <windows.h>
#include<vector>
#include <gl/gl.h>
#include "glut.h"
#include "Point.h"
#include "LineString.h"
#include "wktReader.h"
#include"Contour.h"
#include"Poly.h"


//Declaring Points
vector<Point*> points_of_interest;
vector<Point*> stations;
vector<Point*> traffic;

//Declaring Lines
vector<LineString*> railways;
vector<LineString*> roads;

//Declaring Polygons
vector<Poly*> water;
vector<Poly*> land_use;
vector<Poly*> buildings;

//For Drawing Point Features
void DrawPointFeatures() {
for (int i = 0; i < points_of_interest.size(); i++) { //Drawing Points of Interest
		glPointSize(2.0f);
		glColor3f(0.133f, 0.545f, 0.133f);
		glBegin(GL_POINTS);
		glVertex2f(points_of_interest[i]->x, points_of_interest[i]->y);
		}
	glEnd();

	for (int j = 0; j < stations.size(); j++) { //Drawing Stations
		glPointSize(2.0f);
		glColor3f(0.0f, 1.0f, 1.0f);
		glBegin(GL_POINTS);
		glVertex2f(stations[j]->x, stations[j]->y);
	}
	glEnd();

	for (int k = 0; k < traffic.size(); k++) { //Drawing Traffic Points
		glPointSize(3.0f);
		glColor3f(1.0f, 0.0f, 0.0f);
		glBegin(GL_POINTS);
		glVertex2f(traffic[k]->x, traffic[k]->y);
		
	}
	glEnd();
}

//Function for Drawing Lines
void DrawLinearFeatures() {
	for (int i = 0; i < railways.size(); i++) { //Drawing Railway Lines
		for (int j = 0; j < railways[i]->points.size(); j++) {
			glLineWidth(1.0f);
			glColor3f(0.184f, 0.310f, 0.310f);
			glBegin(GL_LINE_STRIP);
			glVertex2f(railways[i]->points[j].x, railways[i]->points[j].y);
		}
		glEnd();
	}

	for (int i = 0; i < roads.size(); i++) { //Drawing Roads
		for (int j = 0; j < roads[i]->points.size(); j++) {
			glLineWidth(1.0f);
			glColor3f(0.412f, 0.412f, 0.412f);
			glBegin(GL_LINE_STRIP);
			glVertex2f(roads[i]->points[j].x, roads[i]->points[j].y);

		}
		glEnd();
	}
}

//Function for Drawing Polygons
void DrawPolygonFeatures() {
	
	for (int i = 0;i < water.size();i++) {
		for (int j = 0;j < water[i]->outer_contour.points.size();j++) {
			glBegin(GL_LINE_STRIP);
			glColor3f(0.275f, 0.510f, 0.706f); //Steel Blue
			glVertex2f(water[i]->outer_contour.points[j].x, water[i]->outer_contour.points[j].y);
		}
		glEnd();
	}


	/*//Land Use
	for (int i = 0;i < land_use.size();i++) {
		for (int j = 0;j < land_use[i]->outer_contour.points.size();j++) {
			glBegin(GL_LINE_STRIP);
			glColor3f(0.647f, 0.165f, 0.165f);
			glVertex2f(land_use[i]->outer_contour.points[j].x, land_use[i]->outer_contour.points[j].y);
		}
		glEnd();
	}
	//BUILDINGS
	for (int i = 0;i < buildings.size();i++) {
		for (int j = 0;j < buildings[i]->outer_contour.points.size();j++) {
			glBegin(GL_LINE_STRIP);
			glColor3f(0.867f, 0.627f, 0.867f); //Peru
			glVertex2f(buildings[i]->outer_contour.points[j].x, buildings[i]->outer_contour.points[j].y);
		}
		glEnd();
	}*/
}

//Function for Switching Between the Layers
void disp() {
	char c;
	cout << "Enter any of the followings" << endl;
	cout << "Press 'p' or 'P' for Point Features" << endl;
	cout << "Press 'l' or 'L' for Line Feature" << endl;
	cout << "Press 'o' or 'O' for Polygon Feature" << endl;
	cout << "Press 'a' or 'A' to get all features ";
	cin >> c;
	if (c == 'p' || c == 'P') {
		DrawPointFeatures();
	}
	if (c == 'l' || c == 'L') {
		DrawLinearFeatures();
	}
	if (c == 'o' || c == 'O') {
		DrawPolygonFeatures();
	}
	if (c == 'a' || c == 'A') {
		DrawPointFeatures();
		DrawLinearFeatures();
		DrawPolygonFeatures();
	}
	/*else {
		cout << "Please Enter Valid Key";
	}*/
}

//Function for Rendering Scene
void RenderScene(void) 
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f); 
	glClear(GL_COLOR_BUFFER_BIT); 

	glTranslatef(-13.334, -52.511, 0); 
	
	disp(); //Calling Display Function
	
	glFlush(); 
}

void ChangeSize(GLsizei width, GLsizei height) 
{
	if (height == 0) 
		height = 1;

	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity(); 

	GLfloat AspectRatio; 
	AspectRatio = (GLfloat)width / (GLfloat)height;

	GLfloat multiple = 0.015;

	if (width <= height)
		gluOrtho2D(-1.0*multiple, 1.0*multiple, -1.0 / AspectRatio *multiple, 1.0 / AspectRatio*multiple);
	else
		gluOrtho2D(-1.0*AspectRatio*multiple, 1.0*AspectRatio*multiple, -1.0*multiple, 1.0*multiple);

	glViewport(0, 0, width, height); 
}

void main(void)
{

	wktReader wkt;
	
	//Loading Point Files
	points_of_interest = wkt.ReadPointsFile("C:\\Users\\Arghadeep\\Documents\\Visual Studio 2015\\Projects\\Geoviz Assgn 2\\Geoviz1\\points_of_interest.txt");
	stations = wkt.ReadPointsFile("C:\\Users\\Arghadeep\\Documents\\Visual Studio 2015\\Projects\\Geoviz Assgn 2\\Geoviz1\\stations.txt");
	traffic = wkt.ReadPointsFile("C:\\Users\\Arghadeep\\Documents\\Visual Studio 2015\\Projects\\Geoviz Assgn 2\\Geoviz1\\traffic_points.txt");
	
	//Loading Line Files
	railways = wkt.ReadLineFile("C:\\Users\\Arghadeep\\Documents\\Visual Studio 2015\\Projects\\Geoviz Assgn 2\\Geoviz1\\railways.txt");
	roads = wkt.ReadLineFile("C:\\Users\\Arghadeep\\Documents\\Visual Studio 2015\\Projects\\Geoviz Assgn 2\\Geoviz1\\roads.txt");
	
	//Loading Polygon Files
	water = wkt.ReadPolygonFile("C:\\Users\\Arghadeep\\Documents\\Visual Studio 2015\\Projects\\Geoviz Assgn 2\\Geoviz1\\water.txt");
	land_use = wkt.ReadPolygonFile("C:\\Users\\Arghadeep\\Documents\\Visual Studio 2015\\Projects\\Geoviz Assgn 2\\Geoviz1\\land_use.txt");
	buildings = wkt.ReadPolygonFile("C:\\Users\\Arghadeep\\Documents\\Visual Studio 2015\\Projects\\Geoviz Assgn 2\\Geoviz1\\buildings.txt");

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(1200, 800);
	glutCreateWindow("2D City");
	glutDisplayFunc(RenderScene);

	glutReshapeFunc(ChangeSize);
	glutMainLoop();

	system("PAUSE");
}

	

