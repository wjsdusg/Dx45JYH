#pragma once
#include <string_view>
#include "GameEngineRenderer.h"
#include "GameEngineFont.h"

// ���� :
class GameEngineFontUIRenderer : public GameEngineRenderer
{
public:
	// constrcuter destructer
	GameEngineFontUIRenderer();
	~GameEngineFontUIRenderer();

	// delete Function
	GameEngineFontUIRenderer(const GameEngineFontUIRenderer& _Other) = delete;
	GameEngineFontUIRenderer(GameEngineFontUIRenderer&& _Other) noexcept = delete;
	GameEngineFontUIRenderer& operator=(const GameEngineFontUIRenderer& _Other) = delete;
	GameEngineFontUIRenderer& operator=(GameEngineFontUIRenderer&& _Other) noexcept = delete;

	void SetFont(const std::string_view& _Font);
	void SetText(const std::string_view& _Text);

	void SetScale(float _FontScale)
	{
		FontScale = _FontScale;
	}

	void SetColor(float4 _FontColor)
	{
		FontColor = _FontColor;
	}

	inline void SetFontFlag(FW1_TEXT_FLAG _Flag)
	{
		FwTextFlag = _Flag;
	}

protected:
	void Render(float _Delta) override;

private:
	void Start() override;


	float FontScale = 10.0f;
	float4 FontColor = float4::Red;
	std::string Text;
	std::shared_ptr<GameEngineFont> Font;

	FW1_TEXT_FLAG FwTextFlag = FW1_TEXT_FLAG::FW1_TOP;
};

