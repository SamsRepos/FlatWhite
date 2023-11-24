#include "common/LineSegment.h"

#include "common/Util.h"

namespace fw
{

LineSegment::LineSegment(const Vec2f& startPoint, const Vec2f& endPoint)
	:
	m_startPoint(startPoint),
	m_endPoint(endPoint)
{
}

void LineSegment::resetStartPoint(const Vec2f& point)
{
	m_startPoint = point;
}

void LineSegment::resetEndPoint(const Vec2f& point)
{
	m_endPoint = point;
}


Vec2f LineSegment::getStartPoint() const
{
	return m_startPoint;
}



Vec2f LineSegment::getEndPoint() const
{
	return m_endPoint;
}


Vec2f LineSegment::getShortestDirectionToPoint(const Vec2f& point) const
{
	const Vec2f& A = m_startPoint;
	const Vec2f& B = m_endPoint;
	const Vec2f& E = point;

	Vec2f AB       = B - A;
	Vec2f AE       = E - A;
	Vec2f AEscaled = AE * (1.f / AB.magnitude());
	float t        = util::dotProduct(AB.normalised(), AEscaled);
	t              = util::clamp(0.f, t, 1.f);
	Vec2f AS       = AB * t;
	Vec2f dist     = AE - AS;
	return dist;

}

}