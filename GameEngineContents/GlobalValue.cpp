#include "PrecompileHeader.h"
#include "GlobalValue.h"

GameEngineAstar GlobalValue::AStart;
std::shared_ptr<JPSCollision> GlobalValue::Collision;
JPSPath GlobalValue::JpsP;

std::shared_ptr<JPSCollision> DefenseGlobalValue::Collision;
JPSPath DefenseGlobalValue::JpsP;