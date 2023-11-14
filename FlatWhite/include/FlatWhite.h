// includes most of what you need to use the FlatWhite API
#pragma once

#include "gameObject/GameObject.h"

#include "component/BodyComponent.h"
#include "component/Component.h"
#include "component/ParticleSystemComponent.h"
#include "component/RenderableComponent.h"
#include "component/SpawnerComponent.h"
#include "component/SpriteComponent.h"
#include "component/GaugeComponent.h"
#include "component/SoundComponent.h"

#include "common/Util.h"
#include "common/Vec2f.h"
#include "common/Rectangle.h"

#include "space/PhysicsSpace.h"
#include "space/Space.h"

#include "system/Graphics.h"
#include "system/Input.h"
#include "system/Physics.h"
#include "system/TextureManager.h"
#include "system/DeltaClock.h"
#include "system/Window.h"
#include "system/Sound.h"
#include "system/SoundBufferManager.h"