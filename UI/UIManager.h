#pragma once
#include<vector>
#include<memory>
#include<type_traits>

#include"UIBase.h"

/// <summary>
/// UIを管理するクラス
/// </summary>
class UIManager
{

public:

	UIManager();
	~UIManager();

	void Init();
	void Update(float deltaTime);
	void Draw();
	void End();

	/// <summary>
	/// UIの生成を行う
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <typeparam name="...Args"></typeparam>
	/// <param name="...args"></param>
	template<class T,class ...Args>
	T* CreateUI(Args&&... args);

	/// <summary>
	/// 指定のUIを探す
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <returns></returns>
	template<class T>
	T* FindUI();

private:

	/// <summary>
	/// 管理しているUI
	/// </summary>
	std::vector<std::unique_ptr<UIBase>>m_UIList;

};

template<class T, class ...Args>
inline T* UIManager::CreateUI(Args&& ...args)
{
	//継承しているかチェック
	static_assert(std::is_base_of<UIBase, T>::value, "is not base of UIBase");
	//生成
	auto ui = std::make_unique<T>(std::forward<Args>(args)...);
	//初期化
	ui->Init();
	//返還用のポインタ
	T* ptr = ui.get();
	//リストに追加
	m_UIList.push_back(std::move(ui));

	return ptr;

}

template<class T>
inline T* UIManager::FindUI()
{
	//継承しているかチェック
	static_assert(std::is_base_of<UIBase, T>::value, "is not base of UIBase");

	for (const auto& ui : m_UIList) {

		T* check = dynamic_cast<T*>(ui.get());
		//ダウンキャストが失敗していたら処理しない
		if (check == nullptr)continue;
		//見つかったものを返す
		return check;
	}
	//見つからなかったら
	return nullptr;

}
