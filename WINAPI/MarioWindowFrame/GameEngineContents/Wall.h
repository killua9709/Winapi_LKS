#pragma once
#include <GameEngineCore/GameEngineActor.h>

// ���� : �����÷��̿� ������ ���� player�� moster�� �ۿ��ϴ� �浹ü�� ����׸�忡�� ���̴� ��� �簢�� ������ ������.
// ���1. �»�� ���� ���� ���� ũ�⸸ �˸� �浹ü�� �簢�� ������ ������.
class Wall : public GameEngineActor
{
public:
	// constrcuter destructer
	Wall();
	~Wall();

	// delete Function
	Wall(const Wall& _Other) = delete;
	Wall(Wall&& _Other) noexcept = delete;
	Wall& operator=(const Wall& _Other) = delete;
	Wall& operator=(Wall&& _Other) noexcept = delete;

	GameEngineCollision* GetBodyCollision()
	{
		return BodyCollision;
	}


protected:
	void Start() override;
	void Render(float _Time) override;	//������ �浹ü ũ�⸸ŭ�� ����� ��������

private:

	GameEngineCollision* BodyCollision = nullptr;	//���� �浹ü�� ������ ��������

};

