#include "EnemyBookSystem.h"
#include "../ecs/Manager.h"
#include "../game/Game.h"


EnemyBookSystem::~EnemyBookSystem()
{
	for (auto en : mngr_->getHandler(_hdlr_BUTTON_ENEMYBOOK)) {
		mngr_->setAlive(en, false);
	}
	mngr_->refresh();
	mngr_->deleteAllHandlers(_hdlr_BUTTON_ENEMYBOOK);
}
void EnemyBookSystem::initSystem() {
	Vistos = game().getSaveGame()->getEnemiesBook();
	ButtonSystem* bS = mngr_->getSystem<ButtonSystem>();
	//BACKGROUND
	Vector2D pAux = { sdlutils().width() / 2.0f, sdlutils().height() / 2.0f };
	Vector2D sAux = { 1000.0f , 600.0f };
	bS->addImage(pAux, sAux, 0.0, gameTextures::large_box, _grp_HUD_FOREGROUND);
	//boton cerrar
	pAux = pAux + Vector2D(430.0f, -230.0f);
	sAux = { 70.0f, 70.0f };
	bS->addButton(pAux, sAux, gameTextures::close, gameTextures::close_hover, ButtonTypes::back_selector);

	// Calcular la posición inicial del contenido
	float contentPosX = 400.f; // Posición inicial x del contenido
	float contentPosY = 350.f; // Posición y del contenido
	float contentPosYaux = 300.f; // Posición y del contenido aux
	float contentWidth = 100.f; // Ancho del contenido
	float contentHeight = 100.f; // Alto del contenido


	// imágenes de enemigos
	float spacingX = 120.f; // Espacio horizontal entre las imágenes de enemigos
	int t = 0;

	auto text = gameTextures::large_box;
	for (size_t i = 0; i < _enm_SIZE; i++) {
		// Calcular la posición de la imagen del enemigo
		Vector2D pAux = { contentPosX + t * spacingX, contentPosY };
		Vector2D sAux = { contentWidth, contentHeight };
		Vector2D sAuxbox = { contentWidth + 15, contentHeight + 15 };
		Message m;
		m.id = _m_ENEMY_BOOKPOPUP;
		m.start_enemy_book_but.n = i;
		if (Vistos[i] == true)
		{
			text = Texturas[i];
			bS->addImage(pAux, sAuxbox, 0.0, gameTextures::large_box, _grp_HUD_FOREGROUND);
			bS->addButton(pAux, sAux, text, text, ButtonTypes::enemybook,0,0,0,m);

		}
		else {
			text = TexturasSilueta[i];
			bS->addImage(pAux, sAuxbox, 0.0, gameTextures::large_box, _grp_HUD_FOREGROUND);
			bS->addImage(pAux, sAuxbox, 0.0, text, _grp_HUD_FOREGROUND);
		}

		t++;
		if (t % 5 == 0 && t != 0)
		{
			contentPosY += contentPosYaux / 2;
			t = 0;
		}
	}
}
void  EnemyBookSystem::receive(const Message& m) {
	switch (m.id)
	{
	case _m_ENEMY_BOOKPOPUP:
		EnemyPopUp(m.start_enemy_book_but.n);
		break;
	case _m_ENEMY_BOOKPOPUPABILITY:
		EnemyPopUpABILITY(m.start_enemy_book_but.n);
		break;
	default:
		break;
	}
}
void EnemyBookSystem::EnemyPopUp(int i) {
	ButtonSystem* bS = mngr_->getSystem<ButtonSystem>();
	//BACKGROUND
	Vector2D pAux = { sdlutils().width() / 2.0f, sdlutils().height() / 2.0f };
	Vector2D sAux = { 500.0f , 300.0f };
	bS->addImage(pAux, sAux, 0.0, gameTextures::large_box, _grp_HUD_FOREGROUND);
	//BOTON CERRAR
	pAux = pAux + Vector2D(200, -100.0f);
	sAux = { 50.0f, 50.0f };
	bS->addButton(pAux, sAux, gameTextures::close, gameTextures::close_hover, ButtonTypes::back_selector);

	string hab = "";
	string vel = "";
	string vida = "";
	string tipo = "";
	string atq = "";
	string nombre = "";
	string rango = "";
	string Tiempo = "";
	bool habilidad = false;
	switch (i)
	{
            case 0:
                nombre = "Soul Master";
                vida = std::to_string(sdlutils().intConst().at("MaestroVida"));
                atq = std::to_string(sdlutils().intConst().at("MaestroAtaque"));
                vel = std::to_string(sdlutils().intConst().at("MaestroVelocidad"));
                Tiempo = std::to_string(sdlutils().intConst().at("Maestrotiempo"));

                if (sdlutils().intConst().at("MaestroTipo") == 1)
                {
                    tipo = "Aerial";
                }
                else {
                    tipo = "ground";
                }

                if (sdlutils().intConst().at("MaestroRango") == 1)
                {
                    rango = "Range";
                }
                else {
                    rango = "Melee";
                }
                habilidad = true;
                break;
            case 1:
                nombre = "Electric Stalker";
                vida = std::to_string(sdlutils().intConst().at("AcechanteVida"));
                atq = std::to_string(sdlutils().intConst().at("AcechanteAtaque"));
                vel = std::to_string(sdlutils().intConst().at("AcechanteVelocidad"));
                Tiempo = std::to_string(sdlutils().intConst().at("Acechantetiempo"));
                if (sdlutils().intConst().at("AcechanteTipo") == 1)
                {
                    tipo = "Aerial";
                }
                else {
                    tipo = "ground";
                }
                if (sdlutils().intConst().at("AcechanteRango") == 1)
                {
                    rango = "Range";
                }
                else {
                    rango = "Melee";
                }
                habilidad = true;
                break;
            case 2:
                nombre = "Cursed";
                vida = std::to_string(sdlutils().intConst().at("MalditoVida"));
                atq = std::to_string(sdlutils().intConst().at("MalditoAtaque"));
                vel = std::to_string(sdlutils().intConst().at("MalditoVelocidad"));
                Tiempo = std::to_string(sdlutils().intConst().at("Malditotiempo"));
                if (sdlutils().intConst().at("MalditoTipo") == 1)
                {
                    tipo = "Aerial";
                }
                else {
                    tipo = "ground";
                }
                if (sdlutils().intConst().at("MalditoRango") == 1)
                {
                    rango = "Range";
                }
                else {
                    rango = "Melee";
                }
                break;
            case 3:
                nombre = "Golem";
                vida = std::to_string(sdlutils().intConst().at("GolemVida"));
                atq = std::to_string(sdlutils().intConst().at("GolemAtaque"));
                vel = std::to_string(sdlutils().intConst().at("GolemVelocidad"));
                Tiempo = std::to_string(sdlutils().intConst().at("Golemtiempo"));
                if (sdlutils().intConst().at("GolemTipo") == 1)
                {
                    tipo = "Aerial";
                }
                else {
                    tipo = "ground";
                }
                if (sdlutils().intConst().at("GolemRango") == 1)
                {
                    rango = "Range";
                }
                else {
                    rango = "Melee";
                }
                habilidad = true;
                break;
            case 4:
                nombre = "Winged Demon";
                vida = std::to_string(sdlutils().intConst().at("DemonioAladoVida"));
                atq = std::to_string(sdlutils().intConst().at("DemonioAladoAtaque"));
                vel = std::to_string(sdlutils().intConst().at("DemonioAladoVelocidad"));
                Tiempo = std::to_string(sdlutils().intConst().at("DemonioAladotiempo"));
                if (sdlutils().intConst().at("DemonioAladoTipo") == 1)
                {
                    tipo = "Aerial";
                }
                else {
                    tipo = "ground";
                }
                if (sdlutils().intConst().at("DemonioAladoRango") == 1)
                {
                    rango = "Range";
                }
                else {
                    rango = "Melee";
                }
                break;
            case 5:
                nombre = "Goblin";
                vida = std::to_string(sdlutils().intConst().at("GoblinVida"));
                atq = std::to_string(sdlutils().intConst().at("GoblinAtaque"));
                vel = std::to_string(sdlutils().intConst().at("GoblinVelocidad"));
                Tiempo = std::to_string(sdlutils().intConst().at("Goblintiempo"));
                if (sdlutils().intConst().at("GoblinTipo") == 1)
                {
                    tipo = "Aerial";
                }
                else {
                    tipo = "ground";
                }
                if (sdlutils().intConst().at("GoblinRango") == 1)
                {
                    rango = "Range";
                }
                else {
                    rango = "Melee";
                }
                break;
            case 6:
                nombre = "Elf";
                vida = std::to_string(sdlutils().intConst().at("ElfoVida"));
                atq = std::to_string(sdlutils().intConst().at("ElfoAtaque"));
                vel = std::to_string(sdlutils().intConst().at("ElfoVelocidad"));
                Tiempo = std::to_string(sdlutils().intConst().at("Elfotiempo"));
                if (sdlutils().intConst().at("ElfoTipo") == 1)
                {
                    tipo = "Aerial";
                }
                else {
                    tipo = "ground";
                }
                if (sdlutils().intConst().at("ElfoRango") == 1)
                {
                    rango = "Range";
                }
                else {
                    rango = "Melee";
                }
                break;
            case 7:
                nombre = "Messenger of Death";
                vida = std::to_string(sdlutils().intConst().at("MensajeroVida"));
                atq = std::to_string(sdlutils().intConst().at("MensajeroAtaque"));
                vel = std::to_string(sdlutils().intConst().at("MensajeroVelocidad"));
                Tiempo = std::to_string(sdlutils().intConst().at("Mensajerotiempo"));
                if (sdlutils().intConst().at("MensajeroTipo") == 1)
                {
                    tipo = "Aerial";
                }
                else {
                    tipo = "ground";
                }
                if (sdlutils().intConst().at("MensajeroRango") == 1)
                {
                    rango = "Range";
                }
                else {
                    rango = "Melee";
                }
                habilidad = true;
                break;
            case 8:
                nombre = "Angel";
                vida = std::to_string(sdlutils().intConst().at("AngelVida"));
                atq = std::to_string(sdlutils().intConst().at("AngelAtaque"));
                vel = std::to_string(sdlutils().intConst().at("AngelVelocidad"));
                Tiempo = std::to_string(sdlutils().intConst().at("Angeltiempo"));
                if (sdlutils().intConst().at("AngelTipo") == 1)
                {
                    tipo = "Aerial";
                }
                else {
                    tipo = "ground";
                }
                if (sdlutils().intConst().at("AngelRango") == 1)
                {
                    rango = "Range";
                }
                else {
                    rango = "Melee";
                }
                habilidad = true;
                break;
            case 9:
                nombre = "Infernal Demon";
                vida = std::to_string(sdlutils().intConst().at("DemonioInfernalVida"));
                atq = std::to_string(sdlutils().intConst().at("DemonioInfernalAtaque"));
                vel = std::to_string(sdlutils().intConst().at("DemonioInfernalVelocidad"));
                Tiempo = std::to_string(sdlutils().intConst().at("DemonioInfernaltiempo"));
                if (sdlutils().intConst().at("DemonioInfernalTipo") == 1)
                {
                    tipo = "Aerial";
                }
                else {
                    tipo = "ground";
                }
                if (sdlutils().intConst().at("DemonioInfernalRango") == 1)
                {
                    rango = "Range";
                }
                else {
                    rango = "Melee";
                }
                break;
            case 10:
                nombre = "Defender";
                vida = std::to_string(sdlutils().intConst().at("DefensorVida"));
                atq = std::to_string(sdlutils().intConst().at("DefensorAtaque"));
                vel = std::to_string(sdlutils().intConst().at("DefensorVelocidad"));
                Tiempo = std::to_string(sdlutils().intConst().at("Defensortiempo"));
                if (sdlutils().intConst().at("DefensorTipo") == 1)
                {
                    tipo = "Aerial";
                }
                else {
                    tipo = "ground";
                }
                if (sdlutils().intConst().at("DefensorRango") == 1)
                {
                    rango = "Range";
                }
                else {
                    rango = "Melee";
                }
                habilidad = true;
                break;
            case 11:
                nombre = "Cursed One";
                vida = std::to_string(sdlutils().intConst().at("CMalditoVida"));
                atq = std::to_string(sdlutils().intConst().at("CMalditoAtaque"));
                vel = std::to_string(sdlutils().intConst().at("CMalditoVelocidad"));
                Tiempo = std::to_string(sdlutils().intConst().at("CMalditotiempo"));
                if (sdlutils().intConst().at("CMalditoTipo") == 1)
                {
                    tipo = "Aerial";
                }
                else {
                    tipo = "ground";
                }
                if (sdlutils().intConst().at("CMalditoRango") == 1)
                {
                    rango = "Range";
                }
                else {
                    rango = "Melee";
                }
                habilidad = true;
                break;
            case 12:
                nombre = "Little Prince";
                vida = std::to_string(sdlutils().intConst().at("PrincipitoVida"));
                atq = std::to_string(sdlutils().intConst().at("PrincipitoAtaque"));
                vel = std::to_string(sdlutils().intConst().at("PrincipitoVelocidad"));
                Tiempo = std::to_string(sdlutils().intConst().at("Principitotiempo"));
                if (sdlutils().intConst().at("PrincipitoTipo") == 1)
                {
                    tipo = "Aerial";
                }
                else {
                    tipo = "ground";
                }
                if (sdlutils().intConst().at("PrincipitoRango") == 1)
                {
                    rango = "Range";
                }
                else {
                    rango = "Melee";
                }
                habilidad = true;
                break;
            case 13:
                nombre = "Monk";
                vida = std::to_string(sdlutils().intConst().at("MonjeVida"));
                atq = std::to_string(sdlutils().intConst().at("MonjeAtaque"));
                vel = std::to_string(sdlutils().intConst().at("MonjeVelocidad"));
                Tiempo = std::to_string(sdlutils().intConst().at("Monjetiempo"));
                if (sdlutils().intConst().at("MonjeTipo") == 1)
                {
                    tipo = "Aerial";
                }
                else {
                    tipo = "ground";
                }
                if (sdlutils().intConst().at("MonjeRango") == 1)
                {
                    rango = "Range";
                }
                else {
                    rango = "Melee";
                }
                habilidad = true;
                break;
            case 14:
                nombre = "Death";
                vida = std::to_string(sdlutils().intConst().at("MuerteVida"));
                atq = std::to_string(sdlutils().intConst().at("MuerteAtaque"));
                vel = std::to_string(sdlutils().intConst().at("MuerteVelocidad"));
                Tiempo = std::to_string(sdlutils().intConst().at("Muertetiempo"));
                if (sdlutils().intConst().at("MuerteTipo") == 1)
                {
                    tipo = "Aerial";
                }
                else {
                    tipo = "ground";
                }
                if (sdlutils().intConst().at("MuerteRango") == 1)
                {
                    rango = "Range";
                }
                else {
                    rango = "Melee";
                }
                habilidad = true;
                break;
            default:
                break;
	}
	// IMG ENEMIGO
	pAux = Vector2D{500,470};
	sAux = Vector2D{ 100,100 };
	bS->addImage(pAux, sAux + Vector2D{50,50}, 0.0, gameTextures::large_box, _grp_HUD_FOREGROUND);
	bS->addImage(pAux, sAux,0.0,Texturas[i], _grp_HUD_FOREGROUND);
	//NOMBRE
	pAux = Vector2D{ 700,420 };
	sAux = Vector2D{ 210,70};
	SDL_Color NombreColor = { 255, 255, 255, 255 };
	Entity* nombreT = bS->addText(nombre, NombreColor, pAux, sAux);
	texto.push_back(nombreT);
	//ATAQUE
	pAux = Vector2D{ 650,470 };
	sAux = Vector2D{ 90,30 };
	Entity* ataqueT = bS->addText("Attack: " + atq, NombreColor, pAux, sAux);
	texto.push_back(ataqueT);
	// VIDA
	pAux = Vector2D{ 800,470 };
	Entity* vidaT = bS->addText("Health: " +vida, NombreColor, pAux, sAux);
	texto.push_back(vidaT);
	// VELOCIDAD
	pAux = Vector2D{ 650,510 };
	Entity* velocidadT = bS->addText("Velocity: " +vel, NombreColor, pAux, sAux);
	texto.push_back(velocidadT);
	// TIEMPO ATAQUE
	sAux = Vector2D{ 100,34 };
	pAux = Vector2D{ 800,510};
	Entity* tiempoT = bS->addText("Attck.Vel: " +Tiempo, NombreColor, pAux, sAux);
	texto.push_back(tiempoT);
	// RANGO
	pAux = Vector2D{ 650,560 };
	Entity* rangoT = bS->addText("Range: " + rango, NombreColor, pAux, sAux);
	texto.push_back(rangoT);
	// TIPO
	pAux = Vector2D{ 800,560 };
	Entity* tipoT = bS->addText("Type: " + tipo, NombreColor, pAux, sAux);
	texto.push_back(tipoT);
	// HABILIDAD
	if (habilidad)
	{
		Message m;
		m.id = _m_ENEMY_BOOKPOPUPABILITY;
		m.start_enemy_book_but.n = i;
		pAux = Vector2D{ 500,595 };
		sAux = Vector2D{ 140,50 };
		bS->addButton(pAux, sAux, gameTextures::ability, gameTextures::ability_hover, ButtonTypes::enemybookPopAbility,0, 0, 0,m);
	}

}
void EnemyBookSystem::EnemyPopUpABILITY(int i) {
	for (size_t i = 0; i < texto.size(); i++)
	{
		mngr_->getComponent<TextComponent>(texto[i])->isActive = false;
	}
	ButtonSystem* bS = mngr_->getSystem<ButtonSystem>();
	//BACKGROUND
	Vector2D pAux = { sdlutils().width() / 2.0f, sdlutils().height() / 2.0f };
	Vector2D sAux = { 500.0f , 300.0f };
	bS->addImage(pAux, sAux, 0.0, gameTextures::large_box, _grp_HUD_FOREGROUND);
	//BOTON CERRAR
	pAux = pAux + Vector2D(200, -100.0f);
	sAux = { 50.0f, 50.0f };
	bS->addButton(pAux, sAux, gameTextures::close, gameTextures::close_hover, ButtonTypes::back_selector);
	//IMG ENEMIGO
	pAux = Vector2D{ 500,470 };
	sAux = Vector2D{ 100,100 };
	bS->addImage(pAux, sAux + Vector2D{ 50,50 }, 0.0, gameTextures::large_box, _grp_HUD_FOREGROUND);
	bS->addImage(pAux, sAux, 0.0, Texturas[i], _grp_HUD_FOREGROUND);

	string nombre;
    std::vector<std::string> habilidad;
		switch (i)
		{
        case 0:
            nombre = "Soul Master";
            habilidad = getDescription("soul_master");
            break;
        case 1:
            nombre = "Electric Stalker";
            habilidad = getDescription("electric_stalker");
            break;
        case 2:
            nombre = "Cursed";
            habilidad = getDescription("cursed");
            break;
        case 3:
            nombre = "Golem";
            habilidad = getDescription("golem");
            break;
        case 4:
            nombre = "Winged Demon";
            habilidad = getDescription("winged_demon");
            break;
        case 5:
            nombre = "Goblin";
            habilidad = getDescription("goblin");
            break;
        case 6:
            nombre = "Elf";
            habilidad = getDescription("elf");
            break;
        case 7:
            nombre = "Messenger of Death";
            habilidad = getDescription("messenger_of_death");
            break;
        case 8:
            nombre = "Angel";
            habilidad = getDescription("angel");
            break;
        case 9:
            nombre = "Infernal Demon";
            habilidad = getDescription("infernal_demon");
            break;
        case 10:
            nombre = "Defender";
            habilidad = getDescription("defender");
            break;
        case 11:
            nombre = "Cursed One";
            habilidad = getDescription("cursed_one");
            break;
        case 12:
            nombre = "Little Prince";
            habilidad = getDescription("little_prince");
            break;
        case 13:
            nombre = "Monk";
            habilidad = getDescription("monk");
            break;
        case 14:
            nombre = "Death";
            habilidad = getDescription("death");
            break;
        default:
            break;
		}
        //IMG ENEMIGO
        pAux = Vector2D{ 500,470 };
        sAux = Vector2D{ 100,100 };
        bS->addImage(pAux, sAux + Vector2D{ 50,50 }, 0.0, gameTextures::large_box, _grp_HUD_FOREGROUND);
        bS->addImage(pAux, sAux, 0.0, Texturas[i], _grp_HUD_FOREGROUND);

        // NOMBRE
        pAux = Vector2D{ 700,420 };
        sAux = Vector2D{ 210,70 };
        SDL_Color NombreColor = { 255, 255, 255, 255 };
        bS->addText(nombre, NombreColor, pAux, sAux);

        //TEXTO
        Vector2D auxPos = { 0, body_separation + (bPos.getY() - bSize.getY() / 2) + font_size_body.getY() };
        for (int i = 0; i < habilidad.size(); ++i) {
            Vector2D namePos = Vector2D(bPos.getX() - bSize.getX() / 2 + habilidad[i].size() * font_size_body.getX() / 2 + right_separation, between_line_offset * i) + auxPos;
            Vector2D nameScale = { font_size_body.getX() * habilidad[i].size(), font_size_body.getY() };
            bS->addText(habilidad[i], body_c,namePos,nameScale);

            if (i == habilidad.size() - 1) {
                stats_initial_pos_y = namePos.getY() + stats_separation;
            }
        }

}