#include"LevelUpUI.h"

LevelUpUI::LevelUpUI() :
	draw_flag(),
	window(),
	table_01(),
	header()
{
	//リソース管理インスタンス取得
	ResourceManager* rm = ResourceManager::GetInstance();
	window = rm->GetImages("Resource/Images/LevelUpUI/Window.png")[0];
	table_01 = rm->GetImages("Resource/Images/LevelUpUI/Table_01.png")[0];
	header = rm->GetImages("Resource/Images/LevelUpUI/Header.png")[0];
}

LevelUpUI::~LevelUpUI()
{

}

void LevelUpUI::Initialize()
{

}

void LevelUpUI::Update(bool draw_flag)
{

}

void LevelUpUI::Draw() const
{

	DrawRotaGraph(640, 360, 0.9, 0, window, 1, 0);
	DrawRotaGraph(640, 80, 1.0, 0, header, 1, 0);


	DrawRotaGraph(360, 400, 0.6, 0, table_01, 1, 0);
	DrawRotaGraph(640, 400, 0.6, 0, table_01, 1, 0);
	DrawRotaGraph(920, 400, 0.6, 0, table_01, 1, 0);




}

void LevelUpUI::Finalize()
{

}