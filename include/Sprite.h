#ifndef SPRITE_H_INCLUDED
#define SPRITE_H_INCLUDED

	#include "constants.h"

	class Sprite
	{
	#define NORMAL_SCALE 4096
	public:
		Sprite();
		Sprite(int frameWidth, int frameHeight, const unsigned int* bitmap = nullptr, const uint16* palette = nullptr, int framesNumber = 1, int statesNumber = 1, bool transparency = false);
		~Sprite();

		void update();
		void display(int posX, int posY);
		void manualDisplay(int posX, int posY, int frame = 0, int state = 0, float scale = 1.f, bool flipX = false, bool flipY = false);
		void displayAll();
		void skipFrame(int num = 1);
		void setFrame(int frame);
		void setState(int state);
		void setAnimationSpeed(int animationSpeed);
		int getSize(bool xOrY);
	private:
		glImage* m_images;
		int m_size[2];
		int m_framesNumber;
		int m_statesNumber;
		unsigned int* m_textCoord;
		int m_currentFrame;
		int m_currentState;
		int m_animationSpeed;
		int m_counter;
		static int loadedSprites;
	};

	#define CREATE_SPRITE(pixelW,pixelH,name,frames,states) Sprite(pixelW, pixelH, name ## Bitmap, name ## Pal, frames, states)
	//_T for transparency
	#define CREATE_SPRITE_T(pixelW,pixelH,name,frames,states) Sprite(pixelW, pixelH, name ## Bitmap, name ## Pal, frames, states, true)

#endif