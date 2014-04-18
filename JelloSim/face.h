#include "vec.h"
#include <vector>

struct edge 
{
	vec3 p1,p2;
	edge(vec3 _p1, vec3 _p2){p1 = _p1; p2 = _p2;}
};
class face {
public:
	void draw();
private:
	vector<edge> edges; 
	vec3 normal;
protected:
};