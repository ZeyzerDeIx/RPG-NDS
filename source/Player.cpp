#include "Player.h"
#include "PlayerSprite.h"

using namespace std;

//As a unique character, the player class manages it's sprite itself
Player::Player(TileMap* tileMap):
Character(tileMap,
	new CREATE_SPRITE_T(24, 34, PlayerSprite, 4, 8),
	24, 34)

{
	//As a friend class of TileMap, the player can assign itself to the private attribute of TileMap "m_player"
	tileMap->m_player = this;
	//default position, top left corner of the TileMap
	m_pos[X] = m_pos[Y] = 0;
	m_sprint = false;

	//positionning the player in the middle of the screen
	m_displayPos[X] = 256.f/2.f - m_size[W]/2.f;
	m_displayPos[Y] = 192.f/2.f - m_size[H]/2.f;
}
//Because it manages it's sprite itself, it also has to free the memory manually
Player::~Player() { delete m_sprite; }

void Player::display()
{
	m_sprite->display(m_displayPos);
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