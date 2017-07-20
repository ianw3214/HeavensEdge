#pragma once

enum SHAPE_TYPE {
	RECT = 0,
	LINE = 1,
	CIRCLE = 2
};

struct Shape {
	int x, y;
	SHAPE_TYPE type;
	Shape() {}
	Shape(SHAPE_TYPE t) : type(t) {}
	Shape(int _x, int _y) : x(_x), y(_y) {}
	Shape(int _x, int _y, SHAPE_TYPE t) : type(t), x(_x), y(_y) {}
};

struct Rectangle : Shape {
	int w, h;
	Rectangle() : Shape(RECT) {}
	Rectangle(int _x, int _y) : Shape(_x, _y, RECT) {}
	Rectangle(int _x, int _y, int _w, int _h) : Shape(_x, _y, RECT), w(_w), h(_h) {}
	// copy constructor
	Rectangle(const Rectangle &obj) : Shape(obj.x, obj.y, RECT), w(obj.w), h(obj.h) {}
};

struct Line : Shape {
	int x2, y2;
	Line() : Shape(LINE) {}
	Line(int _x1, int _y1) : Shape(_x1, _y1, LINE) {}
	Line(int _x1, int _y1, int _x2, int _y2) : Shape(_x1, _y1, LINE) {
		x2 = _x2;
		y2 = _y2;
	}
	// copy constructor
	Line(const Line &obj) : Line(obj.x, obj.y, obj.x2, obj.y2) {}
};

struct Circle : Shape {
	int r;
	Circle() : Shape(CIRCLE) {}
	Circle(int x, int y, int rIn) : Shape(x, y, CIRCLE) , r(rIn) {}
	// copy constructor
	Circle(const Circle &obj) : Circle(obj.x, obj.y, obj.r) {}
};

// pass shape parameters by reference to avoid slicing	

// functions to get collisions
bool isColliding(Shape&, Shape&);

// helper functions for different collisions of different shapes
bool collisionRectRect(const Rectangle&, const Rectangle&);
bool collisionLineLine(const Line&, const Line&);
bool collisionLineRect(const Line&, const Rectangle&);
bool collisionCircleRect(const Circle&, const Rectangle&);

// further helper functions
int clamp(int, int, int);