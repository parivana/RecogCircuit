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

	cvNot(img_gray, img_gray);
	//cvCanny(img_gray, img_gray, 50, 200, 3);
	cvCvtColor(img_gray, pre, CV_GRAY2BGR);
	CvSeq *lines = 0;
	CvMemStorage *storage = cvCreateMemStorage(0);

	//
	lines = cvHoughLines2(img_gray, storage, CV_HOUGH_PROBABILISTIC,
			3, CV_PI / 180, 100, 50, 3);
	for(int i = 0 ; i < lines->total ; i++) {
		CvPoint *line = (CvPoint *)cvGetSeqElem(lines,i);
		cvLine(pre, line[0], line[1], CV_RGB(0, 255, 0), 1, 1);
	}
	/*
	lines = cvHoughLines2(img_gray, storage, CV_HOUGH_STANDARD, 3,
			CV_PI / 36, 100, 0, 0);

	printf("%d\n", lines->total);
	for(int i = 0 ; i < lines->total ; i++) {
		double *line = (double *)cvGetSeqElem(lines, i);
		double rho = line[0];
		double theta = line[1];

		CvPoint pt1, pt2;
		double a = cos(theta), b = sin(theta);
		double x0 = a/rho, y0 = b/rho;
		pt1.x = cvRound(x0 + 1000 * (-b));
		pt1.y = cvRound(y0 + 1000 * (a));
		pt2.x = cvRound(x0 - 1000 * (-b));
		pt2.y = cvRound(y0 - 1000 * (a));
		cvLine(pre, pt1, pt2, CV_RGB(0, 0, 255), 3, 8);
	}
	*/
	/*
	double minVal, maxVal;
	cvCornerHarris(img_gray, pre, 3);
	cvMinMaxLoc(pre, &minVal, &maxVal, NULL, NULL, 0);
	double scale = 255 / (maxVal - minVal);
	cvConvertScale(pre, pre, scale, -minVal * scale);
	cvReleaseImage(&img_gray);
	*/
	/*
	IplImage *dst1 = cvCloneImage(img);
	IplImage *dst2 = cvCloneImage(img);
	IplImage *eig_img = cvCreateImage(cvGetSize(img_gray), 
			IPL_DEPTH_32F, 1);
	IplImage *temp_img = cvCreateImage(cvGetSize(img_gray), 
			IPL_DEPTH_32F, 1);
	CvPoint2D32f *corners = (CvPoint2D32f *)cvAlloc(
			corner_count * sizeof(CvPoint2D32f));

	cvGoodFeaturesToTrack(img_gray, eig_img, temp_img, corners,
			&corner_count, 0.1, 15);
	cvFindCornerSubPix(img_gray, corners, corner_count,
			cvSize(3, 3), cvSize(-1, -1),
			cvTermCriteria(CV_TERMCRIT_ITER|CV_TERMCRIT_EPS, 20, 0.03));

	for(int i = 0 ; i < corner_count ; i++) {
		cvCircle(dst1, cvPointFrom32f(corners[i]), 3,
				CV_RGB(255, 0, 0), 2);
	}

	corner_count = 150;
	cvGoodFeaturesToTrack(img_gray, eig_img, temp_img, corners,
			&corner_count, 0.1, 15, NULL, 3, 1, 0.01);
	cvFindCornerSubPix(img_gray, corners, corner_count,
			cvSize(3, 3), cvSize(-1, -1),
			cvTermCriteria(CV_TERMCRIT_ITER | CV_TERMCRIT_EPS, 20, 0.03));

	for(int i = 0 ; i < corner_count ; i++) {
		cvCircle(dst2, cvPointFrom32f(corners[i]), 3, CV_RGB(0, 0, 255),
				2);
	}

	cvNamedWindow("EigenVal", CV_WINDOW_AUTOSIZE);
	cvShowImage("EigenVal", dst1);
	cvNamedWindow("Harris", CV_WINDOW_AUTOSIZE);
	cvShowImage("Harris", dst2);
	cvWaitKey(0);

	cvReleaseImage(&eig_img);
	cvReleaseImage(&temp_img);
	cvReleaseImage(&dst1);
	cvReleaseImage(&img_gray);
	*/
	return pre;
}

