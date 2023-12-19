#ifndef FPS_H_INCLUDED
#define FPS_H_INCLUDED

	#include "constants.h"

	#ifdef FPS_ENABLE

	class Fps
	{
		public:
			Fps();
			Fps(int updatesPerSeconds);
			~Fps();

			void newFrame();
			void update();
			int getFps();
		private:
			int m_frameCounter;
			int m_fps;
			int m_updatesPerSeconds;
	};
	void updateGlobalFps();
	static Fps* globalFps;
	#endif

#endif