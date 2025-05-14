#include"LevelUI.h"

LevelUI::LevelUI() :
	// level_bar(),
	level(0),
	level_ui1(0),
	level_ui2(0)
{
	// リソース管理インスタンス取得
	ResourceManager* rm = ResourceManager::GetInstance();
	// level_bar = rm->GetImages("Resource/Images/LevelUi/Loading_Bar_1_2.png", 10, 10, 1, 32, 32);
	level_ui1 = rm->GetImages("Resource/Images/LevelUi/level_ui1.png")[0];
	level_ui2 = rm->GetImages("Resource/Images/LevelUi/level_ui2.png")[0];
}

LevelUI::~LevelUI()
{

}

void LevelUI::Initialize()
{

}

void LevelUI::Update()
{

}

void LevelUI::Draw() const
{
	// テスト用描画
	DrawRotaGraph(30, 700, 0.9, 0, level_ui1, 1, 0);
	DrawFormatString(640, 80, 0xff00ff, "%d", level);
	// DrawRotaGraph(58, 700, 0.9, 0, level_bar[1], 1, 0);
	// DrawRotaGraph(640, 80, 1.0, 0, window[1], 1, 0);

}

void LevelUI::Finalize()
{

}

void LevelUI::SetExperience(int exp)
{
	level = exp;
}
