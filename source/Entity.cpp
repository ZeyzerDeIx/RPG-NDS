#include "Entity.h"
//#include "TileMap.h"

using namespace std;

Entity::Entity(Sprite* sprite, float w, float h):
	m_sprite(sprite),
	m_pos{0,0},
	m_size{w,h},
	m_speed(1.5f),
	m_hitbox(m_pos[X],m_pos[Y],w,h),
	m_zoomed(false)
{}

Entity::~Entity() {}


void Entity::update()
{
	m_sprite->update();
	m_hitbox.setRect(m_pos[X],m_pos[Y],m_size[W],m_size[H]);
}

void Entity::display()
{
	m_sprite->display(m_pos[X], m_pos[Y]);
}

/*void Entity::displayHitbox()
{
	m_hitbox.display();
}*/

void Entity::move(float x, float y)
{
	m_pos[X] += x;
	m_pos[Y] += y;
}
void Entity::setPos(float x, float y)
{
	m_pos[X] = x;
	m_pos[Y] = y;
}

void Entity::setZoomed(bool zoomed)
{
	m_zoomed = zoomed;
}

float Entity::getPos(bool xOrY)
{
	return m_pos[xOrY];
}

float Entity::getSize(bool wOrH)
{
	return m_size[wOrH];
}

Hitbox& Entity::getHitbox()
{
	return m_hitbox;
}