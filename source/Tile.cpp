#include "Tile.h"
#include "TileMap.h"
//#include "Debugger.h"

using namespace TILE;
using namespace std;

Tile::Tile() {}

Tile::Tile(Sprite* sprite, int corner, int posX, int posY, float scale):
	m_sprite(sprite),
	m_pos{posX,posY},
	m_displayPos{posX,posY},
	m_connections(0),
	m_corner(corner),
	m_scale(scale)
{}

Tile::~Tile() {}


void Tile::display()
{
	m_sprite->manualDisplay(m_displayPos[X], m_displayPos[Y], m_connections, 0, m_scale, m_corner&1, m_corner>1);
}

void Tile::setConnections(u8 connections)
{
	m_connections = connections;
}

int Tile::getPos(bool xOrY)
{
	return m_pos[xOrY];
}

void Tile::setPos(int posX, int posY)
{
	m_pos[X] = posX, m_pos[Y] = posY;
}
void Tile::setDisplayPos(short posX, short posY)
{
	m_displayPos[X] = posX, m_displayPos[Y] = posY;
}

short Tile::getDisplayPos(bool xOrY)
{
	return m_displayPos[xOrY];
}