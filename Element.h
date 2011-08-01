#ifndef __ELEMENT_H__
#define __ELEMENT_H__

#include "Rect.h"

#define ENAME_SIZE 8

class Element {
	public:
		Element() {};
		Element(const char *name, UIntRect rect);

		virtual ~Element();

		void setName(const char *name);
		char *getName() { return name; };

		void setParam(const char *name);
		char *getParam() { return param; };

		void setRect(unsigned int left, unsigned int top,
				unsigned int right, unsigned int bottom);
		//void setRect(UIntRect r) { this->rect = r; };
		UIntRect getRect() { return rect; };

	private:
		char name[ENAME_SIZE];
		char *param;
		int type;
		UIntRect rect;
};

#endif // __ELEMENT_H__
