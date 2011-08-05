#include <vector>
#include <string.h>
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
	IplImage *pre = cvCloneImage(img);
	
	cvThreshold(pre, pre, 128, 255, CV_THRESH_BINARY);
	return pre;
}
