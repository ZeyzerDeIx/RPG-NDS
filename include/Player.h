#ifndef PLAYER_H
#define PLAYER_H

	#include "Character.h"

	class Player: public Character
	{
		public:
			Player(TileMap* tileMap, Sprite* sprite, float w, float h);
			void display();
			void setSprint(bool sprint);
		private:
			bool m_sprint;
	};

#endif//PLAYER_H