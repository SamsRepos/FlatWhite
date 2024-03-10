#include "component/ParticleSystemComponent.hpp"

#include "common/Util.hpp"
#include "common/Vec2f.hpp"

namespace fw
{

const float DEFAULT_MAX_SPEED            = 1.f;
const float DEFAULT_ALPHA_CHANGE         = -0.01f; // 0.f <= alpha <= 1.f
const Vec2f DEFAULT_MIN_SCALE            = Vec2f(1.f);
const Vec2f DEFAULT_MAX_SCALE            = Vec2f(1.f);
const float DEFAULT_MIN_ROTATION         = -(util::PI);
const float DEFAULT_MAX_ROTATION         = util::PI;
const float DEFAULT_MIN_ROTATION_SPEED   = -1.f;
const float DEFAULT_MAX_ROTATION_SPEED   = 1.f;
const float DEFAULT_MIN_ALPHA            = 1.f; // 0.f <= alpha <= 1.f
const float DEFAULT_MAX_ALPHA            = 1.f; // 0.f <= alpha <= 1.f
const Vec2f DEFAULT_ACCELERATION         = Vec2f::zero();
const Vec2f DEFAULT_GROWTH_LINEAR        = Vec2f::zero();
const Vec2f DEFAULT_GROWTH_EXPONENTIAL   = Vec2f::zero();
const float DEFAULT_ROTATION_SLOWDOWN    = 0.0001f;
const float DEFAULT_VELOCITY_SLOWDOWN    = 0.0001f;
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
    float depth
)
    :
RenderableComponent(owner, depth),
    m_defaultTtl(defaultTtl),
    m_defaultTint(defaultTint),
    m_texture(texture),
    m_sourceArea(sourceArea),
    m_particlesPerSecond(particlesPerSecond),
    m_maxSpeed(DEFAULT_MAX_SPEED),
    m_alphaChange(DEFAULT_ALPHA_CHANGE),
    m_maxScale(DEFAULT_MAX_SCALE),
    m_minRotation(DEFAULT_MIN_ROTATION),
    m_maxRotation(DEFAULT_MAX_ROTATION),
    m_minRotationSpeed(DEFAULT_MIN_ROTATION_SPEED),
    m_maxRotationSpeed(DEFAULT_MAX_ROTATION_SPEED),
    m_minAlpha(DEFAULT_MIN_ALPHA),
    m_maxAlpha(DEFAULT_MAX_ALPHA),
    m_acceleration(DEFAULT_ACCELERATION),
    m_growthLinear(DEFAULT_GROWTH_LINEAR),
    m_growthExponential(DEFAULT_GROWTH_EXPONENTIAL),
    m_rotationSlowDown(DEFAULT_ROTATION_SLOWDOWN),
    m_velocitySlowDown(DEFAULT_VELOCITY_SLOWDOWN)
{
    setParticlesPerSecond(particlesPerSecond);
}

void ParticleSystemComponent::setParticlesPerSecond(const float& particlesPerSecond)
{
    m_particlesPerSecond = particlesPerSecond;

    if (m_particlesPerSecond > FLT_EPSILON)
    {
        m_timeBetweenParticles = 1.f / m_particlesPerSecond;
    }
    else
    {
        m_timeBetweenParticles = -1;
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
// PROTECTED:
//

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

    float speed       = util::lerp(0.f, m_maxSpeed, util::randomFloat());
    particle.velocity = Vec2f(fw::util::randomUnitVec2f() * speed);

    float scaleX   = util::lerp(m_minScale.x, m_maxScale.x, util::randomFloat());
    float scaleY   = util::lerp(m_minScale.y, m_maxScale.y, util::randomFloat());
    particle.scale = Vec2f(scaleX, scaleY);

    particle.rotation      = util::lerp(m_minRotation, m_maxRotation, util::randomFloat());
    particle.rotationSpeed = util::lerp(m_minRotationSpeed, m_maxRotationSpeed, util::randomFloat());
    // rotation speed should be 50/50 as to whether it's clockwise/counter-clockwise 
    if(rand() % 2 == 0) particle.rotationSpeed *= -1.f;

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
            particle.scale    += m_growthLinear * deltaTime;

            particle.scale.x *= 1 + (m_growthExponential.x * deltaTime);
            particle.scale.y *= 1 + (m_growthExponential.y * deltaTime);
            
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
    //shape.setScale(scale);
    Vec2f size = Vec2f(
        texture->getSize().x * scale.x,
        texture->getSize().y * scale.y
    );
    shape.setOrigin(size / 2.f);
    shape.setSize(size);
    shape.setRotation(rotation);
    shape.setFillColor(tint);

    window->draw(shape);
}

}
