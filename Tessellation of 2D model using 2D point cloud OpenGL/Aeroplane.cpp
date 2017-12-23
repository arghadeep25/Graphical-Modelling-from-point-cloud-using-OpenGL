#include <Windows.h>
#include <gl/gl.h>
#include "glut.h"
#include "Poly.h"
#include <iostream>
using namespace std;

void ChangSize(GLsizei width, GLsizei height);
void RenderScene(void);

Poly Create_Aeroplane();
void Drawaeroplane();

Poly aeroplane;
vector<Point> tess_pts;


void CALLBACK beginCallback(GLenum which); //Begin of Tessellation
void CALLBACK endCallback(void); //End of Tessellation
void CALLBACK vertexCallback(void * vertex_data); //Output of Tessellation that should be sorted
void CALLBACK TessEdgeFlagCallback(GLboolean flag); // Flag that force tessellation to give triangles as output

vector<Point> tessellate(Poly* p); 

void DrawTesselated(); // Declaration of Tessellation function

float x_axis = 0;
float y_axis = 0;
float angle = 0;
void input_rot(unsigned char c, int x, int y)
{
	if (c == 'l' || c == 'L') angle = angle + 1;  //Rotate left
	if (c == 'r' || c == 'R') angle = angle - 1; //Rotate right
	RenderScene();
}

void input_trans(int c, int x, int y)
{
	if (c == GLUT_KEY_LEFT) x_axis = x_axis - 1;  // Translate left
	if (c == GLUT_KEY_RIGHT) x_axis = x_axis + 1; // Translate right
	if (c == GLUT_KEY_UP) y_axis = y_axis+1; // Translate up
	if (c == GLUT_KEY_DOWN) y_axis = y_axis-1; // Translate down
	RenderScene();
}


void main(void)
{
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowPosition(200, 50);
	glutInitWindowSize(720, 720);
	glutCreateWindow("Aeroplane");
	aeroplane = Create_Aeroplane();
	tessellate(&aeroplane);
	glutKeyboardFunc(input_rot);
	glutSpecialFunc(input_trans);
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangSize);
	glutMainLoop();
	system("PAUSE");
}
	

//Function impementation
void ChangSize(GLsizei width, GLsizei height)
{
	if (height == 0)
		height = 1;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	GLfloat AspectRatio = (GLfloat)width / (GLfloat)height;

	GLfloat multiple = 5;

	if (width <= height)
		gluOrtho2D(-1.0*multiple, 1.0*multiple, -1.0 / AspectRatio*multiple, 1.0 / AspectRatio*multiple);
	else
		gluOrtho2D(-1.0*AspectRatio*multiple, 1.0*AspectRatio*multiple, -1.0*multiple, 1.0*multiple);

	glViewport(0, 0, width, height);
}

void RenderScene(void)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	DrawTesselated();
	glFlush();
}

