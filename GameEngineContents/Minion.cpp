#include "PrecompileHeader.h"
#include "Minion.h"
#include "ContentsEnum.h"

Minion::Minion()
{

}

Minion::~Minion()
{
}
void Minion::Update(float _DeltaTime)
{


}
void Minion::Start()
{
	MyTeam = Team::Enemy;
	EnemyFOVCollision = CreateComponent<GameEngineCollision>();
	EnemyFOVCollision->GetTransform()->SetLocalScale({ FightFOV,FightFOV,1.f });
	EnemyFOVCollision->SetOrder(static_cast<int>(ColEnum::EnemyFOV));
}

