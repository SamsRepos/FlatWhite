#pragma once

#include "RenderableComponent.hpp"

namespace fw
{

typedef sf::Font Font;
typedef sf::Text Text;

enum OriginPoints{
	TOP_LEFT,    TOP_CENTRE,    TOP_RIGHT,
	CENTRE_LEFT, CENTRE,        CENTRE_RIGHT,
	BOTTOM_LEFT, BOTTOM_CENTRE, BOTTOM_RIGHT
};

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
	inline void setCharacterSize(const unsigned int& size) { m_text.setCharacterSize(size); };

	void setPosition(const Vec2f& position);
	void setOrigin(const Vec2f& origin);
	void setOrigin(OriginPoints originPoint);

	void setColour(const fw::Colour& colour);

protected:
	virtual void update(const float& deltaTime) { };
	virtual void render(RenderTarget* window);

private:
	Text m_text;

	Font m_font;
	Colour m_colour;
	Vec2f m_position;
	Vec2f m_origin;
	std::string m_content;
};
}