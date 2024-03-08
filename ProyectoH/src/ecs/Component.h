#pragma once
#ifndef COMPONENT_H_
#define COMPONENT_H_

#include "ecs.h"

struct Component 
{
protected:
	Entity* ent_;
	Manager* mngr_;
public: 
	Component() {}  
	virtual ~Component() {}
	/// <summary>
	/// Establece referencia al manager y la entidad a la que pertenece el componente
	/// </summary>
	/// <param name="ent">entidad a la que pertenece</param>
	/// <param name="mngr">manager de la escena</param>
	inline void setContext(Entity* ent, Manager* mngr) {
		ent_ = ent;
		mngr_ = mngr;
	}
	/// <summary>
	/// Inicializa el componente despuese de crearlo y establecer el manager
	/// </summary>
	virtual void initComponent() { }
};
#endif