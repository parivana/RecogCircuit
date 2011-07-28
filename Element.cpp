#include <string.h>

#include "Element.h"
#include "Rect.h"

Element::Element(const char *name, UIntRect rect)
{
	strncpy(this->name, name, ENAME_SIZE);
	this->rect = rect;
}

void Element::setName(const char *name) 
{
	strncpy(this->name, name, ENAME_SIZE);
}
