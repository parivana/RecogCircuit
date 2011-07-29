#ifndef __RECT_H__
#define __RECT_H__

template <class T>
struct Rect{
	Rect() : left(), right(), top(), bottom() {}
	Rect(T left, T top, T right, T bottom) :
		left(left), top(top), right(right), bottom(bottom) {}
	T left, right;
	T top, bottom;
};

typedef struct Rect<unsigned int> UIntRect;

#endif // __RECT_H__

