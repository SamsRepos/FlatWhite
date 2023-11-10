#include "component/ParticleSystemComponent.h"

#include "common/Util.h"

ParticleSystemComponent::ParticleSystemComponent(
    GameObject* owner,
    float defaultTtl,
    gfx::Colour defaultTint,
    std::shared_ptr<gfx::Texture> texture,
    Vec2f sourceMin, // top left corner
    Vec2f sourceMax, // bottom right corner
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
m_sourceMin(sourceMin), // top left corner,
m_sourceMax(sourceMax), // bottom right corner,
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
    m_timeBetweenParticles = 1.f / m_particlesPerSecond;
}

void ParticleSystemComponent::update(float deltaTime)
{
    m_spawnTimer -= deltaTime;
    
    if(m_spawnTimer <= 0.f)
    {
        emitParticles(1);
        m_spawnTimer = m_timeBetweenParticles;
    };

    updateParticles(deltaTime);
}

void ParticleSystemComponent::render(gfx::RenderTarget* window)
{
    for(auto& particle : m_particles)
    {
        particle.render(window);
    }
}

void ParticleSystemComponent::clear()
{
    m_particles.clear();
}

//
// PRIVATE:
//

void ParticleSystemComponent::emitParticles(int number)
{
    for (int i = 0; i < number; ++i)
    {
        Particle particle;
        particle.ttl = m_defaultTtl;
        particle.texture = m_texture;
        particle.tint = m_defaultTint;

        float tintFloat = util::lerp(m_minAlpha, m_maxAlpha, util::randomFloat());
        particle.tint.a = util::lerp(0, 0xff, tintFloat);

        float posX = util::lerp(m_sourceMin.x, m_sourceMax.x, util::randomFloat());
        float posY = util::lerp(m_sourceMin.y, m_sourceMax.y, util::randomFloat());
        particle.position = Vec2f(posX, posY);
        
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
}

void ParticleSystemComponent::updateParticles(float deltaTime)
{
    std::list<Particle>::iterator current = m_particles.begin();
    std::list<Particle>::iterator next;

    while(current != m_particles.end())
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
            particle.rotation      += particle.rotationSpeed * deltaTime;
            

            int alphaChange = int(util::lerp(0, 0xff, (m_alphaChange * deltaTime)));
            int newAlpha = int(std::max(0, particle.tint.a + alphaChange));
            particle.tint.a = sf::Uint8(newAlpha);
        }
        else
        {
            m_particles.erase(current);
        }
        current = next;
    }
}

//#include <iostream>

void ParticleSystemComponent::Particle::render(gfx::RenderTarget* window)
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

    //std::cout << int(shape.getFillColor().a) << std::endl;
}