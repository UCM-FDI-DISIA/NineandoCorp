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
	void drop(const Vector2D& pos, Height h);

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
	
	/// <param name="pos">posicion del mouse</param>
	/// <returns>posicion relativa de la casilla correspondiente</returns>
	Vector2D getPosFromTile(const Vector2D& pos);

	
	/// <param name="initPos">posicion relativa de la casilla</param>
	/// <returns>posicion ajustada a la escala 
	/// para que la imagen ocupe en su totalidad la casilla</returns>
	Vector2D adjustPosToTile(const Vector2D& initPos);
	

	/// <param name="tId"></param>
	/// <returns>la escala correspondiente al tipo de torre</returns>
	Vector2D setScaleToIcon(twrId tId);

private:

	bool dragging_;
	Transform* tr_;
	twrId tId_;
};

