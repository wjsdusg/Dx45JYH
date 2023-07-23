#pragma once
#include <GameEngineBase/GameEngineMath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
 
enum class ColEnum
{
	MapOverlay = 10,
	Unit,
	Building,
	Monster,
	Hero,
	Player,
	UnitFOV,
	MonsterFOV,
	HeroFOV,	
	Mouse,
	UIPannel,
	Optionsheet,
	Max
};

enum class Team
{
	Mine,
	Ally,
	Enemy,
	Max
};

enum class Field
{
	DungeonMap,
	DefenseMap,
	Max
};

enum class AttackType
{
	Far,
	Near,
	Max
};