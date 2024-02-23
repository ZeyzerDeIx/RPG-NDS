#ifndef SPRITE_H_INCLUDED
#define SPRITE_H_INCLUDED

	#include "constants.h"

	class Sprite
	{
	#define NORMAL_SCALE 4096
	public:
		Sprite();
		/*Main constructor:
		* - int frameWidth: the width of one frame
		* - int frameHeight: the height of one frame
		* - const unsigned int* bitmap: a pointer to the image
		* - const uint16* palette: a pointer to the color palette
		* - int framesNumber: number of frame (the x axis)
		* - int statesNumber: number of state (the y axis)
		* - bool transparency: if true, the first pixel color will be transparent
		*/
		Sprite(int frameWidth, int frameHeight, const unsigned int* bitmap = nullptr, const uint16* palette = nullptr, int framesNumber = 1, int statesNumber = 1, bool transparency = false);
		~Sprite();


		/*Needs to be called each frame, manage the animation if there is one*/
		void update();

		/*Displays the sprite at given position
		* - short* position: The position where to display the sprite, an array of 2 short for the x and y coordinates
		*/
		void display(short* position);

		/*Displays the sprite mannualy at the given position with the given frame, scale, and it can be reversed
		* - short position: The position where to display the sprite, an array of 2 short for the x and y coordinates
		* - int frame: the frame to display (x axis on the original image)
		* - int state: the state to display (y axis on the original image)
		* - float scale: the scale of the sprite, if it's 1.f, the image will not be changed
		* - bool flipX: if true, the sprite is flipped on the x axis on the display
		* - bool flipY: if true, the sprite is flipped on the y axis on the display
		*/
		void manualDisplay(short* position, int frame = 0, int state = 0, float scale = 1.f, bool flipX = false, bool flipY = false);

		/*Use it for debug purposes. Displays all frame ordered as on the original image*/
		void displayAll();

		/*Mannualy skip on frame, if last frame is reached, it go back to the first one*/
		void skipFrame();

		/*Mannualy set current display frame to the given one
		* - int frame: new index for the currently seleted frame
		*/
		void setFrame(int frame);

		/*Mannualy set current display state to the given one
		* - int state: new index for the currently seleted state
		*/
		void setState(int state);

		/* Set the animation speed to the given value, if you want to disable the animation, set it to 0
		* - int animationSpeed: number of frame between two frame skip
		*/
		void setAnimationSpeed(int animationSpeed);

		/* Get the size of the sprite (it's the size of any of it's frames)
		* - bool xOrY: 0 if X, 1 if Y
		* - Returns the requested size on the requested axis
		*/
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

		int calculateTextureSize(bool wOrH);
	};

	#define CREATE_SPRITE(pixelW,pixelH,name,frames,states) Sprite(pixelW, pixelH, name ## Bitmap, name ## Pal, frames, states)
	//_T for transparency
	#define CREATE_SPRITE_T(pixelW,pixelH,name,frames,states) Sprite(pixelW, pixelH, name ## Bitmap, name ## Pal, frames, states, true)

#endif