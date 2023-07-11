#pragma once
#include <GameEngineBase/GameEngineAstar.h>
#include <GameEngineBase/JPSCollision.h>
#include <GameEngineBase/JPSPath.h>


class GlobalValue 
{
public:
	static GameEngineAstar AStart;
	static std::shared_ptr<JPSCollision> Collision;
	static JPSPath JpsP;
	// jps.Init(spCollision);

};