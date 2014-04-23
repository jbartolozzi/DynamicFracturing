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

	// initialize faces
	face f1 = face(v1,v2,v3);
	face f2 = face(v1,v3,v4);
	face f3 = face(v5,v6,v7);
	face f4 = face(v5,v7,v8);
	face f5 = face(v2,v3,v7);
	face f6 = face(v2,v7,v6);
	face f7 = face(v4,v1,v5);
	face f8 = face(v4,v5,v8);
	face f9 = face(v3,v4,v8);
	face f10 = face(v3,v8,v7);
	face f11 = face(v1,v2,v6);
	face f12 = face(v1,v6,v5);
	faces.push_back(f1);
	faces.push_back(f2);
	faces.push_back(f3);
	faces.push_back(f4);
	faces.push_back(f5);
	faces.push_back(f6);
	faces.push_back(f7);
	faces.push_back(f8);
	faces.push_back(f9);
	faces.push_back(f10);
	faces.push_back(f11);
	faces.push_back(f12);

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

bool fractureMesh::intersect(vec3 p0, vec3 v0, vec3& intersectionPoint)
{
	bool output = false;
	float minTValue = 10000;
	vec3 O = p0;
	vec3 D = v0;
	vec3 E1,E2,Q,P,T,check;
	for(int i = 0; i < faces.size(); i++)
	{
		E1 = faces[i].vertices[1]->pos - faces[i].vertices[0]->pos;
		E2 = faces[i].vertices[2]->pos - faces[i].vertices[0]->pos;
		T = O - faces[i].vertices[0]->pos;
		P = D.Cross(E2);
		Q = T.Cross(E1);
		check = (1/(P*E1))*vec3(Q*E2,P*T,Q*D);
		if (check[1] >= 0 && check[2] >= 0 && check[1]+check[2] <= 1)
		{
			if (check[0] < minTValue) minTValue = check[0];
			output = true;
		}
	}
	intersectionPoint = p0 + minTValue * v0;
	return output;
}