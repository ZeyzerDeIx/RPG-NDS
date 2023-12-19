#ifndef HITBOX_H
#define HITBOX_H

	#include "constants.h"

	struct rect { int x;int y; int w;int h; };

	class Hitbox
	{
		public:
			Hitbox(int x, int y, int w, int h);
			~Hitbox();
			bool collide(const Hitbox& other);
			//void display(int x, int y);
			//void display();
			void setRect(int x, int y, int w, int h);
			const rect& getRect();
		private:
			rect m_rect;
			bool m_isCollidingSomething;
	};

#endif//HITBOX_H