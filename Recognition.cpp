#include <vector>
#include <opencv/cv.h>

#include "Recognition.h"
#include "Element.h"
#include "Wire.h"
#include "Vertex.h"
#include "Edge.h"

using namespace std;
using namespace cv;

static vector<Element> FindElement(IplImage *img)
{
	vector<Element> emt;
	Element e;

	// write your element recognition code here...
	//

	// here is sample code...
	//
	e.setName("R1");
	e.setRect(0, 0, 50, 50);

	e.setNport(2);
	e.makeWire();
	Wire *wp = new Wire();
	Wire *wn = new Wire();
	e.setWire(wp, 0);
	e.setWire(wn, 1);
	e.setParam("200");

	emt.push_back(e);
	return emt;
}

static vector<Element> Wiring(IplImage *img, vector<Element> emt)
{
	Wire *w;
	// write your wiring recognition code here...
	
	// here is sample code...
	// 

	return emt;
}

static void FindCross(Mat &src, vector<Vec4i> lines)
{
	Mat temp(src.size(), CV_8UC1, 0);

	vector<Vec4i>::const_iterator iter;

	for(iter = lines.begin() ; iter != lines.end() ; iter++) {
		circle(temp, Point((*iter)[0], (*iter)[1]), 10, 1, 0);
		circle(temp, Point((*iter)[2], (*iter)[3]), 10, 1, 0);
	}
}

vector<Element> DoRecog(IplImage *img)
{
	vector<Element> emt = FindElement(img);

	return Wiring(img, emt);
}

void FindVE(IplImage *src, vector<Vertex> &v, vector<Edge> &e)
{
	CvSeq *lines = 0;
	CvMemStorage *storage = cvCreateMemStorage(0);

	lines = cvHoughLines2(src, storage, CV_HOUGH_STANDARD,
			1, CV_PI / 180, 50, 0, 0);

	float **line = new float *[lines->total];
	v.clear();
	vector<Point> vec_point;

	for(int i = 0 ; i < lines->total ; i++) {
		line[i] = (float *)cvGetSeqElem(lines, i);
		float r1 = line[i][0];
		float th1 = line[i][1];

		for(int j = i + 1 ; j < lines->total ; j++) {
			float r2 = line[j][0];
			float th2 = line[j][1];

			float dth = abs(th1 - th2);
			if((dth < CV_PI / 6.0) || 
				((CV_PI - dth) < CV_PI / 6.0))
				continue;

			// get (x, y)
			CvMat *m = cvCreateMat(2, 2, CV_32FC1);
			CvMat *mi = cvCreateMat(2, 2, CV_32FC1);
			CvMat *r = cvCreateMat(2, 1, CV_32FC1);
			CvMat *p = cvCreateMat(2, 1, CV_32FC1);

			cvmSet(m, 0, 0, cos(th1)); cvmSet(m, 0, 1, sin(th1));
			cvmSet(m, 1, 0, cos(th2)); cvmSet(m, 1, 1, sin(th2));

			cvmSet(r, 0, 0, r1); cvmSet(r, 1, 0, r2);

			double det = cvInvert(m, mi);
			if(det == 0.0)
				continue;

			cvMatMul(mi, r, p);

			float x = cvmGet(p, 0, 0);
			float y = cvmGet(p, 1, 0);
			float errth = min(abs(CV_PI * 3.0 / 4.0 - dth), 
					min(abs(CV_PI / 4.0 - dth), abs(CV_PI / 2.0 - dth)));
	
			Point pt(cvRound(x), cvRound(y));
			if(!CheckValid(src, v, pt, th1, th2))
				continue;

			vec_point.push_back(pt);

		}
	}
}

vector<Element> FindElementRegion(vector<Vertex> v, vector<Edge> e)
{
	vector<Element> emt;

	return emt;
}

bool CheckValid(const CvArr *src, vector<Vertex> &v, Point pt, float th1, float th2)
{
	Vertex *vertex = NULL;
	CvSize size = cvGetSize(src);
	IplImage *img_src = (IplImage *)src;
	char *data;
 	int step;
	char direction[8] = {0, };
	int direc1, direc2;

	data = img_src->imageData;
	step = img_src->widthStep;

	if((pt.x < 0 || pt.y < 0) || (pt.x >= size.width || pt.y >= size.height))
		return false;

	// 
	float tan1 = CV_PI / 2.0 - th1;
	float tan2 = CV_PI / 2.0 - th2;

	if(tan1 < 0) tan1 = 2.0 * CV_PI + tan1;
	if(tan2 < 0) tan2 = 2.0 * CV_PI + tan1;

	float angle;
	float radius = 20.0;
	bool flag = false;
	for(int i = 0 ; i < 8 ; i++) {
		flag = false;
		angle = (float)i * CV_PI / 4.0;
		for(float dangle = 0.0 ; dangle < CV_PI / 8 ; dangle += 0.01) {
			int x = round(pt.x + radius * cos(angle+dangle));
			int y = round(pt.y - radius * sin(angle+dangle));
			if((x < 0 || y < 0) || (x >= size.width || y >= size.height))
				continue;

			if(data[x + y * step] != 0) {
				flag = true;
				break;
			}

			x = round(pt.x + radius * cos(angle-dangle));
			y = round(pt.y - radius * sin(angle-dangle));
			if((x < 0 || y < 0) || (x >= size.width || y >= size.height))
				continue;
			if(data[x + y * step] != 0) {
				flag = true;
				break;
			}
		}

		if(flag) {
			if(vertex == NULL) {
				vertex = new Vertex();
				vertex->pt = pt;
			}
			vertex->direction[i] = 1;
		}
	}
	
	if(vertex == NULL)
		return false;

	flag = true;
	direc1 = round(tan1 / (CV_PI / 4.0));
	direc2 = round(tan2 / (CV_PI / 4.0));

	if((vertex->direction[direc1] != 1 &&
				vertex->direction[(direc1 + 4) % 8] != 1) ||
			(vertex->direction[direc2] != 1 &&
			vertex->direction[(direc2 + 4) % 8] != 1))
		return false;

	if(flag) {
		v.push_back(*vertex);
		return true;
	}

	return false;
}

void CalcVertexPos(vector<Point> &p, vector<Vertex> &v)
{
	vector<Point>::const_iterator iter;

	for(iter = p.begin() ; iter != p.end() ; iter++) {
		int x1, y1;
		x1 = iter->x;
		y1 = iter->y;
	}
}
