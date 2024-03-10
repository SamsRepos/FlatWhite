#pragma once

#include "RenderableComponent.hpp"

namespace fw
{

typedef sf::Font Font;
typedef sf::Text Text;

class TextComponent : public RenderableComponent
{
public:
	TextComponent(
		GameObject*   owner,
		const Font&   font,
		const Colour& colour,
		const Vec2f&  position,
		const std::string& content,
		float depth = 10.f
	);

	void setContent(const std::string& content);
	inline void setPosition(const Vec2f& position);
	inline void setCharacterSize(const unsigned int& size) { m_text.setCharacterSize(size); };

protected:
	virtual void update(const float& deltaTime) { };
	virtual void render(RenderTarget* window);

private:
	Text m_text;

	Font m_font;
	Colour m_colour;
	Vec2f m_position;
	std::string m_content;
};
}