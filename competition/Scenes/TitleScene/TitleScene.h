#pragma once
#include"../SceneBase.h"

class TitleScene : public SceneBase
{
protected:

private:
	int menu_num;			// メニューカーソル番号
	bool help;				// ヘルプが開かれてるかどうか?
	bool is_button;			// ボタンが操作できるかどうか?
	int back_ground_sound;	// BGM
	int sounds_effect[2];	// 効果音
	//int button_sound0;		// 選択音
	//int button_sound1;		// 決定音
	int back_ground_image;				// 背景画像
	Vector2D back_ground_location;		// 背景座標

	// フォントの登録
	// int title_name;
	// int button;
	// int push_button;
	// int help_font;
	// int help_font_title;

	// ボタン画像		test			0 :	十字カーソル 1: Aボタン	2:　Bボタン
	std::vector<int> ui_button;
	std::vector<Vector2D> ui_location;
	std::vector<Vector2D> font_location;

	int font[5];
public:
	TitleScene();
	~TitleScene();

public:
	virtual void Initialize() override;
	virtual eSceneType Update(const float& delta_second);
	virtual void Draw() const override;
	virtual void Finalize() override;

public:
	virtual eSceneType GetNowSceneType() const override;
};