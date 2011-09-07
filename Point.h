#ifndef __POINT_H__
#define __POINT_H__

template <class T>
struct Point{
	Point() : left(0), right(0) {}
	Point(T x, T y) :
		x(x), y(y) {}
	T x, y;
};

typedef struct Point<int> Point2i;

#endif // __POINT_H__
