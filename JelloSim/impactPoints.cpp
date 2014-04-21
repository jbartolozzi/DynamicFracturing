#include "impactPoints.h"
#include <GL/glut.h>

impactPoints::impactPoints()
{
	generatedPoints = vector<vec3>();
}

impactPoints::impactPoints(vec3 impactLocation, vec3 force, int numPoints)
{
	Perlin *p = new Perlin(2,0.1,1,123);
	float rSquared = force.Length();
	rSquared *= rSquared;
	generatedPoints = vector<vec3>();
	for (unsigned int i = 0; i < numPoints; i++)
	{
		srand(i);
		double ratio = (double)i/(double)numPoints;
		ratio = ratio*ratio;
		float a = ratio*(rand() % 10 - 5.f)/10.f;
		float b = ratio*(rand() % 10 - 5.f)/10.f;
		float c = ratio*(rand() % 10 - 5.f)/10.f;
		
		vec3 point = impactLocation + rSquared*vec3(a,b,c);
		
		float noise = p->Get(point[0]*point[0],point[1]*point[1],point[2]*point[2]);
		point = vec3(point[0] + noise, point[1] + noise,point[2] + noise);
		float inOrOut = (point[0] - impactLocation[0])*(point[0] - impactLocation[0]) 
					  + (point[1] - impactLocation[1])*(point[1] - impactLocation[1])
					  + (point[2] - impactLocation[2])*(point[2] - impactLocation[2]);
		if (inOrOut <= rSquared) {
			generatedPoints.push_back(point);
		}
	}
	delete p;
	const double x_min=-1,x_max=1;
	const double y_min=-1,y_max=1;
	const double z_min=-1,z_max=1;
	const double cvol=(x_max-x_min)*(y_max-y_min)*(x_max-x_min);
	// vectror of generatedPoints
	const int n_x=6,n_y=6,n_z=6;

	// Set the number of particles that are going to be randomly introduced
	const int particles=20;
	int i;
	double x,y,z;

	// Create a container with the geometry given above, and make it
	// non-periodic in each of the three coordinates. Allocate space for
	// eight particles within each computational block
	//voro::container con = voro::container(x_min,x_max,y_min,y_max,z_min,z_max,n_x,n_y,n_z,
		//	false,false,false,8);
	voro::container c = voro::container(1,1,1,1,1,1,1,1,1,true,true,true,1); 
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
		glPointSize(2);
		glBegin(GL_POINTS);
		
		glColor3f(1.0,1.0,1.0);
		for(int i = 0; i < generatedPoints.size(); i++) 
		{
			glVertex3f(generatedPoints.at(i)[0],generatedPoints.at(i)[1],generatedPoints.at(i)[2]);
		}

		glEnd();
		glPopAttrib();
		/* DRAW LINES
		glPushAttrib(GL_LIGHTING_BIT | GL_LINE_BIT);
		glDisable(GL_LIGHTING);
		glBegin(GL_LINES);
		glColor3f(1.0,0,0);
		for(int j = 0; j < generatedPoints.size(); j++)
		{
			for(int i = 0; i < generatedPoints.size();i++) 
			{
				if (j != i)
				{
					glVertex3f(generatedPoints.at(j)[0],generatedPoints.at(j)[1],generatedPoints.at(j)[2]);
					glVertex3f(generatedPoints.at(i)[0],generatedPoints.at(i)[1],generatedPoints.at(i)[2]);
				}
			}
		}
		glEnd();
		glPopAttrib();*/
	}
}

impactPoints::~impactPoints()
{
}