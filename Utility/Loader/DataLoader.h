#pragma once
#include"LoadData.h"
#include"DataBinder.h"

namespace DataLoader {

	template<typename T>
	std::vector<T>LoadMasterData(const std::string& path) {

		//データの読み込み
		Data::Csv rawData = Data::LoadRaw(path);
		//ヘッダーデータに変換
		std::vector<Data::HeaderData> datas = Data::ToHeaderData(rawData);

		std::vector<T>res;
		//メモリの確保
		res.reserve(rawData.size());

		for (auto data : datas) {

			res.emplace_back(Data::FromData<T>::Binding(data));

		}

		return res;

	}

}
