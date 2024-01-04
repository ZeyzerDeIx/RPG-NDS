#include "Hitbox.h"
//#include "Debugger.h"

Hitbox::Hitbox(int x, int y, int w, int h):m_rect{x,y,w,h}
{
    m_isCollidingSomething = false;
}
Hitbox::~Hitbox() {}

bool Hitbox::collide(const Hitbox& other)
{
	const rect& r1 = m_rect;
    const rect& r2 = other.m_rect;
	m_isCollidingSomething = 
           (r1.x < r2.x+r2.w && //r1's Left Edge to left of r2's right edge
            r1.x+r1.w > r2.x && //r1's right edge to right of r2's left edge
            r1.y < r2.y+r2.h && //r1's top above r2's bottom
            r1.y+r1.h > r2.y);  //r1's bottom below r2's Top
    return m_isCollidingSomething;
}

void Hitbox::display(int x, int y)
{
    int r=5,g=5,b=5;
    if(m_isCollidingSomething)
        r = 15, g = 15, b = 5;
    int w = x+m_rect.w;
    int h = y+m_rect.h;
    glLine(x,y,w-1,y,RGB15(r,g,b));
    glLine(x,h-1,w-1,h-1,RGB15(r,g,b));
    glLine(x,y,x-1,h-1,RGB15(r,g,b));
    glLine(w-1,y,w-2,h-1,RGB15(r,g,b));
}

void Hitbox::setRect(int x, int y, int w, int h)
{
    m_rect = {x,y,w,h};
}

const rect& Hitbox::getRect()
{
    return m_rect;
}