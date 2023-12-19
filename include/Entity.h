#ifndef ENTITY_H
#define ENTITY_H

	#include "constants.h"
	#include "Sprite.h"
	#include "Hitbox.h"

	class Entity
	{
		public:
			Entity(Sprite* sprite, float w, float h);
			~Entity();
			void update();
			void display();
			//void displayHitbox();
			void move(float x, float y);
			void setPos(float x, float y);
			void setZoomed(bool zoomed = true);
			float getPos(bool xOrY);
			float getSize(bool wOrH);
			Hitbox& getHitbox();
		protected:
			Sprite* m_sprite;
			float m_pos[2];
			float m_size[2];
			float m_speed;
			Hitbox m_hitbox;
			bool m_zoomed;

	};

#endif//ENTITY_H