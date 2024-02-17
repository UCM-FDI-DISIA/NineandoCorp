#pragma once
#include "../ecs/Component.h"
#include <SDL_scancode.h>

enum State { NONE };

class Transform;
class DragAndDrop : public Component
{
public:
	DragAndDrop();
	virtual ~DragAndDrop();
	void initComponent() override;

	inline void drop() {
		// Mandar un mensaje a PlaceTower
	}
private:
	Transform* tr_;
	State currState;
	// Si la torre puede ser "droppeda"
	inline bool canBeDropped() {
		return false;
		
	}


	//Mouse button
	SDL_Scancode right_;
	SDL_Scancode left_;
};

