#pragma once
#include "../ecs/Component.h"
#include <SDL_scancode.h>
#include "../systems/TowerSystem.h"

class Transform;
class DragAndDrop : public Component
{
public:

	static const cmpId id = cmpId::_DRAG_AND_DROP;

	DragAndDrop(twrId i);
	virtual ~DragAndDrop();

	void initComponent() override;

	/// <summary>
	/// 
	/// </summary>
	/// <param name="pos"> posicion</param>
	/// <param name="h"> pradera o montaña</param>
	void drop(const Vector2D& pos, Height h, const Vector2D& scale);

	/// <summary>
	/// habilita si el objeto esta siendo arrastrado o no
	/// </summary>
	/// <param name="b">booleano true / false </param>
	inline void enableDrag(bool b) {
		dragging_ = b;
	}
	
	/// <returns> si el objeto esta siendo arrastrado</returns>
	inline bool isDragged() { return dragging_; }

	/// <summary>
	/// Sigue al cursor y se situa en la casilla mas cercana
	/// </summary>
	void drag();

	Vector2D getPosFromTile(const Vector2D& pos);
private:
	bool dragging_;
	Transform* tr_;
	twrId tId_;
};

