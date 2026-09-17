#include "Input.h"

#include<DxLib.h>
#include<array>

namespace {
	//保持する期間 (フレーム)
	static constexpr int kLogMax = 20;
	//入力履歴
	std::array<int, kLogMax>m_inputLog;

}

void Input::Update()
{
	//入力状態を取得
	int inputState = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	//入力情報の更新
	for (int i = m_inputLog.size() - 1; i > 0; i--) {

		m_inputLog[i] = m_inputLog[i - 1];

	}

	// 最新の入力を格納
	m_inputLog[0] = inputState;

}

bool Input::IsDown(int key)
{
	return (m_inputLog[0] & key);
}

bool Input::IsPressed(int key)
{
	//現在の入力情報
	bool isNow = (m_inputLog[0] & key);
	//1F前の入力情報
	bool isLast = (m_inputLog[1] & key);

	//今のフレームは押されていて前のフレームが押されていなかったらtrue
	return (isNow && !isLast);
}

bool Input::IsReleased(int key)
{
	bool isNow = (m_inputLog[0] & key);
	bool isLast = (m_inputLog[1] & key);

	return(!isNow && isLast);

}

bool Input::IsHold(int key)
{

	//10フレーム押されていなかったらfalse
	for (const auto& e : m_inputLog) {

		if (e != key) {
			return false;
		}

	}

	return true;

}
