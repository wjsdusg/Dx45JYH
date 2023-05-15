#include "PrecompileHeader.h"
#include "GameEngineTransform.h"
#include "GameEngineObject.h"
#include "GameEngineActor.h"
#include "GameEngineLevel.h"

GameEngineTransform::GameEngineTransform()
{
	TransformUpdate();
}

GameEngineTransform::~GameEngineTransform()
{
}


void GameEngineTransform::TransformUpdate()
{
	TransData.ScaleMatrix.Scale(TransData.Scale);

	TransData.Rotation.w = 0.0f;
	TransData.Quaternion = TransData.Rotation.EulerDegToQuaternion();
	TransData.RotationMatrix = TransData.Quaternion.QuaternionToRotationMatrix();
	TransData.PositionMatrix.Pos(TransData.Position);

	TransData.LocalWorldMatrix = TransData.ScaleMatrix * TransData.RotationMatrix * TransData.PositionMatrix;


	if (nullptr == Parent)
	{
		TransData.WorldMatrix = TransData.LocalWorldMatrix;
	}
	else // ����
	{
		WorldCalculation();
	}

	WorldDecompose();
	LocalDecompose();
	// ParentWorldMatrix.Decompose(PScale, PRoatation, PPosition);

}

void GameEngineTransform::WorldCalculation()
{
	float4x4 ParentWorldMatrix = Parent->GetWorldMatrixRef();
	float4 PScale, PRotation, PPosition;
	ParentWorldMatrix.Decompose(PScale, PRotation, PPosition);


	if (true == AbsoluteScale)
	{
		// �θ��� ����� �������� 1
		PScale = float4::One;
	}
	if (true == AbsoluteRotation)
	{
		// �θ��� ȸ�� 
		PRotation = float4::Zero;
		PRotation.EulerDegToQuaternion();
	}
	if (true == AbsolutePosition)
	{
		PPosition = float4::Zero;
	}

	float4x4 MatScale, MatRot, MatPos;

	//scale
	MatScale.Scale(PScale);

	//rot
	MatRot = PRotation.QuaternionToRotationMatrix();

	//pos
	MatPos.Pos(PPosition);

	TransData.WorldMatrix = TransData.LocalWorldMatrix * (MatScale * MatRot * MatPos);
}

void GameEngineTransform::LocalDecompose()
{
	TransData.LocalWorldMatrix.Decompose(TransData.LocalScale, TransData.LocalQuaternion, TransData.LocalPosition);
	TransData.LocalRotation = TransData.LocalQuaternion.QuaternionToEulerDeg();

}
void GameEngineTransform::WorldDecompose()
{
	TransData.WorldMatrix.Decompose(TransData.WorldScale, TransData.WorldQuaternion, TransData.WorldPosition);
	TransData.WorldRotation = TransData.WorldQuaternion.QuaternionToEulerDeg();

}

void GameEngineTransform::SetParent(GameEngineTransform* _Parent)
{
	if (IsDebug())
	{
		int a = 0;
	}

	if (nullptr == _Parent && nullptr == Master)
	{
		if (nullptr == dynamic_cast<GameEngineActor*>(Master))
		{
			MsgAssert("���͸��� ��Ʈ ����Ʈ�� �߰��ɼ� �ֽ��ϴ�.");
			return;
		}
	}

	if (nullptr == Parent && nullptr == _Parent)
	{
		return;
	}

	// ���� ���� ������ �θ� ������ �ִٸ�
	if (nullptr != Parent)
	{
		Parent->Child.remove(this);
		GameEngineObject* ParentMaster = Parent->Master;

		if (nullptr == ParentMaster)
		{
			MsgAssert("�����Ҽ� ���� ��Ȳ�Դϴ� Master�� nullptr�Դϴ�");
			return;
		}

		std::shared_ptr<GameEngineObject> MasterPtr = Master->shared_from_this();
		ParentMaster->Childs.remove(MasterPtr);
		Parent = nullptr;

		GameEngineLevel* Level = Master->GetLevel();

		Level->Actors[MasterPtr->GetOrder()].push_back(std::dynamic_pointer_cast<GameEngineActor>(MasterPtr));
	}





	Parent = _Parent;

	// ���� �������� �޶����°� ����.

	// �� WorldMatrix;
	// �θ��� WorldMatrix;


	//TransformData ParentData = Parent->TransData;
	//TransformData ChildData = TransData;
	//ParentData.WorldMatrix;
	//ChildData.WorldMatrix;
	//float4x4 NewWorld = ChildData.WorldMatrix * ParentData.WorldMatrix.InverseReturn();

	if (nullptr != Parent)
	{
		TransData.LocalWorldMatrix = TransData.WorldMatrix * Parent->TransData.WorldMatrix.InverseReturn();

		LocalDecompose();

		TransData.Position = TransData.LocalPosition;
		TransData.Rotation = TransData.LocalRotation;
		TransData.Scale = TransData.LocalScale;

		TransformUpdate();

		AbsoluteReset();

		// ���� ���������� ���� ���� �̷��͵��� �־��µ�.
		// ���� ���ο� �θ� �����
		// ���� �̹� �ٸ� �θ� �ִٸ�

		Parent->Child.push_back(this);
	}
	else
	{
		WorldDecompose();

		TransData.Position = TransData.WorldPosition;
		TransData.Rotation = TransData.WorldRotation;
		TransData.Scale = TransData.WorldScale;
		TransformUpdate();
		AbsoluteReset();
	}
}




