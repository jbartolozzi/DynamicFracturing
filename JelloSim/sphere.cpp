#include "sphere.h"


sphere::sphere(void)
{
	vertices = std::vector<vertex*>();
	edges = std::vector<edge>();

	Reset();
}


sphere::~sphere(void)
{
}

void sphere::Reset()
{
	setUpMesh();
}

void sphere::setUpMesh()
{

	
}

float sphere::intersect(vec3 p0, vec3 v0)
{
	float a = v0*v0;
	float b = 2 * (v0*p0);
	//float b = 2 * (v0.x*(p0.x - 0) + v0.y*(p0.y - 0) + v0.z*(p0.z - 0));
	float c = p0*p0 - 1;
	//float c = p0.x*p0.x + p0.y*p0.y + p0.z*p0.z -1;

	float disc = b*b - 4*a*c;
	if (disc < 0.0){
		return -1;
	}
	else{
		float t0 = (-b - sqrt(disc))/(2*a);
		if (t0 > 0){
			//intNormal = normalize(p0 + t0*v0);
			return t0;
		}
		else {
			float t1 = (-b + sqrt(disc))/(2*a);
			if(t1 > 0){
				//intNormal = normalize(p0 + t1*v0);
				return t1;
			}
			else return -1;
		}
	}
	
}
