#pragma once
#include <GameEngineBase/GameEngineMath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
 
enum class ColEnum
{
	MapOverlay = 10,
	Unit,
	Building,
	Treasure,
	Monster,
	Hero,
	Player,
	Enemy,
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

enum class BuildingType
{
	IncludeUnit,
	NotUnit,
	Max
};