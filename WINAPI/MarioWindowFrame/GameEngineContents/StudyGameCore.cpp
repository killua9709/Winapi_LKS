#include "StudyGameCore.h"
#include <GameEnginePlatform/GameEngineWindow.h>

#include "TutorialLevel.h"
#include "TitleLevel.h"
#include "Tutorial2Level.h"
#include "Stage1_1Level.h"
#include "Stage1_2Level.h"
#include "Stage1_3Level.h"
#include "Stage1_BossLevel.h"


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
	ChangeLevel("Stage1_3Level");
}

void StudyGameCore::Update()
{
	
}
void StudyGameCore::End() 
{
	
}