#pragma once
#include<vector>
#include<string>
#include<unordered_map>

/// <summary>
/// データ読み込み
/// </summary>
namespace Data {

	/// <summary>
	/// 読み込むデータのエイリアス
	/// </summary>
	using Csv = std::vector<std::vector<std::string>>;

	using HeaderData = std::unordered_map<std::string, std::string>;

	/// <summary>
	/// 型変換されない状態で読み込む
	/// </summary>
	/// <param name="path"></param>
	/// <returns></returns>
	Csv LoadRaw(const std::string& path);

	/// <summary>
	/// 読み込んだデータをヘッダーデータに変換
	/// </summary>
	/// <param name="csvData"></param>
	/// <returns></returns>
	std::vector<HeaderData> ToHeaderData(const Csv& csvData);

	/// <summary>
	/// 読み込んだデータを分割する
	/// </summary>
	/// <param name="string"></param>
	/// <param name="separate"></param>
	/// <returns></returns>
	std::vector<std::string> Split(const std::string& string, char separate = ',');

}
