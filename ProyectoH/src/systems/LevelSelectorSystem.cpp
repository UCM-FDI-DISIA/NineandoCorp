#include "LevelSelectorSystem.h"
#include "../ecs/Manager.h"
#include "../game/Game.h"

LevelSelectorSystem::LevelSelectorSystem()
{
}

LevelSelectorSystem::~LevelSelectorSystem()
{
}

void LevelSelectorSystem::initSystem()
{
	//play button
	Vector2D pAux(sdlutils().width() / 2, (sdlutils().height() / 2) + 150);
	Vector2D sAux(350, 110);
	addButton(pAux, sAux, gameTextures::play, gameTextures::play_hover, ButtonTypes::backButton);
	//-------//
	pAux = { 800,  800 };
	sAux = { sdlutils().height() - 100.0f , 400 };
	addImage(pAux, sAux, 90.0, gameTextures::box);
}

void LevelSelectorSystem::receive(const Message& m)
{
	switch (m.id)
	{
	default:
		break;
	}
}

void LevelSelectorSystem::update()
{
}

void LevelSelectorSystem::addButton(Vector2D pos, Vector2D scale, gameTextures tex, gameTextures hov, ButtonTypes type)
{
	Entity* b = mngr_->addEntity(_grp_HUD_FOREGROUND);
	mngr_->setHandler(_hdlr_BUTTON, b);

	Transform* tr = mngr_->addComponent<Transform>(b);
	tr->setScale(scale);
	Vector2D aux = tr->getScale();
	tr->setPosition(pos - aux / 2);

	mngr_->addComponent<RenderComponent>(b, tex);

	ButtonComponent* bC = mngr_->addComponent<ButtonComponent>(b, type);
	bC->setTexture(tex);
	bC->setHover(hov);
}

void LevelSelectorSystem::addImage(Vector2D pos, Vector2D(scale), double rot, gameTextures t)
{
	Entity* img = mngr_->addEntity(_grp_HUD_FOREGROUND);
	Transform* tr = mngr_->addComponent<Transform>(img);
	tr->setScale(scale);
	Vector2D aux = tr->getScale();
	tr->setPosition(pos - aux / 2);
	tr->setRotation(rot);
	mngr_->addComponent<RenderComponent>(img, t);
}



