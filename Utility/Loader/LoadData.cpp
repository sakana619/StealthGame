#include "LoadData.h"
#include<unordered_map>
#include<vector>
#include<string>

#include<fstream>
#include<sstream>
#include<cassert>

Data::Csv Data::LoadRaw(const std::string& path)
{

	Csv res;

	//ファイルを開く
	std::ifstream ifs(path);

	//ファイルを開けたかチェック
	if (ifs.fail()) {
		//即時リターン
		assert(false && "");
		return res;
	}
	//保管用の変数
	std::string line;

	while (std::getline(ifs, line)) {
		//1行分割して格納
		res.push_back(Split(line));
	}

	return res;

}

std::vector<Data::HeaderData> Data::ToHeaderData(const Csv& csvData)
{

	std::vector<HeaderData>datas;

	//空チェック
	if (csvData.empty()) {
		return datas;
	}

	//1行目をヘッダーとして保管
	const std::vector<std::string> header = csvData[0];
	//ヘッダーのサイズ
	size_t headerSize = header.size();

	//2行目から読み込む
	for (size_t i = 1; i < csvData.size(); i++) {
		//読み込む列を取得
		const auto& line = csvData[i];

		HeaderData data;

		for (size_t j = 0; j < headerSize; j++) {
			//範囲外にアクセスしない用にする
			if (j > line.size()) continue;

			data[header[j]] = line[j];

		}
		//読み込んだデータリストに追加
		datas.push_back(data);

	}

	return datas;

}

std::vector<std::string> Data::Split(const std::string& string, char separate) {

	std::vector<std::string> split;

	std::string buf;

	std::stringstream ss(string);

	while (std::getline(ss, buf, separate)) {
		split.push_back(buf);
	}

	return split;

}
