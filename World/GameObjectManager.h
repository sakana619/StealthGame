#pragma once
#include"GameObject.h"

#include<vector>
#include<memory>
#include<type_traits>

class GameObjectManager
{

public:

	GameObjectManager();
	~GameObjectManager();

	void Update(float deltaTime);
	void Draw();

	void CheckCollision();

	/// <summary>
	/// ゲームオブジェクトの生成を行う
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <typeparam name="...Args"></typeparam>
	/// <param name="...args"></param>
	/// <returns></returns>
	template<class T,class... Args>
	T* CreateObject(Args&&... args);

	/// <summary>
	/// 管理しているオブジェクトの取得
	/// </summary>
	/// <returns></returns>
	const std::vector<std::unique_ptr<GameObject>>& GetObjcts()const { return m_pObjects; }

private:

	/// <summary>
	/// 管理しているゲームオブジェクト
	/// </summary>
	std::vector<std::unique_ptr<GameObject>>m_pObjects;

};

template<class T, class ...Args>
inline T* GameObjectManager::CreateObject(Args && ...args)
{
	//GameObjectを継承しているか確認
	static_assert(std::is_base_of<GameObject, T>::value, "");

	auto obj = std::make_unique<T>(std::forward<Args>(args)...);

	obj->Init();

	T* rawPtr = obj.get();

	//スマートポインタをm_objectsに登録
	m_pObjects.push_back(std::move(obj));

	return rawPtr;

}
