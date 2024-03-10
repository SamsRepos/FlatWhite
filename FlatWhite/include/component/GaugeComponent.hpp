#pragma once

#include "RenderableComponent.hpp"

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
		float borderWidth = GAUGE_DEFAULT_BORDER_WIDTH,
		float depth = 10.f
	);

	void addColourThreshold(float threshold, const Colour& colour); // 0.f <= threshold <= 1.f

	//void setGameObjectToTrack(GameObject* gameObject, Vec2f offset);
	// need to think about this. if gameObject is deleted that's bad. for now, update with position will suffice

	void updatePosition(const Vec2f& position);
	void updateHealth(const float& health); // 0.f <= health <= 1.f
	
protected:
	virtual void update(const float& deltaTime);
	virtual void render(RenderTarget* window);
	
	RectangleShape m_outerRect;
	RectangleShape m_innerRect;

private:
	void setPosition(const Vec2f& position);
	void setSize(const Vec2f& size);

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