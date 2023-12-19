#include "MetaTile.h"
#include "TileMap.h"

using namespace METATILE;


MetaTile::MetaTile(): m_hitbox(0,0,0,0) {}
MetaTile::MetaTile(TileMap* tileMap, Sprite* sprite, u8 type, int posX, int posY, short cooX, short cooY):
	m_tileMap(tileMap),
	m_type(type),
	m_coo{cooX, cooY},
	m_hitbox(posX,posY,SIZE+4,SIZE)
{
	for (int i = 0; i < 4; ++i)
		m_tiles[i] = Tile(sprite, i, posX+TILE::SIZE*(i&1), posY+TILE::SIZE*(i>1));
	m_connections = 0b0000'0000;
	m_isLoaded = false;
}
MetaTile::~MetaTile() {}


/*void MetaTile::setPos(int posX, int posY)
{
	m_hitbox.getRect().x = posX;
	m_hitbox.getRect().y = posY;
}*/
void MetaTile::setDisplayPos(int posX, int posY)
{
	for (int i = 0; i < 4; ++i)
		m_tiles[i].setDisplayPos(posX+TILE::SIZE*(i&1), posY+TILE::SIZE*(i>1));
}

int MetaTile::getDisplayPos(bool xOrY)
{
	return m_tiles[0].getDisplayPos(xOrY);
}

void MetaTile::setConnections(u8 connections)
{
	m_connections = connections;
	u8 topLeftCorner = bitCheck(connections, TILE::TOP, 0) |
					   bitCheck(connections, TILE::LEFT, 1) |
					   bitCheck(connections, TILE::TOP_LEFT, 2);
	m_tiles[TOP_LEFT].setConnections(cornerFilter(topLeftCorner));

	u8 topRightCorner = bitCheck(connections, TILE::TOP, 0) |
						bitCheck(connections, TILE::RIGHT, 1) |
						bitCheck(connections, TILE::TOP_RIGHT, 2);
	m_tiles[TOP_RIGHT].setConnections(cornerFilter(topRightCorner));

	u8 bottomLeftCorner = bitCheck(connections, TILE::BOTTOM, 0) |
						  bitCheck(connections, TILE::LEFT, 1) |
						  bitCheck(connections, TILE::BOTTOM_LEFT, 2);
	m_tiles[BOTTOM_LEFT].setConnections(cornerFilter(bottomLeftCorner));

	u8 bottomRightCorner = bitCheck(connections, TILE::BOTTOM, 0) |
						   bitCheck(connections, TILE::RIGHT, 1) |
						   bitCheck(connections, TILE::BOTTOM_RIGHT, 2);
	m_tiles[BOTTOM_RIGHT].setConnections(cornerFilter(bottomRightCorner));
}

void MetaTile::display(int playerPosX, int playerPosY)
{
	m_isLoaded = true;
	for (int i = 0; i < 4; ++i)
	{
		if(m_tiles[i].isInRenderZone(playerPosX,playerPosY))
			m_tiles[i].display();
		m_isLoaded = m_isLoaded && m_tiles[i].isLoaded();
	}
}

bool MetaTile::hasSameTypeAs(MetaTile& other)
{
	return m_type == other.m_type;
}

bool MetaTile::collide(Entity& entity)
{
	return m_hitbox.collide(entity.getHitbox());
}

void MetaTile::displayHitbox()
{
	//m_hitbox.display(getDisplayPos(X), getDisplayPos(Y));
}

int MetaTile::getPos(bool xOrY)
{
	return xOrY ? m_hitbox.getRect().y : m_hitbox.getRect().x;
}

Hitbox& MetaTile::getHitbox()
{
	return m_hitbox;
}

u8 MetaTile::getType()
{
	return m_type;
}

bool MetaTile::isLoaded()
{
	return m_isLoaded;
}

void MetaTile::unload()
{
	m_isLoaded = false;
	for (int i = 0; i < 4; ++i)
		m_tiles[i].unload();
}

bool MetaTile::isInRenderZone(int playerPosX, int playerPosY)
{
	/*if(std::max(std::abs(getPos(X)),std::abs(getPos(Y))) > 10000)
		std::cout << std::endl << " " << m_coo[X] << " " << m_coo[Y];*/
	return (playerPosY<getPos(Y)?
			(getPos(Y)-playerPosY):
			(playerPosY-(getPos(Y)+m_hitbox.getRect().h))) <= FOG_DISTANCE_Y &&
		   (playerPosX<getPos(X)?
			(getPos(X)-playerPosX):
			(playerPosX-(getPos(X)+m_hitbox.getRect().w))) <= FOG_DISTANCE_X;
}

void MetaTile::forcedDisplay()
{
	for (int i = 0; i < 4; ++i)
		m_tiles[i].display();
}

void MetaTile::update(int playerPosX, int playerPosY)
{
	if(playerPosX/SIZE == m_coo[X] and playerPosY/SIZE == m_coo[Y] and
	   m_tileMap->getCenterMetaTile() != this)
		m_tileMap->setCenterMetaTile(this);
}

short MetaTile::getCoo(bool xOrY)
{
	return m_coo[xOrY];
}









u8 MetaTile::bitCheck(u8 source, u8 filter, int offset)
{
	return ((source & filter) == filter) << offset;
}

u8 MetaTile::cornerFilter(u8 source)
{
	if(source == 0b0000'0111) return 0b0000'0100;
	return source & 0b0000'0011;
}

/*
m_tiles[0] = Tile(sprite, 0, posX, posY);
m_tiles[1] = Tile(sprite, 1, posX+TILE::SIZE, posY);
m_tiles[2] = Tile(sprite, 2, posX, posY+TILE::SIZE);
m_tiles[3] = Tile(sprite, 3, posX+TILE::SIZE, posY+TILE::SIZE);
->
for (int i = 0; i < 4; ++i)
	m_tiles[i] = Tile(sprite, i, posX+TILE::SIZE*(i%2 == 1), posY+TILE::SIZE*(i>1));
*/