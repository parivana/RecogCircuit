#include <string.h>

#include "Element.h"
#include "Rect.h"

Element::Element(const char *name, UIntRect rect)
{
	strncpy(this->name, name, ENAME_SIZE);
	this->rect = rect;
}

Element::~Element()
{
	if(this->param)
		delete this->param;
}

void Element::setName(const char *name) 
{
	strncpy(this->name, name, ENAME_SIZE);
}

void Element::setParam(const char *param)
{
	int length = strlent(param);
	if(this->param)
		delete this->param;

	this->param = new char[length];
	strncpy(this->param, param, length);
}

void Element::setRect(
		unsigned int left,
		unsigned int top,
		unsigned int right,
		unsigned int bottom) 
{
	this->rect.left = left;
	this->rect.top = top;
	this->rect.right = right;
	this->rect.bottom = bottom;
}
