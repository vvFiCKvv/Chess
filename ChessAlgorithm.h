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
#include "ChessBoard.h"
/*================================================*/

/*One step depth for the minimax algorithm. It is used by the ChessAlgorithm()
  constuctor.*/
#define SINGLE_STEP 1

/*Multiplier that is used by the evaluation functions*/
#define ATACKED_BY_SMALLER_VALUE_MULTIPLIER 2

/*Define for the staring values of each piece type*/
#define DEFAULT_QUEEN_VALUE    9
#define DEFAULT_ROCK_VALUE     4
#define DEFAULT_BISHOP_VALUE   3
#define DEFAULT_KNIGHT_VALUE   3
#define DEFAULT_SOLDIER_VALUE  1
#define DEFAULT_KING_VALUE     1

/*Represents a move. This is obviously the best move that an evaluation function
  has found. COntains the rate of the move that was set by the evaluation functions
  the staring position of the moving piece and its end position.*/
struct bestmove {
	int x0;
	int y0;
	int x1;
	int y1;
	int rate;
};


/*This class represents an algorithm. Offers functions and individual propertines*/
class ChessAlgorithm 
{
private:
	/*Is the class ChessBoard instance that the algorithm processes
	  to get a best move.*/
	ChessBoard *brd;

	/*The team of the algorithm.*/
	enum team_ team; /*true = white, false = black*/
	int rateMove00(ChessBoard *cboard,int x0,int y0,int x1,int y1);
	int rateMove01(ChessBoard *cboard, Pown *movedP);
	int rateMove02(ChessBoard *cboard, Pown *movedP);
	int rateMove03(ChessBoard *cboard, Pown *movedP);
	int rateMove04(ChessBoard *cboard, Pown *movedP);
	void rateMoves(void);
	int rateBoard00(ChessBoard *cboard, enum team_ team);
	int rateBoard01(ChessBoard *cboard, enum team_ team);
	int rateBoard02(ChessBoard *cboard, enum team_ team);
	int rateBoard03(ChessBoard *cboard, enum team_ team);
	int rateBoard04(ChessBoard *cboard, enum team_ team);
	int rateBoard(ChessBoard *cboard, enum team_ curTeam);
	
	/*Initializes all rates lists to have their items set to 0.*/
	void initializeRates(void);

	/*this function initializes all the piece values (points) to the default
	  values.*/
	void initializePieceValues(void);

	/*this function returns the current value (points) of the piece
	  that is given as an argument. Values are kept in the variables
	  below.*/
	int getPownValue(Pown *p);

	/*Flag variable that indicates whether an exchange of pieces in a movement
	  is suitable or not.*/
	bool exchange;

	/*Is the max depth that the minimax algorithm can run. It is set in the
	  class ChessAlgorithm constructor.*/
	int maxSteps;
	
	/*The minimum limit used by the Alpha-Beta pruning method.*/
	int min_limit;

	/*The maximum limit used by the Alpha-Beta pruning method.*/
	int max_limit;

	/*The below variables represent thet value (points) of each piece
	  type. It is used by the evaluation functions to calculate the rates.*/
	int queenValue;
	int rockValue;
	int bishopValue;
	int soldierValue;
	int knightValue;
	int kingValue;
		
public:
	/*Constructor of the class ChessAlgorithm. The first argument is an instance
	  of the class ChessBoard that the algorithm will process. The second argument
	  is the team of the algorithm.*/
	ChessAlgorithm(ChessBoard *cboard, enum team_ ateam);

	struct bestmove *getBestMove(void);
	struct bestmove *getWorstMove(void);
	struct bestmove *getBestMoveWithSteps(int startStep);

	/*This function is the implementation of the MiniMax algorithm. 
	  This is recycling function, which created the algorithm tree
	  containing all the possible movements and has a certain depth.
	  Uses Alpha-Beta pruning method to improve the MiniMax algorithm and
	  gain a good increase in the speed of the execution of the algorithm.
	  The leaves of the trees have a value that is given by both opponents
	  and a rate is determined. It means that if a rate is maximum it is
	  suitable for the one player and if it is minimum it is suitable for
	  the other player. The nodes of the tree take the minimum or the maximum
	  rate of their children, accornding to the depth they belong to. A node
	  can take only the minimum or the maximum rate of its children. The way that
	  a rate between those two is chosen is defined by the depth the node belongs to.
	  That way the first time the corresponding node will take the maximum, the next
	  time the corresponding node will take the minimu, the next the maximum...
	  and so on. Finally, following this algorithm we will have at the root of the 
	  tree the movemenet (rate) that is the best for both players. This is the
	  best move that the algorithm must return to play as best as it can.*/ 
	struct bestmove *getBestMoveWithSteps(ChessBoard *cur, int startStep);

	/*Destructor of class ChessAlgorithm*/
	~ChessAlgorithm();	
};
