#pragma once

#include "Vec2f.hpp"

namespace fw
{

class LineSegment
{
public:
	LineSegment(const Vec2f& startPoint, const Vec2f& endPoint);

	void resetStartPoint(const Vec2f& point);
	void resetEndPoint(const Vec2f& point);

	Vec2f getStartPoint() const;
	Vec2f getEndPoint() const;
	Vec2f getShortestDisplacementToPoint(const Vec2f& point) const;
	Vec2f getStartToEndDisplacement() const;

private:
	Vec2f m_startPoint;
	Vec2f m_endPoint;

};

}