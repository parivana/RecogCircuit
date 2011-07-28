#include <stdlib.h>
#include <opencv/cv.h>

#include "Recognition.h"
#include "desc_type.h"
#include "LinkedList.h"

static void FindElement(IplImage *img)
{
	Element e;

	// write your element recognition code here...
	// if you want to add new Element to linked list,
	// you have to call ElementAdd function with passing an Element.
	//

	// here is sample code...
	//
	e.type = RESISTOR;
	e.rect.x = 0;
	e.rect.y = 0;
	e.rect.width = 50;
	e.rect.height = 50;
	e.param.value = 200;
	strcpy(e.name, "R1");
	e.next = NULL;
	ElementAdd(e);
}

static void Wiring(IplImage *img)
{
	Element *c = &listhead;
	// write your wiring recognition code here...
	
	// here is sample code...
	// 
	while(c->next != NULL) {
		c = c->next;
		c->pnode = 0;	c->nnode = 1;
	}
}

void DoRecog(IplImage *img)
{
	FindElement(img);

	Wiring(img);
}

