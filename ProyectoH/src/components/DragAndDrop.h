#pragma once
#include "../ecs/Component.h"
#include <SDL_scancode.h>

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

	/// <summary>
	/// habilita si el objeto esta siendo arrastrado o no
	/// </summary>
	/// <param name="b">booleano true / false </param>
	inline void enableDrag(bool b) {
		dragging_ = b;
	}
	
	/// <returns> si el objeto esta siendo arrastrado</returns>
	inline bool isDragged() { return dragging_; }

	void drag();
private:
	bool dragging_;
	Transform* tr_;
};

