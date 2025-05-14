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
	window[3] = rm->GetImages("Resource/Images/LevelUpUi/window_3.png")[0];

	power[0] = rm->GetImages("Resource/Images/LevelUpUi/Health.png")[0];
	power[1] = rm->GetImages("Resource/Images/LevelUpUi/Damage.png")[0];
	power[2] = rm->GetImages("Resource/Images/LevelUpUi/Speed.png")[0];
	power[3] = rm->GetImages("Resource/Images/LevelUpUi/X100.png")[0];

	power_icon[0] = rm->GetImages("Resource/Images/LevelUpUi/HP_Icon.png")[0];
	power_icon[1] = rm->GetImages("Resource/Images/LevelUpUi/Damage_Icon.png")[0];
	power_icon[2] = rm->GetImages("Resource/Images/LevelUpUi/Speed_Icon.png")[0];
	power_icon[3] = rm->GetImages("Resource/Images/LevelUpUi/Close_BTN.png")[0];
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
		//抽選
		int nums[3] = { 0,0,0 };
		Lottery(nums);
		for (int i = 0; i < 3; i++)
		{
			//抽選結果
			switch (nums[i])
			{
			case STATS_HP:
				lot[i] = ePowerUp::eHp;
				break;
			case STATS_DAMAGE:
				lot[i] = ePowerUp::eDamage;
				break;
			case STATS_SPEED:
				lot[i] = ePowerUp::eSpeed;
				break;
			case WAPON_3WAY:
				lot[i] = ePowerUp::eThreeway;
			default:
				break;
			}

			//画像変更
			lot_str[i] = power[nums[i]];
			lot_icon[i] = power_icon[nums[i]];
		}
	}
	old_flag = flag;
}

void LevelUpUI::Draw(PlayerStats stats) const
{

	float choice_size[3] = { 1.0,1.0,1.0 };
	choice_size[cursor] = 1.3;

	int pluse_x = 120;

	//外枠
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 180);
	DrawRotaGraph(pluse_x + 640, 360, 0.9, 0, window[0], 1, 0);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	DrawRotaGraph(pluse_x + 640, 80, 1.0, 0, window[1], 1, 0);
	//内枠
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
	DrawRotaGraph(pluse_x + 360, 400, 0.6 * choice_size[0], 0, window[2], 1, 0);
	DrawRotaGraph(pluse_x + 640, 400, 0.6 * choice_size[1], 0, window[2], 1, 0);
	DrawRotaGraph(pluse_x + 920, 400, 0.6 * choice_size[2], 0, window[2], 1, 0);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	//強化内容（文字）
	DrawRotaGraph(pluse_x + 360, 440, 0.6 * choice_size[0], 0, lot_str[0], 1, 0);
	DrawRotaGraph(pluse_x + 640, 440, 0.6 * choice_size[1], 0, lot_str[1], 1, 0);
	DrawRotaGraph(pluse_x + 920, 440, 0.6 * choice_size[2], 0, lot_str[2], 1, 0);
	//強化内容（アイコン）
	DrawRotaGraph(pluse_x + 360, 340, 0.8 * choice_size[0], 0, lot_icon[0], 1, 0);
	DrawRotaGraph(pluse_x + 640, 340, 0.8 * choice_size[1], 0, lot_icon[1], 1, 0);
	DrawRotaGraph(pluse_x + 920, 340, 0.8 * choice_size[2], 0, lot_icon[2], 1, 0);


	//現在ステータス描画
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 180);
	DrawRotaGraph(70, 400, 0.4, 0, window[3], 1, 0);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	int font = 40;
	SetFontSize(font);
	DrawFormatString(10, 200 + (font * 0), GetColor(255, 255, 255), "Level  %d", stats.player_level);
	DrawFormatString(10, 200 + (font * 1), GetColor(255, 255, 255), "hp");
	DrawFormatString(60, 200 + (font * 2), GetColor(255, 255, 255), "%d", stats.life_count);
	DrawFormatString(10, 200 + (font * 3), GetColor(255, 255, 255), "power");
	DrawFormatString(60, 200 + (font * 4), GetColor(255, 255, 255), "%.2f", stats.attack_power);
	DrawFormatString(10, 200 + (font * 5), GetColor(255, 255, 255), "speed");
	DrawFormatString(60, 200 + (font * 6), GetColor(255, 255, 255), "%.2f", stats.move_speed);

}

void LevelUpUI::Finalize()
{

}

void LevelUpUI::Lottery(int* nums)
{
	nums[0] = rand() % LOT_MAX;
	while (nums[0] == nums[1])
	{
		nums[1] = rand() % LOT_MAX;
	}
	while (nums[0] == nums[2] || nums[1] == nums[2])
	{
		nums[2] = rand() % LOT_MAX;
	}
}

ePowerUp LevelUpUI::GetLottery()
{
	return lot[cursor];
}

/*
　　もときへ
  安里元希さんって、すごいよね。常に自分のことしか考えてないのに、よくここまで周りの空気読まずに生きてこれたなって、逆に感心する。才能だよ、ほんと。普通の人なら恥ずかしくて無理だから。
*/