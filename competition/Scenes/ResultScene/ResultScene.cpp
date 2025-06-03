#include"ResultScene.h"
#include"../../Utility/InputManager.h"
#include"../../Resource/ResourceManager.h"


ResultScene::ResultScene(): m_selectedbutton(selectedbutton::Title), menu_num(0), is_button(true)			//�����̓^�C�g���I��
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

	//�摜�擾

	// �����擾
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
}

eSceneType ResultScene::Update(const float& delta_second)
{
	//���͋@�\�C���X�^���X�擾
	InputManager* input = InputManager::GetInstance();

	//���͏��̍X�V
	input->Update();

	// �J�[�\���E�ړ�
	if (input->GetButtonDown(XINPUT_BUTTON_DPAD_RIGHT) && is_button == true)
	{
		PlaySoundMem(sounds_effect[1], DX_PLAYTYPE_BACK, TRUE);

		menu_num--;
		if (menu_num < 0)
		{
			menu_num = 1;
		}
	}

	// �J�[�\�����ړ�
	if (input->GetButtonDown(XINPUT_BUTTON_DPAD_LEFT) && is_button == true)
	{
		PlaySoundMem(sounds_effect[1], DX_PLAYTYPE_BACK, TRUE);

		menu_num++;
		if (menu_num > 1)
		{
			menu_num = 0;
		}
	}


	if (input->GetButtonDown(XINPUT_BUTTON_A) && is_button == true)
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
		/*		���U���g��ʈ�*/
		// �����N
		DrawBox(50, 20, 615, 550, 0xffffff, TRUE);
		DrawFormatString(50, 270, 0x000000, "�X�R�A�����N");

		// �X�R�A����
		DrawBox(665, 20, 1230, 550, 0xffffff, TRUE);
		DrawFormatString(665, 270, 0x000000, "�X�R�A����");

		// �G���h�{�^��
		int endColor = (m_selectedbutton == selectedbutton::Title) ? GetColor(255, 0, 0):GetColor(128,128,128);
		DrawBox(25, 600, 325, 700, 0xffffff, TRUE);
		DrawFormatString(25, 630, endColor, "Title");		// �^�C�g���{�^���ɕύX

		// �^�C�g���{�^��
		int titleColor = (m_selectedbutton == selectedbutton::End) ? GetColor(255, 0, 0) : GetColor(128,128,128);
		DrawBox(955, 600, 1255, 700, 0xffffff, TRUE);
		DrawFormatString(955, 630, titleColor, "End");		// �G���h�{�^���ɕύX
	
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

}

eSceneType ResultScene::GetNowSceneType()const
{
	return eSceneType::eResult;
}