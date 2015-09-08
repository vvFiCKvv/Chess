/*|============================================================================|*
 *| Chess Application: file ChessBoard.h                                       |*
 *|                                                                            |*
 *| Developed and programmed by:                                               |*
 *|           Milios Nikos, RN: 1523, email: milios@csd.uoc.gr                 |*
 *|        Velegrakis Ioannis, RN: 1494, email: jveleg@csd.uoc.gr              |*
 *|                                                                            |*
 *|                                                                            |*
 *| Copyright 2006: All rights reserved. Any copying, lending, seling or       |*
 *|                 public performance without a written permission is         |*
 *|					prohibited.                                                |*
 *| You must accept the enclosed License Agreement before you can use this     |*
 *| product. This is licensed as a single product. Its component parts may not |*
 *| be separated for use by more than one user. if you do not accept the terms |*
 *| of the License Agreement, you should promptly return the product for a     |*
 *| refund.                                                                    |*
 *|============================================================================|*/

#ifndef _CHESSBOARD_H_
#define _CHESSBOARD_H_

/*======== Other files used ================*/
#include "Pown.h"
#include <stdio.h>
/*==========================================*/

/*======== Variables, Fuctions and Objects ====================*/
#define IS_MAT  1
#define IS_PAT  2
#define IS_OK   0

/*Take this out of the comments if you want all the rates lists to be initializes
  every time the function getAllValidMoves() or getAllValidMovesSimple() is called.
  If it is defined it will add an overhead to the algorithm thinkng time, and the speed
  will be decreased. So, if an algorithm is used it is prefered not to define this.
  If no algorithm is used it has not any difference. Indeed when no algorithm is used
  it is useless to have a movements rate list.*/
#define INITIALIZE_RATES

	/*defines for the action structure.*/
	#define SIMPLE_ACT 0
	#define QUEEN_ROKE_ACT 1
	#define KING_ROKE_ACT  2
	#define PROMOTION_ACT  3

/*|------ Pownstatus structure -----------------------------|* 
 *|This structure represents the whole situtation of a      |
 *|piece in the chessboard. A pownstatus structure has the  | 
 *|following members:                                       |
 *|-> currentPosition: Is the current position of the piece |
 *|                    in the chessboard table.             |
 *|-> currentType: Is the current type of the piece.        |
 *|-> currentPown: Is a pointer the the corresponding       | 
 *|                piece Object. It is used to access its   |
 *|                specific functions.                      |
 *|-> validMoves: Is a list a point structures and keeps    |
 *|               all the valed moves for the piece.        |
 *|-> validMovesRate: Is a list parralled to the validMoves | 
 *|                   list each item is an integer that is  |
 *|                   the rate that the algorith determined |
 *|                   for the corresponding move.           | 
 *|---------------------------------------------------------|*/
struct pownstatus {
	struct point currentPosition;
	enum powntype currentType;
	Pown *currentPown;
	
	/*validMoves and validMovesRate are two parrallel tables.*/
	DoubleLinkedList *validMoves;
	DoubleLinkedList *validMovesRate;
};


/*|-------- class ChessBoard --------------------------------------------|*
 *|This is the class that represents the chessboard. It is the main core |
 *|of the application. All operations and actions are controlled and     |
 *|checked by this object. Except of the chessboard table it represents  |
 *|the mathematical explanation of the rules of a chess game.            |  
 *|----------------------------------------------------------------------|*/
class ChessBoard 
{
private:
	/*This function initializes all variables and structures if the 
	  game is 6x6.*/
	void initializeChessBoard6x6(void);

	/*This function initializes all variables and structures if the 
	  game is 8x8.*/
	void initializeChessBoard8x8(void);

	/*This is the list of the current valid moves for all the pieces
	  of the white team. Each item of this list is a pownstatus structure
	  containing the current siutuation and valid moves of a piece. The list
	  is updated by the upgradeValidMoves() functions. This list exists to
      make the program run faster (it does not have to recalculate all the valid
	  moves each time it wants to) and to make the development easier.*/
	DoubleLinkedList *whiteValidMoves;

	/*This is the list of the current valid moves for all the pieces
	  of the black team. Each item of this list is a pownstatus structure
	  containing the current siutuation and valid moves of a piece. The list
	  is updated by the upgradeValidMoves() functions. This list exists to
      make the program run faster (it does not have to recalculate all the valid
	  moves each time it wants to) and to make the development easier.*/
	DoubleLinkedList *blackValidMoves;

	/*This list contains all the white pieces that exist in the chessboard. It
	  is used in order to easy access the white pieces and not trying to get them
	  from the board[][] table. In that way we no always what pieces the white
	  team has got in the chessboard.*/
	DoubleLinkedList *whitePowns;

	/*This list contains all the black pieces that exist in the chessboard. It
	  is used in order to easy access the white pieces and not trying to get them
	  from the board[][] table. In that way we no always what pieces the black
	  team has got in the chessboard.*/
	DoubleLinkedList *blackPowns;

