#pragma once

#include "component/RenderableComponent.hpp"

#include "common/LineSegment.hpp"

namespace fw
{

class LineComponent : public RenderableComponent
{
public:
	LineComponent(GameObject* owner);

	void addLineSegment(const LineSegment& lineSegment);
	void updateLineSegment(unsigned int index, const Vec2f& startPoint, const Vec2f& endPoint);
	void updateLineSegment(unsigned int index, const LineSegment& segment);
	void clear();

	void setColour(const Colour& colour);
	void setSegmentColour(unsigned int index, const fw::Colour& colour);
	void setSegmentGradient(unsigned int index, const fw::Colour& colour0, const fw::Colour& colour1);

	virtual void update(const float& deltaTime);
	virtual void render(RenderTarget* window);

private:
	std::vector<LineSegment> m_segments;
	fw::Colour m_colour;
	std::map<unsigned int, fw::Colour[2]> m_segmentColours;
};

}