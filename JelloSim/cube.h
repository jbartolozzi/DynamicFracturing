#pragma once
#include "fractureMesh.h"
class cube : public fractureMesh
{
public:
	cube(void);
	~cube(void);
	void Reset();
	void setUpMesh();
	float intersect(vec3 p0, vec3 v0);
};

