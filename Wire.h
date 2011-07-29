#ifndef __WIRE_H__
#define __WIRE_H__

class Wire {
	public:
		Wire() : wire_number(wire_count++) {};
		~Wire() {};

		int getWireNum() { return wire_number; };
	private:
		static int wire_count = 0;
		int wire_number;
};

#endif // __WIRE_H__
