#ifndef TILE_H
#define TILE_H

	#include "constants.h"
	#include "Sprite.h"
	namespace TILE
	{
		enum{ TOP          = 0b0000'0001,
			  BOTTOM       = 0b0000'0010,
			  LEFT         = 0b0000'0100,
			  RIGHT        = 0b0000'1000,
			  TOP_LEFT     = 0b0001'0000,
			  TOP_RIGHT    = 0b0010'0000,
			  BOTTOM_LEFT  = 0b0100'0000,
			  BOTTOM_RIGHT = 0b1000'0000
			};
		const int SIZE = 16;
		const int STATE_NUM = 4;
		const int FRAME_NUM = 5;
	}
	
	class Tile
	{
		public:
			Tile();
			Tile(Sprite* sprite, int corner, int posX, int posY, float scale=1.f);
			~Tile();
			void display();
			void setConnections(u8 connections);
			int getPos(bool xOrY);
			void setPos(int posX, int posY);
			void setDisplayPos(int posX, int posY);
			int getDisplayPos(bool xOrY);
			bool isLoaded();
			//void load();
			void unload();
			bool isInRenderZone(int playerPosX, int playerPosY);
		private:
			Sprite* m_sprite;
			int m_pos[2];
			int m_displayPos[2];
			u8 m_connections;
			u8 m_corner;
			float m_scale;
			bool m_isLoaded;
	};

#endif//TILE_H