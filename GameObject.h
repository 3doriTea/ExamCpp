#pragma once
#include <vector>

class GameObject
{
public:
	GameObject();
	virtual ~GameObject();
	virtual void Update() = 0;
	virtual void Draw() = 0;
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
