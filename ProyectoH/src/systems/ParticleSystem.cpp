#include "ParticleSystem.h"
#include "../ecs/Manager.h"
#include "../components/FramedImage.h"
#include "../components/Transform.h"
#include "../components/ParticleLifeTime.h"

ParticleSystem::ParticleSystem() {

}
ParticleSystem::~ParticleSystem() {

}


void ParticleSystem::initSystem() {

}
void  ParticleSystem::receive(const Message& m) {
	switch (m.id) {
	case _m_ANIM_CREATE:
		addParticle(m.anim_create.idGrp, m.anim_create.tex, m.anim_create.pos, m.anim_create.scale, m.anim_create.frameInit, m.anim_create.frameEnd,
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
		f->updateCurrentFrame();
		if (p->getIters() <= f->getIters()) {
			mngr_->setAlive(par, false);
			mngr_->deleteHandler(_hdlr_PARTICLES, par);
		}
	}
}

Entity* ParticleSystem::addParticle(grpId id, gameTextures tex, Vector2D pos, Vector2D scale, int frameFirst, int lastFrame, int speed, int rows, int col, int width, int height, int iter) {
	auto p = mngr_->addEntity(id);
	mngr_->setHandler(_hdlr_PARTICLES, p);
	mngr_->addComponent<RenderComponent>(p, tex);
	mngr_->addComponent<FramedImage>(p, rows, col, width, height, frameFirst, speed, lastFrame);
	mngr_->addComponent<ParticleLifeTime>(p, iter);
	auto t = mngr_->addComponent<Transform>(p);
	t->setPosition(pos);
	t->setScale(scale);
	Message m;
	m.id = _m_RETURN_ENTITY;
	m.return_entity.ent = p;
	mngr_->send(m);
	return p;
}