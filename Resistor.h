#ifndef __RESISTOR_H__
#define __RESISTOR_H__

#include "Rect.h"
#include "Element.h"
#include "Wire.h"

class Resistor : public Element
{
	public:
		Resistor(const char *name, UIntRect rect) :
			Element(name, rect), value(0.0) {};
		Resistor(const char *name, UIntRect rect, 
				float value, Wire &p, Wire &n) : 
			Element(name, rect), value(value), p(p), n(n) {};
		~Resistor() {};

		void setValue(float value) { this.value = value; };
		float getValue() { return this.value; };

		void wiring(Wire *p, Wire *n) {
			this.p = p;	this.n = n; };
		Wire *getPositiveWire() { return p; };
		Wire *getNegativeWire() { return n; };
	
	private:
		float value;
		Wire *p, *n;
};

#endif // __RESISTOR_H__
