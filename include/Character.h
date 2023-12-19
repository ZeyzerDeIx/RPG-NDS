#ifndef CHARACTER_H
#define CHARACTER_H

	#include "Entity.h"
	#include "TileMap.h"

	namespace DIRECTIONS
	{
		enum {UP,DOWN,LEFT,RIGHT};
	}

	class Character: public Entity
	{
		public:
			Character(TileMap* tileMap, Sprite* sprite, float w, float h);
			void update();
			void setDirection(int direction, bool value = true);
			void move(float x, float y); //override
		private:
			TileMap* m_tileMap;
			bool m_isWalking;
			bool m_directions[4];
			int m_lastDirection;
			void updateHitbox();
	};

#endif//CHARACTER_H