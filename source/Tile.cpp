#include "Tile.h"
#include "TileMap.h"
//#include "Debugger.h"

using namespace TILE;
using namespace std;

Tile::Tile() {}
Tile::Tile(Sprite* sprite, int corner, int posX, int posY):m_sprite(sprite), m_corner(corner)
{
	m_displayPos[X] = m_pos[X] = posX;
	m_displayPos[Y] = m_pos[Y] = posY;
	m_connections = 0;
	m_isLoaded = false;
}
Tile::~Tile() {}


void Tile::display()
{
	m_sprite->manualDisplay(m_displayPos[X], m_displayPos[Y], m_connections, 0 ,m_corner&1, m_corner>1);
	m_isLoaded = true;
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
void Tile::setDisplayPos(int posX, int posY)
{
	m_displayPos[X] = posX, m_displayPos[Y] = posY;
}

int Tile::getDisplayPos(bool xOrY)
{
	return m_displayPos[xOrY];
}

bool Tile::isLoaded()
{
	return m_isLoaded;
}

void Tile::unload()
{
	m_isLoaded = false;
}

bool Tile::isInRenderZone(int playerPosX, int playerPosY)
{
	return ((playerPosY<m_pos[Y]?
			(m_pos[Y]-playerPosY):
			(playerPosY-(m_pos[Y]+SIZE))) <= FOG_DISTANCE_Y &&
		   (playerPosX<m_pos[X]?
			(m_pos[X]-playerPosX):
			(playerPosX-(m_pos[X]+SIZE))) <= FOG_DISTANCE_X);
}