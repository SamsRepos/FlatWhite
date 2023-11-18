#pragma once

#include "Vec2f.h"

namespace fw
{

class LineSegment
{
public:
	LineSegment(const Vec2f& startPoint, const Vec2f& endPoint);

	Vec2f getStartPoint() const;
	Vec2f getEndPoint() const;
	Vec2f getShortestDirectionToPoint(const Vec2f& point) const;

private:
	Vec2f m_startPoint;
	Vec2f m_endPoint;

};

}