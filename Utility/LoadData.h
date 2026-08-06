#pragma once
#include<vector>
#include<string>

namespace LoadData {

	using Csv = std::vector<std::vector<std::string>>;

	Csv LoadRaw(const std::string& path);

	std::vector<std::string> Split(const std::string& string, char separate = ',');

}
