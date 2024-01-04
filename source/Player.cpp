#include "Player.h"

using namespace std;

Player::Player(TileMap* tileMap, Sprite* sprite, float w, float h):
Character(tileMap, sprite, w, h)

{
	tileMap->m_player = this;
	m_pos[X] = m_pos[Y] = 0;
	m_sprint = false;
	m_displayPos[X] = 256.f/2.f - m_size[W]/2.f;
	m_displayPos[Y] = 192.f/2.f - m_size[H]/2.f;
}

void Player::display()
{
	//centered in screen
	m_sprite->display(m_displayPos[X],m_displayPos[Y]);
	#ifdef DEBUG_MODE_ENABLE
	displayHitbox();
	#endif
}

void Player::setSprint(bool sprint)
{
	if((m_sprint = sprint))
	{
		m_speed = 2.8f;
		m_sprite->setAnimationSpeed(5);
	}
	else
	{
		m_speed = 1.6f;
		m_sprite->setAnimationSpeed(8);
	}
}