#include "TextComponent.h"

void TextComponent::changeText(std::string newText) {
	text_ = newText;
	update();
}

void TextComponent::update() {
	if (textTexture_ != nullptr) {
		delete textTexture_;
		textTexture_ = nullptr;
	}

	textTexture_ = new Texture(sdlutils().renderer(),
		text_,
		sdlutils().fonts().at(font_),
		build_sdlcolor(color_));
}