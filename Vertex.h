#ifndef __VERTEX_H__
#define __VERTEX_H__

#include "Point.h"

class Vertex {
	public : 
		Vertex();
		Vertex(Vertex &v);
		Vertex(int x, int y) { pt.x = x;	pt.y = y; }

	private:
		Point2i pt;
};

#endif // __VERTEX_H__
