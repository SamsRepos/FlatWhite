#pragma once

#include "component/RenderableComponent.h"

#include "common/LineSegment.h"

namespace fw
{

class LineComponent : public RenderableComponent
{
public:
	LineComponent(GameObject* owner);

	void addLineSegment(const LineSegment& lineSegment);
	void clear();

	void setColour(const Colour& colour);

	virtual void update(const float& deltaTime);
	virtual void render(RenderTarget* window);

private:
	std::vector<LineSegment> m_lineSegments;
	fw::Colour m_colour = fw::Colour::White;
};

}