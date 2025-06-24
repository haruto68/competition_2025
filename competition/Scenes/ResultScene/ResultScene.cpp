#include"ResultScene.h"
#include"../../Utility/InputManager.h"
#include"../../Resource/ResourceManager.h"
//#define DEBUG 1

ResultScene::ResultScene() : 
	m_selectedbutton(selectedbutton::Title), //�����̓^�C�g���I��
	menu_num(0), 
	is_button(true), 
	back_ground_sound(0), 
	score(0), 
	back_ground_image(), 
	ranking(), 
	font(), 		
	window(),
	power_icon(),
	level(0),
	stagelevel(0),
	power(0),
	speed(0)
{
	// //���\�[�X�Ǘ��C���X�^���X�擾
	// ResourceManager* rm = ResourceManager::GetInstance();
	// 
	// //�摜�擾
	
	sounds_effect[0] = NULL;
	sounds_effect[1] = NULL;
}

ResultScene::~ResultScene()
{

}

void ResultScene::Initialize()
{
	//���\�[�X�Ǘ��C���X�^���X�擾
	ResourceManager* rm = ResourceManager::GetInstance();
	back_ground_location = Vector2D(D_WIN_MAX_X / 2, D_WIN_MAX_Y / 2);

	//�摜�擾
	back_ground_image = rm->GetImages("Resource/Images/back_ground/universe_asteroid03.png")[0];		// �w�i�摜
	// �����擾
	back_ground_sound = rm->GetSounds("Resource/Sounds/BGM/Title/Title.mp3");

	// �{�^�����艹
	sounds_effect[0] = rm->GetSounds("Resource/Sounds/SoundsEffect/Button/button_enter.mp3");
	// �I����
	sounds_effect[1] = rm->GetSounds("Resource/Sounds/SoundsEffect/Button/button_select.mp3");
	// �{�^�����艹�̉��ʂ̐ݒ�
	ChangeVolumeSoundMem(200, sounds_effect[0]);
	// �I�����̉��ʂ̐ݒ�
	ChangeVolumeSoundMem(200, sounds_effect[1]);
	//�I����ԃ��Z�b�g
	m_selectedbutton = selectedbutton::Title;

	// �����Đ�
	ChangeVolumeSoundMem(100, back_ground_sound);
	PlaySoundMem(back_ground_sound, DX_PLAYTYPE_BACK, TRUE);

	ranking = new RankingScene();
	// ranking->Initialize();

	// �t�H���g�̓o�^
	// font_name.push_back(CreateFontToHandle("�������ۃS�V�b�N", 70, 6));
	// font_name.push_back(CreateFontToHandle("�������ۃS�V�b�N", 40, 6));
	// font_name.push_back(CreateFontToHandle("�������ۃS�V�b�N", 50, 6));
	// font_name.push_back(CreateFontToHandle("�������ۃS�V�b�N", 100, 6));
	// font_name.push_back(CreateFontToHandle("�������ۃS�V�b�N", 80, 6));

	font[0] = CreateFontToHandle("�������ۃS�V�b�N", 40, 6);
	font[1] = CreateFontToHandle("�������ۃS�V�b�N", 50, 6);
	font[2] = CreateFontToHandle("�������ۃS�V�b�N", 70, 6);
	font[3] = CreateFontToHandle("�������ۃS�V�b�N", 80, 6);
	font[4] = CreateFontToHandle("�������ۃS�V�b�N", 100, 6);

	// power_icon[0] = rm->GetImages("Resource/Images/UpGrade_Icon/hp.png")[0];
	power_icon[0] = rm->GetImages("Resource/Images/UpGrade_Icon/power.png")[0];
	power_icon[1] = rm->GetImages("Resource/Images/UpGrade_Icon/speed.png")[0];
	power_icon[2] = rm->GetImages("Resource/Images/UpGrade_Icon/shot_speed.png")[0];
	power_icon[3] = rm->GetImages("Resource/Images/UpGrade_Icon/shot_size.png")[0];
	power_icon[4] = rm->GetImages("Resource/Images/UpGrade_Icon/three_way.png")[0];
	power_icon[5] = rm->GetImages("Resource/Images/UpGrade_Icon/drone.png")[0];

	window = rm->GetImages("Resource/Images/LevelUpUi/Table_01.png")[0];
}

