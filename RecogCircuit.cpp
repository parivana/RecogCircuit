#include <string.h>
#include <opencv/cv.h>
#include <opencv/highgui.h>

#include "desc_type.h"
#include "Recognition.h"
#include "DescWriter.h"
#include "LinkedList.h"

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
	DoRecog(circuit);

	anl.type = DC;
	strcpy(anl.u.dc.srcname, "vin");
	anl.u.dc.vstart = 0;
	anl.u.dc.vstop = 5;
	anl.u.dc.vincr = 0.1;

	char *desc;
	char cname[8] = "sample";
	desc = DescWriter(cname, anl);

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
	Element *c = &listhead;
	IplImage *recog = cvCloneImage(img);

	CvScalar color = cvScalar(0, 0, 255);
	while(c->next != NULL) {
		c = c->next;
		// draw element region
		cvDrawRect(recog, 
				cvPoint(c->rect.x, c->rect.y), 
				cvPoint(c->rect.x + c->rect.width, 
					c->rect.y + c->rect.height), 
				color);
	}

	return recog;
}
