#ifndef METATILE_H
#define METATILE_H

	#include "Tile.h"
	#include "Entity.h"

	class TileMap;

	namespace METATILE
	{
		enum{TOP_LEFT, TOP_RIGHT, BOTTOM_LEFT, BOTTOM_RIGHT};
		const int SIZE = TILE::SIZE * 2;
		enum TYPE{PATH,WALL,NUMBER};
	}
	
	class MetaTile
	{
		public:
			MetaTile();
			MetaTile(TileMap* tileMap, Sprite* sprite, u8 type, int posX, int posY, short cooX, short cooY);
			~MetaTile();
			//void setPos(int posX, int posY);
			void setDisplayPos(int posX, int posY);
			int getDisplayPos(bool xOrY);
			void setConnections(u8 connections);
			void display(int playerPosX, int playerPosY);
			bool hasSameTypeAs(MetaTile& other);
			bool collide(Entity& entity);
			void displayHitbox();
			int getPos(bool xOrY);
			Hitbox& getHitbox();
			u8 getType();
			bool isLoaded();
			void unload();
			bool isInRenderZone(int playerPosX, int playerPosY);
			void forcedDisplay();
			void update(int playerPosX, int playerPosY);
			short getCoo(bool xOrY);
		private:
			TileMap* m_tileMap;
			Tile m_tiles[4];
			u8 m_connections;
			u8 m_type;
			short m_coo[2];
			Hitbox m_hitbox;
			bool m_isLoaded;

			u8 bitCheck(u8 source, u8 filter, int offset);
			u8 cornerFilter(u8 source);

			friend class TileMap;
	};

#endif//METATILE_H