#pragma once

#include "RenderableComponent.h"

#include <list>

#include "common/Util.h"

class ParticleSystemComponent : public RenderableComponent
{
public:
    ParticleSystemComponent(
        GameObject* owner,
        float defaultTtl,
        gfx::Colour defaultTint,
        std::shared_ptr<gfx::Texture> texture,
        Vec2f sourceMin, // top left corner
        Vec2f sourceMax, // bottom right corner
        float particlesPerSecond = 10.f,
        Vec2f minVelocity = Vec2f(-1.f, -1.f),
        Vec2f maxVelocity = Vec2f(1.f, 1.f),
        float alphaChange = -0.01f,
        Vec2f minScale    = Vec2f(1.f, 1.f),
        Vec2f maxScale    = Vec2f(1.f, 1.f),
        float minRotation = -(util::PI),
        float maxRotation       = util::PI,
        float minRotationSpeed  = -1.f,
        float maxRotationSpeed  = 1.f,
        float minAlpha          = 1.f,
        float maxAlpha          = 1.f,
        Vec2f acceleration      = Vec2f(0.f, 0.f),
        Vec2f growthLinear      = Vec2f(0.f, 0.f),
        Vec2f growthExponential = Vec2f(0.f, 0.f),
        float rotationSlowDown  = 0.0001f,
        float velocitySlowDown  = 0.0001f
        
    );

    virtual void update(float deltaTime);
    virtual void render(gfx::RenderTarget* window);

    void clear();

private:
    void emitParticles(int number);
    void updateParticles(float deltaTime);

	struct Particle
	{
		Vec2f position = Vec2f(0.f, 0.f);
		float ttl; // time to live
		std::shared_ptr<gfx::Texture> texture;
		// ^ maybe not necessary in particle struct per se
		Vec2f velocity = Vec2f(0.f, 0.f);
		Vec2f scale = Vec2f(1.f, 1.f);
		float rotation;
		float rotationSpeed;
		gfx::Colour tint = gfx::Colour::White;

		void render(gfx::RenderTarget* window);

        gfx::RectangleShape shape;
	};

	std::list<Particle> m_particles;

    float m_defaultTtl;
    gfx::Colour m_defaultTint;
    std::shared_ptr<gfx::Texture> m_texture;
    Vec2f m_sourceMin; // top left corne
    Vec2f m_sourceMax; // bottom right corne
    Vec2f m_minVelocity;
    Vec2f m_maxVelocity;
    Vec2f m_minScale;
    Vec2f m_maxScale;
    float m_minRotation;
    float m_maxRotation;
    float m_minRotationSpeed;
    float m_maxRotationSpeed;
    float m_minAlpha;
    float m_maxAlpha;
    Vec2f m_acceleration;
    Vec2f m_growthLinear;
    Vec2f m_growthExponential;
    float m_rotationSlowDown;
    float m_velocitySlowDown;
    float m_alphaChange;
    float m_particlesPerSecond;

    float m_timeBetweenParticles = 1.f; // seconds
    float m_spawnTimer = 0.f;
};
