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

// 중간에 절대로 지워지지 않을애를 포인터형으로 만들어서 동적할당해서 사용한다는건
// 제가보기에는 왜??? 그래야하지?
StudyGameCore StudyGameCore::Core;

StudyGameCore::StudyGameCore() 
{
}

StudyGameCore::~StudyGameCore() 
{
}

void StudyGameCore::Start()
{
	// 정수의 연산 결과값은? 무조건 정수만 나옵니다.
	// 실수 1.2 원한다면 
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