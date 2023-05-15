#pragma once
#include "GameEngineTexture.h"

// �̰� ���鶧 �� �ؽ�ó�� �ε��� �ȵǾ������� �ؽ�ó�� �ε��� ���մϴ�.

// ���� : ��������Ʈ�� ������ 1�� �̻��� �̹��� ������ ����ִ�
class GameEngineSprite : public GameEngineResource<GameEngineSprite>
{
private:
	class SpriteInfo
	{
		std::shared_ptr<GameEngineTexture> Sprite;
		float4 CutData;
	};

public:
	// constrcuter destructer
	GameEngineSprite();
	~GameEngineSprite();

	// delete Function
	GameEngineSprite(const GameEngineSprite& _Other) = delete;
	GameEngineSprite(GameEngineSprite&& _Other) noexcept = delete;
	GameEngineSprite& operator=(const GameEngineSprite& _Other) = delete;
	GameEngineSprite& operator=(GameEngineSprite&& _Other) noexcept = delete;


	static std::shared_ptr<GameEngineSprite> LoadFolder(const std::string_view& _Path);

	//// �ؽ�ó�� ������� �����ǰ� 
	//static std::shared_ptr<GameEngineTexture> CreateTexture(const std::string_view& _TexureName, int X, int Y)
	//{
	//	return;
	//}


protected:

private:
	std::vector<SpriteInfo> Sprites;

};

