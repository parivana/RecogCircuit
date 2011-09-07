#ifndef __EDGE_H__
#define __EDGE_H__

#include "Vertex.h"

class Edge {
	public : 
		Edge();
		Edge(Edge &e);

	private:
		Vertex *v;
};
 
#endif // __EDGE_H__
