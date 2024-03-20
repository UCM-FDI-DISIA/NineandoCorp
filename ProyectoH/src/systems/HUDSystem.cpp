#include "HUDSystem.h"
#include "../sdlutils/InputHandler.h"
#include "../ecs/Manager.h"

HUDSystem::HUDSystem() :
	buttonsSpace_length_() , // 
	infoSpace_length_(),
	towers_imgs(){
}
HUDSystem::~HUDSystem(){
}

void HUDSystem::initSystem() {
	towers_imgs.resize(7);
	initial_pos.resize(7);

	ButtonSystem* bS = mngr_->getSystem<ButtonSystem>();

	buttonsSpace_length_ = sdlutils().width() - 200; 
	float heightH = (float)sdlutils().height() - 80.0f;
	//float xAux = (float)(sdlutils().width() - 150)  / 7;
	float xAux = (float)(buttonsSpace_length_ - 150 ) / 7;
	float separation = 150.0f;
	Vector2D bSize = Vector2D(100.0f, 100.0f);
	bS->addImage({ (float)sdlutils().width() / 2 , heightH },
		{ (float)sdlutils().width() + 30.0f, 200.0f },

		0.0,
		gameTextures::box,
		_grp_HUD_BACKGROUND);
	
	// bullet tower
	bS->addButton({ xAux, heightH },
		bSize,
		gameTextures::none_box, gameTextures::none_box_hover,
		ButtonTypes::bullet_drag);

	towers_imgs[_twr_BULLET] = bS->addImage({ xAux, heightH },
		{ 55.0f, 80.0f }, 0.0f,
		gameTextures::bullet_tower_image,
		_grp_HUD_FOREGROUND);
	mngr_->addComponent<DragAndDrop>(towers_imgs[_twr_BULLET], _twr_BULLET);
	initial_pos[_twr_BULLET] = { xAux, heightH };


	// cristal tower
	bS->addButton({ xAux * 2, heightH },
		bSize,
		gameTextures::none_box, gameTextures::none_box_hover,
		ButtonTypes::crystal_drag);
	towers_imgs[_twr_CRISTAL] = bS->addButton({ xAux * 2, heightH },
		{ 55.0f, 80.0f },
		gameTextures::crystal_tower_image, gameTextures::crystal_tower_image,
		ButtonTypes::none);
	mngr_->addComponent<DragAndDrop>(towers_imgs[_twr_CRISTAL], _twr_CRISTAL);
	initial_pos[_twr_CRISTAL] = { xAux * 2, heightH };

	//phoenix_tower
	bS->addButton({ xAux * 3, heightH },
		bSize,
		gameTextures::none_box, gameTextures::none_box_hover,
		ButtonTypes::fenix_drag);
	towers_imgs[_twr_FENIX] = bS->addButton({ xAux * 3, heightH },
		{ 60.0f, 80.0f },
		gameTextures::phoenix_tower_image, gameTextures::phoenix_tower_image,
		ButtonTypes::none);
	mngr_->addComponent<DragAndDrop>(towers_imgs[_twr_FENIX], _twr_FENIX);
	initial_pos[_twr_FENIX] = { xAux * 3, heightH };

	//dirt_tower
	bS->addButton({ xAux * 4, heightH },
		bSize,
		gameTextures::none_box, gameTextures::none_box_hover,
		ButtonTypes::clay_drag);
	towers_imgs[_twr_CLAY] = bS->addButton({ xAux * 4, heightH },
		{ 60.0f, 80.0f },
		gameTextures::clay_tower_image, gameTextures::clay_tower_image,
		ButtonTypes::none);
	mngr_->addComponent<DragAndDrop>(towers_imgs[_twr_CLAY], _twr_CLAY);
	initial_pos[_twr_CLAY] = { xAux * 4, heightH };

	//sniper_tower
	bS->addButton({ xAux * 5, heightH },
		bSize,
		gameTextures::none_box, gameTextures::none_box_hover,
		ButtonTypes::sniper_drag);
	towers_imgs[_twr_DIEGO] = bS->addButton({ xAux* 5, heightH },
		{ 45.0f, 80.0f },
		gameTextures::sniper_tower_image, gameTextures::sniper_tower_image,
		ButtonTypes::none);
	mngr_->addComponent<DragAndDrop>(towers_imgs[_twr_DIEGO], _twr_DIEGO);
	initial_pos[_twr_DIEGO] = { xAux * 5, heightH };

	//slime_tower
	bS->addButton({ xAux * 6, heightH },
		bSize,
		gameTextures::none_box, gameTextures::none_box_hover,
		ButtonTypes::slime_drag);
	towers_imgs[_twr_SLIME] = bS->addButton({ xAux * 6, heightH },
		{ 60.0f, 80.0f },
		gameTextures::slime_tower_image, gameTextures::slime_tower_image,
		ButtonTypes::none);
	mngr_->addComponent<DragAndDrop>(towers_imgs[_twr_SLIME], _twr_SLIME);
	initial_pos[_twr_SLIME] = { xAux * 6, heightH };

	//boost_tower
	bS->addButton({ xAux * 7, heightH },
		bSize,
		gameTextures::none_box, gameTextures::none_box_hover,
		ButtonTypes::enhancer_drag);
	towers_imgs[_twr_POWER] = (bS->addButton({ xAux * 7, heightH },
		{ 55.0f, 80.0f },
		gameTextures::power_tower_image, gameTextures::power_tower_image,
		ButtonTypes::none));
	mngr_->addComponent<DragAndDrop>(towers_imgs[_twr_POWER], _twr_POWER);
	initial_pos[_twr_POWER] = { xAux * 7, heightH };
}

void HUDSystem::receive(const Message& m) {
	switch (m.id) 
	{
	case _m_DRAG:
		dragTowerIcon(towers_imgs[m.drag_data.towerId]);
		break;
	default:
		break;
	}
}	
void HUDSystem::update() {
	int i = 0;
	for (auto en : towers_imgs) {
		auto dC = mngr_->getComponent<DragAndDrop>(en);
		if (dC != nullptr && dC->isDragged()) {
				dC->drag();
				if (ih().mouseButtonEvent()) {
					// click derecho para reset 
					if (ih().getMouseButtonState(InputHandler::MOUSEBUTTON::RIGHT) == 1) {
						auto tr = mngr_->getComponent<Transform>(en);
						Vector2D aux = tr->getScale();
						tr->setPosition(initial_pos[i] - aux / 2);
						dC->enableDrag(false);
					}
					//click izquierdo para colocar la torre
					else if (ih().getMouseButtonState(InputHandler::MOUSEBUTTON::LEFT) == 1) {
						auto mS = mngr_->getSystem<mapSystem>();
						auto net = mS->getMalla();
						auto tr = mngr_->getComponent<Transform>(en);
						Vector2D mPos = { (float)ih().getMousePos().first, (float)ih().getMousePos().second };
						Vector2D pos = net->searchCell(mPos)->position;
						dC->drop(pos, Height::LOW);
						
						//resetea el icono de la torre
						Vector2D aux = tr->getScale();
						tr->setPosition(initial_pos[i] - aux / 2);
						dC->enableDrag(false);

					}
				}
		}
		i++;
	}
	

}

void HUDSystem::dragTowerIcon(Entity* en){
	mngr_->getComponent<DragAndDrop>(en)->enableDrag(true);
}





