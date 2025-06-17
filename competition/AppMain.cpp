#include"Utility/Application.h"
#include<Windows.h>

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR pCmdLine, _In_ int nShowCmd)
{
	// フォントの一時登録
	AddFontResourceExW(L"Resource/Font/MadouFutoMaruGothic-d9Xo7.ttf", FR_PRIVATE, 0);

	try
	{
		Application application;

		//初期化処理
		application.WakeUp();

		//実行処理
		application.Run();

		//終了時処理
		application.Shutdown();

		// フォント解放（使い終わった後）
		RemoveFontResourceExW(L"Resource/Font/MadouFutoMaruGothic-d9Xo7.ttf", FR_PRIVATE, 0);

	}
	catch (std::string error_log)
	{
		//エラー内容を出力する
		//Log.txtにエラー内容を追加する
		ErrorLogFmtAdd(error_log.c_str());
		return D_FAILURE;
	}

	return D_SUCCESS;
}