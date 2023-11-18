#include "component/LineComponent.h"

namespace fw
{

LineComponent::LineComponent(GameObject* owner)
	:
	RenderableComponent(owner)
{

}

void LineComponent::addLineSegment(const LineSegment& lineSegment)
{
	m_lineSegments.push_back(lineSegment);
}

void LineComponent::clear()
{
	m_lineSegments.clear();
}

void LineComponent::setColour(const Colour& colour)
{
	m_colour = colour;
}

void LineComponent::update(float deltaTime)
{

}

void LineComponent::render(RenderTarget* window)
{
	std::vector<Vertex> vertices; 
	
	for (const auto& lineSegment : m_lineSegments)
	{
		vertices.push_back(Vertex(lineSegment.getStartPoint()));
		vertices.push_back(Vertex(lineSegment.getEndPoint()));
	}

	for (auto& vertex : vertices)
	{
		vertex.color = m_colour;
	}

	
	window->draw(vertices.data(), vertices.size(), sf::Lines);
}

}