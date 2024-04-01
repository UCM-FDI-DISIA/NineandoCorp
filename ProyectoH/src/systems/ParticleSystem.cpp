#include "ParticleSystem.h"
#include "../ecs/Manager.h"
#include "../components/FramedImage.h"
#include "../components/Transform.h"
#include "../components/ParticleLifeTime.h"
#include "../components/RouteComponent.h"
#include "../components/MovementComponent.h"

ParticleSystem::ParticleSystem() {

}
ParticleSystem::~ParticleSystem() {

}


void ParticleSystem::initSystem() {

}
void  ParticleSystem::receive(const Message& m) {
	switch (m.id) {
	case _m_ANIM_CREATE:
		addParticle(m.anim_create.idGrp, m.anim_create.tex, m.anim_create.pos,m.anim_create.route, m.anim_create.scale, m.anim_create.frameInit, m.anim_create.frameEnd,
		m.anim_create.animSpeed, m.anim_create.rows, m.anim_create.cols, m.anim_create.width, m.anim_create.height, m.anim_create.iterationsToDelete);
		break;
	default:
			break;
	}
}


void ParticleSystem::update() {
	for (auto& par : mngr_->getHandler(_hdlr_PARTICLES))
	{
		auto p = mngr_->getComponent<ParticleLifeTime>(par);
		auto f = mngr_->getComponent<FramedImage>(par);
		MovementComponent* mc = mngr_->getComponent<MovementComponent>(par);
		RouteComponent* rc = mngr_->getComponent<RouteComponent>(par);

		f->updateCurrentFrame();

		

		if (rc != nullptr) {
			rc->checkdestiny();
			if (mc != nullptr && !mc->getStop()) {
				mc->Move();
			}
			else {
				Message m;
				m.id = _m_REMOVE_RECT;
				m.rect_data.rect = par;
				m.rect_data.id = _TORNADO;
				mngr_->send(m);

				mngr_->setAlive(par, false);
				mngr_->deleteHandler(_hdlr_PARTICLES, par);
			}

		}
		else if (p->getIters() <= f->getIters()) {
			mngr_->setAlive(par, false);
			mngr_->deleteHandler(_hdlr_PARTICLES, par);
		}
	}
}

Entity* ParticleSystem::addParticle(grpId id, gameTextures tex, Vector2D pos,vector<Vector2D> route, Vector2D scale, int frameFirst, int lastFrame, int speed, int rows, int col, int width, int height, int iter) {
	auto p = mngr_->addEntity(id);
	mngr_->setHandler(_hdlr_PARTICLES, p);
	mngr_->addComponent<RenderComponent>(p, tex);
	mngr_->addComponent<FramedImage>(p, rows, col, width, height, frameFirst, speed, lastFrame);
	mngr_->addComponent<ParticleLifeTime>(p, iter);
	auto t = mngr_->addComponent<Transform>(p);
	Vector2D correct;
	bool meteorologic = false;
	switch (tex)
	{
	
	case thunder:
		correct = { t->getWidth() / 1.2f, t->getHeight() / 0.4f };
		meteorologic = true;
		break;
	case meteorites:
		correct = { t->getWidth() / 1.05f, t->getHeight() / 0.55f };
		meteorologic = true;
		break;
	case earthquake:
		correct = { t->getWidth() / 3.6f, t->getHeight() / 2.0f };
		meteorologic = true;
		break;
	case tornado:
		correct = { t->getWidth(), t->getHeight()  };
		meteorologic = true;
		for (auto& e : route) {
			e = e - correct;
		}
		break;
	default:
		break;
	}
	if (route.empty()) {
		pos = pos - correct;
		t->setPosition(pos);
	}
	else {
		MovementComponent* mc = mngr_->addComponent<MovementComponent>(p);
		t->setSpeed(300.0f);
		t->setPosition(pos);
		mngr_->addComponent<RouteComponent>(p, route);
		
	}
	
	if (meteorologic) {
		t->setScale(scale);
		Message m;
		m.id = _m_RETURN_ENTITY;
		m.return_entity.ent = p;
		mngr_->send(m);
	}
	
	return p;
}