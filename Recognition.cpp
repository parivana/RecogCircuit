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

void FindVE(InputArray src, vector<Vertex> &v, vector<Edge> &e)
{
	CvSeq *lines = 0;
	CvMemStorage *storage = cvCreateMemStorage(0);

	lines = cvHoughLines2(img_gray, storage, CV_HOUGH_STANDARD,
			1, CV_PI / 180, 50, 0, 0);

	float (*line)[] = new float *[lines->total];

	for(int i = 0 ; i < lines->total ; i++) {
		line[i] = (float *)cvGetSeqElem(lines, i);
		float r1 = line[i][0];
		float th1 = line[i][1];

		for(int j = i + 1 ; j < lines->total ; j++) {
			float r2 = line[j][0];
			float th2 = line[j][0];

			dth = abs(th1 - th2);
			if(dth < PI / 6.0)
				continue;

			// get (x, y)
			// valid check
		}
	}
}

vector<Element> FindElementRegion(vector<Vertex> v, vector<Edge> e)
{
	vector<Element> emt;

	return emt;
}

