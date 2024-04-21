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
        min_ = tr_->getX() - min_;
        max_ = tr_->getX() + max_;;
    }
    void setRelativeBounds(float newRelativeMax_, float newRelativeMin_) {
        relativeMax_ = newRelativeMax_;
        relativeMin_ = newRelativeMin_;
    }
    float getRelativeMax() const { return relativeMax_; };
    
    float getMax() const { return max_; }
    float getMin() const { return min_; }
    void setMax(float newMax) { max_ = newMax; }
    void setMin(float newMin) { min_ = newMin; }

    bool isPressed(const Vector2D& mousePos);

    bool getDragging() const { return dragging_; };
    void setDragging(bool dr) { dragging_ = dr; };

    SliderTypes getSlider() const { return id_; };
private:
    float value_ = 0.0f;
    float min_ = 100.0f;
    float max_ = 150.0f;
    float relativeMax_ = 1.0f;
    float relativeMin_ = 1.0f;
    std::function<void(float)> onChange_;
    SliderTypes id_;

    //Transform del boton del slider
    Transform* tr_;
    bool dragging_ = false;
};


