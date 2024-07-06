#include "component/TextComponent.hpp"

namespace fw
{

TextComponent::TextComponent(
	GameObject*   owner,
	const Font&   font,
	const Colour& colour,
	const Vec2f&  position,
	const std::string& content,
	OriginPoints originPoint,
	float depth
)
	:
	RenderableComponent(owner, depth),
	m_font(font),
	m_colour(colour),
	m_position(position),
	m_originPoint(originPoint),
	m_content(content)

{
	m_text.setFont(font);
	m_text.setFillColor(colour);
	m_text.setPosition(position);
	m_text.setString(content);
	updateOrigin();
}

void TextComponent::setContent(const std::string& content) 
{ 
	m_content = content; 
	m_text.setString(content);

	updateOrigin();
}

void TextComponent::setPosition(const Vec2f& position)
{
	m_position = position;
	m_text.setPosition(position);
}

void TextComponent::setOriginPoint(OriginPoints originPoint)
{
	m_originPoint = originPoint;
	updateOrigin();
}

void TextComponent::setColour(const fw::Colour& colour)
{
	m_text.setFillColor(colour);
}

//
// PROTECTED:
//

void TextComponent::render(RenderTarget* window)
{
	window->draw(m_text);
}

//
// PRIVATE:
//

void TextComponent::updateOrigin()
{
	float width = m_text.getGlobalBounds().width;
	float height = m_text.getGlobalBounds().height;

	float halfWidth  = width / 2.f;
	float halfHeight = height / 2.f;

	switch(m_originPoint)
	{

	case OriginPoints::TOP_LEFT:
		m_origin = fw::Vec2f(0.f, 0.f);
		break;
	case OriginPoints::TOP_CENTRE:
		m_origin = fw::Vec2f(halfWidth, 0.f);
		break;
	case OriginPoints::TOP_RIGHT:
		m_origin = fw::Vec2f(width, 0.f);
		break;

	case OriginPoints::CENTRE_LEFT:
		m_origin = fw::Vec2f(0.f, halfHeight);
		break;
	case OriginPoints::CENTRE:
		m_origin = fw::Vec2f(halfWidth, halfHeight);
		break;
	case OriginPoints::CENTRE_RIGHT:
		m_origin = fw::Vec2f(width, halfHeight);
		break;

	case OriginPoints::BOTTOM_LEFT:
		m_origin = fw::Vec2f(0.f, height);
		break;
	case OriginPoints::BOTTOM_CENTRE:
		m_origin = fw::Vec2f(halfWidth, height);
		break;
	case OriginPoints::BOTTOM_RIGHT:
		m_origin = fw::Vec2f(width, height);
		break;
	}

	m_text.setOrigin(m_origin);
}

}