eSceneType ResultScene::Update(const float& delta_second)
{
	//���͋@�\�C���X�^���X�擾
	InputManager* input = InputManager::GetInstance();

	stagelevel = score->GetStageLevel();
	level = score->GetPlayerLevel();
	power = score->GetPlayerPower();
	speed = score->GetPlayerSpeed();

	//���͏��̍X�V
	input->Update();

	// �J�[�\���E�ړ�
	if (input->GetKeyUp(KEY_INPUT_D) || input->GetButtonDown(XINPUT_BUTTON_DPAD_RIGHT) && is_button == true)
	{
		PlaySoundMem(sounds_effect[1], DX_PLAYTYPE_BACK, TRUE);

		menu_num--;
		if (menu_num < 0)
		{
			menu_num = 1;
		}
	}

	// �J�[�\�����ړ�
	if (input->GetKeyUp(KEY_INPUT_A) || input->GetButtonDown(XINPUT_BUTTON_DPAD_LEFT) && is_button == true)
	{
		PlaySoundMem(sounds_effect[1], DX_PLAYTYPE_BACK, TRUE);

		menu_num++;
		if (menu_num > 1)
		{
			menu_num = 0;
		}
	}


	if (input->GetKeyUp(KEY_INPUT_E) || input->GetButtonDown(XINPUT_BUTTON_A) && is_button == true)
	{
		switch (menu_num)
		{
		case 0:
			//�^�C�g���V�[���֑J��
			PlaySoundMem(sounds_effect[0], DX_PLAYTYPE_NORMAL, TRUE);
			return eSceneType::eTitle;
			break;
		case 1:
			//�Q�[�����I��
			PlaySoundMem(sounds_effect[0], DX_PLAYTYPE_NORMAL, TRUE);
			return eSceneType::eExit;
			break;
		default:
			break;

		}
	}
	return GetNowSceneType();
}

