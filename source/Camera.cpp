#include "Camera.h"
#include "Player.h"

Camera::Camera(TileMap* tileMap):m_tileMap(tileMap) {}

Camera::~Camera() {}


void Camera::followPlayer()
{
	float offset[2]
	{
		-m_tileMap->m_player->getPos(X) + SCREEN_RESOLUTION_X/2.f - m_tileMap->m_player->getSize(W)/2,
		-m_tileMap->m_player->getPos(Y) + SCREEN_RESOLUTION_Y/2.f - m_tileMap->m_player->getSize(H)/2
	};
	for (unsigned int i = 0; i < m_tileMap->m_map.size(); ++i)
		for (unsigned int j = 0 ; j < m_tileMap->m_map[i].size() ; ++j)
			m_tileMap->m_map[i][j].setDisplayPos(
				m_tileMap->m_map[i][j].getPos(X) + offset[X],
				m_tileMap->m_map[i][j].getPos(Y) + offset[Y]);
}