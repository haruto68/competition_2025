#include"LevelUpUI.h"

LevelUpUI::LevelUpUI() :
	old_flag(),
	cursor(0)
{
	//リソース管理インスタンス取得
	ResourceManager* rm = ResourceManager::GetInstance();

	window[0] = rm->GetImages("Resource/Images/LevelUpUi/Window.png")[0];
	window[1] = rm->GetImages("Resource/Images/LevelUpUi/Header.png")[0];
	window[2] = rm->GetImages("Resource/Images/LevelUpUi/Table_01.png")[0];

	power[0] = rm->GetImages("Resource/Images/LevelUpUi/Damage.png")[0];
	power[1] = rm->GetImages("Resource/Images/LevelUpUi/Speed.png")[0];
	power[2] = rm->GetImages("Resource/Images/LevelUpUi/Health.png")[0];

	power_icon[0] = rm->GetImages("Resource/Images/LevelUpUi/Damage_Icon.png")[0];
	power_icon[1] = rm->GetImages("Resource/Images/LevelUpUi/Speed_Icon.png")[0];
	power_icon[2] = rm->GetImages("Resource/Images/LevelUpUi/HP_Icon.png")[0];
}

LevelUpUI::~LevelUpUI()
{

}

void LevelUpUI::Initialize()
{

}

void LevelUpUI::Update(bool flag)
{
	//強化内容抽選会
	if (old_flag != flag)
	{
		for (int i = 0; i < 3; i++)
		{
			int random = rand() % 3;
			lottery[i] = power[random];
			lottery_icon[i] = power_icon[random];
		}
	}
	old_flag = flag;
}

void LevelUpUI::Draw() const
{

	float choice_size[3] = { 1.0,1.0,1.0 };
	switch (cursor)
	{
	case 0:
		choice_size[0] = 1.3;
		break;
	case 1:
		choice_size[1] = 1.3;
		break;
	case 2:
		choice_size[2] = 1.3;
		break;
	default:
		break;
	}

	//外枠
	DrawRotaGraph(640, 360, 0.9, 0, window[0], 1, 0);
	DrawRotaGraph(640, 80, 1.0, 0, window[1], 1, 0);
	//内枠
	DrawRotaGraph(360, 400, 0.6 * choice_size[0], 0, window[2], 1, 0);
	DrawRotaGraph(640, 400, 0.6 * choice_size[1], 0, window[2], 1, 0);
	DrawRotaGraph(920, 400, 0.6 * choice_size[2], 0, window[2], 1, 0);
	//強化内容（文字）
	DrawRotaGraph(360, 440, 0.6 * choice_size[0], 0, lottery[0], 1, 0);
	DrawRotaGraph(640, 440, 0.6 * choice_size[1], 0, lottery[1], 1, 0);
	DrawRotaGraph(920, 440, 0.6 * choice_size[2], 0, lottery[2], 1, 0);
	//強化内容（アイコン）
	DrawRotaGraph(360, 340, 0.8 * choice_size[0], 0, lottery_icon[0], 1, 0);
	DrawRotaGraph(640, 340, 0.8 * choice_size[1], 0, lottery_icon[1], 1, 0);
	DrawRotaGraph(920, 340, 0.8 * choice_size[2], 0, lottery_icon[2], 1, 0);

}

void LevelUpUI::Finalize()
{

}