#include"ResultScene.h"
#include"../../Utility/InputManager.h"
#include"../../Resource/ResourceManager.h"

ResultScene::ResultScene(): m_selectedbutton(selectedbutton::Title)			//�����̓^�C�g���I��
{
	//���\�[�X�Ǘ��C���X�^���X�擾
	ResourceManager* rm = ResourceManager::GetInstance();

	//�摜�擾
}

ResultScene::~ResultScene()
{

}

void ResultScene::Initialize()
{
	//�I����ԃ��Z�b�g
	m_selectedbutton = selectedbutton::Title;
}

eSceneType ResultScene::Update(const float& delta_second)
{
	//���͋@�\�C���X�^���X�擾
	InputManager* input = InputManager::GetInstance();

	//���͏��̍X�V
	input->Update();

	//�{�^���I��
	if (input->GetButtonDown(XINPUT_BUTTON_DPAD_LEFT))
	{
		m_selectedbutton= selectedbutton::End;
	}

	if (input->GetButtonDown(XINPUT_BUTTON_DPAD_RIGHT))
	{
		m_selectedbutton = selectedbutton::Title;
	}

	//����{�^���őJ��
	if (input->GetButtonDown(XINPUT_BUTTON_A))
	{
		if (m_selectedbutton == selectedbutton::Title)
		{
			return eSceneType::eTitle;
		}
		else if (m_selectedbutton == selectedbutton::End)
		{
			return eSceneType::eExit;
		}
	}
	//�C���Q�[���V�[���֑J��
	if (input->GetKeyUp(KEY_INPUT_SPACE))
	{
		return eSceneType::eTitle;
	}

	//�Q�[�����I��
	if (input->GetKeyUp(KEY_INPUT_ESCAPE))
	{
		return eSceneType::eExit;
	}

	return GetNowSceneType();
}

void ResultScene::Draw() const
{
		DrawFormatString(10, 10, GetColor(255, 255, 255), "���U���g�V�[��");
		/*		���U���g��ʈ�*/
		// �����N
		DrawBox(50, 20, 615, 550, 0xffffff, TRUE);
		DrawFormatString(50, 270, 0x000000, "�X�R�A�����N");

		// �X�R�A����
		DrawBox(665, 20, 1230, 550, 0xffffff, TRUE);
		DrawFormatString(665, 270, 0x000000, "�X�R�A����");

		// �G���h�{�^��
		int endColor = (m_selectedbutton == selectedbutton::End) ? GetColor(255, 0, 0):GetColor(128,128,128);
		DrawBox(25, 600, 325, 700, 0xffffff, TRUE);
		DrawFormatString(25, 630, endColor, "End");

		// �^�C�g���{�^��
		int titleColor = (m_selectedbutton == selectedbutton::Title) ? GetColor(255, 0, 0) : GetColor(128,128,128);
		DrawBox(955, 600, 1255, 700, 0xffffff, TRUE);
		DrawFormatString(955, 630, titleColor, "Title");
	
}

void ResultScene::Finalize()
{

}

eSceneType ResultScene::GetNowSceneType()const
{
	return eSceneType::eResult;
}