#include <vector>
#include <string.h>
#include <opencv/cv.h>
#include <opencv/highgui.h>

#include "Recognition.h"
#include "DescWriter.h"
#include "Element.h"
#include "Analysis.h"

using namespace std;

IplImage *DrawRecogImage(IplImage *);

int main(int argc, char *argv[])
{
	if(argc < 2) {
		fprintf(stderr, "Usage : ./RecogCircuit.out [circuit_image]\n");
		exit(1);
	}

	IplImage* circuit = cvLoadImage(argv[1], -1);
	IplImage* recogcircuit;

	cvNamedWindow("Circuit Image", CV_WINDOW_AUTOSIZE);

	cvShowImage("Circuit Image", circuit);

	Analysis anl;
	vector<Element> emt = DoRecog(circuit);

	char *desc;
	char cname[8] = "sample";
	//desc = DescWriter(cname, anl);

	recogcircuit = DrawRecogImage(circuit);
	cvNamedWindow("Recognized Circuit Image", CV_WINDOW_AUTOSIZE);
	cvShowImage("Recognized Circuit Image", recogcircuit);

	cvWaitKey(0);
	cvReleaseImage(&circuit);
	cvReleaseImage(&recogcircuit);
	return 0;
}

// draw recognized element region on the original image...
IplImage *DrawRecogImage(IplImage *img)
{
	IplImage *recog = cvCloneImage(img);

	CvScalar color = cvScalar(0, 0, 255);

	return recog;
}
