#pragma once

#include "../ecs/Component.h"
#include <functional>
#include "Transform.h"
enum SliderTypes {
    general, effects, music
};
class SliderComponent : public Component {
public:
    static const cmpId id = cmpId::_SLIDER;
    SliderComponent(SliderTypes id):id_(id) {}

    virtual ~SliderComponent() {}

    void initComponent() override;

    float getValue() const { return value_; }

    void setValue(float value) { value_ = value; }

    void setBounds() {
        min_ = tr_->getX() - 100.0f;
        max_ = tr_->getX() + 150.0f;;
    }
    void setRelativeBounds(float newRelativeMax_) {
        relativeMax_ = newRelativeMax_;
    }
    float getRelativeMax() const { return relativeMax_; };
    void setOnChangeCallback(std::function<void(float)> onChange) {
        onChange_ = onChange;
    }
    float getMax() const { return max_; }
    float getMin() const { return min_; }

    bool isPressed(const Vector2D& mousePos);

    bool getDragging() const { return dragging_; };
    void setDragging(bool dr) { dragging_ = dr; };

    SliderTypes getSlider() const { return id_; };
private:
    float value_ = 0.0f;
    float min_ = 0.0f;
    float max_ = 1.0f;
    float relativeMax_ = 1.0f;
    std::function<void(float)> onChange_;
    SliderTypes id_;

    //Transform del boton del slider
    Transform* tr_;
    bool dragging_ = false;
};


