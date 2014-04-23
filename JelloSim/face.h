#include "vec.h"
#include <vector>

struct vertex 
{
	vec3 pos;
	int index;
	vertex(int _index){pos = vec3(); index = _index;}
	vertex(vec3 _pos, int _index){pos = _pos; index = _index;}
};
struct edge 
{
	vertex* p1;
	vertex* p2;
	int index;
	edge(vertex* _p1, vertex* _p2, int _index){p1 = _p1; p2 = _p2; index = _index;}
};
struct tri
{
	vec3 p1;
	vec3 p2;
	vec3 p3;
	tri(vec3 _p1, vec3 _p2, vec3 _p3){p1 = _p1; p2 = _p2; p3 = _p3;}
};
class face {
public:
	void draw();
	face();
	face(vector<vertex*> vertices);
	face(vertex *p1, vertex *p2, vertex *p3);
	std::vector<vertex*> vertices; 
	std::vector<tri> triangles;
	void triangulate();
	~face();
private:
	
	vec3 normal;
	int index;
protected:
};