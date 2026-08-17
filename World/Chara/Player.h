#pragma once
#include"CharacterBase.h"

class Camera;
class EnemyManager;

class Player :public CharacterBase
{

public:

	Player();
	Player(Camera* pCamera);
	~Player()override = default;

	void Init()override;

	void Update(float deltaTime)override;

	void Draw()override;

	void End()override;

	/// <summary>
	/// 衝突結果の解決を行う
	/// </summary>
	/// <param name="result"></param>
	/// <param name="myData"></param>
	/// <param name="otherData"></param>
	/// <param name="other"></param>
	void ResolveCollision(
		const Collision::Result result,
		const CollisionData& myData,
		const CollisionData& otherData,
		CollisionTag other)override;

	void SetEnemyManager(EnemyManager* pEnemyManager);

private:

	Vector3 GetInputVectorRotedByCamera();

	void UpdateAnimation(float deltaTime);

	void Move();

	void Dodge();

private:

	enum class State {

		Idle,
		Run,
		Jump,
		Attack,
		Dead,

	};

	State m_state;

	bool m_isDodging;

	Camera* m_pCamera;

	EnemyManager* m_pEnemyManager;

};
