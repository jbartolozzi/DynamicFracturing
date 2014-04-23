#include "impactPoints.h"
#include <GL/glut.h>

impactPoints::impactPoints()
{
	generatedPoints = vector<vec3>();
}

impactPoints::impactPoints(vec3 impactLocation, vec3 force, int numPoints)
{
	//store impact point
	impactPoint = impactLocation;
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
	//SET THE VALUES OF THE CONTAINER BASED ON THE IMPACT LOCATION
	//
	const double x_min=-1,x_max=1;
	const double y_min=-1,y_max=1;
	const double z_min=-1,z_max=1;
	const int n_x=3,n_y=3,n_z=3;
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
	voroPoints = con.output_voronoi_vertices(r/3,impactLocation,generatedPoints);
	//cullVoroPoints(impactLocation, rSquared);
}

void impactPoints::cullVoroPoints(vec3 impactLocation, float rSquared)
{
	for(int i = 0; i < voroPoints.size(); i++) 
	{
		for(int j = 0; j < voroPoints[i].size(); j++)
		{
			float x = voroPoints[i][j][0];
			float y = voroPoints[i][j][1];
			float z = voroPoints[i][j][2];
			float newX = x * sqrt(1-(y*y)/2 - (z*z)/2 + (y*y*z*z)/3);
			float newY = y * sqrt(1-(z*z)/2 - (x*x)/2 + (z*z*x*x)/3);
			float newZ = z * sqrt(1-(x*x)/2 - (y*y)/2 + (x*x*y*y)/3);
			voroPoints[i][j] -= vec3(newX,newY,newZ);
		}
	}
}

vector<vec3> impactPoints::points() 
{
	return generatedPoints;
}

// draw points
void impactPoints::draw(int frame)
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
			//initialize center of mass
			vec3 com = vec3(0.0,0.0,0.0);
			int points=0;
			for(int j = 0; j < voroPoints[i].size()-1; j++)
			{
				com  += vec3(voroPoints[i][j][0],voroPoints[i][j][1],voroPoints[i][j][2]);
				com+= vec3(voroPoints[i][j+1][0],voroPoints[i][j+1][1],voroPoints[i][j+1][2]);
				points+=2;
		
			}
			com/=(double)points;
			//set vel in proportion to distance from impact point
			vec3 vel = com*frame;//-impactPoint;
			double speed = .1;
			vel[0] = speed*vel[0];
			vel[1] = speed*vel[1];
			vel[2] = speed*vel[2];
			for(int j = 0; j < voroPoints[i].size()-1; j++)
			{
				glVertex3d(voroPoints[i][j][0]+vel[0],voroPoints[i][j][1]+vel[1],voroPoints[i][j][2]+vel[2]);
				glVertex3d(voroPoints[i][j+1][0]+vel[0],voroPoints[i][j+1][1]+vel[1],voroPoints[i][j+1][2]+vel[2]);
			}
		}
		glEnd();
		glPopAttrib();
	}
}

impactPoints::~impactPoints()
{
}