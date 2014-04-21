#ifndef IMPACTPOINTS
#define IMPACTPOINTS

#include <vector>
#include "vec.h"
#include "perlin.h"
#include "voro++.hh"

class impactPoints {
public:
	impactPoints();
	// generates randomized points to use for voronoi generation
	impactPoints(vec3 impactLocation, vec3 force, int numPoints);
	~impactPoints();
	void draw();
private:
	vector<vec3> generatedPoints;
	vector<vector<vec3>> voroPoints;
	void cullVoroPoints();
protected:
	vector<vec3> points();
};

#endif
