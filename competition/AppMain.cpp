#include"Utility/Application.h"
#include<Windows.h>

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR pCmdLine, _In_ int nShowCmd)
{
	// �t�H���g�̈ꎞ�o�^
	AddFontResourceExW(L"Resource/Font/MadouFutoMaruGothic-d9Xo7.ttf", FR_PRIVATE, 0);

	try
	{
		Application application;

		//����������
		application.WakeUp();

		//���s����
		application.Run();

		//�I��������
		application.Shutdown();

		// �t�H���g����i�g���I�������j
		RemoveFontResourceExW(L"Resource/Font/MadouFutoMaruGothic-d9Xo7.ttf", FR_PRIVATE, 0);

	}
	catch (std::string error_log)
	{
		//�G���[���e���o�͂���
		//Log.txt�ɃG���[���e��ǉ�����
		ErrorLogFmtAdd(error_log.c_str());
		return D_FAILURE;
	}

	return D_SUCCESS;
}