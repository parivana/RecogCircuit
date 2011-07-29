#include <vector>
#include <opencv/cv.h>

#include "Recognition.h"
#include "Element.h"
#include "Wire.h"

using namespace std;

static vector<Element> FindElement(IplImage *img)
{
	vector<Element> emt;
	Element e;

	// write your element recognition code here...
	// if you want to add new Element to linked list,
	// you have to call ElementAdd function with passing an Element.
	//

	// here is sample code...
	//

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

vector<Element> DoRecog(IplImage *img)
{
	vector<Element> emt = FindElement(img);

	return Wiring(img, emt);
}

