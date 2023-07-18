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
//
//if (Angle < 10 || Angle >= 350)
//{
//
//}
//if (Angle < 80 && Angle >= 10)
//{
//
//}
//
//if (Angle < 100 && Angle >= 80)
//{
//
//}
//if (Angle < 170 && Angle >= 100)
//{
//
//}
//if (Angle < 190 && Angle >= 170)
//{
//
//}
//if (Angle < 260 && Angle >= 190)
//{
//
//}
//if (Angle < 280 && Angle >= 260)
//{
//
//}
//if (Angle < 350 && Angle >= 280)
//{
//
//}