/*|============================================================================|*
 *| Chess Application: file ChessAlgorithm.h                                   |*
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

/*========== Other files used ====================*/
#include "ChessBoard2.h"
/*================================================*/

/*One step depth for the minimax algorithm. It is used by the ChessAlgorithm()
  constuctor.*/
#define SINGLE_STEP 1

/*Represents a move. This is obviously the best move that an evaluation function
  has found. Cntains the staring position of the moving piece and its end position.*/
struct bestmove {
	int x0;
	int y0;
	int x1;
	int y1;
};


/*This class represents an algorithm. Offers functions and individual propertines*/
class ChessAlgorithm 
{
private:
	ChessBoard *brd;
	enum team_ team; /*true = white, false = black*/
	int rateMove00(ChessBoard *cboard,int x0,int y0,int x1,int y1);
	int rateMove01(ChessBoard *cboard, Pown *movedP);
	int rateMove02(ChessBoard *cboard, Pown *movedP);
	int rateMove03(ChessBoard *cboard, Pown *movedP);
	int rateMove04(ChessBoard *cboard, Pown *movedP);
	void rateMoves(void);
	void initializeRates(void);

	int maxSteps;
	
public:
	ChessAlgorithm(ChessBoard *cboard, enum team_ ateam);
	struct bestmove *getBestMove(void);


	~ChessAlgorithm();	
};
