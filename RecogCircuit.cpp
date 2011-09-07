#include <vector>
#include <string.h>
#include <math.h>
#include <opencv/cv.h>
#include <opencv/highgui.h>

#include "Recognition.h"
#include "DescWriter.h"
#include "Element.h"
#include "Analysis.h"

using namespace std;
using namespace cv;

IplImage *DrawVE(IplImage *, vector<Vertex>, vector<Edge);
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
	
	lines = cvHoughLines2(img_gray, storage, CV_HOUGH_STANDARD,
			1, CV_PI / 60, 50, 20, 0);

	for(int i = 0 ; i < lines->total ; i++) {
		float *line = (float *)cvGetSeqElem(lines, i);
		float rho = line[0];
		float theta = line[1];
		double a = cos(theta), b = sin(theta);
		double x0 = a * rho, y0 = b*rho;
		Point pt1(cvRound(x0 + 1000*(-b)), cvRound(y0 + 1000*(a)));
		Point pt2(cvRound(x0 - 1000*(-b)), cvRound(y0 - 1000*(a)));
		cvLine(pre, pt1, pt2, CV_RGB(0, 255, 0), 1, 8);
	}
	
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
