#include "component/LineComponent.hpp"

namespace fw
{

LineComponent::LineComponent(GameObject* owner)
	:
	RenderableComponent(owner),
	m_colour(fw::Colour::White)
{

}

void LineComponent::addLineSegment(const LineSegment& lineSegment)
{
	m_segments.push_back(lineSegment);
}

void LineComponent::updateLineSegment(unsigned int index, const Vec2f& startPoint, const Vec2f& endPoint)
{
	if(index >= m_segments.size()) addLineSegment(LineSegment(startPoint, endPoint));

	m_segments[index].resetStartPoint(startPoint);
	m_segments[index].resetEndPoint(endPoint);
}

void LineComponent::updateLineSegment(unsigned int index, const LineSegment& segment)
{
	updateLineSegment(index, segment.getStartPoint(), segment.getEndPoint());
}

void LineComponent::clear()
{
	m_segments.clear();
}

void LineComponent::setColour(const Colour& colour)
{
	m_colour = colour;
}

void LineComponent::setSegmentColour(unsigned int index, const fw::Colour& colour)
{
	m_segmentColours[index][0] = colour;
	m_segmentColours[index][1] = colour;
}

void LineComponent::setSegmentGradient(unsigned int index, const fw::Colour& colour0, const fw::Colour& colour1)
{
	m_segmentColours[index][0] = colour0;
	m_segmentColours[index][1] = colour1;
}

//
// PROTECTED:
//

void LineComponent::update(const float& deltaTime)
{

}

void LineComponent::render(RenderTarget* window)
{
	std::vector<Vertex> vertices; 
	
	for(unsigned int i = 0; i < m_segments.size(); ++i)
	{
		auto v0 = Vertex(m_segments[i].getStartPoint());
		auto v1 = Vertex(m_segments[i].getEndPoint());
		if (m_segmentColours.find(i) != m_segmentColours.end())
		{
			v0.color = m_segmentColours[i][0];
			v1.color = m_segmentColours[i][1];
		}
		else
		{
			v0.color = m_colour;
			v1.color = m_colour;
		}
		vertices.push_back(v0);
		vertices.push_back(v1);
	}

	window->draw(vertices.data(), vertices.size(), sf::Lines);
}

}