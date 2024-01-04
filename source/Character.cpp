#include "Character.h"
//#include "Debugger.h"

using namespace std;
using namespace DIRECTIONS;

Character::Character(TileMap* tileMap, Sprite* sprite, float w, float h):
		Entity(sprite,w,h),
		m_isWalking(false),
		m_directions{false,false,false,false},
		m_lastDirection(DOWN)
{
	m_tileMap = tileMap;
	this->updateHitbox();
	m_sprite->setAnimationSpeed(8);
}

void Character::update()
{
	move(-m_speed*m_directions[LEFT] + m_speed*m_directions[RIGHT], -m_speed*m_directions[UP] + m_speed*m_directions[DOWN]);
	m_sprite->setState(4*m_isWalking + m_lastDirection);
	Entity::update();
	this->updateHitbox();
}

void Character::setDirection(int direction, bool value)
{
	m_isWalking = false;
	//on update la valeure et on vérifie si elle est vrai
	if((m_directions[direction] = value) == true)
		m_isWalking = true, m_lastDirection = direction; //auquel cas le personnage est en mouvement
	else
		for (bool i : m_directions) //on regarde toutes les direction
			if(i) m_isWalking = true;
			//si une est vrai alors le personnage est en mouvement
}

void Character::move(float x, float y)
{
	m_pos[X] += x;
	this->updateHitbox();
	if(m_tileMap->collide(*this))
		m_pos[X] -= x;
	m_pos[Y] += y;
	this->updateHitbox();
	if(m_tileMap->collide(*this))
		m_pos[Y] -= y;
}



void Character::updateHitbox()
{
	m_hitbox.setRect(m_pos[X],
		             m_pos[Y] + m_size[H]/2.f,
		             m_size[W],
		             m_size[H]/2.f);
}