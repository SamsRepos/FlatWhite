// includes most of what you need to use the FlatWhite API
#pragma once

#include "gameObject/GameObject.hpp"

#include "component/BodyComponent.hpp"
#include "component/Component.hpp"
#include "component/ParticleSystemComponent.hpp"
#include "component/RenderableComponent.hpp"
#include "component/SpawnerComponent.hpp"
#include "component/SpriteComponent.hpp"
#include "component/GaugeComponent.hpp"
#include "component/SoundComponent.hpp"
#include "component/LineComponent.hpp"
#include "component/TextComponent.hpp"

#include "common/Util.hpp"
#include "common/Vec2f.hpp"
#include "common/Rectangle.hpp"
#include "common/lineSegment.hpp"

#include "space/PhysicsSpace.hpp"
#include "space/Space.hpp"

#include "system/Graphics.hpp"
#include "system/Input.hpp"
#include "system/Physics.hpp"
#include "system/TextureManager.hpp"
#include "system/DeltaClock.hpp"
#include "system/Window.hpp"
#include "system/Sound.hpp"
#include "system/SoundBufferManager.hpp"