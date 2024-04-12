#pragma once
#include "../ecs/Component.h"
#include <SDL_scancode.h>
#include "../systems/TowerSystem.h"

class Transform;
class DragAndDrop : public Component
{
public:

	static const cmpId id = cmpId::_DRAG_AND_DROP;

	DragAndDrop(twrId i, int cost, Height h);
	virtual ~DragAndDrop();

	void initComponent() override;

	/// <summary>
	/// 
	/// </summary>
	/// <param name="pos"> posicion</param>
	/// <param name="h"> pradera o montaña</param>
	void drop(const Vector2D& pos, Height h, Cell* cell);

	/// <summary>
	/// habilita si el objeto esta siendo arrastrado o no
	/// </summary>
	/// <param name="b">booleano true / false </param>
	inline void enableDrag(bool b) {
		dragging_ = b;
	}
	
	/// <returns> si el objeto esta siendo arrastrado</returns>
	inline bool isDragged() const { return dragging_; }

	/// <summary>
	/// Sigue al cursor y se situa en la casilla mas cercana
	/// </summary>
	void drag(const Vector2D& tilePos);

	
	/// <param name="initPos">posicion relativa de la casilla</param>
	/// <returns>posicion ajustada a la escala 
	/// para que la imagen ocupe en su totalidad la casilla</returns>
	Vector2D adjustPosToTile(const Vector2D& initPos);
	

	/// <param name="tId"></param>
	/// <returns>la escala correspondiente al tipo de torre</returns>
	Vector2D setScaleToIcon(twrId tId);

	inline twrId getTowerId() const {
		return tId_;
	}

	inline bool canDrop() const { return canDrop_; }

	inline void enableDrop(Cell* c) { 
		if (c->isFree) {
			if (c->id == TILE_LOW && height_ == LOW) {
				canDrop_ = true;
			}
			else if (c->id == TILE_HIGH && height_ == HIGH) {
				canDrop_ = true;
			}
			else if (c->id == TILE_PATH && height_ == PATH) {
				canDrop_ = true;
			}
			else if ((c->id == TILE_HIGH || c->id == TILE_LOW) && height_ == BOTH) {
				canDrop_ = true;
			}
			else canDrop_ = false;
		}
		else canDrop_ = false;
	}

	inline int getCost() const { return cost; }

private:

	bool dragging_;
	bool canDrop_;
	Transform* tr_;
	Height height_;
	twrId tId_;
	int cost;
};

