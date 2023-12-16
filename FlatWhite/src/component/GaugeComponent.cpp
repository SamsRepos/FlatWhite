#include "component/GaugeComponent.hpp"

#include <algorithm>

namespace fw
{

GaugeComponent::GaugeComponent(
	GameObject* owner,
	Colour innerColour,
	Colour outerColour,
	Vec2f initPosition,
	Vec2f size,
	float borderWidth
)
	:
	RenderableComponent(owner),
	m_borderWidth(borderWidth)
{
	m_innerRect.setFillColor(innerColour);
	m_outerRect.setFillColor(outerColour);

	addColourThreshold(1.f, innerColour);
	
	setPosition(initPosition);
	setSize(size);
}

void GaugeComponent::addColourThreshold(float threshold, const Colour& colour)
{
	ColourThreshold newCT;
	newCT.threshold = threshold;
	newCT.colour = colour;
	m_colourThresholds.push_back(newCT);

	std::sort(m_colourThresholds.begin(), m_colourThresholds.end());
}

void GaugeComponent::updatePosition(const Vec2f& position)
{
	m_outerRect.setPosition(
		position.x - m_outerRect.getSize().x / 2,
		position.y - 2 * m_outerRect.getSize().y
	);

	m_innerRect.setPosition(
		m_outerRect.getPosition() + Vec2f(m_borderWidth, m_borderWidth)
	);
}

void GaugeComponent::updateHealth(const float& health)
{
	m_innerRect.setSize(
		Vec2f(
			health * m_innerRectMaxSize.x,
			m_innerRectMaxSize.y
		)
	);

	for (auto& ct : m_colourThresholds)
	{
		if (health < ct.threshold)
		{
			m_innerRect.setFillColor(ct.colour);
			break;
		}
	}
}

//
// PROTECTED:
//

void GaugeComponent::update(const float& deltaTime)
{

}

void GaugeComponent::render(RenderTarget* window)
{
	window->draw(m_outerRect);
	window->draw(m_innerRect);
}

//
// PRIVATE:
//

void GaugeComponent::setPosition(const Vec2f& position)
{
	m_outerRect.setPosition(position);
	m_innerRect.setPosition(position + Vec2f(m_borderWidth, m_borderWidth));
}

void GaugeComponent::setSize(const Vec2f& size)
{
	m_outerRect.setSize(size);

	Vec2f borderAllowance(m_borderWidth * 2.f, m_borderWidth * 2.f);
	m_innerRectMaxSize = (size - borderAllowance);
	m_innerRect.setSize(m_innerRectMaxSize);
}


bool GaugeComponent::ColourThreshold::operator<(const ColourThreshold& other)
{
	return threshold < other.threshold;
};

}
