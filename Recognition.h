#ifndef __RECOGNITION_H__
#define __RECOGNITION_H__

#include <vector>
#include <opencv/cv.h>

#include "Element.h"

using namespace std;

vector<Element> DoRecog(IplImage *);

#endif // __RECOGNITION_H__
