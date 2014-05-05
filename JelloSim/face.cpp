#include "face.h"

face::face()
{
	vertices = std::vector<vertex*>();
}

face::face(vertex *_p1, vertex *_p2, vertex *_p3)
{
	vertices = std::vector<vertex*>();
	vertices.push_back(_p1);
	vertices.push_back(_p2);
	vertices.push_back(_p3);
}

face::face(vector<vertex*> _vertices)
{
	vertices = _vertices;
	triangulate();
}

void face::draw()
{

}

face::~face()
{

}

void face::triangulate()
{
	vec3 v1, v2, v3;
	vector<tri> newtris;

	v1 = vertices[0]->pos;
	for ( int i=1; i < vertices.size()-1; i++ )
	{
		v2 = vertices[i]->pos;
		v3 = vertices[i+1]->pos;

		newtris.push_back( tri(v1, v2, v3) );
	}
	triangles = newtris;
}