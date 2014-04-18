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
    virtual void Draw(const vec3& eyePos);
	virtual void DrawEdge(edge e, const vec3& eyePos);

    // Reset to the initial state
    virtual void Reset();

	//Sets up vertices and edges
	void setUpMesh();

	std::vector<edge> edges;
	std::vector<vertex*> vertices;

};

