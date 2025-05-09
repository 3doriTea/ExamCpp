#pragma once
#include "Vector2Ref.h"
#include <DirectXMath.h>

class Transform
{
public:
	Transform(const Vector2Ref& _position);
	~Transform();

private:
	DirectX::XMMATRIX translate_;
	DirectX::XMMATRIX rotate_;
	DirectX::XMMATRIX scale_;
	DirectX::XMVECTORF32 qurtanion_;
};
