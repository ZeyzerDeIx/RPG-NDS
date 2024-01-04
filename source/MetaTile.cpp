#include "MetaTile.h"
#include "TileMap.h"

using namespace METATILE;
using namespace std;

MetaTile::MetaTile(): m_hitbox(0,0,0,0) {}
MetaTile::MetaTile(TileMap* tileMap, Sprite* sprite, u8 type, int posX, int posY, short cooX, short cooY, float scale):
	m_tileMap(tileMap),
	m_connections(0b0000'0000),
	m_type(type),
	m_coo{cooX, cooY},
	m_hitbox(posX,posY,(SIZE*scale),(SIZE*scale)),
	m_scale(scale)
{
	for (int corner = 0; corner < 4; ++corner)
		m_tiles[corner] = Tile(sprite, corner,
			posX+ (corner&1)*TILE::SIZE*m_scale,
			posY+ (corner>1)*TILE::SIZE*m_scale,
			m_scale);
}
MetaTile::~MetaTile() {}


/*void MetaTile::setPos(int posX, int posY)
{
	m_hitbox.getRect().x = posX;
	m_hitbox.getRect().y = posY;
}*/
void MetaTile::setDisplayPos(int posX, int posY)
{
	for (int corner = 0; corner < 4; ++corner)
		m_tiles[corner].setDisplayPos(
			posX+ (corner&1)*TILE::SIZE*m_scale,
			posY+ (corner>1)*TILE::SIZE*m_scale);
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

void MetaTile::display()
{
	for (int i = 0; i < 4; ++i)
		m_tiles[i].display();
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
	m_hitbox.display(getDisplayPos(X), getDisplayPos(Y));
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
void MetaTile::forcedDisplay()
{
	for (int i = 0; i < 4; ++i)
		m_tiles[i].display();
}

void MetaTile::update(int playerPosX, int playerPosY)
{
	if(playerPosX/((int)(SIZE*m_scale)) == m_coo[X] and playerPosY/((int)(SIZE*m_scale))== m_coo[Y] and
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