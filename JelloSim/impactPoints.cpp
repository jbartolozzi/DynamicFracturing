#include "impactPoints.h"
#include <GL/glut.h>

impactPoints::impactPoints()
{
	generatedPoints = vector<vec3>();
}

impactPoints::impactPoints(vec3 impactLocation, vec3 force, int numPoints)
{
	generatedPoints = vector<vec3>();
	for (int i = 0; i < numPoints; i++)
	{
		float a = rand() % 10;
		float b = rand() % 10;
		float c = rand() % 10;
		generatedPoints.push_back(impactLocation + vec3(a/10,b/10,c/10));
	}
}

vector<vec3> impactPoints::points() 
{
	return generatedPoints;
}

// draw points
void impactPoints::draw()
{
	if (generatedPoints.size() > 0){
		glBegin(GL_POINTS);
		glColor3f(1.0,1.0,1.0);
		for(int i = 0; i < generatedPoints.size(); i++) 
		{
			glVertex3f(generatedPoints.at(i)[0],generatedPoints.at(i)[1],generatedPoints.at(i)[2]);
		}

		glEnd();
	}
}

impactPoints::~impactPoints()
{
}