#ifndef __ELEMENT_H__
#define __ELEMENT_H__

#include "Rect.h"

#define ENAME_SIZE 8

class Element {
	public:
		Element() {};
		Element(const char *name, UIntRect rect);

		void setName(const char *name);
		char *getName() { return name; };

	private:
		char name[ENAME_SIZE];
		UIntRect rect;

	protected:
		virtual ~Element() {};
};

#endif // __ELEMENT_H__
