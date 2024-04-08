#include "HUDSystem.h"
#include "../sdlutils/InputHandler.h"
#include "../ecs/Manager.h"

HUDSystem::HUDSystem() :
	buttonsSpace_length_() , // 
	infoSpace_length_(),
	towers_imgs(){
	mActive = true;
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
	
	#pragma region BULLET TOWER
		bS->addButton({ xAux, heightH },
			bSize,
			gameTextures::none_box, gameTextures::none_box_hover,
			ButtonTypes::bullet_drag);

		towers_imgs[_twr_BULLET] = bS->addImage(
			{ xAux + 3, heightH },
			{ floatAt("IconBulletScaleX"), floatAt("IconBulletScaleY")},
			0.0f,
			gameTextures::bulletTowerTexture,
			_grp_HUD_FOREGROUND);
		auto dndBullet = mngr_->addComponent<DragAndDrop>(towers_imgs[_twr_BULLET], _twr_BULLET, sdlutils().intConst().at("BalasPrecio"), Height::LOW);
		
		mngr_->addComponent<FramedImage>(towers_imgs[_twr_BULLET],
			intAt("BalasColumns"), intAt("BalasRows"),
			intAt("BalasWidth"), intAt("BalasHeight"),
			0, 0);
		initial_pos[_twr_BULLET] = { xAux + 3, heightH };

	#pragma endregion

	#pragma region CRISTAL TOWER
		bS->addButton({ xAux * 2, heightH},
			bSize,
			gameTextures::none_box, gameTextures::none_box_hover,
			ButtonTypes::crystal_drag);
		towers_imgs[_twr_CRISTAL] = bS->addImage(
			{ xAux * 2 + 3, heightH - 10 },
			{ floatAt("IconCristalScaleX"), floatAt("IconCristalScaleY") },
			0.0,
			cristalTowerTexture,
			_grp_HUD_FOREGROUND);

		mngr_->addComponent<DragAndDrop>(towers_imgs[_twr_CRISTAL], _twr_CRISTAL, sdlutils().intConst().at("CristalPrecio"), Height::HIGH);
		mngr_->addComponent<FramedImage>(towers_imgs[_twr_CRISTAL],
			intAt("CristalColumns"), intAt("CristalRows"),
			intAt("CristalWidth"), intAt("CristalHeight"),
			0, 0);
		initial_pos[_twr_CRISTAL] = { xAux * 2 + 3, heightH - 10 };

	#pragma endregion

	#pragma region PHOENIX TOWER

		bS->addButton({ xAux * 3, heightH },
			bSize,
			gameTextures::none_box, gameTextures::none_box_hover,
			ButtonTypes::fenix_drag);

		towers_imgs[_twr_FENIX] = bS->addImage(
			{ xAux * 3 + 3, heightH },
			{ floatAt("IconFenixScaleX"), floatAt("IconFenixScaleY") },
			0.0,
			phoenixTowerTexture,
			_grp_HUD_FOREGROUND);

		mngr_->addComponent<DragAndDrop>(towers_imgs[_twr_FENIX], _twr_FENIX, sdlutils().intConst().at("FenixPrecio"), Height::BOTH);
		mngr_->addComponent<FramedImage>(towers_imgs[_twr_FENIX],
			intAt("FenixColumns"), intAt("FenixRows"),
			intAt("FenixWidth"), intAt("FenixHeight"),
			0, 0);

		initial_pos[_twr_FENIX] = { xAux * 3 + 3, heightH };
	#pragma endregion

	#pragma region CLAY TOWER

		bS->addButton({ xAux * 4, heightH },
			bSize,
			gameTextures::none_box, gameTextures::none_box_hover,
			ButtonTypes::clay_drag);
		towers_imgs[_twr_CLAY] = bS->addImage(
			{ xAux * 4 + 3, heightH },
			{ floatAt("IconClayScaleX"), floatAt("IconClayScaleY") },
			0.0,
			clayTowerTexture,
			_grp_HUD_FOREGROUND);

		mngr_->addComponent<DragAndDrop>(towers_imgs[_twr_CLAY], _twr_CLAY, sdlutils().intConst().at("ArcillaPrecio"), Height::PATH);
		mngr_->addComponent<FramedImage>(towers_imgs[_twr_CLAY],
			intAt("ArcillaColumns"), intAt("ArcillaRows"),
			intAt("ArcillaWidth"), intAt("ArcillaHeight"),
			0, 0);

		initial_pos[_twr_CLAY] = { xAux * 4 + 3, heightH };
	#pragma endregion

	#pragma region SNIPER TOWER

		bS->addButton({ xAux * 5, heightH },
			bSize,
			gameTextures::none_box, gameTextures::none_box_hover,
			ButtonTypes::sniper_drag);

		towers_imgs[_twr_DIEGO] = bS->addImage(
			{ xAux * 5 + 3, heightH },
			{ floatAt("IconSniperScaleX"), floatAt("IconSniperScaleY") },
			0.0,
			sniperTowerTexture,
			_grp_HUD_FOREGROUND);

		mngr_->addComponent<DragAndDrop>(towers_imgs[_twr_DIEGO], _twr_DIEGO, sdlutils().intConst().at("DiegoSniperPrecio"), Height::HIGH);
		mngr_->addComponent<FramedImage>(towers_imgs[_twr_DIEGO],
			intAt("DiegoSniperColumns"), intAt("DiegoSniperRows"),
			intAt("DiegoSniperWidth"), intAt("DiegoSniperHeight"),
			0, 0);

		initial_pos[_twr_DIEGO] = { xAux * 5 + 3, heightH };
#pragma endregion
	
	#pragma region SLIME TOWER

		bS->addButton({ xAux * 6, heightH },
			bSize,
			gameTextures::none_box, gameTextures::none_box_hover,
			ButtonTypes::slime_drag);

		towers_imgs[_twr_SLIME] = bS->addImage(
			{ xAux * 6 + 3, heightH },
			{ floatAt("IconSlimeScaleX"), floatAt("IconSlimeScaleY") },
			0.0,
			slimeTowerTexture,
			_grp_HUD_FOREGROUND);

		mngr_->addComponent<DragAndDrop>(towers_imgs[_twr_SLIME], _twr_SLIME, sdlutils().intConst().at("SlimePrecio"), Height::LOW);
		mngr_->addComponent<FramedImage>(towers_imgs[_twr_SLIME],
			intAt("SlimeColumns"), intAt("SlimeRows"),
			intAt("SlimeWidth"), intAt("SlimeHeight"),
			0, 0);

		initial_pos[_twr_SLIME] = { xAux * 6 + 3, heightH };
#pragma endregion

	#pragma region POWER TOWER

		bS->addButton({ xAux * 7, heightH },
			bSize,
			gameTextures::none_box, gameTextures::none_box_hover,
			ButtonTypes::enhancer_drag);

		towers_imgs[_twr_POWER] = bS->addImage(
			{ xAux * 7 + 3, heightH - 4},
			{ floatAt("IconPotenciadorScaleX"), floatAt("IconPotenciadorScaleY") },
			0.0,
			boosterTowerTexture,
			_grp_HUD_FOREGROUND);

		mngr_->addComponent<DragAndDrop>(towers_imgs[_twr_POWER], _twr_POWER, sdlutils().intConst().at("PotenciadoraPrecio"), Height::BOTH);
		mngr_->addComponent<FramedImage>(towers_imgs[_twr_POWER],
			intAt("PotenciadoraColumns"), intAt("PotenciadoraRows"),
			intAt("PotenciadoraWidth"), intAt("PotenciadoraHeight"),
			0, 0);

		initial_pos[_twr_POWER] = { xAux * 7 + 3 , heightH - 4 };
#pragma endregion

	bS->addButton({ (float)sdlutils().width() - 50.0f , 50.0f },
		{50.0f, 50.0f},
		gameTextures::pause_button, gameTextures::pause_button_hover,
		ButtonTypes::pause_main);

	
	Vector2D pAux = { xAux * 8.6f, heightH };
	Vector2D sAux = { 250, 90 };
	
	play = bS->addButton(pAux, sAux, gameTextures::play, gameTextures::play_hover, ButtonTypes::play_wave);

}

