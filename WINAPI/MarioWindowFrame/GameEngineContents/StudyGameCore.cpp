#include "StudyGameCore.h"
#include <GameEnginePlatform/GameEngineWindow.h>

#include "TutorialLevel.h"
#include "TitleLevel.h"
#include "Tutorial2Level.h"
#include "Stage1_1Level.h"
#include "Stage1_2Level.h"
#include "Stage1_3Level.h"
#include "Stage1_BossLevel.h"
#include "Stage2_1Level.h"
#include "Stage2_2Level.h"
#include "Stage2_3Level.h"
#include "Stage2_BossLevel.h"
#include "Last_danceLevel.h"


// StudyGameCore StudyGameCore::Core = new StudyGameCore();

// �߰��� ����� �������� �����ָ� ������������ ���� �����Ҵ��ؼ� ����Ѵٴ°�
// �������⿡�� ��??? �׷�������?
StudyGameCore StudyGameCore::Core;

StudyGameCore::StudyGameCore() 
{
}

StudyGameCore::~StudyGameCore() 
{
}

void StudyGameCore::Start()
{
	// ������ ���� �������? ������ ������ ���ɴϴ�.
	// �Ǽ� 1.2 ���Ѵٸ� 
	CreateLevel<TitleLevel>("TitleLevel");
	CreateLevel<TutorialLevel>("TutorialLevel");
	CreateLevel<Tutorial2Level>("Tutorial2Level");
	CreateLevel<Stage1_1Level>("Stage1_1Level");
	CreateLevel<Stage1_2Level>("Stage1_2Level");
	CreateLevel<Stage1_3Level>("Stage1_3Level");
	CreateLevel<Stage1_BossLevel>("Stage1_BossLevel");
	CreateLevel<Stage2_1Level>("Stage2_1Level");
	CreateLevel<Stage2_2Level>("Stage2_2Level");
	CreateLevel<Stage2_3Level>("Stage2_3Level");
	CreateLevel<Stage2_BossLevel>("Stage2_BossLevel");
	CreateLevel<Last_danceLevel>("Last_danceLevel");
	ChangeLevel("Stage1_BossLevel");
}

void StudyGameCore::Update()
{
	
}
void StudyGameCore::End() 
{
	
}