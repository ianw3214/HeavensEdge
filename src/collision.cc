#include "collision.h"

bool isColliding(Shape& shape1, Shape& shape2) {
	if (shape1.type == RECT && shape2.type == RECT) {
		Rectangle& shape1rect = static_cast<Rectangle&>(shape1);
		Rectangle& shape2rect = static_cast<Rectangle&>(shape2);
		return collisionRectRect(shape1rect, shape2rect);
	}
	// temporarily return false for any other case.
	return false;
}

bool collisionRectRect(Rectangle& rect1, Rectangle& rect2) {
	if (rect1.x < rect2.x + rect2.w && rect1.x + rect1.w > rect2.x &&
		rect1.y < rect2.y + rect2.h && rect1.h + rect1.y > rect2.y) {
		// Collision detected
		return true;
	}
	return false;
}