void GameEngineTransform::CalChild()
{
	for (GameEngineTransform* ChildTrans : Child)
	{
		ChildTrans->WorldCalculation();
		ChildTrans->WorldDecompose();
		ChildTrans->CalChild();
	}
}



float4 GameEngineTransform::GetLocalPosition()
{
	return TransData.LocalPosition;
}

float4 GameEngineTransform::GetLocalScale()
{
	return TransData.LocalScale;
}

float4 GameEngineTransform::GetLocalRotation()
{
	return TransData.LocalRotation;
}

float4 GameEngineTransform::GetWorldPosition()
{
	return TransData.WorldPosition;
}

float4 GameEngineTransform::GetWorldScale()
{
	return TransData.WorldScale;
}

float4 GameEngineTransform::GetWorldRotation()
{
	return TransData.WorldRotation;
}

void GameEngineTransform::AbsoluteReset()
{
	AbsoluteScale = false;
	AbsoluteRotation = false;
	AbsolutePosition = false;
}

void GameEngineTransform::SetMaster(GameEngineObject* _Master)
{
	Master = _Master;
}

void GameEngineTransform::AllAccTime(float _DeltaTime)
{
	if (nullptr == Master)
	{
		return;
	}

	if (false == Master->IsUpdate())
	{
		return;
	}

	Master->AccLiveTime(_DeltaTime);

	for (GameEngineTransform* Trans : Child)
	{
		Trans->AllAccTime(_DeltaTime);
	}
}

void GameEngineTransform::AllUpdate(float _DeltaTime)
{

	if (nullptr == Master)
	{
		return;
	}

	if (false == Master->IsUpdate())
	{
		return;
	}

	Master->Update(_DeltaTime);

	for (GameEngineTransform* Trans : Child)
	{
		Trans->AllUpdate(_DeltaTime);
	}
}


void GameEngineTransform::AllRender(float _DeltaTime)
{
	if (nullptr == Master)
	{
		return;
	}

	if (false == Master->IsUpdate())
	{
		return;
	}

	Master->Render(_DeltaTime);

	for (GameEngineTransform* Trans : Child)
	{
		Trans->AllRender(_DeltaTime);
	}
}

void GameEngineTransform::AllRelease()
{
	if (nullptr == Master)
	{
		return;
	}

	if (false == Master->IsUpdate())
	{
		return;
	}

	Master->Release();

	for (GameEngineTransform* Trans : Child)
	{
		Trans->AllRelease();
	}
}

void GameEngineTransform::ChildRelease()
{
	std::list<GameEngineTransform*>::iterator ReleaseStartIter = Child.begin();
	std::list<GameEngineTransform*>::iterator ReleaseEndIter = Child.end();

	for (; ReleaseStartIter != ReleaseEndIter; )
	{
		GameEngineTransform* Trans = *ReleaseStartIter;

		if (nullptr == Trans->Master)
		{
			MsgAssert("�� �߸��� ���󿡸��� �θ���.");
		}

		if (false == Trans->Master->IsDeath())
		{
			++ReleaseStartIter;
			continue;
		}

		ReleaseStartIter = Child.erase(ReleaseStartIter);
	}
}
