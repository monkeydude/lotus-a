// Include the foundation
#include "foundation.h"
#include <cstring>

// Define who is playing the game
void ChangeAI (bool &isHuman, bool &isRule)
{
	if (isHuman)
	{
		isHuman=false;
		isRule=true;
	}
	else if (isRule)
		isRule=false;
	else if (!isRule && !isHuman)
		isHuman=true;
}

void GameSelectPlayers()
{
	// Create four players in memory, even though they may not be used
	for (int i = 0; i < 4; i++)
		GameData()->CreatePlayer();

	GameData()->players.at(0).piece = PIECE_P1;
	GameData()->players.at(1).piece = PIECE_P2;
	GameData()->players.at(2).piece = PIECE_P3;
	GameData()->players.at(3).piece = PIECE_P4;

	// Get number of players
	GameData()->numplayers = 0;
	GameData()->selectPlayerType = 0; // tell the rendering function what to do


	//confirm variable added for Req104.18 
	//ALSO AN OPTION TO HAVE AN EXTRA BUTTON LETTING THE PLAYER GO BACK 1 SCREEN  FOR THIS REQUIREMENT
	bool confirm=0;

	while (!confirm){
		confirm=1;
		while (true)
		{
			// Reset click
			GameData()->ResetLastClick();
			Point2i mousepos;

			// Sit and wait for a click to come through
			do
			mousepos = GameData()->GetLastClick();
			while (mousepos == Point2i(-1,-1));

			if (mousepos.x >= 165 && mousepos.x <= 181 && mousepos.y >= 376 && mousepos.y <= 400)
				GameData()->numplayers = 2;
			else if (mousepos.x >= 244 && mousepos.x <= 260 && mousepos.y >= 376 && mousepos.y <= 400)
				GameData()->numplayers = 3;
			else if (mousepos.x >= 323 && mousepos.x <= 341 && mousepos.y >= 376 && mousepos.y <= 400)
				GameData()->numplayers = 4;

			// Acceptable value?
			if (GameData()->numplayers >= 2 && GameData()->numplayers <= 4)
				break;
		}


		// Set players to playing
		for (int i = 0; i < GameData()->numplayers; i++)
			GameData()->players.at(i).isPlaying = 1;

		// Select the type for each player
		GameData()->selectPlayerType = 1;

		//Req105.3 professional rules are defaulted to off NEEDS TO BE CHANGED
		GameData()->pro=1;


		while (true)
		{
			// Reset click
			GameData()->ResetLastClick();
			Point2i mousepos;

			// Sit and wait for a click to come through
			do
			mousepos = GameData()->GetLastClick();
			while (mousepos == Point2i(-1,-1));

			// Adjust player types...
			if (mousepos.x >= 100 && mousepos.x <= 228 && mousepos.y >= 300 && mousepos.y <= 364)
				ChangeAI(GameData()->players.at(0).isHuman, GameData()->players.at(0).isRule);
			else if (mousepos.x >= 300 && mousepos.x <= 428 && mousepos.y >= 300 && mousepos.y <= 364)
				ChangeAI(GameData()->players.at(1).isHuman, GameData()->players.at(1).isRule);
			else if (mousepos.x >= 100 && mousepos.x <= 228 && mousepos.y >= 400 && mousepos.y <= 464 && GameData()->players.at(2).isPlaying)
				ChangeAI(GameData()->players.at(2).isHuman, GameData()->players.at(2).isRule);
			else if (mousepos.x >= 300 && mousepos.x <= 428 && mousepos.y >= 400 && mousepos.y <= 464 && GameData()->players.at(3).isPlaying)
				ChangeAI(GameData()->players.at(3).isHuman, GameData()->players.at(3).isRule);


			//Req105.3 NEED A BUTTON THAT CHANGES FROM YES/NO TO PROFESSIONAL RULES AND PROPER COORDINATES
			else if (mousepos.x >= -1 && mousepos.x <= 1 && mousepos.y >= -1 && mousepos.y <= 1)
				if (GameData()->pro==0)
					GameData()->pro=1;
				else
					GameData()->pro=0;



			// Exit when you click on "Done"
			if (mousepos.x >= 232 && mousepos.x <= 296 && mousepos.y >= 350 && mousepos.y <= 414)
				break;
		}


		//TEXT BOX APPEARS ASKING TO CONFIRM SELECTIONS Req104.18 
		//IF PLAYER CONFIRMS SELECTIONS, confirm=1
		//IF A PLAYER WISHES TO GO BACK, confirm=0

		if (!confirm){
			for (int i = 0; i < GameData()->numplayers; i++)
			GameData()->players.at(i).isPlaying = 0;
		}



	}



	//NEED AN OPTION BOX TO APPEAR ASKING WHICH PLAYER GOES FIRST, 0=WHITE ETC
	GameData()->adjustplayer=0;//Req104.11 

	GameData()->exitedplayer1=-1;
	GameData()->exitedplayer2=-1;


	GameData()->firstturn=0; //Req105.3

	// Create the board
	GameData()->CreateBoard();

	// Change the scene to the game board
	GameData()->SceneState = SCENE_MAINBOARD;
}

