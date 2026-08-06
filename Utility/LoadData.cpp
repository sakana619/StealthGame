#include "LoadData.h"
#include<unordered_map>
#include<vector>
#include<string>

#include<fstream>
#include<sstream>
#include<cassert>

LoadData::Csv LoadData::LoadRaw(const std::string& path)
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

std::vector<std::string> LoadData::Split(const std::string& string, char separate) {

	std::vector<std::string> split;

	std::string buf;

	std::stringstream ss(string);

	while (std::getline(ss, buf, separate)) {
		split.push_back(buf);
	}

	return split;

}
