#include "TileMap.h"
#include "Player.h"

#include "PathTile.h"
#include "WallTile.h"

using namespace std;

TileMap::TileMap(const int8 mapTab[][TILEMAP_SIZE_X], float scale):
m_map(LOADED_ZONE_W),
m_pos{0,0},
m_tileSprites{
	*(new CREATE_SPRITE(16,16,PathTile,5,1)),
	*(new CREATE_SPRITE(16,16,WallTile,5,1))
},
m_scale(scale)
{
	for (unsigned int i = 0 ; i < TILEMAP_SIZE_X ; ++i)
		for (unsigned int j = 0 ; j < TILEMAP_SIZE_Y ; ++j)
			m_intMap[i][j] = mapTab[j][i];
	generateMap();
}
TileMap::~TileMap() {}

void TileMap::update()
{
	if(m_centerMetaTile->getType()==METATILE::WALL)
	{
		m_map.clear();
		generateMap();
	}
	//center player pos
	int playPos[2]{
		int(m_player->getPos(X)+m_player->getSize(W)/2),
		int(m_player->getPos(Y)+m_player->getSize(H)/2)};
	for (unsigned int i = 0; i < m_map.size(); ++i)
		for (unsigned int j = 0 ; j < m_map[i].size() ; ++j)
			m_map[i][j].update(playPos[X],playPos[Y]);
}

void TileMap::display()
{
	for (unsigned int i = 0; i < m_map.size(); ++i)
		for (unsigned int j = 0 ; j < m_map[i].size() ; ++j)
			m_map[i][j].display();
}

void TileMap::displayHitboxs()
{
	for (unsigned int i = 0; i < m_map.size(); ++i)
		for (unsigned int j = 0 ; j < m_map[i].size() ; ++j)
			m_map[i][j].displayHitbox();
}

bool TileMap::collide(Entity& entity)
{
	for (unsigned int i = 0; i < m_map.size(); ++i)
		for (unsigned int j = 0 ; j < m_map[i].size() ; ++j)
			if(m_map[i][j].getType() == METATILE::TYPE::WALL &&
			   m_map[i][j].collide(entity))
				return true;
	return false;
}

deque<rect> TileMap::getCollisions(Entity& entity)
{
	deque<rect> collisions;
	for (unsigned int i = 0; i < m_map.size(); ++i)
		for (unsigned int j = 0 ; j < m_map[i].size() ; ++j)
			if(m_map[i][j].getType() == METATILE::TYPE::WALL &&
			   m_map[i][j].collide(entity))
				collisions.push_back(m_map[i][j].getHitbox().getRect());
	return collisions;
}

void TileMap::setCenterMetaTile(MetaTile* centerMetaTile)
{
	int x = centerMetaTile->getCoo(X);
	int y = centerMetaTile->getCoo(Y);
	for(MetaTile middle = m_map.middle().middle();
		x != m_map.middle().middle().getCoo(X) or
		y != m_map.middle().middle().getCoo(Y);
		middle = m_map.middle().middle())
	{
		if(x > middle.getCoo(X))
			loadRight();
		else if(x < middle.getCoo(X))
			loadLeft();
		if(y > middle.getCoo(Y))
			loadBottom();
		else if(y < middle.getCoo(Y))
			loadTop();
	}

	m_centerMetaTile = centerMetaTile;

	calculateConnections();
}

MetaTile* TileMap::getCenterMetaTile()
{
	return m_centerMetaTile;
}











void TileMap::setPos(int x, int y)
{
	m_pos[X] = x;
	m_pos[Y] = y;
	for (unsigned int i = 0; i < m_map.size(); ++i)
		for (unsigned int j = 0 ; j < m_map[i].size() ; ++j)
			m_map[i][j].setDisplayPos(m_pos[X]+m_map[i][j].getCoo(X)*METATILE::SIZE, m_pos[Y]+m_map[i][j].getCoo(Y)*METATILE::SIZE);
}

