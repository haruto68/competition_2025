#include "Score.h"

// ��p(�\���̂ō쐬�\)
 int Score::stagelevel = 0;
 int Score::level = 0;
 int Score::power = 0;
 int Score::hp = 0;
 int Score::speed = 0;
 float Score::cool_time = 0;
 int Score::hit_range = 0;
 bool Score::three_way = false;
 int  Score::drone = 0;
 // int Score::bullet_speed = 0;

Score::Score()
{
	
}

Score::~Score()
{

}

void Score::Initialize()
{
	ResourceManager* rm = ResourceManager::GetInstance();
}

void Score::Update()
{

}

void Score::Draw() const
{
	
}

void Score::Finalize()
{

}

void Score::SetPlayerLevel(int p_level)
{
	level = p_level;
}

void Score::SetPlayerHp(int p_hp)
{
	hp = p_hp;
}

void Score::SetPlayerPower(int p_power)
{
	// ���̃p���[��1����������
	power = (p_power - 1);
}

void Score::SetPlayerSpeed(int p_speed)
{
	// ��񋭉������100�����邽�߁����ڂ����5����������
	speed = ((p_speed / 5) - 19);
}

void Score::SetPlayerCoolTime(float p_cooltime)
{
	cool_time = p_cooltime;
}

void Score::SetPlayerHitRange(int p_hitrange)
{
	// ���擾���邲�Ƃ�2.0���������邽��
	hit_range = (p_hitrange / 2);
}

void Score::SetPlayerThreeWay(bool p_threeway)
{
	// ��񂫂肾����擾������bool�^(�擾�������A�擾���Ă��Ȃ���)
	// ���擾�����LvMAX
	three_way = p_threeway;
}

void Score::SetPlayerDrone(int p_drone)
{
	// �h���[����I����������drone_count���Q�Ƃ��Ă��邽�߁A
	// �����ɂȂ��Ă����擾������m�F�\���ǔj�󂳂ꂽ���̂��J�E���g����(���擾�����LvMAX)
	drone = p_drone;
}

int Score::SetPlayerHp()
{
	return hp;
}

int Score::GetPlayerLevel()
{
	return level;
}

int Score::GetPlayerPower()
{
	return power;
}

int Score::GetPlayerSpeed()
{
	return speed;
}

int Score::GetPlayerCoolTime()
{
	return cool_time;
}

int Score::GetPlayerHitRange()
{
	return hit_range;
}

bool Score::GetPlayerThreeWay()
{
	return three_way;
}

int Score::GetPlayerDrone()
{
	return drone;
}
