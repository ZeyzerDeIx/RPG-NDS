#ifndef PLAYER_H
#define PLAYER_H

	#include "Character.h"

	class Player: public Character
	{
		public:
			Player(TileMap* tileMap);
			~Player();
			void display();
			//enable or disable sprintMode
			void setSprint(bool sprint);
		private:
			bool m_sprint;
	};

#endif//PLAYER_H