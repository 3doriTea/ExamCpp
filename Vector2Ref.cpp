#include "Vector2Ref.h"

Vector2Ref::Vector2Ref(float& _xRef, float& _yRef) :
	x_{ _xRef },
	y_{ _yRef }
{
}

Vector2Ref::~Vector2Ref()
{
}
