#include "GameObject.h"

size_t totalGameObjectCount{ 0 };

GameObject::GameObject(const bool _isAlive, const bool _isRegister) :
	isAlive_{ _isAlive }  // ê∂Ç´ÇƒÇ¢ÇÈ
{
	totalGameObjectCount++;
	if (_isRegister)
	{
		AddGameObject(this);
	}
	// Empty
}

GameObject::~GameObject()
{
	totalGameObjectCount--;
	// Empty
}
