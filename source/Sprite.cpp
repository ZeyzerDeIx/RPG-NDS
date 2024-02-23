#include "Sprite.h"

using namespace std;
int Sprite::loadedSprites = 0;

Sprite::Sprite(){}
Sprite::Sprite(int frameWidth, int frameHeight, const unsigned int* bitmap, const uint16* palette, int framesNumber, int statesNumber, bool transparency):
	m_size{frameWidth, frameHeight},
	m_framesNumber(framesNumber),
	m_statesNumber(statesNumber)
{
	int imagesNumber = m_framesNumber*m_statesNumber;

	m_images = new glImage[imagesNumber];

	m_textCoord = new unsigned int[imagesNumber*4];
	for (int i = 0; i < m_statesNumber; ++i)
	{
		for (int j = 0; j < m_framesNumber; ++j)
		{
			m_textCoord[(i*m_framesNumber+j)*4]   = j*m_size[W];
			m_textCoord[(i*m_framesNumber+j)*4+1] = i*m_size[H];
			m_textCoord[(i*m_framesNumber+j)*4+2] = m_size[W];
			m_textCoord[(i*m_framesNumber+j)*4+3] = m_size[H];
		}
	}

	glColorSubTableEXT(0,(loadedSprites++)*256,256,0,0,palette);

	glLoadSpriteSet(m_images,
		imagesNumber,
		m_textCoord,
		GL_RGB256,
		calculateTextureSize(W),
		calculateTextureSize(H),
			TEXGEN_OFF|
			GL_TEXTURE_COLOR0_TRANSPARENT*transparency,
		256,
		(u16*)palette,
		(u8*)bitmap);

	m_currentFrame = 0;
	m_currentState = 0;
	m_animationSpeed = 0;
	m_counter = 0;
}
Sprite::~Sprite()
{
	delete[] m_images;
	delete[] m_textCoord;
}


void Sprite::update()
{
	if(m_animationSpeed == 0) return;
	if (++m_counter >= m_animationSpeed) 
		skipFrame(), m_counter = 0;
}

void Sprite::display(short* position)
{
	glSprite(position[X],position[Y],0,&m_images[m_currentState*m_framesNumber+m_currentFrame]);
}

void Sprite::manualDisplay(short* position, int frame, int state, float scale, bool flipX, bool flipY)
{
	glSpriteScale(position[X],position[Y], NORMAL_SCALE*scale,(GL_FLIP_H*flipX)|(GL_FLIP_V*flipY),&m_images[state*m_framesNumber+frame]);
}

void Sprite::displayAll()
{
	for (int i = 0; i < m_statesNumber; ++i)
	{
		for (int j = 0; j < m_framesNumber; ++j)
		{
			glSprite(j*m_size[W], i*m_size[H], 0,&m_images[i*m_framesNumber+j]);
		}
	}
}

void Sprite::skipFrame()
{
	//si l'animation dépasse le nombre total de frame on la réinitialise
	if(m_currentFrame >= m_framesNumber-1) m_currentFrame = 0;
	else m_currentFrame++;
}

void Sprite::setState(int state)
{
	if(state == m_currentState) return;
	//le modulo assure qu'on ne mette pas un état qui n'existe pas
	m_currentState = state%m_statesNumber;
}

void Sprite::setFrame(int frame)
{
	if(frame == m_currentFrame) return;
	m_currentFrame = frame<m_framesNumber?frame:(m_framesNumber-1);
}

void Sprite::setAnimationSpeed(int animationSpeed)
{
	m_animationSpeed = animationSpeed;
}

int Sprite::getSize(bool xOrY)
{
	return m_size[xOrY];
}



//privates methodes

//calculate wich TEXTURE_SIZE is required for the requested axis
int Sprite::calculateTextureSize(bool wOrH)
{
	int number = wOrH ? m_statesNumber : m_framesNumber;

	int textureSize = TEXTURE_SIZE_8;
	if(number*m_size[wOrH] <= 16)
		textureSize = TEXTURE_SIZE_16;
	else if(number*m_size[wOrH] <= 32)
		textureSize = TEXTURE_SIZE_32;
	else if(number*m_size[wOrH] <= 64)
		textureSize = TEXTURE_SIZE_64;
	else if(number*m_size[wOrH] <= 128)
		textureSize = TEXTURE_SIZE_128;
	else if(number*m_size[wOrH] <= 256)
		textureSize = TEXTURE_SIZE_256;
	else if(number*m_size[wOrH] <= 512)
		textureSize = TEXTURE_SIZE_512;
	else if(number*m_size[wOrH] <= 1024)
		textureSize = TEXTURE_SIZE_1024;
	else
		cout << "Error: texture size " << (wOrH ? "H" : "W") << " > 1024!!" << endl;

	return textureSize;
}