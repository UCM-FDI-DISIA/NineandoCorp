#include "SliderComponent.h"
#include "../sdlutils/InputHandler.h"
#include "../ecs/Manager.h"
#include "../systems/RenderSystem.h"

SliderComponent::SliderComponent(RenderSystem& renderSystem, int x, int y, int width, int height)
    : value(0), isDragging(false) {}

SliderComponent::~SliderComponent() {}

void SliderComponent::handleEvent() {
    //Posicion actual del mouse
    Vector2D pos = { (float)ih().getMousePos().first, (float)ih().getMousePos().second };

    if (ih().mouseButtonEvent()) {  // Añadir condición de posición y dragging

        if (ih().getMouseButtonState(InputHandler::MOUSEBUTTON::LEFT) == 1) {

            // Logica de Mover el knob
        }

    }
}

void SliderComponent::updateKnobPosition() {
    int auxKnobX = sliderX + (sliderX - knobX) * value / 100;
    knobX = auxKnobX;
}

void SliderComponent::setValue(int value) {
    this->value = value;
    updateKnobPosition();
}

int SliderComponent::getValue() const {
    return value;
}

