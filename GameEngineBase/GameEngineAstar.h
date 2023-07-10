#pragma once
#include <vector>
#include "GameEngineMath.h"

class PathIndex 
{
public:
	static const int DirCount = 8;
	static PathIndex Dir[DirCount];

public:
	union 
	{
		struct
		{
			int X;
			int Y;
		};

		__int64 Key;
	};

	float4 ReturnFloat4() 
	{
		return {static_cast<float>(X), static_cast<float>(Y)};
	}

	bool operator==(PathIndex& _Other)
	{
		return X == _Other.X && Y == _Other.Y;
	}

	PathIndex operator+(PathIndex& _Other) 
	{
		return PathIndex{X + _Other.X, Y + _Other.Y };
	}
};

class GameEngineAstar
{
private:
	class PathNode 
	{
		friend GameEngineAstar;
	public:
		// � �ε����� Ž���ϰ� �ִ�.
		PathIndex Index;

		// ���� ��� �ε����� ���ӵǾ��ִ�.
		PathNode* Parent;

		float F = 0.0f;
		float G = 0.0f;
		float H = 0.0f;

		void Reset() 
		{
			F = 0.0f;
			G = 0.0f;
			H = 0.0f;
			Parent = nullptr;
		}
	};

public:
	bool IsOver(PathIndex _Index);
	//                   100   100          1000���� Ÿ�� ���� ã�´�.
	void CreateTileData(int X, int Y, int _PathFindLimit);
	//                1    1                5
	void SetPathData(PathIndex _Index, int _Data);

	//                ����                ��           5�� ���ؼ�
	bool FindPath(PathIndex _Start, PathIndex _End, int _BlockData, std::list<PathIndex>& Result);

	PathNode* CreatePathNode(PathIndex _Index, GameEngineAstar::PathNode* _Parent);

private:
	int SizeX;
	int SizeY;

	std::vector<std::vector<int>> PathMapData;

	int PathNodeLimit = 0;
	int CurPathNode = 0;
	std::vector<PathNode> Nodes;

	PathIndex EndPoint;

	// ���¸���Ʈ Ž���ؾ��� ���
	std::multimap<float, PathNode*> OpenList;
	std::set<__int64> OpenNodeFinder;

	// �̹� �� Ž���� ���
	std::map<__int64, PathNode*> CloseList;

};

