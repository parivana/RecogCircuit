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
<<<<<<< HEAD

	if(this->wire)
		delete this->wire;
=======
>>>>>>> 4637b1cd3273ae2537e2231d65eb083c41dc937c
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
<<<<<<< HEAD

void Element::setNport(int nport)
{
	this->nport = nport;
}

int Element::makeWire()
{
	if(this->nport <= 0)
		return -1;

	this->wire = new (Wire *)[this->nport];
	return 0;
}

int Element::setWire(Wire *w, int port)
{
	if(!this->wire)
		return -1;

	this->wire[port] = w;
	return 0;
}

Wire *Element::getWire(int port) 
{
	if(!this->wire)
		return NULL;

	if(port >= this->nport)
		return NULL;

	return this->wire[port];
}
=======
>>>>>>> 4637b1cd3273ae2537e2231d65eb083c41dc937c
