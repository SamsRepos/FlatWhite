#pragma once

#include "RenderableComponent.h"

namespace fw
{

const float GAUGE_DEFAULT_BORDER_WIDTH = 1.f;

class GaugeComponent : public RenderableComponent
{
public:
	GaugeComponent(
		GameObject* owner,
		Colour innerColour,
		Colour outerColour,
		Vec2f initPosition,
		Vec2f size,
		float borderWidth = GAUGE_DEFAULT_BORDER_WIDTH
	);

	void addColourThreshold(float threshold, const Colour& colour); // 0.f <= threshold <= 1.f

	//void setGameObjectToTrack(GameObject* gameObject, Vec2f offset);
	// need to think about this. if gameObject is deleted that's bad. for now, update with position will suffice

	virtual void update(const Vec2f& position, float health); // 0.f <= health <= 1.f;
	virtual void update(float health); // 0.f <= health <= 1.f
	virtual void render(RenderTarget* window);

protected:
	RectangleShape m_outerRect;
	RectangleShape m_innerRect;

private:
	void setPosition(Vec2f position);
	void setSize(Vec2f size);

	Vec2f m_innerRectMaxSize;
	float m_borderWidth;

	struct ColourThreshold
	{
		float threshold;
		Colour colour;

		bool operator<(const ColourThreshold& other);
	};

	std::vector<ColourThreshold> m_colourThresholds;
};


}