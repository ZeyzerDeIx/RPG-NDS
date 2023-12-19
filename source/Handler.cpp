#include "Handler.h"

using namespace std;

Handler::Handler(Player* player, TileMap* tileMap):
m_player(player),
m_tileMap(tileMap)
{}
Handler::~Handler() {}

void Handler::handleInputs()
{
    int held=0, down=0, up=0;
	scanKeys();

    held = keysHeld();
    if(held & KEY_UP)
        m_player->setDirection(DIRECTIONS::UP);
    if(held & KEY_DOWN)
        m_player->setDirection(DIRECTIONS::DOWN);
    if(held & KEY_LEFT)
        m_player->setDirection(DIRECTIONS::LEFT);
    if(held & KEY_RIGHT)
        m_player->setDirection(DIRECTIONS::RIGHT);

    down = keysDown();
    if(down & KEY_B)
        m_player->setSprint(true);

    up = keysUp();
    if(up & KEY_UP)
        m_player->setDirection(DIRECTIONS::UP, false);
    if(up & KEY_DOWN)
        m_player->setDirection(DIRECTIONS::DOWN, false);
    if(up & KEY_LEFT)
        m_player->setDirection(DIRECTIONS::LEFT, false);
    if(up & KEY_RIGHT)
        m_player->setDirection(DIRECTIONS::RIGHT, false);
    if(up & KEY_B)
        m_player->setSprint(false);
}