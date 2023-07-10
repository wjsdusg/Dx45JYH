#include "PrecompileHeader.h"
#include "GameEngineAstar.h"
#include "GameEngineDebug.h"

PathIndex PathIndex::Dir[PathIndex::DirCount] =
{
	{1, 0},
	{-1, 0},
	{0, 1},
	{0, -1},
	{1, 1},
	{-1, 1},
	{1, -1},
	{1, 1},
};


void GameEngineAstar::CreateTileData(int X, int Y, int _PathFindLimit)
{
	SizeY = Y;
	SizeX = X;

	PathMapData.resize(Y);

	for (size_t y = 0; y < Y; y++)
	{
		PathMapData[y].resize(X);

		for (size_t x = 0; x < X; x++)
		{
			PathMapData[y][x] = 0;
		}
	}

	PathNodeLimit = _PathFindLimit;
	Nodes.resize(_PathFindLimit);
}

bool GameEngineAstar::IsOver(PathIndex _Index)
{
	if (0 > _Index.X)
	{
		return true;
	}

	if (0 > _Index.Y)
	{
		return true;
	}

	if (SizeX <= _Index.X)
	{
		return true;
	}

	if (SizeY <= _Index.Y)
	{
		return true;
	}

	return false;
}

void GameEngineAstar::SetPathData(PathIndex _Index, int _Data)
{
	if (true == IsOver(_Index))
	{
		MsgAssert("인덱스를 오버하여 패스 데이터를 입력하려고 했습니다.");
	}

	PathMapData[_Index.X][_Index.Y] = _Data;
}

GameEngineAstar::PathNode* GameEngineAstar::CreatePathNode(PathIndex _Index, GameEngineAstar::PathNode* _Parent)
{
	GameEngineAstar::PathNode* NodePtr = &Nodes[CurPathNode];
	NodePtr->Reset();
	NodePtr->Index = _Index;
	OpenNodeFinder.insert(_Index.Key);

	if (nullptr != _Parent)
	{
		float4 Start = NodePtr->Index.ReturnFloat4();
		float4 Parent = _Parent->Index.ReturnFloat4();
		float4 End = EndPoint.ReturnFloat4();

		NodePtr->Parent = _Parent;
		NodePtr->H = (Start - End).Size();
		NodePtr->G = (Start - Parent).Size();
		NodePtr->F = NodePtr->H + NodePtr->G;
	}

	return NodePtr;
}

bool GameEngineAstar::FindPath(PathIndex _Start, PathIndex _End, int _BlockData, std::list<PathIndex>& Result)
{
	CurPathNode = 0;

	EndPoint = _End;

	GameEngineAstar::PathNode* Node = CreatePathNode(_Start, nullptr);

	GameEngineAstar::PathNode* EndPointNode = nullptr;

	// 내가 주변을 탐삭해야하는 최우선 노드들이 모여있는 곳.
	OpenList.insert(std::make_pair(Node->F, Node));

	while (CurPathNode <= PathNodeLimit)
	{
		if (OpenList.size() == 0)
		{
			break;
		}

		std::multimap<float, PathNode*>::iterator StartIter = OpenList.begin();
		PathNode* CurFindNode = StartIter->second;
		OpenNodeFinder.erase(CurFindNode->Index.Key);
		OpenList.erase(StartIter);
		CloseList.insert(std::make_pair(CurFindNode->Index.Key, CurFindNode));

		for (size_t i = 0; i < PathIndex::DirCount; i++)
		{
			//                      -1, -1                       13
			PathIndex DirIndex = PathIndex::Dir[i] + CurFindNode->Index;
			
			// 이미 오픈리스트에서 탐색대상으로 삼은애라는 겁니다.
			if (true == OpenNodeFinder.contains(DirIndex.Key))
			{
				continue;
			}

			if (true == CloseList.contains(DirIndex.Key))
			{
				continue;
			}

			if (PathMapData[DirIndex.Y][DirIndex.X] == _BlockData)
			{
				continue;
			}
			
			GameEngineAstar::PathNode* NextFindNode = CreatePathNode(DirIndex, CurFindNode);

			if (NextFindNode->Index == EndPoint)
			{
				EndPointNode = NextFindNode;
				break;
			}

			OpenList.insert(std::make_pair(NextFindNode->F, NextFindNode));
		}

		if (nullptr != EndPointNode)
		{
			break;
		}

	}


	if (nullptr == EndPointNode)
	{
		return false;
	}

	GameEngineAstar::PathNode* PathResultNode = EndPointNode;

	while (nullptr != PathResultNode)
	{
		Result.push_back(PathResultNode->Index);
		PathResultNode = PathResultNode->Parent;
	}

	// 무조건 찾아낸것이다.

	return true;
}
