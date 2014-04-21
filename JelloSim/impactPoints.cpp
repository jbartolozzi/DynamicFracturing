#include "impactPoints.h"
#include <GL/glut.h>

impactPoints::impactPoints()
{
	generatedPoints = vector<vec3>();
}

impactPoints::impactPoints(vec3 impactLocation, vec3 force, int numPoints)
{
	Perlin *p = new Perlin(2,0.1,1,123);
	float r = force.Length();
	float rSquared = r*r;
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

	// Create a container with the geometry given above, and make it
	// non-periodic in each of the three coordinates. Allocate space for
	// eight particles within each computational block
	//voro::container con = voro::container(x_min,x_max,y_min,y_max,z_min,z_max,n_x,n_y,n_z,
		//	false,false,false,8);
	const double x_min=-r,x_max=r;
	const double y_min=-r,y_max=r;
	const double z_min=-r,z_max=r;
	const int n_x=numPoints,n_y=numPoints,n_z=numPoints;
	const double cvol=(x_max-x_min)*(y_max-y_min)*(x_max-x_min);
	voro::container con(x_min,x_max,y_min,y_max,z_min,z_max,n_x,n_y,n_z,
			false,false,false,8);
	for(int i = 0; i < generatedPoints.size(); i++) 
	{
		double a = generatedPoints[i][0];
		double b = generatedPoints[i][1];
		double z = generatedPoints[i][2];
		con.put(i,a,b,z);
	}
	con.sum_cell_volumes();
	voroPoints = con.output_voronoi_vertices(r/10,impactLocation,generatedPoints);
}

void impactPoints::cullVoroPoints()
{
	
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
		/* DRAW LINES */
		glPushAttrib(GL_LIGHTING_BIT | GL_LINE_BIT);
		glDisable(GL_LIGHTING);
		glBegin(GL_LINES);
		glColor3f(0,1.0,0);
		for(int i = 0; i < voroPoints.size(); i++)
		{
			for(int j = 0; j < voroPoints[i].size()-1; j++)
			{
				glVertex3d(voroPoints[i][j][0],voroPoints[i][j][1],voroPoints[i][j][2]);
				glVertex3d(voroPoints[i][j+1][0],voroPoints[i][j+1][1],voroPoints[i][j+1][2]);
		
			}
		}
		glEnd();
		glPopAttrib();
	}
}

impactPoints::~impactPoints()
{
}