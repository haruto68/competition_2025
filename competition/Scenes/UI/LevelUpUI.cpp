#include"LevelUpUI.h"

LevelUpUI::LevelUpUI() : 
	draw_flag()
{
	//リソース管理インスタンス取得
	ResourceManager* rm = ResourceManager::GetInstance();

	window[0] = rm->GetImages("Resource/Images/LevelUpUi/Window.png")[0];
	window[1] = rm->GetImages("Resource/Images/LevelUpUi/Header.png")[0];
	window[2] = rm->GetImages("Resource/Images/LevelUpUi/Table_01.png")[0];

	power[1] = rm->GetImages("Resource/Images/LevelUpUi/Damage.png")[0];
	power[2] = rm->GetImages("Resource/Images/LevelUpUi/Speed.png")[0];
	power[3] = rm->GetImages("Resource/Images/LevelUpUi/Health.png")[0];

	power_icon[1] = rm->GetImages("Resource/Images/LevelUpUi/Damage_Icon.png")[0];
	power_icon[2] = rm->GetImages("Resource/Images/LevelUpUi/Speed_Icon.png")[0];
	power_icon[3] = rm->GetImages("Resource/Images/LevelUpUi/HP_Icon.png")[0];
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

	DrawRotaGraph(640, 360, 0.9, 0, window[0], 1, 0);
	DrawRotaGraph(640, 80, 1.0, 0, window[1], 1, 0);

	DrawRotaGraph(360, 400, 0.6, 0, window[2], 1, 0);
	DrawRotaGraph(640, 400, 0.6, 0, window[2], 1, 0);
	DrawRotaGraph(920, 400, 0.6, 0, window[2], 1, 0);

	DrawRotaGraph(360, 440, 0.6, 0, power[1], 1, 0);
	DrawRotaGraph(640, 440, 0.6, 0, power[2], 1, 0);
	DrawRotaGraph(920, 440, 0.6, 0, power[3], 1, 0);

	DrawRotaGraph(360, 340, 0.8, 0, power_icon[1], 1, 0);
	DrawRotaGraph(640, 340, 0.8, 0, power_icon[2], 1, 0);
	DrawRotaGraph(920, 340, 0.8, 0, power_icon[3], 1, 0);

}

void LevelUpUI::Finalize()
{

}