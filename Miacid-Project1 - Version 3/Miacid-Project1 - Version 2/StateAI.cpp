#include<iostream>
#include<string>
#include "foundation.h"


string BaseState::GetStateName(void)
{
 return stateName_;
}

exitingPieceState::exitingPieceState(/*BaseState* state*/)
{
	// populate valid moves list

	validMoves_.push_back(-8);
	stateName_ = "exitingPiece";
}

void exitingPieceState::movePiece()
{
	int toMove;
	//sort vector to have piece closest to the end at its tail
	std::sort(validMoves_.begin(), validMoves_.end());
	//get a piece from the vector list
	toMove = validMoves_.back();
	//remove last element
	validMoves_.pop_back();

	GameData()->board.MovePiece(toMove, 3);
 //move a piece, this funct may not be needed as it's not being over written
	cout << "I moved a piece! (YA RLY) of value:"<<toMove<<endl;
}

void exitingPieceState::StateChangeCheck(int source, int destination)
{
	printf("I'm checking stack %d and %d\n", source, destination);
}

movePieceState::movePieceState()
{
	validMoves_.push_back(-8);
	validMoves_.push_back(-6);
	validMoves_.push_back(-7);
	validMoves_.push_back(-5);
	stateName_ = "movePiece";
}

void movePieceState::movePiece()
{
	int toMove;

	//get a piece from the vector list
	toMove = validMoves_.back();
	//remove last element
	validMoves_.pop_back();

	//piece is in starting position
	if(toMove<0){

		switch (GameData()->board.GetSizeOfStack(toMove)){
			case 1:
				if(GameData()->board.GetSizeOfStack(0)<GameData()->board.GetSizeOfStack(3)){
						GameData()->board.MovePiece(toMove, 3); //move to right
				}
					else{
						GameData()->board.MovePiece(toMove, 0);	//move to left				
					}
				return;

			case 2:
				if(GameData()->board.GetSizeOfStack(1)<GameData()->board.GetSizeOfStack(4)){
						GameData()->board.MovePiece(toMove, 4); //move to right
				}
					else{
						GameData()->board.MovePiece(toMove, 1);	//move to left				
					}
				return;
			
			case 3:
				if(GameData()->board.GetSizeOfStack(2)<GameData()->board.GetSizeOfStack(5)){
						GameData()->board.MovePiece(toMove, 5); //move to right
				}
					else{
						GameData()->board.MovePiece(toMove, 2);	//move to left				
					}
				return;

			case 4:
				GameData()->board.MovePiece(toMove, 6);
				return;

			default: cout << "I BROKE" <<endl;
				break;
		}

	}

	GameData()->board.MovePiece(toMove, -1);
}

void movePieceState::StateChangeCheck(int source, int destination)
{
	printf("I'm checking stack %d and %d\n", source, destination);
}


void useTrampState::movePiece()
{
	int toMove;
	//sort vector to have piece whith lowest value at its tail
	std::sort(validMoves_.begin(), validMoves_.end(),greater<int>());
	//get a piece from the vector list
	toMove = validMoves_.back();
	//remove last element
	validMoves_.pop_back();

	//tells to move piece
	GameData()->board.MovePiece(toMove, -1);
}

void captureTrampState::movePiece()
{
	int toMove;

	//get a piece from the vector list
	toMove = validMoves_.back();
	//remove last element
	validMoves_.pop_back();

	//tells to move piece
	GameData()->board.MovePiece(toMove, -1);
}

captureStackState::captureStackState()
{
	validMoves_.push_back(-5);
	validMoves_.push_back(-6);
	validMoves_.push_back(-7);
	validMoves_.push_back(-8);
	
	stateName_ = "captureStack";
}

void captureStackState::movePiece()
{
	int tempEnd=-1;
	int captureValue=0;

	int toErase=0;

	int finalLoc = validMoves_.front();
	int finalEnd = -1;
	int finalCap = 0;

	for (int x = 0; x<validMoves_.size();x++){

		if(validMoves_[x]<0){//if it's in starting area  i need to figure out it's best capture location (L|R)
					 //and potential capture stack size

			switch (GameData()->board.GetSizeOfStack(validMoves_[x])){
				case 1:
					if(GameData()->board.GetSizeOfStack(0)<GameData()->board.GetSizeOfStack(3)){
							tempEnd=3;
							captureValue=GameData()->board.GetSizeOfStack(3);
					}
						else{
							tempEnd=0;
							captureValue=GameData()->board.GetSizeOfStack(0);
						}
					break;

				case 2:
					if(GameData()->board.GetSizeOfStack(1)<GameData()->board.GetSizeOfStack(4)){
							tempEnd=4;
							captureValue=GameData()->board.GetSizeOfStack(4);
					}
						else{
							tempEnd=1;
							captureValue=GameData()->board.GetSizeOfStack(1);				
						}
					break;
				
				case 3:
					if(GameData()->board.GetSizeOfStack(2)<GameData()->board.GetSizeOfStack(5)){
							tempEnd=5;
							captureValue=GameData()->board.GetSizeOfStack(5);
					}
						else{
							tempEnd=2;
							captureValue=GameData()->board.GetSizeOfStack(2);				
						}
					break;

				case 4:
					tempEnd=6;
					captureValue=GameData()->board.GetSizeOfStack(6);
					break;

				default: cout << "I BROKE: captureStackState" <<endl;
					break;
			}
		
		}

		else{
		// itmust be a piece on the board, aka no L|R checking
			tempEnd=-1;
			captureValue=GameData()->board.GetSizeOfStack(validMoves_[x]);
		}

		//now to check vs previous vector
		if (captureValue>finalCap){
			finalCap=captureValue;
			finalEnd=tempEnd;
			finalLoc=validMoves_[x];
			toErase=x;
		}

	}
	//add it to the board
	GameData()->board.MovePiece(finalLoc, finalEnd);
	//remove the stack from possible choices
	validMoves_.erase(validMoves_.begin()+toErase);
}

void captureStackState::StateChangeCheck(int source, int destination)
{
	printf("I'm checking stack %d and %d\n", source, destination);
}

void cantMoveState::movePiece()
{
	int toMove;

	//get a piece from the vector list
	toMove = validMoves_.back();
	//remove last element
	validMoves_.pop_back();

	//tells to move piece
	GameData()->board.MovePiece(toMove, -1);
}