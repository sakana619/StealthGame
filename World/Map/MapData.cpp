#include "MapData.h"
#include"../../Utility/Vector3.h"
#include<vector>

#include"../../Utility/Loader/LoadData.h"
#include"../../Utility/Loader/DataConvert.h"

namespace {
	//ステージデータのファイルパス
	const char* const kStageDataPath = ".\\Data\\Stage\\Stage.csv";

	//読み込み済みか
	bool isLoaded = false;
	//ステージのマップオブジェクトのデータ
	std::vector<std::vector<MapData::ObjectType>> stageData;

}

const Vector3 MapData::kSize::scale{ 0.05f, 0.05f, 0.05f };
const Vector3 MapData::kSize::offSetPos{ 0.0f, 0.0f, 0.0f };

std::vector<std::vector<MapData::ObjectType>> MapData::GetStageData()
{
	//読み込まれていなければステージの読み込み
	if (!isLoaded) {
		//ステージデータのcsvを取得
		auto stageDataCsv = Data::LoadRaw(kStageDataPath);

		//ステージのZサイズ
		int stageZSize = stageDataCsv.size();
		//データサイズの変更
		stageData.resize(stageZSize);

		for (int z = 0; z < stageZSize; z++) {
			//ステージのXサイズ
			int stageXSize = stageDataCsv[z].size();
			//データサイズの変更
			stageData[z].resize(stageXSize);

			for (int x = 0; x < stageXSize; x++) {
				//読み込んだデータをObjectTypeに変換して設定する
				stageData[z][x] = Data::Convert<MapData::ObjectType>(stageDataCsv[z][x]);

			}
		}

		//読み込み状態にする
		isLoaded = true;

	}

	return stageData;

}