Poly Create_Aeroplane() {
	Poly p;
	// Exterior co-ordinates for Aeroplane
	p.outer_contour.points.push_back(Point(0.011210513812000, 3.011903684610000));
	p.outer_contour.points.push_back(Point(0.205714758412000, 2.708287302800000));
	p.outer_contour.points.push_back(Point(0.312454892643000, 2.452110980640000));
	p.outer_contour.points.push_back(Point(0.329058913524000, 2.238630712180000));
	p.outer_contour.points.push_back(Point(0.332748695942000, 2.093279640500000));
	p.outer_contour.points.push_back(Point(0.331870176318000, 1.327122677020000));
	p.outer_contour.points.push_back(Point(0.338986185267000, 0.938114187819000));
	p.outer_contour.points.push_back(Point(0.338986185267000, 0.748353949185000));
	p.outer_contour.points.push_back(Point(0.863198844493000, 0.482689615098000));
	p.outer_contour.points.push_back(Point(0.864834229362000, 0.495978854466000));
	p.outer_contour.points.push_back(Point(0.813611473541000, 0.537069636609000));
	p.outer_contour.points.push_back(Point(0.800665062729000, 0.586040842724000));
	p.outer_contour.points.push_back(Point(0.797259941259000, 0.875170401633000));
	p.outer_contour.points.push_back(Point(0.802596947970000, 0.936545978816000));
	p.outer_contour.points.push_back(Point(0.814605213072000, 0.984579039220000));
	p.outer_contour.points.push_back(Point(0.845293001663000, 1.004592814390000));
	p.outer_contour.points.push_back(Point(1.129488609050000, 1.004592814390000));
	p.outer_contour.points.push_back(Point(1.160176397650000, 0.960562509018000));
	p.outer_contour.points.push_back(Point(1.156173642610000, 0.576298025784000));
	p.outer_contour.points.push_back(Point(1.142831125830000, 0.518925203635000));
	p.outer_contour.points.push_back(Point(1.114811840600000, 0.472226394908000));
	p.outer_contour.points.push_back(Point(1.065444528520000, 0.461552381485000));
	p.outer_contour.points.push_back(Point(1.061441773480000, 0.386834287523000));
	p.outer_contour.points.push_back(Point(2.785844016090000, -0.488669085075000));
	p.outer_contour.points.push_back(Point(2.775708095930000, -0.818559723889000));
	p.outer_contour.points.push_back(Point(2.764572393210000, -0.851603300599000));
	p.outer_contour.points.push_back(Point(2.738609210660000, -0.870600751247000));
	p.outer_contour.points.push_back(Point(2.259326202660000, -0.722604356394000));
	p.outer_contour.points.push_back(Point(2.241980930840000, -0.758629151697000));
	p.outer_contour.points.push_back(Point(2.229972665740000, -0.785314185255000));
	p.outer_contour.points.push_back(Point(1.662350155630000, -0.610329548535000));
	p.outer_contour.points.push_back(Point(1.026653356210000, -0.407918627326000));
	p.outer_contour.points.push_back(Point(1.039304038780000, -0.363641238311000));
	p.outer_contour.points.push_back(Point(0.378305874208000, -0.363641238311000));
	p.outer_contour.points.push_back(Point(0.365980569271000, -1.235002553570000));
	p.outer_contour.points.push_back(Point(0.342084835517000, -1.618739925030000));
	p.outer_contour.points.push_back(Point(0.308349681982000, -1.894243678900000));
	p.outer_contour.points.push_back(Point(0.268992002858000, -2.085409548930000));
	p.outer_contour.points.push_back(Point(0.235256849323000, -2.203482586310000));
	p.outer_contour.points.push_back(Point(0.378959883261000, -2.293883068990000));
	p.outer_contour.points.push_back(Point(0.518117391593000, -2.386654741210000));
	p.outer_contour.points.push_back(Point(0.653058005733000, -2.470992625050000));
	p.outer_contour.points.push_back(Point(0.821733773407000, -2.589065662420000));
	p.outer_contour.points.push_back(Point(0.944023704971000, -2.677620440450000));
	p.outer_contour.points.push_back(Point(0.927156128204000, -2.783042795240000));
	p.outer_contour.points.push_back(Point(0.910288551436000, -2.871597573270000));
	p.outer_contour.points.push_back(Point(0.543418756744000, -2.791476583630000));
	p.outer_contour.points.push_back(Point(0.125946231750000, -2.702921805600000));
	p.outer_contour.points.push_back(Point(-0.004085653994870, -2.987968822050000));
	p.outer_contour.points.push_back(Point(-0.078803747957000, -2.813181852240000));
	p.outer_contour.points.push_back(Point(-0.108157284871000, -2.703773214660000));
	p.outer_contour.points.push_back(Point(-0.410208803606000, -2.766038292960000));
	p.outer_contour.points.push_back(Point(-0.653734443186000, -2.819803693900000));
	p.outer_contour.points.push_back(Point(-0.913073435986000, -2.867243753560000));
	p.outer_contour.points.push_back(Point(-0.941537471781000, -2.680646185570000));
	p.outer_contour.points.push_back(Point(-0.758102574435000, -2.541488677240000));
	p.outer_contour.points.push_back(Point(-0.492438240347000, -2.370704462470000));
	p.outer_contour.points.push_back(Point(-0.233099247548000, -2.218896271560000));
	p.outer_contour.points.push_back(Point(-0.290027319138000, -1.969045290700000));
	p.outer_contour.points.push_back(Point(-0.334304708152000, -1.687567603390000));
	p.outer_contour.points.push_back(Point(-0.350118061372000, -1.336511161920000));
	p.outer_contour.points.push_back(Point(-0.359606073303000, -1.001268073660000));
	p.outer_contour.points.push_back(Point(-0.362768743947000, -0.362408603595000));
	p.outer_contour.points.push_back(Point(-1.030092249810000, -0.356083262307000));
	p.outer_contour.points.push_back(Point(-1.026929579170000, -0.409848663253000));
	p.outer_contour.points.push_back(Point(-2.222419082560000, -0.767230446014000));
	p.outer_contour.points.push_back(Point(-2.241395106420000, -0.713465045068000));
	p.outer_contour.points.push_back(Point(-2.737934397510000, -0.862110565331000));
	p.outer_contour.points.push_back(Point(-2.769561103950000, -0.824158517604000));
	p.outer_contour.points.push_back(Point(-2.798025139750000, -0.511054123858000));
	p.outer_contour.points.push_back(Point(-2.763235762670000, -0.473102076131000));
	p.outer_contour.points.push_back(Point(-1.055393614960000, 0.383981668365000));
	p.outer_contour.points.push_back(Point(-1.052712757420000, 0.461880964244000));
	p.outer_contour.points.push_back(Point(-1.097743751550000, 0.466884408036000));
	p.outer_contour.points.push_back(Point(-1.130766480580000, 0.504910580856000));
	p.outer_contour.points.push_back(Point(-1.141774056920000, 0.562950528845000));
	p.outer_contour.points.push_back(Point(-1.154783010780000, 0.657015272136000));
	p.outer_contour.points.push_back(Point(-1.152781633270000, 0.955220522146000));
	p.outer_contour.points.push_back(Point(-1.134769235610000, 0.998250138758000));
	p.outer_contour.points.push_back(Point(-1.103747884100000, 1.014261158890000));
	p.outer_contour.points.push_back(Point(-0.848572250705000, 1.014261158890000));
	p.outer_contour.points.push_back(Point(-0.808544700368000, 0.990244628690000));
	p.outer_contour.points.push_back(Point(-0.792533680234000, 0.942211568286000));
	p.outer_contour.points.push_back(Point(-0.792533680234000, 0.602978079182000));
	p.outer_contour.points.push_back(Point(-0.804541945335000, 0.548940886227000));
	p.outer_contour.points.push_back(Point(-0.860580515806000, 0.499907137064000));
	p.outer_contour.points.push_back(Point(-0.855577072014000, 0.484896805688000));
	p.outer_contour.points.push_back(Point(-0.772519905065000, 0.525925044783000));
	p.outer_contour.points.push_back(Point(-0.332550414279000, 0.744408757038000));
	p.outer_contour.points.push_back(Point(-0.318099109648000, 1.357614767760000));
	p.outer_contour.points.push_back(Point(-0.318099109648000, 1.846247382240000));
	p.outer_contour.points.push_back(Point(-0.308611097716000, 2.230511865480000));
	p.outer_contour.points.push_back(Point(-0.292007076836000, 2.421062771770000));
	p.outer_contour.points.push_back(Point(-0.247729687821000, 2.585521645260000));
	p.outer_contour.points.push_back(Point(-0.190801616231000, 2.705703129720000));
	p.outer_contour.points.push_back(Point(-0.105409508846000, 2.848023308700000));
	p.outer_contour.points.push_back(Point(-0.042156095967800, 2.949228769300000));
	p.outer_contour.points.push_back(Point(0.011210513812000, 3.011903684610000));
	p.outer_contour.points.push_back(Point(0.011210513812000, 3.011903684610000));

	
	/*Contour win1;
	win1.points.push_back(Point(-0.295142488563000, 2.178645236280000));
	win1.points.push_back(Point(-0.292473985207000, 2.091918877220000));
	win1.points.push_back(Point(-0.251112183192000, 2.175976732930000));
	win1.points.push_back(Point(-0.251112183192000, 2.089250373860000));
	win1.points.push_back(Point(-0.295142488563000, 2.178645236280000));
	p.inner_contours.push_back(win1);

	Contour win2;
	win2.points.push_back(Point(-0.295142488563000, 2.017200783260000));
	win2.points.push_back(Point(-0.251112183192000, 2.014532279900000));
	win2.points.push_back(Point(-0.295142488563000, 1.949153947690000));
	win2.points.push_back(Point(-0.256449189904000, 1.943816940970000));
	win2.points.push_back(Point(-0.295142488563000, 2.017200783260000));
	p.inner_contours.push_back(win2);
	Contour win3;
	win3.points.push_back(Point(-0.295142488563000, 1.890446873860000));
	win3.points.push_back(Point(-0.292473985207000, 1.825068541640000));
	win3.points.push_back(Point(-0.251112183192000, 1.887778370500000));
	win3.points.push_back(Point(-0.252446434870000, 1.818397283250000));
	win3.points.push_back(Point(-0.295142488563000, 1.890446873860000));
	p.inner_contours.push_back(win3);
	Contour win4;
	win4.points.push_back(Point(0.250566447696000, 2.170639726220000));
	win4.points.push_back(Point(0.309273521523000, 2.166636971180000));
	win4.points.push_back(Point(0.241226685951000, 2.086581870510000));
	win4.points.push_back(Point(0.305270766490000, 2.081244863800000));
	win4.points.push_back(Point(0.250566447696000, 2.170639726220000));
	p.inner_contours.push_back(win4);
	Contour win5;
	win5.points.push_back(Point(0.239892434273000, 1.998521259770000));
	win5.points.push_back(Point(0.295931004744000, 1.995852756410000));
	win5.points.push_back(Point(0.238558182595000, 1.921134662450000));
	win5.points.push_back(Point(0.291928249711000, 1.911794900700000));
	win5.points.push_back(Point(0.239892434273000, 1.998521259770000));
	p.inner_contours.push_back(win5);
	Contour win6;
	win6.points.push_back(Point(0.234555427561000, 1.854422078550000));
	win6.points.push_back(Point(0.291928249711000, 1.854422078550000));
	win6.points.push_back(Point(0.234555427561000, 1.779703984590000));
	win6.points.push_back(Point(0.294596753067000, 1.777035481240000));
	win6.points.push_back(Point(0.234555427561000, 1.854422078550000));
	p.inner_contours.push_back(win6);*/
	return p;
}

