#include "component/ParticleSystemComponent.hpp"

#include "common/Util.hpp"

namespace fw
{

//
// Point source spawner:
//

PointParticleSourceArea::PointParticleSourceArea(const Vec2f& point)
    :
    m_point(point)
{
}

void PointParticleSourceArea::updateSourcePoint(const Vec2f& point)
{
    m_point = point;
}

Vec2f PointParticleSourceArea::getSpawnPosition()
{
    return m_point;
}

//
// Rectangle Source Area:
// 

RectangleParticleSourceArea::RectangleParticleSourceArea(const Rectangle& spawnArea)
{
    updateSourceArea(spawnArea);
}

void RectangleParticleSourceArea::updateSourceArea(const Rectangle& area)
{
    m_sourceMin = Vec2f(area.left, area.top);
    m_sourceMax = m_sourceMin + Vec2f(area.width, area.height);
}

Vec2f RectangleParticleSourceArea::getSpawnPosition()
{
    float posX = util::lerp(m_sourceMin.x, m_sourceMax.x, util::randomFloat());
    float posY = util::lerp(m_sourceMin.y, m_sourceMax.y, util::randomFloat());
    return Vec2f(posX, posY);
}


//
// Circle Source Area:
// 

CircleParticleSourceArea::CircleParticleSourceArea(const Vec2f& position, const float& radius)
    :
    m_position(position),
    m_radius(radius)
{
}

void CircleParticleSourceArea::updateSourcePosition(const Vec2f& position)
{
    m_position = position;
}

void CircleParticleSourceArea::updateSourceRadius(const float& radius)
{
    m_radius = radius;
}

Vec2f CircleParticleSourceArea::getSpawnPosition()
{
    return m_position + (util::randomUnitVec2f() * m_radius);
}

//
// Particles System Component:
// 

ParticleSystemComponent::ParticleSystemComponent(
    GameObject* owner,
    float defaultTtl,
    Colour defaultTint,
    std::shared_ptr<Texture> texture,
    std::shared_ptr<ParticleSourceArea> sourceArea,
    float particlesPerSecond,
    Vec2f minVelocity,
    Vec2f maxVelocity,
    float alphaChange,
    Vec2f minScale,
    Vec2f maxScale,
    float minRotation,
    float maxRotation,
    float minRotationSpeed,
    float maxRotationSpeed,
    float minAlpha,
    float maxAlpha,
    Vec2f acceleration,
    Vec2f growthLinear,
    Vec2f growthExponential,
    float rotationSlowDown,
    float velocitySlowDown
)
    :
RenderableComponent(owner),
    m_defaultTtl(defaultTtl),
    m_defaultTint(defaultTint),
    m_texture(texture),
    m_sourceArea(sourceArea),
    m_particlesPerSecond(particlesPerSecond),
    m_minVelocity(minVelocity),
    m_maxVelocity(maxVelocity),
    m_alphaChange(alphaChange),
    m_maxScale(maxScale),
    m_minRotation(minRotation),
    m_maxRotation(maxRotation),
    m_minRotationSpeed(minRotationSpeed),
    m_maxRotationSpeed(maxRotationSpeed),
    m_minAlpha(minAlpha),
    m_maxAlpha(maxAlpha),
    m_acceleration(acceleration),
    m_growthLinear(growthLinear),
    m_growthExponential(growthExponential),
    m_rotationSlowDown(rotationSlowDown),
    m_velocitySlowDown(velocitySlowDown)
{
    if (m_particlesPerSecond > FLT_EPSILON)
    {
        m_timeBetweenParticles = 1.f / m_particlesPerSecond;
    }
    else
    {
        m_timeBetweenParticles = -1;
    }
}

void ParticleSystemComponent::update(const float& deltaTime)
{
    if (m_particlesPerSecond > FLT_EPSILON)
    {
        m_spawnTimer -= deltaTime;

        if (m_spawnTimer <= 0.f)
        {
            emitParticleAtPosition(m_sourceArea->getSpawnPosition());
            m_spawnTimer = m_timeBetweenParticles;
        };
    }
    
    updateParticles(deltaTime);
}

void ParticleSystemComponent::render(RenderTarget* window)
{
    for (auto& particle : m_particles)
    {
        particle.render(window);
    }
}

void ParticleSystemComponent::emitParticles(int number)
{
    for (int i = 0; i < number; ++i)
    {
        emitParticleAtPosition(m_sourceArea->getSpawnPosition());
    }
}

void ParticleSystemComponent::emitParticlesAtPosition(int number, const Vec2f& sourcePoint)
{
    for (int i = 0; i < number; ++i)
    {
        emitParticleAtPosition(sourcePoint);
    }
}

void ParticleSystemComponent::clear()
{
    m_particles.clear();
}

//
// PRIVATE:
//

void ParticleSystemComponent::emitParticleAtPosition(const Vec2f& position)
{
    Particle particle;
    particle.ttl = m_defaultTtl;
    particle.texture = m_texture;
    particle.tint = m_defaultTint;

    particle.alpha = util::lerp(m_minAlpha, m_maxAlpha, util::randomFloat());
    particle.alpha = util::clamp(0.f, particle.alpha, 1.f);

    particle.position = position;

    float velX = util::lerp(m_minVelocity.x, m_maxVelocity.x, util::randomFloat());
    float velY = util::lerp(m_minVelocity.y, m_maxVelocity.y, util::randomFloat());
    particle.velocity = Vec2f(velX, velY);

    float scaleX = util::lerp(m_minScale.x, m_maxScale.x, util::randomFloat());
    float scaleY = util::lerp(m_minScale.y, m_maxScale.y, util::randomFloat());
    particle.scale = Vec2f(scaleX, scaleY);

    particle.rotation = util::lerp(m_minRotation, m_maxRotation, util::randomFloat());
    particle.rotationSpeed = util::lerp(m_minRotationSpeed, m_maxRotationSpeed, util::randomFloat());

    m_particles.push_back(particle);
}

void ParticleSystemComponent::updateParticles(const float& deltaTime)
{
    std::list<Particle>::iterator current = m_particles.begin();
    std::list<Particle>::iterator next;

    while (current != m_particles.end())
    {
        next = current;
        next++;
        Particle& particle = *current;

        if (particle.ttl > 0)
        {
            particle.ttl -= deltaTime;
            particle.velocity *= (1.f - (m_velocitySlowDown * deltaTime));
            particle.velocity += m_acceleration * deltaTime;
            particle.position += particle.velocity * deltaTime;
            particle.scale += m_growthLinear * deltaTime;

            particle.scale.x *= m_growthExponential.x * deltaTime;
            particle.scale.y *= m_growthExponential.y * deltaTime;

            particle.rotationSpeed -= m_rotationSlowDown * deltaTime;
            particle.rotation += particle.rotationSpeed * deltaTime;

            particle.alpha += m_alphaChange * deltaTime;
            particle.alpha = util::clamp(0.f, particle.alpha, 1.f);

            auto alphaChange = sf::Uint8(util::lerp(0, 0xff, (m_alphaChange * deltaTime)));
            auto newAlpha = sf::Uint8(std::max(0, particle.tint.a + alphaChange));
            
            particle.tint = Colour(
                particle.tint.r,
                particle.tint.g,
                particle.tint.b,
                util::lerp(sf::Uint8(0), sf::Uint8(0xff), particle.alpha)
            );

            //particle.tint.a = newAlpha;
        }
        else
        {
            m_particles.erase(current);
        }
        current = next;
    }
}

void ParticleSystemComponent::Particle::render(RenderTarget* window)
{
    shape.setPosition(position);
    shape.setTexture(texture.get());
    shape.setScale(scale);
    shape.setScale(Vec2f(1, 1));
    Vec2f size = Vec2f(
        texture->getSize().x,
        texture->getSize().y
    );
    shape.setSize(size);
    shape.setRotation(rotation);
    shape.setFillColor(tint);

    window->draw(shape);
}

}