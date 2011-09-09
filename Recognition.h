#ifndef __RECOGNITION_H__
#define __RECOGNITION_H__

#include <vector>
#include <opencv/cv.h>

#include "Element.h"
#include "Vertex.h"

using namespace std;
using namespace cv;

vector<Element> DoRecog(IplImage *);
void CalcVertexPos(vector<Point> &p, vector<Vertex> &v);
bool CheckValid(const CvArr *src, vector<Vertex> &v, 
		Point pt, float th1, float th2);

#endif // __RECOGNITION_H__
