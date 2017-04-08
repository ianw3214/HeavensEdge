#pragma once

enum SHAPE_TYPE {
	RECT = 0
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
};

// pass shape parameters by reference to avoid slicing	

// functions to get collisions
bool isColliding(Shape&, Shape&);

// helper functions for different collisions of different shapes
bool collisionRectRect(Rectangle&, Rectangle&);