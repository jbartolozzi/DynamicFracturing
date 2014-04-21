#include "fractureMesh.h"


fractureMesh::fractureMesh(void)
{
	vertices = std::vector<vertex*>();
	edges = std::vector<edge>();

	Reset();
}


fractureMesh::~fractureMesh(void)
{
}

// Draw our FractureMesh
void fractureMesh::Draw(const vec3& eyePos)
{
	for(int i=0; i<edges.size(); i++){
		edge e = edges.at(i);
		DrawEdge(e, eyePos);
	}
}

void fractureMesh::DrawEdge(edge e, const vec3& eyePos)
{

	glPushAttrib(GL_LIGHTING_BIT | GL_LINE_BIT);
      glDisable(GL_LIGHTING);

      glLineWidth(2.0); 
      glBegin(GL_LINES);
         glColor3f(1.0, 0.0, 1.0);
		 glVertex3f(e.p1->pos[0], e.p1->pos[1], e.p1->pos[2]);
         glVertex3f(e.p2->pos[0], e.p2->pos[1], e.p2->pos[2]);
      glEnd();
  glPopAttrib();
}

// Reset to the initial state
void fractureMesh::Reset()
{
	setUpMesh();
}

void fractureMesh::setUpMesh()
{

	//Initialize vertices for cube
	vertex* v1 = new vertex(vec3(-1,-1,-1), 0);
	vertex* v2 = new vertex(vec3(1,-1,-1), 1);
	vertex* v3 = new vertex(vec3(1,-1,1), 2);
	vertex* v4 = new vertex(vec3(-1,-1,1), 3);
	vertex* v5 = new vertex(vec3(-1,1,-1), 4);
	vertex* v6 = new vertex(vec3(1,1,-1), 5);
	vertex* v7 = new vertex(vec3(1,1,1), 6);
	vertex* v8 = new vertex(vec3(-1,1,1), 7);

	//Initialize edges
	edge e1 = edge(v1, v2, 0);
	edge e2 = edge(v2, v3, 1);
	edge e3 = edge(v3, v4, 2);
	edge e4 = edge(v4, v1, 3);
	edge e5 = edge(v5, v6, 4);
	edge e6 = edge(v6, v7, 5);
	edge e7 = edge(v7, v8, 6);
	edge e8 = edge(v8, v5, 7);
	edge e9 = edge(v1, v5, 8);
	edge e10 = edge(v2, v6, 9);
	edge e11 = edge(v4, v8, 10);
	edge e12 = edge(v3, v7, 11);

	//Add verts to vector
	vertices.push_back(v1);
	vertices.push_back(v2);
	vertices.push_back(v3);
	vertices.push_back(v4);
	vertices.push_back(v5);
	vertices.push_back(v6);
	vertices.push_back(v7);
	vertices.push_back(v8);

	//Add edges to vector
	edges.push_back(e1);
	edges.push_back(e2);
	edges.push_back(e3);
	edges.push_back(e4);
	edges.push_back(e5);
	edges.push_back(e6);
	edges.push_back(e7);
	edges.push_back(e8);
	edges.push_back(e9);
	edges.push_back(e10);
	edges.push_back(e11);
	edges.push_back(e12);
}

float fractureMesh::intersect(vec3 p0, vec3 v0)
{

	//vec3 min = vec3(-0.5, -0.5, -0.5);
	//vec3 max = vec3(0.5, 0.5, 0.5);
	vec3 min = vec3(0, 0, -1);
	vec3 max = vec3(1, 1, 0);

	float tmin = (min[0] - p0[0]) / v0[0];
    float tmax = (max[0] - p0[0]) / v0[0];
    if (tmin > tmax) {
		float temp = tmin;
		tmin = tmax;
		tmax = temp;
	}
    float tymin = (min[1] - p0[1]) / v0[1];
    float tymax = (max[1] - p0[1]) / v0[1];
    if (tymin > tymax) {
		float temp = tymin;
		tymin = tymax;
		tymax = temp;
	}
    if ((tmin > tymax) || (tymin > tmax)){
        return -1;
	}
    if (tymin > tmin){
        tmin = tymin;
	}
    if (tymax < tmax){
        tmax = tymax;
	}
    float tzmin = (min[2] - p0[2]) / v0[2];
    float tzmax = (max[2] - p0[2]) / v0[2];
    if (tzmin > tzmax) {
		float temp = tzmin;
		tzmin = tzmax;
		tzmax = temp;
	}
    if ((tmin > tzmax) || (tzmin > tmax)){
        return -1;
	}
    if (tzmin > tmin){
        tmin = tzmin;
	}
    if (tzmax < tmax){
        tmax = tzmax;
	}

	//Enable this part to set intersection normal -- not sure if it'd be useful later
	/*
	vec3 intPoint = p0 + tmin*v0;
	if(intPoint[1] <= 1.01 && intPoint[1] >= 0.99){
		intNormal = vec3(0,1,0);
	}
	else if(intPoint[1] >= -1.01 && intPoint[1] <= -0.99){
		intNormal = vec3(0,-1,0);
	}
	else if(intPoint[0] <= 1.01 && intPoint[0] >= 0.99){
		intNormal = vec3(1,0,0);
	}
	else if(intPoint[0] >= -1.01 && intPoint[0] <= -0.99){
		intNormal = vec3(-1,0,0);
	}
	else if(intPoint[2] <= 1.01 && intPoint[2] >= 0.99){
		intNormal = vec3(0,0,1);
	}
	else if(intPoint[2] >= -1.01 && intPoint[2] <= -0.99){
		intNormal = vec3(0,0,-1);
	}*/

	return tmin;
}