void HUDSystem::receive(const Message& m) {
	switch (m.id) 
	{
	case _m_DRAG:
		dragTowerIcon(towers_imgs[m.drag_data.towerId]);
		break;
	case _m_PAUSE:
		mActive = !mActive;
		break;
	case _m_WAVE_START:
		canStartWave = m.start_wave.play;
		mngr_->getComponent<RenderComponent>(play)->setTexture(gameTextures::play);
		break;
	case _m_SHOW_UPGRADE_TOWER_MENU:
		showUpgradeMenu(m.show_upgrade_twr_menu_data.twr, m.show_upgrade_twr_menu_data.pos);
		break;
	default:
		break;
	}
}	
void HUDSystem::update() {
	if (mActive) {
		auto bC = mngr_->getComponent<ButtonComponent>(play);
		if (canStartWave) {
			bC->setActive(false);
		}
		else {
			bC->setActive(true);
		}
		int i = 0;
		for (auto en : towers_imgs) {
			auto dC = mngr_->getComponent<DragAndDrop>(en);
			if (dC != nullptr && dC->isDragged()) {
				Vector2D mPos = { (float)ih().getMousePos().first, (float)ih().getMousePos().second };
				Cell* cell = getCellFromTile(mPos);
				dC->drag(cell->position);

				dC->enableDrop(cell);
				if (ih().mouseButtonEvent()) {
					// click derecho para reset 
					if (ih().getMouseButtonState(InputHandler::MOUSEBUTTON::RIGHT) == 1) {
						auto tr = mngr_->getComponent<Transform>(en);
						mngr_->changeEntityId(_grp_HUD_FOREGROUND, en);
						tr->setScale(resetScale(dC->getTowerId()));
						Vector2D aux = tr->getScale();
						tr->setPosition(initial_pos[i] - aux / 2);
						dC->enableDrag(false);
						enableAllButtons(true);
					}
					//click izquierdo para colocar la torre
					else if (ih().getMouseButtonState(InputHandler::MOUSEBUTTON::LEFT) == 1) {
						auto tr = mngr_->getComponent<Transform>(en);
						if (cell->isFree) {
							dC->drop(tr->getPosition(), Height::LOW);
							cell->isFree = false;
						}
						else {
							//mensaje de no colocar
							Message m;
							m.id = _m_ADD_TEXT;
							m.add_text_data.txt = "NO SE PUEDE COLOCAR EN ESTA POSICION";
							m.add_text_data.color = { 255, 0 ,0, 255 };
							Vector2D txtScale = Vector2D(800.0f, 75.0f);
							m.add_text_data.pos = Vector2D(sdlutils().width() / 2, sdlutils().height() / 2) - (txtScale / 2);
							m.add_text_data.scale = txtScale;
							m.add_text_data.time = 1000;
							mngr_->send(m);
						}

						//resetea el icono de la torre
						dC->enableDrag(false);
						mngr_->changeEntityId(_grp_HUD_FOREGROUND, en);
						tr->setScale(resetScale(dC->getTowerId()));
						Vector2D aux = tr->getScale();
						tr->setPosition(initial_pos[i] - aux / 2);

						enableAllButtons(true);
					}
				}
			}
			i++;
		}
	}
	

}

