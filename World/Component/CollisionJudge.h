#pragma once

namespace Collision {
	class Shape;
	struct Result;
}

namespace CollisionJudge {

	/// <summary>
	/// aのbに対する衝突結果を返す
	/// </summary>
	/// <param name="a"></param>
	/// <param name="b"></param>
	/// <returns></returns>
	Collision::Result CheckCollision(const Collision::Shape& a, const Collision::Shape& b);

}
