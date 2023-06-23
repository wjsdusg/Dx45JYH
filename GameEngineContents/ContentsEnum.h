#pragma once
#include <GameEngineBase/GameEngineMath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
 
enum class ColEnum
{
	MapOverlay = 10,
	Unit,
	Monster,
	Hero,
	Player,
	UnitFOV,
	MonsterFOV,
	HeroFOV,
	Enemy,
	EnemyFOV,
	Max
};

enum class Team
{
	Ally,
	Enemy,
	Max
};