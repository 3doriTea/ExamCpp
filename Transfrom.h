#pragma once
#include "Vector2Ref.h"
#include <DirectXMath.h>
#include "Vector2Ref.h"

class Transform
{
public:
	Transform(const Vector2Ref& _position);
	~Transform() {};

private:
	DirectX::XMMATRIX translate_;
	DirectX::XMMATRIX rotate_;
	DirectX::XMMATRIX scale_;

	Vector2Ref position_;
	float angle_;
	Vector2Ref scale_;
};