// The main loop for the board game
void GameMainBoard()
{

	// The number of wins must be equal to the number of plays minus one to end
	static int numwins = 0;

	// Go through every player's turn until the game ends
	for (GameData()->currentPlayer = 0; GameData()->currentPlayer < GameData()->GetNumPlayers(); GameData()->currentPlayer++)
	{ 
		if (!(GameData()->exitedplayer2==GameData()->currentPlayer)||!(GameData()->exitedplayer2==GameData()->currentPlayer)){
			//giant if statement for Req104.8 so that players who have exited do not take a turn

			//all for Req104.11 changes current player and gets reset to temp variable when current loop is done
			int temp=GameData()->currentPlayer;

			if (GameData()->adjustplayer>0){

				if (GameData()->numplayers==2){
					if (GameData()->currentPlayer==0)
						GameData()->currentPlayer=1;
					else
						GameData()->currentPlayer=0;
				}
				if (GameData()->numplayers==3){
					GameData()->currentPlayer=GameData()->currentPlayer+GameData()->adjustplayer;
					if (GameData()->currentPlayer==3)
						GameData()->currentPlayer=0;
					if (GameData()->currentPlayer==4)
						GameData()->currentPlayer=1;
				}
				if (GameData()->numplayers==4){
					GameData()->currentPlayer=GameData()->currentPlayer+GameData()->adjustplayer;
					if (GameData()->currentPlayer==4)
						GameData()->currentPlayer=0;
					if (GameData()->currentPlayer==5)
						GameData()->currentPlayer=1;
					if (GameData()->currentPlayer==6)
						GameData()->currentPlayer=2;
				}

			}
			//end of Req104.11 stuff



			// If the player has won already then skip their turn
			if (GameData()->board.PlayerHasWon(GameData()->players.at(GameData()->currentPlayer).piece))
				continue; //exit their turn

			// AI or Human?
			if (GameData()->players.at(GameData()->currentPlayer).isHuman)
				PerformHumanTurn(GameData()->players.at(GameData()->currentPlayer));
			else if (!GameData()->players.at(GameData()->currentPlayer).isRule)
				PerformAIStateTurn(GameData()->players.at(GameData()->currentPlayer), GameData()->states.at(GameData()->currentPlayer));
			else // if (!GameData()->players.at(GameData()->currentPlayer).isRule)
				PerformAIRuleTurn(GameData()->players.at(GameData()->currentPlayer)); // default to the rule AI


			//Req105.3 on first turn in a 2 player game, go twice with pro rules
			if ((GameData()->firstturn==0) && (GameData()->pro) && (GameData()->numplayers==2)){ 
				GameData()->firstturn=1;
				if (GameData()->players.at(GameData()->currentPlayer).isHuman)
					PerformHumanTurn(GameData()->players.at(GameData()->currentPlayer));
				else if (!GameData()->players.at(GameData()->currentPlayer).isRule)
					PerformAIStateTurn(GameData()->players.at(GameData()->currentPlayer), GameData()->states.at(GameData()->currentPlayer));
				else // if (!GameData()->players.at(GameData()->currentPlayer).isRule)
					PerformAIRuleTurn(GameData()->players.at(GameData()->currentPlayer)); // default to the rule AI
				GameData()->firstturn=2;
			}


			//PROBABLY HERE - ADD IN LOGIC TO RE-EVALUATE CURRENT STATE FOR EVERY STATE BASED AI




			// If the player just won the game, then let's exit...
			if (GameData()->board.PlayerHasWon(GameData()->players.at(GameData()->currentPlayer).piece))


				//Req104.8 gives player option to continue playing if one player has exited
				if (GameData()->numplayers>2){
					if (!((GameData()->numplayers==3)&&(GameData()->exitedplayer1!=NULL))){ //if the 2nd person just exited a 3 player game
						if (!((GameData()->numplayers==4)&&(GameData()->exitedplayer2!=NULL))){ //if the 3rd person just exited a 4 player game

							if (GameData()->exitedplayer1==NULL)//DISPLAY CURRENT PLAYER WON 1ST, ASK TO KEEP PLAYING
								if (true){
									GameData()->exitedplayer1=GameData()->currentPlayer;
								}

								else{
									GameData()->SceneState = SCENE_RESULTS;
									//EXIT GAME
								}

							else if (GameData()->exitedplayer2==NULL){//DISPLAY PLAYER WON 2ND, ASK TO KEEP PLAYING
								if (true){
									GameData()->exitedplayer2=GameData()->currentPlayer;
								}
								else{
								GameData()->SceneState = SCENE_RESULTS;
								//EXIT GAME
								}
							}

						}
						else{
							GameData()->SceneState = SCENE_RESULTS;
							//DISPLAY WHO WON 3RD PLACE
						}
					}
					else{
						GameData()->SceneState = SCENE_RESULTS;
						//DISPLAY WHO WON 2ND PLACE
					}
				}
				else{
					GameData()->SceneState = SCENE_RESULTS;
					//DISPLAY WHO WON 1ST PLACE
				}

				//end of Req104.8 

			GameData()->currentPlayer=temp; //Req104.11 to reset back to proper current player
		}

		// End of game?
		/*if (numwins == GameData()->GetNumPlayers() - 1)
			GameData()->SceneState = SCENE_RESULTS;*/
	}
}
// Show the results of the game
void GameResults()
{
	system("cls");
	printf("Congratulations! The game has been won!");
	getchar();
	// Press a key to end the game?
}