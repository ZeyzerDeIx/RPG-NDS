#ifndef TILEMAP_H
#define TILEMAP_H

	#include "constants.h"
	#include "MetaTile.h"
	#include <deque>
	#include "CircularDeque.h"

	#define TILEMAP_SIZE_X 32
	#define TILEMAP_SIZE_Y 32
	#define FOG_DISTANCE_X 150
	#define FOG_DISTANCE_Y 120
	#define LOADED_ZONE_W 11
	#define LOADED_ZONE_H 9

	class Player;
	class Camera;
	class handler;

	class TileMap
	{
		public:
			TileMap(int8 mapTab[][TILEMAP_SIZE_X]);
			~TileMap();

			void update();
			void display();
			void displayHitboxs();
			bool collide(Entity& entity);
			std::deque<rect> getCollisions(Entity& entity);
			void reload();
			void loadAll(); //for debug purposes
			void loadZone(float x, float y);
			void setCenterMetaTile(MetaTile* centerMetaTile);
			MetaTile* getCenterMetaTile();
		private:
			CircularDeque<CircularDeque<MetaTile>> m_map;
			int8 m_intMap[TILEMAP_SIZE_X][TILEMAP_SIZE_Y];
			int m_pos[2];
			Player* m_player;
			MetaTile* m_centerMetaTile;
			Sprite m_tileSprites[METATILE::TYPE::NUMBER];

			void setPos(int x, int y);
			void generateMap();
			void calculateConnections();
			void loadRight();
			void loadLeft();
			void loadBottom();
			void loadTop();

			friend class Player;
			friend class Camera;
			friend class Handler;
	};

#endif//TILEMAP_H