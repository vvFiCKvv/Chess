/*|============================================================================|*
 *| Chess Application: file Pown.h                                             |*
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


/*============ Other files used =======================*/
#include "lib/DoubleLinkedList.h"
/*=====================================================*/

/*============ General Variables and Objects ========================*/

/*|---------------- position point structure -----------------|*
 *|This structure represetnts a point that is the position of |
 *|an object in the chessboard. It has two members:           |
 *|-> x: Integer number that is the coordinate in the x axis  |
 *|      Values can be between 0 and 6 if it is an 6x6        |
 *|      chessboard or between 0 and 6 if it is an 8x8        |
 *|      chessboard.                                          |
 *|-> y: Integer number that is the coordinate in the y axis. |
 *|      Values as above.                                     |
 *|-----------------------------------------------------------|*/
typedef struct point
{
	int x;
	int y;
}*Point;


/*This enumeration represents the team of an object in the chessboard
 *Teams can be: white or black */
enum team_ {WHITE, BLACK};

/*This enumeration represents the type of the piece in the chessboard
  If chessboard is 8x8 it can be soldier, king, queen, knight, rock or bishop
  If chessboard is 6x6 the bishop type is not used.*/
enum powntype {SOLDIER, KING, QUEEN, KNIGHT, ROCK, BISHOP};


/*This variable determines the the type of the chess board
  table in which the game will be played. The board is always
  initializes to 8x8 dimensions, but if this variable is
  6, then the game will occur in a subtable of it with
  6x6 dimensions. This is used to help us to develop a code
  in order to let the user ot choose which type of chess board
  he wants, by selecting it from the console window.*/
extern int boardSize;

/*These are the varaibles that determine if the chessboard will be 8x8 or 6x6
  Note that the chessboard is always a square.*/
#define BOARD_X boardSize
#define BOARD_Y BOARD_X

/*This variable is used to initialize the board table to 8x8 dimensions.
  The chess board table is always 8x8. Only the checking and the operations
  done to it differs between 6x6 and 8x8. To detect whitch type of game 
  is the current we use the above defines and variables. See above for
  more details.*/
#define BOARD_MAX 8




/*|-------------- class Pown ----------------------------------|
 *| This Class is an abstract interface that will be used      |*
 *| by the other specific class. That way we have, 5 more      |*
 *| specific class: King, Queen, Soldier, Knight, Rock         |*
 *| The specific classes of the pieces impelement some of      |*
 *| those virtual functions in the way that meets the requests |*
 *| and based on their individual properties.                  |*
 *|------------------------------------------------------------|*/
class Pown 
{
protected:
	/*Is the current position of the piece in the chessboard*/
	Point position;

	/*Is the current team of the piece*/
	enum team_ team;
	
public:
	/*Generic constructor for all types of objects*/
	 Pown(Point initPosition, enum team_ initTeam);

	 /*Generic constructor for all types of objects*/
	 Pown(void);

	/*Generic destructor for all types of objects*/
	 ~Pown(void);

	 /*Is the number of the times that it was moved in the chessboard
	   from the beginning of the game. It is used to check if the <<roke>>
	   movement is valid at the current time.*/
	 int noOfMoves;

	 /*Gets the current team of the piece and returns it as an enumeration
	   See enum team_ for more details.*/
	 enum team_ getTeam(void);

	 /*Gets the current position of the piece in the chessboard table and 
	   returns it as a point structure. See struct point for more details.*/
	 Point  getPoint(void);

	 /*This function is responsible for changing only the current position
	   of the piece into the new one. It is used by the ChessBoard class. It
	   does not check if the requested movement is valid or not. This control
	   is performed by the ChessBoard::moveTo() function.
	   See ChessBoard::moveTo() for more details.*/
	 void movePownTo(int x, int y);

	 /*This function decreases the number of moves by one.
	   This is mainly used by the ChessBoard::cancellastAction() funtion.
	   See ChessBoard::cancelLastAction() function and Pown->noOfMoves
	   for more details*/
	 void decreaseNoOfMoves(void);

	 /*This function decreases the number of moves by the given integer.
	   This is mainly used by the ChessBoard::cancellastAction() funtion.
	   See ChessBoard::cancelLastAction() function and Pown->noOfMoves
	   for more details*/
	 void decreaseNoOfMoves(int num);

	 /*This is a virtual function that will be implemented by the specific
	   classes of the pieces at different ways for each type of piece. This 
	   function gets all the valid positions that the piece can be moved to.
	   It checks the chessboard's situation by taking as an argument the 
	   chessboar table. This checking of the situation of the
	   chessboard is performed in this level in favor of performance and
	   easier code development. This function allocated memory for the returnd
	   list and is in the above function's responsibility to free the allocated
	   memory. For more details see ChessBoard->board[][] and 
	   ChessBoard::getAllValidMoves().*/
 	 virtual DoubleLinkedList *getValidMoves(Pown *board[BOARD_MAX][BOARD_MAX]) = 0;

	 /*This function gets the current type of the pown and returns it as an
	   enumeration. See enum powntype for more details.*/	
	 virtual enum powntype getType(void)=0;

};

/*============= End of General Variables and Objects ==============================*/



/*======================== Specific Objects =======================================*/

/*|--class Bishop : innherits class Pown--|*
 *|Specific class for bishop object       |*
 *|---------------------------------------|*/
class Bishop : public Pown
{
public:
	Bishop(Point initPosition, enum team_ initTeam); 
	Bishop(void);

	DoubleLinkedList *getValidMoves(Pown *board[BOARD_MAX][BOARD_MAX]);
	enum powntype getType(void);
};

/*|--class Knight : innherits class Pown--|*
 *|Specific class for knight object       |*
 *|---------------------------------------|*/
class Knight : public Pown
{
public:
	Knight(Point initPosition, enum team_ initTeam);
	Knight(void);

	DoubleLinkedList *getValidMoves(Pown *board[BOARD_MAX][BOARD_MAX]);
	enum powntype getType(void);
};	



/*|--class Soldier : innherits class Pown--|*
 *|Specific class for soldier object       |*
 *|----------------------------------------|*/
class Soldier : public Pown
{
public:
	Soldier(Point initPosition, enum team_ initTeam);
	Soldier(void);

	DoubleLinkedList *getValidMoves(Pown *board[BOARD_MAX][BOARD_MAX]);
	enum powntype getType(void);
};

/*|--class Rock : innherits class Pown--|*
 *|Specific class for rock object       |*
 *|-------------------------------------|*/
class Rock : public Pown
{
public:
	Rock(Point initPosition, enum team_ initTeam);
	Rock(void);

	DoubleLinkedList *getValidMoves(Pown *board[BOARD_MAX][BOARD_MAX]);
	enum powntype getType(void);
};

/*|--class King : innherits class Pown--|*
 *|Specific class for king object       |*
 *|-------------------------------------|*/
class King : public Pown
{
public:
	King(Point initPosition, enum team_ initTeam);
	King(void);
	DoubleLinkedList *getValidMoves(Pown *board[BOARD_MAX][BOARD_MAX]);
	enum powntype getType(void);
};

/*|--class Queen : innherits class Pown--|*
 *|Specific class for queen object       |*
 *|--------------------------------------|*/
class Queen : public Pown
{
public:
	Queen(Point initPosition, enum team_ initTeam);
	Queen(void);

	DoubleLinkedList *getValidMoves(Pown *board[BOARD_MAX][BOARD_MAX]);
	enum powntype getType(void);
};

/*============= End of Specific Objects ====================================*/
