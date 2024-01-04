#ifndef ENTITY_H
#define ENTITY_H

	#include "constants.h"
	#include "Sprite.h"
	#include "Hitbox.h"

	class Entity
	{
		public:
			Entity(Sprite* sprite, float w, float h, float posX = 0.f, float posY = 0.f);
			~Entity();
			void update();
			void display();
			void displayHitbox();
			void move(float x, float y);
			void setPos(float x, float y);
			float getPos(bool xOrY);
			float getSize(bool wOrH);
			Hitbox& getHitbox();
		protected:
			Sprite* m_sprite;
			float m_pos[2];
			short m_displayPos[2];
			float m_size[2];
			float m_speed;
			Hitbox m_hitbox;

	};

#endif//ENTITY_H