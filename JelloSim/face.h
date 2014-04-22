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
class face {
public:
	void draw();
	face();
	face(vector<vertex*> vertices);
	face(vertex *p1, vertex *p2, vertex *p3);
	std::vector<vertex*> vertices; 
	~face();
private:
	
	vec3 normal;
	int index;
protected:
};