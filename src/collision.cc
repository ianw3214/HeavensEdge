#include "collision.h"

bool isColliding(Shape& shape1, Shape& shape2) {
	if (shape1.type == RECT && shape2.type == RECT) {
		Rectangle& shape1rect = static_cast<Rectangle&>(shape1);
		Rectangle& shape2rect = static_cast<Rectangle&>(shape2);
		return collisionRectRect(shape1rect, shape2rect);
	}
	if (shape1.type == LINE && shape2.type == LINE) {
		Line& shape1line = static_cast<Line&>(shape1);
		Line& shape2line = static_cast<Line&>(shape2);
		return collisionLineLine(shape1line, shape2line);
	}
	if ((shape1.type == RECT && shape2.type == LINE) || (shape1.type == LINE && shape2.type == RECT)) {
		Rectangle& shapeRect = shape1.type == RECT ? static_cast<Rectangle&>(shape1) : static_cast<Rectangle&>(shape2);
		Line& shapeLine = shape1.type == LINE ? static_cast<Line&>(shape1) : static_cast<Line&>(shape2);
		return collisionLineRect(shapeLine, shapeRect);
	}
	// temporarily return false for any other case.
	return false;
}

bool collisionRectRect(const Rectangle& rect1, const Rectangle& rect2) {
	if (rect1.x < rect2.x + rect2.w && rect1.x + rect1.w > rect2.x &&
		rect1.y < rect2.y + rect2.h && rect1.h + rect1.y > rect2.y) {
		// Collision detected
		return true;
	}
	return false;
}

bool collisionLineLine(const Line& line1, const Line& line2) {
	float denominator = ((line1.x2 - line1.x) * (line2.y2 - line2.y) - (line1.y2 - line1.y) * (line2.x2 - line2.x));
	float numerator1 = ((line1.y - line2.y) * (line2.x2 - line2.x) - (line1.x - line2.x) * (line2.y2 - line2.y));
	float numerator2 = ((line1.y - line2.y) * (line1.x2 - line1.x) - (line1.x - line2.x) * (line1.y2 - line1.y));
	
	// temporarily return false if the lines are parallel
	if (denominator == 0) return false;

	float r = numerator1 / denominator;
	float s = numerator2 / denominator;

	return (r >= 0 && r <= 1) && (s >= 0 && s <= 1);
}

bool collisionLineRect(const Line& line, const Rectangle& rect) {
	// separate the rectangles into 4 lines and check for collisions
	Line top(rect.x, rect.y, rect.x + rect.w, rect.y);
	if (collisionLineLine(line, top)) return true;
	Line left(rect.x, rect.y, rect.x, rect.y + rect.h);
	if (collisionLineLine(line, left)) return true;
	Line right(rect.x + rect.w, rect.y, rect.x + rect.w, rect.y + rect.h);
	if (collisionLineLine(line, right)) return true;
	Line bottom(rect.x, rect.y + rect.h, rect.x + rect.w, rect.y + rect.h);
	if (collisionLineLine(line, bottom)) return true;
	return false;
}