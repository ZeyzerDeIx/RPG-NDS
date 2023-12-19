#ifndef CAMERA_H_INCLUDED
#define CAMERA_H_INCLUDED

	#include "TileMap.h"

	class Camera
	{
		public:
			Camera(TileMap* tileMap);
			~Camera();

			void followPlayer();
		private:
			TileMap* m_tileMap;		
	};

#endif