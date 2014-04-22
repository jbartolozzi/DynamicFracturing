#pragma once
#include "fractureMesh.h"
class sphere : public fractureMesh
{
public:
	sphere(void);
	~sphere(void);
	void Reset();
	void setUpMesh();
	float intersect(vec3 p0, vec3 v0);
};