	/*This functions delallocates the memory that has been reserved for the
	  valid moves lists. It is used frequently, when updating the valid moves
	  lists.*/
	void freeValidMovesLists(void);

	/*This list keeps all the action that have aoccured since the
	  game has started. Each item of this list is a struct action that
	  contains several information and characteristics about the action.
	  It is used in order the program to be able to cancel several actions
	  and return into a chessboards state before those action occured.
	  That way all actions done is possible to be undone one by one from
	  the tail to the head. An item is inserted when move() or promote() 
	  functions are called. The queue of the items are according to the
	  time point that they where happened. If an action must be cancelled
	  then it will be removed from this list after the handling of the
	  returning into the previous state. See structure action, 
	  ChessBord::move() and ChessBord::promote() for more details.*/
	DoubleLinkedList *logFile;

	/*This list maintains the set of all the captured points for
	  both teams. An item into thislist is inserted, when ChessBoard::move()
	  function is called and furthermore if there is an attacked piece involved
	  in the movement. This list helps us knowing what pieces have been
	  captured from the beginning of the game.*/
	DoubleLinkedList *capturedList;

	/*|------- Action structure --------------------------------|
	 *|This structure is a sum of the characteristics of each   |
	 *|action that has occured. An action structure is an item  |
	 *|of the logFile list, which keeps all the actions done    |
	 *|from the beginning of the game. Each time the movement   |
	 *|or promote function is called an action structure is     |
	 *|created and added in the tail of the logFile list.       |
	 *|It helps the program to cancel each time the last action |
	 *|So all can be canceled one by one from the tail to the   |
	 *|head of the list as a chain.                             |
	 *|See inside the structure for the details of each member  |
	 *|---------------------------------------------------------|*/
	struct action {

		/*The team of the piece that is involved in the action.*/
		enum team_ team;

		/*Type of the action that has occured:
		  0 (SIMPLE_ACT): simple action
		  1 (QUEEN_ROKE_ACT): queenside roke movement
		  2 (KING_ROKE_ACT): kingside roke movement
		  3 (PROMOTION_ACT): promotion*/
		unsigned char actionType;

		/*Position before the movement occured.*/
		struct point fromPosition;

		/*New position of the piece after the movement.*/
		struct point toPosition;

		/*Pointer to the attackted piece. If there was no piece attacked
		  this pointer is set to NULL.*/
		Pown *attacked;
	};

	/*This variable show if the maintaing of the logFile is enabled. If it is
	  true it is enabled, otherwise it is disabled..*/
	bool enabledLogFile;

public:

	/*This is the main table of the game. This represents the mathematical
	  identity of the chessboard. Each cell of the table is a pointer to 
	  a piece object. If the pointer in a cell is NULL, it means that there
	  is no piece in that square. In that way we can easily access the pieces'
	  specific functions.*/
	Pown *board[BOARD_MAX][BOARD_MAX];
	Pown *whiteKing;
	Pown *blackKing;

	/*Constructor of the chessboard. It Allocates memory for variables and 
	  structures and initializes them. It uses the two initialization function.
	  It uses default values for several variables. All pieces are placed
	  as in a normal starting of a chess game.
	  For more details see initializeChessBoard6x6() and initializeChessBoard8x8()
	  functions.*/
	ChessBoard(void);

	/*Constructor of the chessboard. It Allocates memory for variables and 
	  structures and initializes them. It uses the two initialization function.
	  A board[][] is given as argument. In that way the pieces are placed as in the
	  given board.
	  For more details see initializeChessBoard6x6() and initializeChessBoard8x8()
	  functions.*/
	ChessBoard(Pown *pboard[BOARD_MAX][BOARD_MAX]);

	ChessBoard(Pown *pboard[BOARD_MAX][BOARD_MAX],int x0,int y0,int x1,int y1);

	/*Destructor of the chessboard. Deallocates all used memory used by the
	  ChessBoard class.*/
	~ChessBoard();

	/*This function returns a pointer to the piece that was found. Arguments
	  represent the position in the board[i][j] that we want to get the
	  piece pointer. i and j must not be negative or greater than the BOARD_X
	  and BOARD_Y defined variables.*/
	Pown *getPown(int i, int j);

	/*This function removes a piece of the game. It removes it from the board[][]
	  and from the coresponding list (whitePowns or blackPowns list). It calls
	  the piece's specific destructor to free the allocated memory for the piece.*/
	bool removePown(Pown *toRemove); 

	/*This function converts a soldier pown to an other piece (except soldier and king).
	  The requested promotion type is given as an argument that is an enumeration. See
	  enum powntype for more details.*/
	bool convertPown(Pown *toConvert, enum powntype type);

	/*This function is responsible for moving a piece frin one position to another if
	  it is possible and legal. It also is responsible for complicated actions such as
	  the roke movement and attack movements. It alwasy checks if the requested movement
	  can be done. If the requested movement is not legal or posible it returns false.
	  Otherwise it returns true state. If the requested movement is an attack movement
	  then the threatened piece is removed form the chessboard and all the sructures and 
	  is inserted in the captured pieced list. Finally, it maintains a log list, in order
	  the chessboard to know what actions have been performed and in order the algorithm
	  to be able to cancel some of them.
	*/
	bool move(int x0,int y0,int x1,int y1);
	bool moveComputer(int x0,int y0,int x1,int y1);

