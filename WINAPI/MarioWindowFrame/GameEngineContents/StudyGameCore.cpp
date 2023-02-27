#include "StudyGameCore.h"
#include <GameEnginePlatform/GameEngineWindow.h>

#include "TutorialLevel.h"
#include "TitleLevel.h"

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
	ChangeLevel("TutorialLevel");
}

void StudyGameCore::Update()
{
	
}
void StudyGameCore::End() 
{
	
}