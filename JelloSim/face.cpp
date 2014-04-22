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
}

void face::draw()
{

}

face::~face()
{

}