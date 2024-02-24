#pragma once

#include "../ecs/Component.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "../systems/RenderSystem.h"

class SliderComponent : public Component {
private:
    int sliderRect;
    int knobRect;
    int value;
    bool isDragging;

    void updateKnobPosition();

public:
    SliderComponent(RenderSystem& renderSystem, int x, int y, int width, int height);
    ~SliderComponent();

    void handleEvent();
    void updateKnobPosition();

    void setValue(int value);
    int getValue() const;
};

