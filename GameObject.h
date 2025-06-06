#pragma once
#include <vector>
#include "Global.h"

class GameObject
{
public:
	GameObject(const bool _isAlive = true, const bool _isRegister = true);
	virtual ~GameObject();
	virtual void Update() = 0;
	virtual void Draw() = 0;

	inline void SetIsAlive(const bool _isAlive)
	{
		isAlive_ = _isAlive;
	}
	inline bool IsAlive() const
	{
		return isAlive_;
	}

protected:
	bool isAlive_;  // ê∂Ç´ÇƒÇ¢ÇÈ true / false
};

extern std::vector<GameObject*> pGameObjects;
extern std::vector<GameObject*> pNewGameObjects;

template<typename GameObjectT>
inline GameObjectT& AddGameObject()
{
	static_assert(std::is_base_of<GameObjectT, GameObject>::value);
	GameObjectT* pGameObject{ new GameObjectT{} };
	pNewGameObjects.push_back(pGameObject);

	return *pGameObject;
}

inline void AddGameObject(GameObject* _pGameObject)
{
	pNewGameObjects.push_back(_pGameObject);
}
