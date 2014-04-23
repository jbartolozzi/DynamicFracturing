#pragma once

#include <vector>
#include <map>
#include "vec.h"
#include "World.h"
#include "face.h"
#include <GL/glut.h>

class fractureMesh
{
public:
	fractureMesh(void);
	~fractureMesh(void);

    // Draw our FractureMesh
    void Draw(const vec3& eyePos);
	void DrawEdge(edge e, const vec3& eyePos);

    // Reset to the initial state
    virtual void Reset();

	//Sets up vertices and edges
	virtual void setUpMesh();

	std::vector<edge> edges;
	std::vector<vertex*> vertices;
	std::vector<face> faces;

	//Returns t value for intersection with a given ray
	bool intersection(vec3 p0, vec3 v0, vec3& intersectionPoint);

};

