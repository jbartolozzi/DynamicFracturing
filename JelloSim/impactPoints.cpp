#include "impactPoints.h"
#include <GL/glut.h>

impactPoints::impactPoints()
{
	generatedPoints = vector<vec3>();
}

impactPoints::impactPoints(vec3 impactLocation, vec3 force, int numPoints)
{
	float rSquared = force.Length();
	rSquared *= rSquared;
	generatedPoints = vector<vec3>();
	for (unsigned int i = 0; i < numPoints; i++)
	{
		srand(i);
		double ratio = (double)i/(double)numPoints;
		float a = ratio*(rand() % 10 - 5.f)/10.f;
		float b = ratio*(rand() % 10 - 5.f)/10.f;
		float c = ratio*(rand() % 10 - 5.f)/10.f;
		
		vec3 point = impactLocation + rSquared*vec3(a,b,c);
		Perlin *p = new Perlin(2,0.1,0.8,123);
		float noise = 0.5 * p->Get(point[0]*point[0],point[1]*point[1],point[2]*point[2]);
		point = vec3(point[0] + noise, point[1] + noise,point[2] + noise);
		float inOrOut = (point[0] - impactLocation[0])*(point[0] - impactLocation[0]) 
					  + (point[1] - impactLocation[1])*(point[1] - impactLocation[1])
					  + (point[2] - impactLocation[2])*(point[2] - impactLocation[2]);
		if (inOrOut <= rSquared) {
			generatedPoints.push_back(point);
		}
		delete p;
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
		glPushAttrib(GL_LIGHTING_BIT | GL_LINE_BIT);
		glDisable(GL_LIGHTING);
		glPointSize(2.f);
		glBegin(GL_POINTS);
		
		glColor3f(0.0,0.0,1.0);
		for(int i = 0; i < generatedPoints.size(); i++) 
		{
			glVertex3f(generatedPoints.at(i)[0],generatedPoints.at(i)[1],generatedPoints.at(i)[2]);
		}

		glEnd();
		glPopAttrib();
	}
}

impactPoints::~impactPoints()
{
}