void ResultScene::Draw() const
{
#ifdef DEBUG
	/*		���U���g��ʈ�*/
// �����N
	DrawBox(50, 20, 615, 550, 0xffffff, TRUE);
	DrawFormatString(50, 270, 0x000000, "�X�R�A�����N");

	// �X�R�A����
	DrawBox(665, 20, 1230, 550, 0xffffff, TRUE);
	DrawFormatString(665, 270, 0x000000, "�X�R�A����");


	DrawFormatString(250, 500, 0x00ffff, "���B�����X�e�[�W: %d", stagelevel);		// ���B�������x����`�悷��
	DrawFormatString(250, 600, 0x00ffff, "���݂̃��x��: %d", level);		// ���݂̃��x����`�悷��

#endif // DEBUG

	char buf[256];

	// �w�i�摜
	DrawRotaGraphF(back_ground_location.x, back_ground_location.y, 1.0, 0.0, back_ground_image, TRUE);

	//DrawBox(50, 20, 1230, 550, 0xffffff, TRUE);
	// DrawFormatString(50, 20, 0xffffff, "Result");
	// DrawStringToHandle(50, 20, "RESULT", GetColor(255, 255, 255), font_name[2]);
	DrawStringToHandle(50, 20, "RESULT", GetColor(255, 255, 255), font[1]);


	// DrawFormatString(50, 80, 0xffffff, "���B�����X�e�[�W");
	// DrawStringToHandle(50, 80, "���B�����X�e�[�W", GetColor(255, 255, 255), font_name[2]);
	DrawStringToHandle(50, 80, "���B�����X�e�[�W", GetColor(255, 255, 255), font[1]);

	snprintf(buf, sizeof(buf), "%d", stagelevel);
	// DrawFormatString(1200, 80, 0xffffff, "%d", stagelevel);		// ���B�������x����`�悷��
	// DrawStringToHandle(1200, 80, buf, GetColor(255, 255, 255), font_name[2]);
	DrawStringToHandle(800, 80, buf, GetColor(255, 255, 255), font[1]);

	// DrawFormatString(50, 140, 0xffffff, "���݂̃��x��");
	// DrawStringToHandle(50, 140, "���݂̃��x��", GetColor(255, 255, 255), font_name[2]);
	DrawStringToHandle(50, 140, "�ō����x��", GetColor(255, 255, 255), font[1]);

	snprintf(buf, sizeof(buf), "%d", level);
	// DrawFormatString(1200, 140, 0xffffff, "%d", level);		// �v���C���[�̌��݂̎��S���̃��x����`�悷��
	// DrawStringToHandle(1200, 140, buf, GetColor(255, 255, 255), font_name[2]);
	DrawStringToHandle(800, 140, buf, GetColor(255, 255, 255), font[1]);


	// �����������e��`�悷��
	// DrawStringToHandle(50, 200, "�A�b�v�O���[�h�������e", GetColor(255, 255, 255), font[1]);
	// 
	// 
	// // �O�g�̕`��
	// for (int i = 0; i < 6; i++)
	// {
	// 	DrawRotaGraphF(125 + (i * 200), 450, 0.5, 0, window, TRUE);
	// }
	// 
	// // �A�C�R���̕`��
	 for (int i = 0; i < 6; i++)
	 {
	 	DrawRotaGraphF(125 + (i * 200), 400, 0.5, 0, power_icon[i], TRUE);
	 }
	// 
	// // ���������l��ݒ肷��`��
	// /*�p���[*/
	// snprintf(buf, sizeof(buf), "�~%d", power);
	// DrawStringToHandle(90, 500, buf, GetColor(255, 255, 255), font[1]);
	// /*�v���C���[�̃X�s�[�h*/
	// snprintf(buf, sizeof(buf), "�~%d", speed);
	// DrawStringToHandle(290, 500, buf, GetColor(255, 255, 255), font[1]);

	// �G���h�{�^��
	int endColor = (m_selectedbutton == selectedbutton::Title) ? GetColor(255, 0, 0) : GetColor(128, 128, 128);
	//DrawBox(25, 600, 325, 700, 0xffffff, TRUE);
	// DrawFormatString(25, 630, endColor, "Title");		// �^�C�g���{�^���ɕύX
	// DrawStringToHandle(25, 630, "Title", GetColor(255, 0, 0), font_name[2]);
	DrawStringToHandle(25, 630, "Title", GetColor(255, 0, 0), font[1]);

	// �^�C�g���{�^��
	int titleColor = (m_selectedbutton == selectedbutton::End) ? GetColor(255, 0, 0) : GetColor(255, 255, 255);
	//DrawBox(955, 600, 1255, 700, 0xffffff, TRUE);
	// DrawFormatString(955, 630, titleColor, "End");		// �G���h�{�^���ɕύX
	// DrawStringToHandle(955, 630, "End", GetColor(255, 255, 255), font_name[2]);
	DrawStringToHandle(955, 630, "End", GetColor(255, 255, 255), font[1]);


		switch (menu_num)
		{
		case 0:
			DrawTriangle(5, 640, 5, 660, 25, 650, GetColor(255, 0, 0), TRUE);
			break;
		case 1:
			DrawTriangle(935, 640, 935, 660, 955, 650, GetColor(255, 0, 0), TRUE);
			break;
		default:
			break;
		}
}

void ResultScene::Finalize()
{
	// ranking->SetRank(stagelevel);
	
	//StopSoundMem()

	// �ݒ肵���t�H���g���폜����
	// for (int i = 0; i < 5; i++)
	// {
	// 	DeleteFontToHandle(font[i]);
	// }

	// �ݒ肵���摜���폜����
	/*for (int i = 0; i < 6; i++)
	{
		DeleteGraph(power_icon[i]);
	}*/
	// DeleteGraph(window);

	StopSoundMem(back_ground_sound);
	score->Finalize();

}

eSceneType ResultScene::GetNowSceneType()const
{
	return eSceneType::eResult;
}