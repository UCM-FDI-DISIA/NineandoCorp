#pragma once

#include "../ecs/System.h"
#include "../sdlutils/SDLUtils.h"
#include "../utils/Vector2D.h"
#include "../ecs/ecs.h"
#include "../components/RenderComponent.h"


class ParticleSystem : public System
{
public:

	static constexpr sysId_type id = _sys_PARTICLES;
	ParticleSystem();
	~ParticleSystem();

	void initSystem() override;
	void receive(const Message& m) override;
	void update();
	Entity* addParticle(grpId id, gameTextures tex, Vector2D pos, Vector2D scale, int frameFirst, int lastFrame, int speed, int rows, int col, int width, int height, int iters = 1);
	int intAt(std::basic_string<char> s) { return sdlutils().intConst().at(s); }
	float floatAt(std::basic_string<char> s) { return sdlutils().floatConst().at(s); }
};