void HUDSystem::showUpgradeMenu(Entity* twr, const Vector2D& pos) {
	auto bS = mngr_->getSystem<ButtonSystem>();
	UpgradeMenu upM;
	/** 
	* BACKGROUND DE MENU
	*/
	upM.background = bS->addImage({ pos.getX(), pos.getY() - 100.0f},
		{ 300.0f, 200.0f },
		0.0,
		gameTextures::box,
		_grp_HUD_BACKGROUND);
	/**
	* BOTON DE MEJORA
	*/
	Message m;
	m.id = _m_UPGRADE_TWR_INGAME;
	m.upgrade_twr_ingame_data.upCmp = twr;

	upM.upgradeButton = bS->addButton({ pos.getX() + 150 , pos.getY()+ 70},
		{ 50.0f, 20.0f },
		upgrade, upgrade_hover, ButtonTypes::upgrade_tower,0,
		m
		);
}

Cell* HUDSystem::getCellFromTile(const Vector2D& pos) {
	auto mS = mngr_->getSystem<mapSystem>();
	auto net = mS->getMalla();
	return net->searchCell(pos);
}

Vector2D HUDSystem::resetScale(twrId tId)
{
	Vector2D scale;
	switch (tId)
	{
	case _twr_BULLET:
		scale.set(Vector2D(floatAt("IconBulletScaleX"), floatAt("IconBulletScaleY")));
		break;
	case _twr_CRISTAL:
		scale.set(Vector2D(floatAt("IconCristalScaleX"), floatAt("IconCristalScaleY")));
		break;
	case _twr_SLIME:
		scale.set(Vector2D(floatAt("IconSlimeScaleX"), floatAt("IconSlimeScaleY")));
		break;
	case _twr_DIEGO:
		scale.set(Vector2D(floatAt("IconSniperScaleX"), floatAt("IconSniperScaleY")));
		break;
	case _twr_FENIX:
		scale.set(Vector2D(floatAt("IconFenixScaleX"), floatAt("IconFenixScaleY")));
		break;
	case _twr_CLAY:
		scale.set(Vector2D(floatAt("IconClayScaleX"), floatAt("IconClayScaleY")));
		break;
	case _twr_POWER:
		scale.set(Vector2D(floatAt("IconPotenciadorScaleX"), floatAt("IconPotenciadorScaleY")));
		break;
	default:
		break;
	}
	return scale;
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