void TileMap::generateMap()
{
	int centerX = (m_player->getPos(X) + m_player->getSize(W)/2)/(METATILE::SIZE*m_scale);
	int centerY = (m_player->getPos(Y) + m_player->getSize(H)/2)/(METATILE::SIZE*m_scale);
	int tileType = METATILE::TYPE::WALL;

	for (int i = 0; i < LOADED_ZONE_W; ++i)
	{
		m_map.push_back(CircularDeque<MetaTile>(LOADED_ZONE_H));
		for (int j = 0; j < LOADED_ZONE_H; ++j)
		{
			int cooX = centerX + i - LOADED_ZONE_W/2;
			int cooY = centerY + j - LOADED_ZONE_H/2;
			tileType = METATILE::TYPE::WALL;
			if (cooX < TILEMAP_SIZE_X and cooX >= 0 and
				cooY < TILEMAP_SIZE_Y and cooY >= 0)
				tileType = m_intMap[cooX][cooY];
			MetaTile metaTile(this,
							  &m_tileSprites[tileType],
							  tileType,
							  cooX*METATILE::SIZE*m_scale,
							  cooY*METATILE::SIZE*m_scale,
							  cooX,cooY,
							  m_scale);
			m_map.back().push_back(metaTile);
		}
	}
	calculateConnections();
}

void TileMap::calculateConnections()
{
	int x = TILEMAP_SIZE_X, y = TILEMAP_SIZE_Y;
	for (unsigned int i = 0; i < m_map.size(); ++i)
	{
		for (unsigned int j = 0; j < m_map[0].size(); ++j)
		{
			u8 type = m_map[i][j].getType();
			int cX = m_map[i][j].getCoo(X);
			int cY = m_map[i][j].getCoo(Y);
			u8 connections = 
			((cY>0    && type == m_intMap[cX][cY-1])? TILE::TOP    :0)|
			((cY<y-1 && type == m_intMap[cX][cY+1])? TILE::BOTTOM :0)|
			((cX>0   && type == m_intMap[cX-1][cY])? TILE::LEFT   :0)|
			((cX<x-1 && type == m_intMap[cX+1][cY])? TILE::RIGHT  :0)|
			((cY>0   && cX>0   && type == m_intMap[cX-1][cY-1])? TILE::TOP_LEFT    :0)|
			((cY>0   && cX<x-1 && type == m_intMap[cX+1][cY-1])? TILE::TOP_RIGHT   :0)|
			((cY<y-1 && cX>0   && type == m_intMap[cX-1][cY+1])? TILE::BOTTOM_LEFT :0)|
			((cY<y-1 && cX<x-1 && type == m_intMap[cX+1][cY+1])? TILE::BOTTOM_RIGHT:0)|
			((cY<=0 && type == METATILE::TYPE::WALL)?
				(TILE::TOP|TILE::TOP_LEFT|TILE::TOP_RIGHT):0)|
			((cY>=y-1 && type == METATILE::TYPE::WALL)?
				(TILE::BOTTOM|TILE::BOTTOM_LEFT|TILE::BOTTOM_RIGHT):0)|
			((cX<=0 && type == METATILE::TYPE::WALL)?
				(TILE::LEFT|TILE::TOP_LEFT|TILE::BOTTOM_LEFT):0)|
			((cX>=x-1 && type == METATILE::TYPE::WALL)?
				(TILE::RIGHT|TILE::TOP_RIGHT|TILE::BOTTOM_RIGHT):0)|
			((cY<0 && type == METATILE::TYPE::WALL)?
				(TILE::LEFT|TILE::RIGHT):0)|
			((cY>y-1 && type == METATILE::TYPE::WALL)?
				(TILE::LEFT|TILE::RIGHT):0)|
			((cX<0 && type == METATILE::TYPE::WALL)?
				(TILE::TOP|TILE::BOTTOM):0)|
			((cX>x-1 && type == METATILE::TYPE::WALL)?
				(TILE::TOP|TILE::BOTTOM):0)|unsigned 
			((cY<-1)?0b11111111:0)|
			((cY>y)?0b11111111:0)|
			((cX<-1)?0b11111111:0)|
			((cX>x)?0b11111111:0)
			;
			m_map[i][j].setConnections(connections);
		}
	}
}

