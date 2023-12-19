#ifndef HANDLER_H
#define HANDLER_H

	#include "Player.h"
	#include "TileMap.h"

	class Handler
	{
		public:
			Handler(Player* player, TileMap* tileMap);
			~Handler();
			void handleInputs();
		private:
			Player* m_player;
			TileMap* m_tileMap;
	};

#endif//HANDLER_H