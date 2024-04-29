#include "GameOverSystem.h"
#include "ButtonSystem.h"
#include "../ecs/Manager.h"
#include "../components/TextComponent.h"
#include "../game/Game.h"

GameOverSystem::GameOverSystem() {
}

void GameOverSystem::initSystem() {
	sdlutils().soundEffects().at("button").haltAllChannels();
	float xAux = (float)sdlutils().width() / 2;
	float heightH = ((float)sdlutils().height() / 8);
	Vector2D bSize = { (float)sdlutils().width() / 4, (float)sdlutils().height() / 8 };
	SDL_Color textColor = { 255, 255, 255, 255 };

	ButtonSystem* bS = mngr_->getSystem<ButtonSystem>();

	bS->addImage({ (float)sdlutils().width()/2 , (float)sdlutils().height()/2 },
		{ (float)sdlutils().width() + 500, (float)sdlutils().height() + 500},
		0.0,
		gameTextures::box,
		_grp_HUD_BACKGROUND);

	header = bS->addText(" ", textColor, { xAux , heightH }, {bSize.getX() * 2, bSize.getY() });

	rounds = bS->addText(" ", textColor, { xAux , heightH * 2 + (heightH/2)}, {bSize.getX(), bSize.getY() / 2});

	enemies = bS->addText(" ", textColor, { xAux , heightH * 3 + (heightH / 2) }, { bSize.getX(), bSize.getY() / 2 });

	coins = bS->addText(" ", textColor, { xAux , heightH * 4 + (heightH / 2) }, { bSize.getX(), bSize.getY()/2 });

	bS->addButton({ xAux, heightH*6},
		bSize,
		gameTextures::backToMenu_button, gameTextures::backToMenu_button_hover,
		ButtonTypes::back_to_menu);
}

GameOverSystem::~GameOverSystem() {

}

void GameOverSystem::receive(const Message& m) {
	switch (m.id) {
		case _m_OVER_GAME:
			win = m.over_game.winner;
			currentLvl = m.over_game.currentLvl;
			roundsPassed = m.over_game.rounds;
			enemiesDefeated =  m.over_game.enemies;
			coinsObtained = m.over_game.coinsH;
			PlayVictory_DefeatSound();
			break;
	}
}

void GameOverSystem::PlayVictory_DefeatSound() {
	sdlutils().soundEffects().at("Victoria").setChannelVolume(game().CalculoVolumenEfectos(), 2);
	if (win) {
		sdlutils().soundEffects().at("Victoria").play(0, 2);
	}
	else{
		sdlutils().soundEffects().at("Derrota").play(0, 2);
	}
}

void GameOverSystem::update() {
	sdlutils().soundEffects().at("WhooshPantallaFinNivel").setChannelVolume(game().CalculoVolumenEfectos(), 1);
	if (currentAnim != NONE_ANIM) {
		if (timer <= 0) {
			string text;
			TextComponent* textC;
			switch (currentAnim) {
			case HEADER_ANIM:
				if (win)
					text = "LEVEL " + std::to_string(currentLvl) + " COMPLETE";
				else
					text = "GAME OVER";
				textC = mngr_->getComponent<TextComponent>(header);
				textC->setText(text);
				textC->update();
				currentAnim = ROUNDS_ANIM;
				timer = startTime;
				sdlutils().soundEffects().at("WhooshPantallaFinNivel").play(0, 1);
				break;
			case ROUNDS_ANIM:
					text = "Rounds complete: " + std::to_string(roundsPassed);
					textC = mngr_->getComponent<TextComponent>(rounds);
					textC->setText(text);
					textC->update();
					currentAnim = ENEMIES_ANIM;
					timer = startTime;
					sdlutils().soundEffects().at("WhooshPantallaFinNivel").play(0, 1);
					break;
			case ENEMIES_ANIM:
				enemiesCont += game().getDeltaTime() * 50;
				if (enemiesCont >= enemiesDefeated) {
					enemiesCont = enemiesDefeated;
					currentAnim = COINS_ANIM;
					timer = startTime;
				}

				text = "Enemies defeated: " + std::to_string((int)enemiesCont);
				textC = mngr_->getComponent<TextComponent>(enemies);
				textC->setText(text);
				textC->update();
				sdlutils().soundEffects().at("WhooshPantallaFinNivel").play(0, 1);
				break;
			case COINS_ANIM:
				coinsCont += game().getDeltaTime() * 500;
				if (coinsCont >= coinsObtained) {
					coinsCont = coinsObtained;
					currentAnim = NONE_ANIM;
				}

				text = "Coins H obtained: " + std::to_string((int)coinsCont);
				textC = mngr_->getComponent<TextComponent>(coins);
				textC->setText(text);
				textC->update();
				sdlutils().soundEffects().at("WhooshPantallaFinNivel").play(0, 1);
				break;
			}
		}
		else {
			timer -= game().getDeltaTime();
		}
	}
}