void TileMap::loadRight()
{
	CircularDeque<MetaTile> previousBack = m_map.back();
	m_map.push_back(CircularDeque<MetaTile>(LOADED_ZONE_H));
	int tileType = METATILE::TYPE::WALL;
	for (unsigned int i = 0; i < previousBack.size(); ++i)
	{
		short cooX = previousBack[i].getCoo(X)+1;
		short cooY = previousBack[i].getCoo(Y);
		tileType = METATILE::TYPE::WALL;
		if (cooX < TILEMAP_SIZE_X and cooX >= 0 and
			cooY < TILEMAP_SIZE_Y and cooY >= 0)
			tileType = m_intMap[cooX][cooY];
		m_map.back().push_back(MetaTile(this,
							  		&m_tileSprites[tileType],
									tileType,
									cooX*METATILE::SIZE*m_scale,
									cooY*METATILE::SIZE*m_scale,
									cooX,cooY,
									m_scale));
		m_map.back().back().setDisplayPos(m_pos[X]+cooX*METATILE::SIZE*m_scale, m_pos[Y]+cooY*METATILE::SIZE*m_scale);
	}
}
void TileMap::loadLeft()
{
	CircularDeque<MetaTile> previousFront = m_map.front();
	m_map.push_front(CircularDeque<MetaTile>(LOADED_ZONE_H));
	int tileType = METATILE::TYPE::WALL;
	for (unsigned int i = 0; i < previousFront.size(); ++i)
	{
		short cooX = previousFront[i].getCoo(X)-1;
		short cooY = previousFront[i].getCoo(Y);
		tileType = METATILE::TYPE::WALL;
		if (cooX < TILEMAP_SIZE_X and cooX >= 0 and
			cooY < TILEMAP_SIZE_Y and cooY >= 0)
			tileType = m_intMap[cooX][cooY];
		m_map.front().push_back(MetaTile(this,
							  		&m_tileSprites[tileType],
									tileType,
									cooX*METATILE::SIZE*m_scale,
									cooY*METATILE::SIZE*m_scale,
									cooX,cooY,
									m_scale));
		m_map.front().back().setDisplayPos(m_pos[X]+cooX*METATILE::SIZE*m_scale, m_pos[Y]+cooY*METATILE::SIZE*m_scale);
	}
}
void TileMap::loadBottom()
{
	int tileType = METATILE::TYPE::WALL;
	for (unsigned int i = 0; i < m_map.size(); ++i)
	{
		short cooX = m_map[i].back().getCoo(X);
		short cooY = m_map[i].back().getCoo(Y)+1;
		tileType = METATILE::TYPE::WALL;
		if (cooX < TILEMAP_SIZE_X and cooX >= 0 and
			cooY < TILEMAP_SIZE_Y and cooY >= 0)
			tileType = m_intMap[cooX][cooY];
		m_map[i].push_back(MetaTile(this,
							  		&m_tileSprites[tileType],
									tileType,
									cooX*METATILE::SIZE*m_scale,
									cooY*METATILE::SIZE*m_scale,
									cooX,cooY,
									m_scale));
		m_map[i].back().setDisplayPos(m_pos[X]+cooX*METATILE::SIZE*m_scale, m_pos[Y]+cooY*METATILE::SIZE*m_scale);
	}
}
void TileMap::loadTop()
{
	int tileType = METATILE::TYPE::WALL;
	for (unsigned int i = 0; i < m_map.size(); ++i)
	{
		short cooX = m_map[i].front().getCoo(X);
		short cooY = m_map[i].front().getCoo(Y)-1;
		tileType = METATILE::TYPE::WALL;
		if (cooX < TILEMAP_SIZE_X and cooX >= 0 and
			cooY < TILEMAP_SIZE_Y and cooY >= 0)
			tileType = m_intMap[cooX][cooY];
		m_map[i].push_front(MetaTile(this,
							  		&m_tileSprites[tileType],
									tileType,
									cooX*METATILE::SIZE*m_scale,
									cooY*METATILE::SIZE*m_scale,
									cooX,cooY,
									m_scale));
		m_map[i].front().setDisplayPos(m_pos[X]+cooX*METATILE::SIZE*m_scale, m_pos[Y]+cooY*METATILE::SIZE*m_scale);
	}
}
