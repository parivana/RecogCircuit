#ifndef __VERTEX_H__
#define __VERTEX_H__

using namespace cv;

class Vertex {
	public : 
		Vertex();
		Vertex(Vertex &v);

	private:
		Point pt;
};

#endif // __VERTEX_H__
