#pragma once
#include "../SceneBase.h"

#define RANKING_DATA	(3)

class RankingScene : public SceneBase
{
protected:

private:
	int back_ground_sound;	// BGM
	int sounds_effect[2];	// ���ʉ�
	int score[RANKING_DATA];	// �����L���O�f�[�^
	int rank[RANKING_DATA];		// �����N
	int player_stats[8];		// �v���C���[�X�e�[�^�X
	int back_ground_image;		// �w�i�摜
	Vector2D back_ground_location;		// �w�i���W

public:
	RankingScene();
	~RankingScene();

public:
	virtual void Initialize() override;
	virtual eSceneType Update(const float& delta_second);
	virtual void Draw() const override;
	virtual void Finalize() override;

public:
	virtual eSceneType GetNowSceneType() const override;

	void SetRank(int);		// �����L���O�̓���ւ�

private:
	void SortData();		// �f�[�^����ւ�����

public:
	void GetScoreNo3()
	{
		return/*score[2]*/;
	}
};