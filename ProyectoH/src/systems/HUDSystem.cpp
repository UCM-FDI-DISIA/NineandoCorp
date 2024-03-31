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
	towers_imgs.resize(twrId::_twr_SIZE - 1);
	initial_pos.resize(twrId::_twr_SIZE - 1);
	intial_scale.resize(7);

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

	towers_imgs[_twr_BULLET] = bS->addImage(
		{ xAux, heightH },
		{ 55.0f, 80.0f }, 
		0.0f,
		gameTextures::bulletTowerTexture,
		_grp_HUD_FOREGROUND);
	mngr_->addComponent<DragAndDrop>(towers_imgs[_twr_BULLET], _twr_BULLET, sdlutils().intConst().at("BalasPrecio"));
	mngr_->addComponent<FramedImage>(towers_imgs[_twr_BULLET],
		intAt("BalasColumns"), intAt("BalasRows"),
		intAt("BalasWidth"), intAt("BalasHeight"),
		0, 0);
	initial_pos[_twr_BULLET] = { xAux, heightH };

	// cristal tower
	bS->addButton({ xAux * 2, heightH },
		bSize,
		gameTextures::none_box, gameTextures::none_box_hover,
		ButtonTypes::crystal_drag);
	towers_imgs[_twr_CRISTAL] = bS->addImage(
		{ xAux * 2, heightH },
		{ 55.0f, 80.0f },
		0.0,
		cristalTowerTexture,
		_grp_HUD_FOREGROUND);

	mngr_->addComponent<DragAndDrop>(towers_imgs[_twr_CRISTAL], _twr_CRISTAL, sdlutils().intConst().at("CristalPrecio"));
	mngr_->addComponent<FramedImage>(towers_imgs[_twr_CRISTAL],
		intAt("CristalColumns"), intAt("CristalRows"),
		intAt("CristalWidth"), intAt("CristalHeight"),
		0, 0);
	initial_pos[_twr_CRISTAL] = { xAux * 2, heightH };

	//phoenix_tower
	bS->addButton({ xAux * 3, heightH },
		bSize,
		gameTextures::none_box, gameTextures::none_box_hover,
		ButtonTypes::fenix_drag);

	towers_imgs[_twr_FENIX] = bS->addImage(
		{xAux * 3, heightH},
		{60.0f, 80.0f},
		0.0,
		phoenixTowerTexture,
		_grp_HUD_FOREGROUND);

	mngr_->addComponent<DragAndDrop>(towers_imgs[_twr_FENIX], _twr_FENIX, sdlutils().intConst().at("FenixPrecio"));
	mngr_->addComponent<FramedImage>(towers_imgs[_twr_FENIX],
		intAt("FenixColumns"), intAt("FenixRows"), 
		intAt("FenixWidth"), intAt("FenixHeight"), 
		0, 0);

	initial_pos[_twr_FENIX] = { xAux * 3, heightH };  
	 
	//dirt_tower
	bS->addButton({ xAux * 4, heightH },
		bSize,
		gameTextures::none_box, gameTextures::none_box_hover,
		ButtonTypes::clay_drag);
	towers_imgs[_twr_CLAY] = bS->addImage(
		{ xAux * 4, heightH },
		{ 60.0f, 80.0f },
		0.0,
		clayTowerTexture,
		_grp_HUD_FOREGROUND);

	mngr_->addComponent<DragAndDrop>(towers_imgs[_twr_CLAY], _twr_CLAY, sdlutils().intConst().at("ArcillaPrecio"));
	mngr_->addComponent<FramedImage>(towers_imgs[_twr_CLAY],
		intAt("ArcillaColumns"), intAt("ArcillaRows"),
		intAt("ArcillaWidth"), intAt("ArcillaHeight"),
		0, 0);

	initial_pos[_twr_CLAY] = { xAux * 4, heightH };

	//sniper_tower
	bS->addButton({ xAux * 5, heightH },
		bSize,
		gameTextures::none_box, gameTextures::none_box_hover,
		ButtonTypes::sniper_drag);

	towers_imgs[_twr_DIEGO] = bS->addImage(
		{ xAux * 5, heightH },
		{ 45.0f, 80.0f },
		0.0,
		sniperTowerTexture,
		_grp_HUD_FOREGROUND);

	mngr_->addComponent<DragAndDrop>(towers_imgs[_twr_DIEGO], _twr_DIEGO, sdlutils().intConst().at("DiegoSniperPrecio"));
	mngr_->addComponent<FramedImage>(towers_imgs[_twr_DIEGO],
		intAt("DiegoSniperColumns"), intAt("DiegoSniperRows"),
		intAt("DiegoSniperWidth"), intAt("DiegoSniperHeight"),
		0, 0);

	initial_pos[_twr_DIEGO] = { xAux * 5, heightH };

	//slime_tower
	bS->addButton({ xAux * 6, heightH },
		bSize,
		gameTextures::none_box, gameTextures::none_box_hover,
		ButtonTypes::slime_drag);

	towers_imgs[_twr_SLIME] = bS->addImage(
		{ xAux * 6, heightH },
		{ 60.0f, 80.0f },
		0.0,
		slimeTowerTexture,
		_grp_HUD_FOREGROUND);

	mngr_->addComponent<DragAndDrop>(towers_imgs[_twr_SLIME], _twr_SLIME, sdlutils().intConst().at("SlimePrecio"));
	mngr_->addComponent<FramedImage>(towers_imgs[_twr_SLIME],
		intAt("SlimeColumns"), intAt("SlimeRows"),
		intAt("SlimeWidth"), intAt("SlimeHeight"),
		0, 0);

	initial_pos[_twr_SLIME] = { xAux * 6, heightH };

	//boost_tower
	bS->addButton({ xAux * 7, heightH },
		bSize,
		gameTextures::none_box, gameTextures::none_box_hover,
		ButtonTypes::enhancer_drag);

	towers_imgs[_twr_POWER] = bS->addImage(
		{ xAux * 7, heightH },
		{ 55.0f, 80.0f },
		0.0,
		boosterTowerTexture,
		_grp_HUD_FOREGROUND);
  
	mngr_->addComponent<DragAndDrop>(towers_imgs[_twr_POWER], _twr_POWER, sdlutils().intConst().at("PotenciadoraPrecio"));
	mngr_->addComponent<FramedImage>(towers_imgs[_twr_POWER],
		intAt("PotenciadoraColumns"), intAt("PotenciadoraRows"),
		intAt("PotenciadoraWidth"), intAt("PotenciadoraHeight"),
		0, 0);

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
			Vector2D mPos = { (float)ih().getMousePos().first, (float)ih().getMousePos().second };
			Cell* cell = getCellFromTile(mPos);
				dC->drag(cell->position);
				dC->enableDrop(cell->isFree);
				if (ih().mouseButtonEvent()) {
					// click derecho para reset 
					if (ih().getMouseButtonState(InputHandler::MOUSEBUTTON::RIGHT) == 1) {
						auto tr = mngr_->getComponent<Transform>(en);
						mngr_->changeEntityId(_grp_HUD_FOREGROUND, en);
						Vector2D aux = tr->getScale();
						tr->setPosition(initial_pos[i] - aux / 2);
						dC->enableDrag(false);
						enableAllButtons(true);
					}
					//click izquierdo para colocar la torre
					else if (ih().getMouseButtonState(InputHandler::MOUSEBUTTON::LEFT) == 1) {
						auto tr = mngr_->getComponent<Transform>(en);
						dC->drop(tr->getPosition(), Height::LOW);
						cell->isFree = false;

						//resetea el icono de la torre
						dC->enableDrag(false);
						mngr_->changeEntityId(_grp_HUD_FOREGROUND, en);
						Vector2D aux = tr->getScale();
						tr->setPosition(initial_pos[i] - aux / 2);

						enableAllButtons(true);
					}
				}
		}
		i++;
	}
	

}

Cell* HUDSystem::getCellFromTile(const Vector2D& pos) {
	auto mS = mngr_->getSystem<mapSystem>();
	auto net = mS->getMalla();
	return net->searchCell(pos);
}

void HUDSystem::dragTowerIcon(Entity* en){
	mngr_->changeEntityId(_grp_HUD_DRAG_AND_DROP, en);
	mngr_->getComponent<DragAndDrop>(en)->enableDrag(true);
	enableAllButtons(false);
}

void HUDSystem::enableAllButtons(bool b)
{
	Message m;
	m.id = _m_ABLEBUTTONS;
	m.able_buttons_data.buttonId = _hdlr_BUTTON_PLAY;
	m.able_buttons_data.isAble = b;
	mngr_->send(m);
}





