#include "component/TextComponent.hpp"

namespace fw
{

TextComponent::TextComponent(
	GameObject*   owner,
	const Font&   font,
	const Colour& colour,
	const Vec2f&  position,
	const std::string& content,
	float depth
)
	:
	RenderableComponent(owner, depth),
	m_font(font),
	m_colour(colour),
	m_position(position),
	m_content(content)

{
	m_text.setFont(font);
	m_text.setFillColor(colour);
	m_text.setPosition(position);
	m_text.setString(content);
}

void TextComponent::setContent(const std::string& content) 
{ 
	m_content = content; 
	m_text.setString(content);
}

void TextComponent::setPosition(const Vec2f& position)
{
	m_position = position;
	m_text.setPosition(position);
}

//
// PROTECTED:
//

void TextComponent::render(RenderTarget* window)
{
	window->draw(m_text);
}

}