	/*This funcyion checks if the given square in the chess board table is threatened
	  by the opponent team. The coordinates of the square are given by the first two arguments.
	  Argument 1 (int i) is the coordinate on the x axis and argument 2 (int y) is the
	  coordinate on the y axis. The 3rd argument is the oppenent team that might threaten
	  a square. See enum_ team and ChessBoard->board[][] for more details.*/
	bool squareIsThreatened(int i, int j, enum team_ tteam);

	/*This fucntions adds the roke movement in the list of the valid moves of the team that
	  is given by the argument. The getValidMoves() functions of the pieces do not
	  consider to add this movement in their returned lists. So every time the
	  ChessBoard::upgradeValidMoves() function is called his fucntion is called too.*/
	void addRokeMoves(enum team_ kingteam);

	/*This function upgrades the valid moves lists. Frees the current valid moves
	  lists and reconstructs them adding the new available valid moves. This function
      also calls the ChessBoard::removeKingThreatMoves() and ChessBoard::addRokeMoves()
	  function for both teams. This function uses the upgradeValidMovesSimple() function.*/
	void upgradeValidMoves(void);

	/*This function upgrades the valid moves lists for only the team that is given
	  as argument.*/
	void upgradeValidMoves(enum team_ tm);

	/*This function upgrades the valid moves lists. Frees the current valid moves
	  lists and reconstructs them adding the new available valid moves. this function
	  calls the ChessBoard::addRokeMoves() function for both teams.*/
	void upgradeValidMovesSimple(void);


	/* This function checks the current situation of the chessboard and the
	   peices and returns if it is Mat, Pet or Nothing. It is used to know
	   the state of the game. If it is Mat the above functions will know
	   which team has given the Mat, because they know the argument team they
	   had given in to this function.
	   Return values of this function:
	   1 (IS_MAT): is Mat
	   2 (IS_PAT): is Pat
	   0 (IS_OK): nothing*/
	unsigned char isMatOrPat(enum team_ team);

	/* This function checks if there is any piece of the team given (by the
	   argument) and returns true state if there is one. Otherwise
	   it returns false, meaning that there is not any piece that can be promoted
	   to another piece of the same team.*/
	bool ChessBoard::isPromote(enum team_ team);

	/*This function promotes the piece (soldier pawn) that has reached the 
	  end of the oppenent area. (Note that only one piece can be reach the end line
	  and be promoted each time.). This function removes the current piece of the
	  board and the internal lists and places another piece in the same position.
	  The type of the new pice is given by the 2nd argument. The team that has a piece
	  to promote is given by the 1st argument. See enum pownstatus and enum team_
	  for more details.*/
	void ChessBoard::promote(enum team_ team , enum powntype type);


	/*This function gets all the available valid moves for the given team (by the
	  argument) and returns a pointer to the constructed list. 
	  this function also removes all the movements that may lead to a threatening of the
	  king by the opponent team. It is fast, because it removes the king threatening
	  moves for each piece's valid moves list, during the construction of the
	  pownstatus structure. When a pownstatus is finally created it does not
	  contain any king threatening movement.
	  The return list is a list, of which each item is a pownstatus structure.
	  See struct pownstatus for more details. See also each pown's getValidMoves()
	  function. */
	DoubleLinkedList *getAllValidMoves(enum team_ t);

	/*This function gets all the available valid moves for the given team (by the
	  argument) and returns a pointer to the constructed list. The return list
	  is a list, of which each item is a pownstatus structure. See struct pownstatus
	  for more details. See also each pown's getValidMoves() function. */
	DoubleLinkedList *ChessBoard::getAllValidMovesSimple(enum team_ t);


	/*This function returns a list of the available valid moves of a specific piece
	 The coordinates of the piece in the chess board table are given by the arguments.
	 If there is not a piece in the corresponding square, the funcion will take
	 no action.*/
	DoubleLinkedList *getValidMoves(int x,int y);

	/*This function cancel the last movement that has been done.*/
	bool cancelLastMove(void);

	/*Enables the log file keeping*/
	void enableLogKeeping(void);

	/*Disables the log file keeping*/
	void disableLogKeeping(void);

	/*Returns a pointer to the captured pieces list.*/
	DoubleLinkedList *getCapturedList(void);

	DoubleLinkedList *getPownsList(enum team_ team);

	#define EQUALITY    0
	#define WHITE_AHEAD 1
	#define BLACK_AHEAD 2
	unsigned char getFirstCommingTeam(void);


	/*----------- Auxiliary class functions ---------------*/
	ChessBoard copy(void);
	void print(FILE *fp);
	void print(void);
	void printAllValidMoves(DoubleLinkedList *validPowns);
	/*-----------------------------------------------------*/
};

/*=========== End of Variables, Fuctions and Objects =====================*/

#endif
