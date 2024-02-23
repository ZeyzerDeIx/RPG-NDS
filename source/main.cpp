#include "Fps.h"
#include "Player.h"
#include "Handler.h"
#include "TileMap.h"
#include "Camera.h"

//contains the gameMap as a 2 dimensionnal array of int8
#include "maps.cpp"

using namespace std;



int main() 
{	
	
	
	//set mode 5, enable BG0 and set it to 3D
	videoSetMode( MODE_5_3D );
	// initialize gl2d
	glScreen2D();
	
	#ifdef DEBUG_MODE_ENABLE
	//Enable bottom screen as debug console
	consoleDemoInit();
	#endif

	#ifdef FPS_ENABLE
	//Create the FPS displayer
	Fps fps(10);
	#endif


    // Set up enough texture memory for our textures
	vramSetBankA(VRAM_A_TEXTURE_SLOT0);
	vramSetBankB(VRAM_B_TEXTURE_SLOT1);
	vramSetBankC(VRAM_C_TEXTURE_SLOT2);
	vramSetBankD(VRAM_D_TEXTURE_SLOT3);
	// Allocate VRAM bank for all the palettes
	vramSetBankF(VRAM_F_TEX_PALETTE_SLOT0);

	//Create the tileMap
	TileMap tileMap(gameMap);

	//Create the player and link it to the tileMap
	Player player(&tileMap);

	//Create the handler wich will read and treat all inputs
	Handler handler(&player, &tileMap);

	//Create the camera to manage tileMap position relative to the screen and the player position
	Camera camera(&tileMap);
	
	while( true ) 
	{

		#ifdef FPS_ENABLE
		//calculate and display FPS
		fps.newFrame();
		#endif

		//Read and handle player inputs
		handler.handleInputs();

		//update map camera and player
		tileMap.update();
		camera.followPlayer();
		player.update();


		// Start 2D mode
		glBegin2D();
		// Normalize color
		glColor( RGB15(31, 31, 31) );
		tileMap.display();
		player.display();
		glEnd2D();

		
		//swap the buffers and wait until new frame
		glFlush( 0 );
	}

	return 0;


}