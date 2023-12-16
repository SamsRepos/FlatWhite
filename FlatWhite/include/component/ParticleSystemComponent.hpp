#pragma once

#include "RenderableComponent.hpp"

#include <list>

#include "common/Util.hpp"
#include "common/Rectangle.hpp"

namespace fw
{
class ParticleSourceArea
{
public:
    virtual Vec2f getSpawnPosition() = 0;
};

class PointParticleSourceArea : public ParticleSourceArea
{
public:
    PointParticleSourceArea(const Vec2f& point);

    void updateSourcePoint(const Vec2f& point);

    virtual Vec2f getSpawnPosition();
private:
    Vec2f m_point;
};

class RectangleParticleSourceArea : public ParticleSourceArea
{
public:
    RectangleParticleSourceArea(const Rectangle& spawnArea);

    void updateSourceArea(const Rectangle& area);

    virtual Vec2f getSpawnPosition();
private:
    Vec2f m_sourceMin;
    Vec2f m_sourceMax;
};


class CircleParticleSourceArea : public ParticleSourceArea
{
public:
    CircleParticleSourceArea(const Vec2f& position, const float& radius);

    void updateSourcePosition(const Vec2f& position);
    void updateSourceRadius(const float& radius);

    virtual Vec2f getSpawnPosition();
private:
    Vec2f m_position;
    float m_radius;

};

const float DEFAULT_PARTICLES_PER_SECOND = 10.f;

class ParticleSystemComponent : public RenderableComponent
{
public:
    ParticleSystemComponent(
        GameObject* owner,
        float defaultTtl,
        Colour defaultTint,
        std::shared_ptr<Texture> texture,
        std::shared_ptr<ParticleSourceArea> sourceArea,
        float particlesPerSecond = DEFAULT_PARTICLES_PER_SECOND
    );

    void setParticlesPerSecond(const float& particlesPerSecond);

    void emitParticles(int number);
    void emitParticlesAtPosition(int number, const Vec2f& sourcePoint);

    void clear();

    float m_defaultTtl;
    Colour m_defaultTint;
    float m_maxSpeed;
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
protected:
    virtual void update(const float& deltaTime);
    virtual void render(RenderTarget* window);

private:
    void emitParticleAtPosition(const Vec2f& position);

    void updateParticles(const float& deltaTime);

    struct Particle
    {
        Vec2f position = Vec2f(0.f, 0.f);
        float ttl; // time to live
        std::shared_ptr<Texture> texture;
        // ^ maybe not necessary in particle struct per se
        Vec2f velocity = Vec2f(0.f, 0.f);
        Vec2f scale = Vec2f(1.f, 1.f);
        float rotation;
        float rotationSpeed;
        Colour tint = Colour::White;
        float alpha = 1.f; // 0.f <= alpha <= 1.f

        void render(RenderTarget* window);

        RectangleShape shape;
    };

    std::list<Particle> m_particles;

    std::shared_ptr<Texture> m_texture;
    std::shared_ptr<ParticleSourceArea> m_sourceArea;

    float m_particlesPerSecond;
    float m_timeBetweenParticles; // seconds
    float m_spawnTimer = 0.f;
};

}