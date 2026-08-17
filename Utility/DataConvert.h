#pragma once
#include<string>
#include<cassert>
#include"../World/Map/MapData.h"

namespace Data {

	/// <summary>
	/// 読み込んだデータを変換する
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <param name="str"></param>
	/// <returns></returns>
	template<typename T>
	T Convert(std::string& str) {

		return T{};
	}

	/// <summary>
	/// intに変換
	/// </summary>
	/// <param name="str"></param>
	/// <returns></returns>
	template<>
	inline int Convert<int>(std::string& str) {
		return std::stoi(str);
	}

	/// <summary>
	/// floatに変換
	/// </summary>
	/// <param name="str"></param>
	/// <returns></returns>
	template<>
	inline float Convert<float>(std::string& str) {
		return std::stof(str);
	}

	/// <summary>
	/// doubleに変換
	/// </summary>
	/// <param name="str"></param>
	/// <returns></returns>
	template<>
	inline double Convert<double>(std::string& str) {
		return std::stod(str);
	}

	/// <summary>
	/// boolに変換
	/// </summary>
	/// <param name="str"></param>
	/// <returns></returns>
	template<>
	inline bool Convert<bool>(std::string& str) {
		if (str == "false" || str == "0")return false;
		if (str == "true" || str == "1")return true;

		assert(false && "Convert<bool> ");
		return false;
	}

	/// <summary>
	/// MapObjectに変換
	/// </summary>
	/// <param name="str"></param>
	/// <returns></returns>
	template<>
	inline MapData::ObjectType Convert<MapData::ObjectType>(std::string& str) {

		if (str == "Floor" || str == "0")return MapData::ObjectType::Floor;
		if (str == "Wall" || str == "1")return MapData::ObjectType::Wall;

		assert(false && "");
		return MapData::ObjectType::Invalid;

	}

}
