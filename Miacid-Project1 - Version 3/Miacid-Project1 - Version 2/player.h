#ifndef PLAYER_H
#define PLAYER_H

// Includes
#include "foundation.h"
#include <vector>

// Defines
#define PLAYERS_MAX 4

enum PTYPE {PLAYER_HUMAN, PLAYER_RULEBASED, PLAYER_STATEBASED};
enum PIECE {PIECE_BAD, PIECE_P1, PIECE_P2, PIECE_P3, PIECE_P4};

class Player
{
public:
	// General
	PIECE piece;
	bool isPlaying;
	bool isHuman;
	bool isRule;
	bool isState;
	bool isNetwork;

	Player()
	{
		this->piece = PIECE_BAD;
		this->isPlaying = 0;
		this->isHuman = 1;
		this->isRule = 0;
		this->isState = 0;
		this->isNetwork = 0;
	}
};

// Somewhat different from Player
class PlayerType
{
public:
	bool isPlaying;
	bool isHuman;
	bool isRule;
	bool isState;
	bool isNetwork;
	
	PlayerType()
	{
		isPlaying=true;
		isHuman=true;
		isRule=false;
		isState = false;
		isNetwork = false;
	}
};

#endif // PLAYER_H