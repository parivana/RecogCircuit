#ifndef __VERTEX_H__
#define __VERTEX_H__

using namespace cv;

class Vertex {
	public : 
		Vertex() {
			for(int i = 0 ; i < 8 ; i++) {
				this->direction[i] = 0;
			}
		};
		Vertex(const Vertex &v) {
			this->pt = v.pt;
			
			for(int i = 0 ; i < 8 ; i++) {
				this->direction[i] = v.direction[i];
			}
		};
		~Vertex() {};

		char direction[8];
		Point pt;
};

#endif // __VERTEX_H__
