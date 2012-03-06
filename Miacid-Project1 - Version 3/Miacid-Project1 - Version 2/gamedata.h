#ifndef GAMEDATA_H
#define GAMEDATA_H

#include "StateAI.h"

enum Scene {SCENE_DEFAULT, SCENE_SELECT_PLAYERS, SCENE_MAINBOARD, SCENE_RESULTS};

class GD
{
public:
	Board board;

	PNG LoadingImage;
	PNG LotusBoard;
	PNG LotusError;
	PNG LotusSelected;
	PNG LotusPossible;
	PNG LotusWhiteMoved;
	PNG LotusBlackMoved;
	PNG LotusRedMoved;
	PNG LotusBlueMoved;
	PNG LotusMoved[4];
	PNG LotusWhite;
	PNG LotusBlack;
	PNG LotusRed;
	PNG LotusBlue;
	PNG LotusNumbers[24];
	PNG LotusMessages[3];

	PNG LotusJoinnet;
	PNG LotusHostnet;
	PNG LotusConfirm;
	PNG LotusContinue;
	PNG LotusRSel;
	PNG LotusPSel;
	PNG LotusSkip;
	PNG LotusCurPlayer;


	PNG LotusTurn;
	PNG LotusWinner;
	PNG LotusFrontBoard;
	PNG LotusPlayers;
	PNG LotusPlayer1;
	PNG LotusPlayer2;
	PNG LotusPlayer3;
	PNG LotusPlayer4;
	PNG LotusAIRule;
	PNG LotusAIState;
	PNG LotusHuman;
	PNG LotusFinished;
	PNG LotusNotPlaying;
	PlayerType player1;
	PlayerType player2;
	PlayerType player3;
	PlayerType player4;

	bool gLoaded;
	bool gRunning;
	bool bCreated;

	bool selectPlayerType;

	int numplayers;
	int currentPlayer;
	vector<Player> players;
	//vector of states where each position refers to the state of that player (some positions will never be used if that player is not a state AI)
	vector<BaseState*> states;

	bool pro; //Req105.3
	int firstturn; //Req105.3
	int firstturnpos; //Req105.3
	int adjustplayer; //Req104.11 
	int exitedplayer1;
	int exitedplayer2;

	Scene SceneState;

	vector<TRule> Rules;
	vector<TMove> Moves;

private:
	Point2i lastclick;

public:
	GD();

	void CreateBoard();
	void SetSelected(PNG * selected, PNG * possible);
	void SetBoardBackground(PNG * bg);
	void SetBoardError(PNG * error);
	void SetBoardPieces(PNG * unit_white, PNG * unit_black, PNG * unit_red, PNG * unit_blue);
	void SetBoardNumbers(PNG img_num[24]);
	void SetBoardMessages(PNG img_num[3]);
	
	void SetLastClick(int x, int y);
	Point2i GetLastClick();
	void ResetLastClick();

	void CreatePlayer();
	int GetNumPlayers();

	void RecordMove(TMove move);
	void CreateRules();
};

// Return pointer to this class
GD * GameData();

#endif // GAMEDATA_H