//We design the shape of object to check if it is as we expect before tesselation
void Drawaeroplane() {

	//Drawing the outer contour
	glLineWidth(2.2f);
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i < aeroplane.outer_contour.points.size(); i++)
	{
		glVertex2f(aeroplane.outer_contour.points.at(i).x, aeroplane.outer_contour.points.at(i).y);
	}
	glEnd();
	
	//Drawing the inner contour
	glLineWidth(2.2f);
	glColor3f(0.0f, 1.0f, 0.0f);

	for (int j = 0; j < aeroplane.inner_contours.size(); j++)
	{
		glBegin(GL_LINE_STRIP);
		for (int i = 0; i < aeroplane.inner_contours[j].points.size(); i++) {
			glVertex2f(aeroplane.inner_contours[j].points.at(i).x, aeroplane.inner_contours[j].points.at(i).y);
		}
		glEnd();
	}
	
}


void CALLBACK beginCallback(GLenum which)
{}

void CALLBACK endCallback(void)
{}

void CALLBACK vertexCallback(void * vertex_data)
{
	double * xyz = (double *)vertex_data;
	tess_pts.push_back(Point(xyz[0], xyz[1]));
}

void CALLBACK TessEdgeFlagCallback(GLboolean flag)
{
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TESSELATION 
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

vector<Point> tessellate(Poly* p)
{
	tess_pts.clear();
	// Copy all points into double array format
	int pts_no = p->outer_contour.points.size(); //outer contour
	for (int i = 0; i < p->inner_contours.size(); i++) {
		pts_no = pts_no + p->inner_contours[i].points.size(); //inner contour
	}
	double * pPts = new double[3 * pts_no];
	double * pPoints = pPts;

	for (int i = 0; i < p->outer_contour.points.size(); i++)
	{
		*pPoints++ = p->outer_contour.points[i].x;
		*pPoints++ = p->outer_contour.points[i].y;
		*pPoints++ = 0;
	}

	for (int j = 0; j < p->inner_contours.size(); j++) {
		for (int i = 0; i < p->inner_contours[j].points.size(); i++)
		{
			*pPoints++ = p->inner_contours[j].points[i].x;
			*pPoints++ = p->inner_contours[j].points[i].y;
			*pPoints++ = 0;

		}
	}
	pPoints = pPts;

	// Creates a new tessellation object and returns a pointer to it
	GLUtesselator *tess = gluNewTess();
	// Define tessellation callbacks
	gluTessCallback(tess, GLU_TESS_BEGIN, (void(CALLBACK *)())&beginCallback);
	gluTessCallback(tess, GLU_TESS_END, (void(CALLBACK *)())&endCallback);
	gluTessCallback(tess, GLU_TESS_VERTEX, (void(CALLBACK *)())&vertexCallback);
	gluTessCallback(tess, GLU_TESS_EDGE_FLAG, (void (CALLBACK *)())&TessEdgeFlagCallback);

	//Start tesselation
	gluTessBeginPolygon(tess, 0);
	gluTessBeginContour(tess);
	//outer contour
	for (int i = 0; i<p->outer_contour.points.size(); i++, pPoints += 3)
	{
		gluTessVertex(tess, pPoints, pPoints);
	}
	gluTessEndContour(tess);

	//inner contour
	for (int j = 0; j < p->inner_contours.size(); j++) {
		gluTessBeginContour(tess);
		for (int i = 0; i < p->inner_contours[j].points.size(); i++, pPoints += 3)
		{
			gluTessVertex(tess, pPoints, pPoints);
		}
		gluTessEndContour(tess);
	}
	gluTessEndPolygon(tess);
	// delete tessellator after processing
	gluDeleteTess(tess);
	cout << "End tesselation" << endl;
	return tess_pts;
}
//we draw tesselate object
void DrawTesselated()
{
	glColor3f(1.0f, 0.0f, 0.0f);
	glPushMatrix();
	glTranslatef(x_axis, y_axis, 0.0);   //glTranslatef(x,y,z)
	glRotatef(angle, 0.0f, 0.0f, 1.0f);  //glRotatef(angle,x,y,z)

	glBegin(GL_TRIANGLES);
	for (int i = 0; i != tess_pts.size(); i++)
	{
		glVertex2f(tess_pts.at(i).x, tess_pts.at(i).y);
	}
	glEnd();
	glPopMatrix();
}

