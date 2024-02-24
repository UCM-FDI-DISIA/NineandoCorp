#include "SliderComponent.h"

SliderComponent::SliderComponent(RenderSystem& renderSystem, int x, int y, int width, int height)
    : renderSystem(renderSystem), value(0), isDragging(false) {
    sliderRect = { x, y, width, height };
    knobRect = { x, y, height, height }; // Knob is initially at the left end
}

SliderComponent::~SliderComponent() {}

void SliderComponent::handleEvent() {
    InputHandler& inputHandler = InputHandler::instance();

    if (inputHandler.isButtonDown(SDL_BUTTON_LEFT) && !isDragging) {
        int mouseX = inputHandler.mouseX();
        int mouseY = inputHandler.mouseY();
        if (mouseX >= knobRect.x && mouseX <= knobRect.x + knobRect.w &&
            mouseY >= knobRect.y && mouseY <= knobRect.y + knobRect.h) {
            isDragging = true;
        }
    }
    else if (inputHandler.isButtonUp(SDL_BUTTON_LEFT) && isDragging) {
        isDragging = false;
    }
    else if (isDragging) {
        int mouseX = inputHandler.mouseX();
        int knobX = mouseX - knobRect.w / 2;
        if (knobX < sliderRect.x) {
            knobX = sliderRect.x;
        }
        else if (knobX > sliderRect.x + sliderRect.w - knobRect.w) {
            knobX = sliderRect.x + sliderRect.w - knobRect.w;
        }
        knobRect.x = knobX;
        updateKnobPosition();
    }
}

void SliderComponent::render() {
    // Render slider bar
    renderSystem.imageRectRender(sliderRect, "slider_texture"); // Reemplaza "slider_texture" con el nombre de la textura para la barra del slider

    // Render knob
    renderSystem.imageRectRender(knobRect, "knob_texture"); // Reemplaza "knob_texture" con el nombre de la textura para el knob
}

void SliderComponent::setValue(int value) {
    this->value = value;
    updateKnobPosition();
}

int SliderComponent::getValue() const {
    return value;
}

void SliderComponent::updateKnobPosition() {
    // Update knob position based on current value
    int knobX = sliderRect.x +
        (sliderRect.w - knobRect.w) * value / 100; // Assuming range 0-100
    knobRect.x = knobX;
}
