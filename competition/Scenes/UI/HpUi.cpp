#include"DxLib.h"
#include"HpUI.h"

HpUI::HpUI() :
	hp_table(),
	hp_bar()
{
	// リソース管理インスタンス取得
	ResourceManager* rm = ResourceManager::GetInstance();
	hp_table = rm->GetImages("Resource/Images/HPUi/Health_Bar_Table.png")[0];
	hp_bar = rm->GetImages("Resource/Images/HPUi/Health_Dot.png")[0];
}

HpUI::~HpUI()
{

}

void HpUI::Initialize()
{

}

void HpUI::Update()
{

}

void HpUI::Draw() const
{
	// HPバー(プレイヤー)の描画
	DrawRotaGraph(200, 35, 1.0, 0, hp_table, 1, 0);
	for (int i = 0; i < 11; i++)
	{
		DrawRotaGraph((20 + (i * 30)), 35, 1.0, 0, hp_bar, 1, 0);
	}
	// DrawRotaGraph(510, 80, 1.0, 0, hp_bar, 1, 0);
}

void HpUI::Finalize()
{

}
