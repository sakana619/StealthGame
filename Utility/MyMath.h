#pragma once

#include <DxLib.h>

namespace MyMath {

	constexpr float Epsilon = 0.00001f;

	constexpr float ToRadian = DX_PI_F / 180.0f;

	/// <summary>
	/// デグリー角度からラジアン角度へ変換
	/// </summary>
	/// <param name="deg">デグリー角度</param>
	/// <returns>ラジアン角度</returns>
	constexpr float DegToRad(float deg)
	{

		return deg * DX_PI_F / 180.0f;
	}

	/// <summary>
	/// ラジアン角度からデグリー角度へ変換
	/// </summary>
	/// <param name="rad">ラジアン角度</param>
	/// <returns>デグリー角度</returns>
	constexpr float RadToDeg(float rad)
	{

		return rad * 180.0f / DX_PI_F;
	}

	/// <summary>
	/// デグリー角度を-180°～180°の範囲に収める
	/// </summary>
	/// <param name="angle"></param>
	/// <returns></returns>
	constexpr float NormalizeAngle(float angle)
	{

		while (angle > 180.0f) angle -= 360.0f;
		while (angle < -180.0f) angle += 360.0f;

		return angle;
	}

	/// <summary>
	/// ラジアン角度を-π～πの範囲内に収める
	/// </summary>
	/// <param name="Rad"></param>
	/// <returns></returns>
	constexpr float NormalizeRadAngle(float angle) 
	{

		while (angle > DX_PI_F)angle -= DX_PI_F * 2;
		while (angle < -DX_PI_F)angle += DX_PI_F * 2;

		return angle;

	}

	/// <summary>
	/// valueの値を最小値min、最大値maxの値に収める
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <param name="value"></param>
	/// <param name="min"></param>
	/// <param name="max"></param>
	/// <returns></returns>
	template<typename T>
	constexpr T Clamp(T value, T min, T max)
	{
		if (value < min) return min;
		if (value > max) return max;
		return value;
	}

	/// <summary>
	/// 2つの値を比較して小さい方を取得
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <param name="a"></param>
	/// <param name="b"></param>
	/// <returns></returns>
	template<typename T>
	constexpr const T Min(const T a, const T b) {

		if (a < b)return a;
		return b;

	}

	/// <summary>
	/// 2つの値を比較して大きい方を取得
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <param name="a"></param>
	/// <param name="b"></param>
	/// <returns></returns>
	template<typename T>
	constexpr const T Max(const T a, const T b) {

		if (a > b)return a;
		return b;

	}

	/// <summary>
	/// 絶対値を取得
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <param name="a"></param>
	/// <returns></returns>
	template<typename T>
	constexpr const T Abs(const T check) {

		if (check < 0)return -check;
		return check;
	}

	template<typename T>
	constexpr const float Rate(const T value, const T max) {
		return value / max;
	}

	template<typename T>
	constexpr const  T Lerp(const T& target, const T& current, const float ratio) {
		return (target - current) * ratio + current;
	}

	template<typename T>
	constexpr void Swap(T* a, T* b) {

		T buf = a;
		a = b;
		b = buf;

	}

}
