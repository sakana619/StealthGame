#pragma once
#include<array>

class Input
{

public:

	void Update();

	bool IsDown(int key);

	bool IsPressed(int key);

	bool IsReleased(int key);

	bool IsHold(int key);

private:

	static constexpr int kLogMax = 20;

	std::array<int, kLogMax>m_inputLog;

};
