#include "PrecompileHeader.h"
#include "GameEngineFontRenderer.h"
#include "GameEngineFont.h"

GameEngineFontRenderer::GameEngineFontRenderer() 
{
}

GameEngineFontRenderer::~GameEngineFontRenderer() 
{
}

void GameEngineFontRenderer::SetFont(const std::string_view& _Font)
{
	Font = GameEngineFont::Find(_Font);
}

void GameEngineFontRenderer::SetText(const std::string_view& _Text)
{
	Text = _Text;
}

void GameEngineFontRenderer::Render(float _Delta)
{
	if (nullptr == Font)
	{
		return;
	}

	if ("" == Text)
	{
		return;
	}

	Font->FontDraw(Text);

	GameEngineDevice::GetContext()->GSSetShader(nullptr, nullptr, 0);

}

void GameEngineFontRenderer::Start() 
{
	GameEngineRenderer::Start();
}