#pragma once
#include "../ecs/Component.h"

class TextComponent : public Component
{
public:
	static const cmpId id = cmpId::_TEXT;

	TextComponent(std::string text, const SDL_Color& color = {255, 255, 255, 255}, std::string font = "ARIAL_ROUNDED") : textTexture_(nullptr), text_(text), font_(font), color_(color) , isActive(true){ update(); };

	~TextComponent() { 
		delete textTexture_;
		textTexture_ = nullptr;
	};

	/// <summary>
	/// Establece un nuevo texto a renderizar.
	/// </summary>
	/// <param name="newText">Texto nuevo a renderizar</param>
	void setText(std::string newText) { text_ = newText; };

	/// <summary>
	/// Establece un nuevo texto a renderizar y actualiza la textura.
	/// </summary>
	/// <param name="newText">Texto nuevo a renderizar</param>
	void changeText(std::string newText);

	/// <summary>
	/// Devuelve la textura con el texto
	/// </summary>
	/// <returns>Puntero con la textura</returns>
	Texture* getTexture() { return textTexture_; };

	/// <summary>
	/// Devuelve el string que se esta renderizando
	/// </summary>
	/// <returns>El texto que se esta usando</returns>
	std::string getText() { return text_; };

	/// <summary>
	/// Establece la fuente del tento
	/// </summary>
	/// <param name="newFont">La id de la fuente segun el JSON</param>
	void setFont(std::string newFont) { font_ = newFont; };

	/// <summary>
	/// Devuelve la fuente que se esta usando
	/// </summary>
	/// <returns>La fuente que se esta usando</returns>
	std::string getFont() { return font_; };

	/// <summary>
	/// Establece el color del texto
	/// </summary>
	/// <param name="newColor">El color en hexaecimal</param>
	void setColor(SDL_Color newColor) { color_ = newColor; };

	/// <summary>
	/// Devuelve el color que se esta usando;
	/// </summary>
	/// <returns>El color que se esta usando</returns>
	SDL_Color getColor() { return color_; };

	/// <summary>
	/// Actualiza la textura, es necesario para que se visualizen los cambios realizados respecto a la anterior textura.
	/// </summary>
	void update();

	// Si el componente se renderiza o no
	bool isActive;
private:
	Texture* textTexture_;
	std::string text_;
	std::string font_;
	SDL_Color color_;
};

