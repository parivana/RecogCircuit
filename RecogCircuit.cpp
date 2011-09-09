#include <vector>
#include <string.h>
#include <math.h>
#include <opencv/cv.h>
#include <opencv/highgui.h>

#include "Recognition.h"
#include "DescWriter.h"
#include "Element.h"
#include "Analysis.h"
#include "Vertex.h"
#include "Edge.h"

using namespace std;
using namespace cv;

IplImage *DrawVE(IplImage *, vector<Vertex>, vector<Edge>);
IplImage *DrawRecogImage(IplImage *, vector<Element>);
IplImage *PreProcess(IplImage *);

int main(int argc, char *argv[])
{
	if(argc < 2) {
		fprintf(stderr, "Usage : ./RecogCircuit.out [circuit_image]\n");
		exit(1);
	}

	IplImage* circuit = cvLoadImage(argv[1], -1);
	IplImage* recogcircuit;
	IplImage* precircuit;

	cvNamedWindow("Circuit Image", CV_WINDOW_AUTOSIZE);
	cvShowImage("Circuit Image", circuit);

	precircuit = PreProcess(circuit);
	cvNamedWindow("Preprocessed Image", CV_WINDOW_AUTOSIZE);
	cvShowImage("Preprocessed Image", precircuit);

	Analysis anl;
	anl.setType(Analysis::DC); //
	anl.setParam("0 5 1");
	vector<Element> emt = DoRecog(precircuit);

	char *desc;
	char cname[8] = "sample";
	desc = DescWriter(cname, emt, anl);

	recogcircuit = DrawRecogImage(precircuit, emt);
	cvNamedWindow("Recognized Circuit Image", CV_WINDOW_AUTOSIZE);
	cvShowImage("Recognized Circuit Image", recogcircuit);

	cvWaitKey(0);
	cvReleaseImage(&circuit);
	cvReleaseImage(&precircuit);
	cvReleaseImage(&recogcircuit);
	return 0;
}

// draw recognized element region on the original image...
IplImage *DrawRecogImage(IplImage *img, vector<Element> emt)
{
	IplImage *recog = cvCloneImage(img);
	CvScalar color = cvScalar(0, 0, 255);
	
	vector<Element>::iterator iter;
	for(iter = emt.begin() ; iter != emt.end() ; iter++) {

	}

	return recog;
}

IplImage *PreProcess(IplImage *img)
{
	int corner_count = 150;
	IplImage *img_gray = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, 1);
	cvCvtColor(img, img_gray, CV_BGR2GRAY);

	IplImage *pre = cvCloneImage(img);
	//IplImage *pre = cvCreateImage(cvGetSize(img), IPL_DEPTH_32F, 1);
	//cvCvtColor(img, pre, CV_BGR2GRAY);
	//cvThreshold(pre, pre, 128, 255, CV_THRESH_BINARY);

	//cvNot(img_gray, img_gray);
	cvCanny(img_gray, img_gray, 100, 20, 3);
	cvCvtColor(img_gray, pre, CV_GRAY2BGR);

	CvSeq *lines = 0;
	CvMemStorage *storage = cvCreateMemStorage(0);
	/*
	//
	lines = cvHoughLines2(img_gray, storage, CV_HOUGH_PROBABILISTIC,
			1, CV_PI / 180, 100, 20, 0);
	for(int i = 0 ; i < lines->total ; i++) {
		CvPoint *line = (CvPoint *)cvGetSeqElem(lines,i);
		cvLine(pre, line[0], line[1], CV_RGB(0, 255, 0), 1, 8);
	}
	*/
	
	CvSize size = cvGetSize(img_gray);
	lines = cvHoughLines2(img_gray, storage, CV_HOUGH_STANDARD,
			1, CV_PI / 180, 50, 0, 0);

	float **line = new float *[lines->total];
	for(int i = 0 ; i < lines->total ; i++) {
		line[i] = (float *)cvGetSeqElem(lines, i);
	}

	vector<Vertex> v;
	vector<Point> vec_point;

	for(int i = 0 ; i < lines->total ; i++) {
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
			if(!CheckValid(img_gray, v, pt, th1, th2))
				continue;

			vec_point.push_back(pt);
			cvCircle(pre, pt, (errth > 0.1) ? 30 : 10, CV_RGB(255, 0, 0));

		}

		double a = cos(th1), b = sin(th1);
		double x0 = a * r1, y0 = b*r1;
		Point pt1(cvRound(x0 + 1000*(-b)), cvRound(y0 + 1000*(a)));
		Point pt2(cvRound(x0 - 1000*(-b)), cvRound(y0 - 1000*(a)));
		//cvLine(pre, pt1, pt2, CV_RGB(0, 255, 0), 1, 8);
	}

	CalcVertexPos(vec_point, v);

	delete line;
	cvReleaseImage(&img_gray);
	return pre;
}

IplImage *DrawVE(IplImage *img, vector<Vertex> v, vector<Edge> e)
{
	IplImage *ret = cvCloneImage(img);
	vector<Vertex>::const_iterator viter;
	vector<Edge>::const_iterator eiter;
	
	for(viter = v.begin() ; viter != v.end() ; viter++) {
	}
	for(eiter = e.begin() ; eiter != e.end() ; eiter++) {
	}
	
	return ret;
}
