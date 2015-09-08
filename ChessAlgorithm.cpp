/*|============================================================================|*
 *| Chess Application: file ChessAlgorithm.cpp                                 |*
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
#include "ChessAlgorithm.h"
#include <stdio.h>

#include <time.h>
/*================================================*/



int rateMoves01percentage;
int rateMoves02percentage;
int rateMoves03percentage;
int rateMoves00percentage;
int rateMove03x(ChessBoard *cboard, Pown *movedP);


int	rateBoard00percentage;
int	rateBoard01percentage;
int	rateBoard02percentage;
int	rateBoard03percentage;
int	rateBoard04percentage;






ChessAlgorithm::ChessAlgorithm(ChessBoard *cboard, enum team_ ateam)
{
	brd = new ChessBoard(cboard->board);
	team = ateam;
	maxSteps = 3;

	initializePieceValues();
	initializeRates();
	brd->upgradeValidMoves();
	exchange=true;
}

ChessAlgorithm::~ChessAlgorithm()
{
	delete brd;
}


void ChessAlgorithm::initializePieceValues(void)
{
	queenValue   = DEFAULT_QUEEN_VALUE;
	rockValue    = DEFAULT_ROCK_VALUE;
	bishopValue  = DEFAULT_BISHOP_VALUE;
	knightValue  = DEFAULT_KNIGHT_VALUE;
	soldierValue = DEFAULT_SOLDIER_VALUE;
	kingValue    = DEFAULT_KING_VALUE;
}

int ChessAlgorithm::getPownValue(Pown *p)
{
	switch (p->getType())
	{
	case SOLDIER:
		return soldierValue;
		break;
	case ROCK:
		return rockValue;
		break;
	case QUEEN:
		return queenValue;
		break;
	case BISHOP:
		return bishopValue;
		break;
	case KNIGHT:
		return knightValue;
		break;
	default:
		return 0;
		break;
	}
}

int ChessAlgorithm::rateMove00(ChessBoard *cboard,int x0,int y0,int x1,int y1)
{
	int res=0;
	if(cboard->board[x1][y1]!=NULL)
	{
		switch(cboard->board[x0][y0]->getType())
		{
			case SOLDIER:
				res -= 1; 
				break;
			case BISHOP:
				res -= 3;
				break;
			case ROCK:
				res -= 4;
				break;
			case KING:
				res -= 9;
				break;
			case QUEEN:
				res -= 9;
				break;
			case KNIGHT:
				res -= 3;
			break;
		}
	
		switch(cboard->board[x1][y1]->getType())
		{
			case SOLDIER:
				res += 1; 
				break;
			case BISHOP:
				res += 3;
				break;
			case ROCK:
				res += 4;
				break;
			case KING:
				res += 9;
				break;
			case QUEEN:
				res += 9;
				break;
			case KNIGHT:
				res += 3;
			break;
		}
		res+=9;
		if (res==0) res = 1;
	}

	return (res*100)/18 ;
}

/* This function calculates how many squares are controlled by the
 * algorithm's team and returns a rate according the number of
 * controlled squares. Rate [-100, 100].
 */
int ChessAlgorithm::rateMove01(ChessBoard *cboard, Pown *movedP)
{
	int threatCnt=0;
	int i,isz;
	int res;

	DoubleLinkedList * lst;
	lst=cboard->getAllValidMoves(movedP->getTeam());
	isz=DoubleLinkedListGetSize(lst);
	for(i=0;i<isz;i++)
	{
		threatCnt+=DoubleLinkedListGetSize(((struct pownstatus *)DoubleLinkedListGet(lst,i))->validMoves);
	}

	res = (threatCnt*100)/64;
	return res;
}

int ChessAlgorithm::rateMove02(ChessBoard *cboard, Pown *movedP)
{
	int i, isz;
	int res;
	DoubleLinkedList *lst;

	lst = movedP->getValidMoves(cboard->board);
	
	isz = DoubleLinkedListGetSize(lst);

	res=0;
	for (i=0;i<isz;i++)
	{
		struct point *pt;

		pt = (struct point *)DoubleLinkedListGet(lst,i);

		if (cboard->board[pt->x][pt->y]!=NULL)
		{
			if (cboard->board[pt->x][pt->y]->getTeam()!=movedP->getTeam())
			{
				switch (cboard->board[pt->x][pt->y]->getType())
				{
				case SOLDIER:
					res += 1; 
					break;
				case BISHOP:
					res += 3;
					break;
				case ROCK:
					res += 4;
					break;
				case KING:
					res += 9;
					break;
				case QUEEN:
					res += 9;
					break;
				case KNIGHT:
					res += 3;
					break;
				}
			}
		}
		free(pt);
	}

	if (res>22)
	{
		res = 22;
	}

	res = (res*100)/22;

	DoubleLinkedListDrop(lst);
	return res;
}

int ChessAlgorithm::rateMove03(ChessBoard *cboard, Pown *movedP)
{
	int i ,j;
	int res=0;
	int flg=0;
	
	for(j=0;j<BOARD_Y;j++)
	{
		for(i=0;i<BOARD_X;i++)
		{
			if(cboard->board[i][j]!=NULL)
			{
				if(cboard->board[i][j]->getTeam()==movedP->getTeam())
				{
					int r1;
					r1=rateMove03x(cboard, cboard->board[i][j]);
					if(r1<0)
					{
						if(flg==0)
						{
							res=r1;
						}else
						{
							res+=r1;
						}
						flg=1;

					}
					if(flg==0)
						res+=r1;

				}
			}
		}
	}
	return res;
}
int rateMove03x(ChessBoard *cboard, Pown *movedP)
{
	int res;
	int mres;
	int cntres;
	int i, isz, j, jsz;

	DoubleLinkedList *lst;
	res=0;
	mres=0;
	cntres=0;
	if (movedP->getTeam()==BLACK)
	{
		lst = cboard->getAllValidMoves(WHITE);
	}else
	{
		lst = cboard->getAllValidMoves(BLACK);
	}
	isz = DoubleLinkedListGetSize(lst);
	for(i=0;i<isz;i++)
	{
		struct pownstatus *ps;
		ps = (struct pownstatus *)DoubleLinkedListGet(lst, i);

		jsz = DoubleLinkedListGetSize(ps->validMoves);
		for(j=0;j<jsz;j++)
		{
			struct point *pt;
			pt = (struct point *)DoubleLinkedListGet(ps->validMoves, j);

			if (cboard->board[pt->x][pt->y]!=NULL)
			{
				if ((movedP->getPoint())->x==pt->x && (movedP->getPoint())->y==pt->y)
				{
					switch (ps->currentPown->getType())
					{
					case SOLDIER:
						res += 1; 
						break;
					case BISHOP:
						res += 3;
						break;
					case ROCK:
						res += 4;
						break;
					case KING:
						res += 9;
						break;
					case QUEEN:
						res += 9;
						break;
					case KNIGHT:
						res += 3;
						break;					
					}
					cntres--;
				}
			}
		}	
	}
	if (movedP->getTeam()==WHITE)
	{
		lst = cboard->getAllValidMoves(WHITE);
	}else
	{
		lst = cboard->getAllValidMoves(BLACK);
	}
	isz = DoubleLinkedListGetSize(lst);
	for(i=0;i<isz;i++)
	{
		struct pownstatus *ps;
		ps = (struct pownstatus *)DoubleLinkedListGet(lst, i);

		jsz = DoubleLinkedListGetSize(ps->validMoves);
		for(j=0;j<jsz;j++)
		{
			struct point *pt;
			pt = (struct point *)DoubleLinkedListGet(ps->validMoves, j);

			if (cboard->board[pt->x][pt->y]!=NULL)
			{
				if ((movedP->getPoint())->x==pt->x && (movedP->getPoint())->y==pt->y)
				{
					switch (ps->currentPown->getType())
					{
					case SOLDIER:
						res += 9; 
						break;
					case BISHOP:
						res += 5;
						break;
					case ROCK:
						res += 4;
						break;
					case KING:
						res += 0;
						break;
					case QUEEN:
						res += 1;
						break;
					case KNIGHT:
						res += 5;
						break;					
					}
					cntres++;
				}
			}
		}	
	}
	mres=0;
	switch(movedP->getType())
	{
		case SOLDIER:
			res += 9; 
			mres=-1;
			break;
		case BISHOP:
			res += 5;
			mres=-3;
			break;
		case ROCK:
			res += 4;
			mres=-4;
			break;
		case KING:
			res += 0;
			mres=-9;
			break;
		case QUEEN:
			res += 1;
			mres=-9;
			break;
		case KNIGHT:
			res += 5;
			mres=-3;
			break;	
	}
	if(cntres>0)
	{
			
	}
	else if(cntres==0)
	{
		res=0;
	}
	else
	{
		res=mres;
	}
	return res;

}


int ChessAlgorithm::rateMove04(ChessBoard *cboard, Pown *movedP)
{
	int res=0;
	if(movedP->getTeam()==WHITE)
	{
		if(cboard->isMatOrPat(BLACK)==IS_MAT)
		{
			res=5000;
		}
	}
	else
	{
		if(cboard->isMatOrPat(WHITE)==IS_MAT)
		{
			res=5000;
		}

	}
	return res;
}



void ChessAlgorithm::rateMoves(void)
{
DoubleLinkedList *lst;
	int i, isz, j, jsz;
	int *rate;

	lst = brd->getAllValidMoves(team);
	
	isz = DoubleLinkedListGetSize(lst);
	for (i=0;i<isz;i++)
	{
		struct pownstatus *ps;
		ps = (struct pownstatus *)DoubleLinkedListGet(lst,i);

		jsz = DoubleLinkedListGetSize(ps->validMoves);	
		for (j=0; j<jsz; j++)
		{
			ChessBoard *tmp;
			int preRate;
			struct point *pt;
			tmp = new ChessBoard(brd->board);
			pt = (struct point *)DoubleLinkedListGet(ps->validMoves, j);

			preRate=rateMove00(tmp,ps->currentPosition.x, ps->currentPosition.y,pt->x,pt->y);
			
			if (tmp->move(ps->currentPosition.x, ps->currentPosition.y,pt->x,pt->y)==false)
			{
			//	printf("\nDen egine!!!");
				break;
			}
			rate = (int *)DoubleLinkedListGet(ps->validMovesRate,j);
			tmp->upgradeValidMoves();
			*rate=0;
			(*rate) += (rateMoves03percentage*rateMove03(tmp,tmp->getPown(pt->x,pt->y)))/100;
				if(*rate>=0)
				{
				//	printf("\nepithesi!!!Amintiko Rate:%d",*rate);
					(*rate) += (rateMoves01percentage*rateMove01(tmp,tmp->getPown(pt->x,pt->y)))/100;
					(*rate) += (rateMoves02percentage*rateMove02(tmp,tmp->getPown(pt->x,pt->y)))/100;
					(*rate)	+= (rateMoves00percentage*preRate)/100;
				}
			(*rate) += (rateMoves03percentage*rateMove04(tmp,tmp->getPown(pt->x,pt->y)));					
		/*	{
				tmp->print();
				printf("\nrate:%d\n",*rate);
			}*/
			delete tmp;
		}
	}	
		//	printf("===============================\n");
}

int ChessAlgorithm::rateBoard00(ChessBoard *cboard, enum team_ team)
{
	DoubleLinkedList * lst;
	int res=0;
	int i,isz;
	lst=cboard->getPownsList(team);
	isz=DoubleLinkedListGetSize(lst);
	for(i=0;i<isz;i++)
	{
		Pown *p;
		p=(Pown *)DoubleLinkedListGet(lst,i);
		res+=getPownValue(p);
	}
	return res;
}

int ChessAlgorithm::rateBoard01(ChessBoard *cboard, enum team_ tteam)
{
	int res=0;
	DoubleLinkedList *lst;
	if(tteam==WHITE)
	{
		lst=cboard->getAllValidMoves(BLACK);
	}
	else
	{
		lst=cboard->getAllValidMoves(BLACK);
	}
	res-=DoubleLinkedListGetSize(lst);
	
	return res;
}

int ChessAlgorithm::rateBoard02(ChessBoard *cboard, enum team_ tteam)
{
	int res=0;
	int i, isz;
	DoubleLinkedList *opponentPieces;

	if (tteam==WHITE)
	{
		opponentPieces = cboard->getPownsList(BLACK);
	}else
	{
		opponentPieces = cboard->getPownsList(WHITE);
	}
	
	res = 0;
	isz = DoubleLinkedListGetSize(opponentPieces);
	for (i=0;i<isz;i++)
	{
		Pown *pwn;
		pwn = (Pown *)DoubleLinkedListGet(opponentPieces, i);

		if (cboard->squareIsThreatened(pwn->getPoint()->x,pwn->getPoint()->y,tteam)==true)
		{	
			res += getPownValue(pwn); 
		}
	}

	return res;
}



int ChessAlgorithm::rateBoard03(ChessBoard *cboard, enum team_ tteam)
{
	int res=0;
	return res;
}

int ChessAlgorithm::rateBoard04(ChessBoard *cboard, enum team_ tteam)
{
	int res=0;
	return res;
}
void ChessAlgorithm::initializeRates(void)
{
	rateBoard00percentage =30;
	rateBoard01percentage =20;
	rateBoard02percentage =10;
	rateBoard03percentage =10;
	rateBoard04percentage =10;
	/*Amina*/
	rateMoves03percentage = 90;
	/*Epithesi*/
	rateMoves00percentage = 70;
		
	rateMoves01percentage = 30;
	rateMoves02percentage = 0;
}
int ChessAlgorithm::rateBoard(ChessBoard *cboard, enum team_ curTeam)
{
	register int rate;
	rate=0;
	//printf("\n\trateBoard(): bhka");
	rate+=rateBoard00percentage*rateBoard00(cboard,curTeam);
	rate+=rateBoard01percentage*rateBoard01(cboard,curTeam);
	//rate+=rateBoard02percentage*rateBoard02(cboard,curTeam);
	//rate+=rateBoard03(cboard,curTeam);
	//rate+=rateBoard04percentage*rateBoard04(cboard,curTeam);
	return rate;
}
struct bestmove *ChessAlgorithm::getBestMove(void)
{
	int max;
	struct bestmove *result;
	DoubleLinkedList *lst;
	int i, isz, j, jsz;
	bool fistTime=true;

	initializeRates();
	rateMoves();

	lst = brd->getAllValidMoves(team);
	isz = DoubleLinkedListGetSize(lst);
	result = new struct bestmove();
	
	for (i=0;i<isz;i++)
	{
		struct pownstatus *ps;

		ps = (struct pownstatus *)DoubleLinkedListGet(lst, i);
		jsz = DoubleLinkedListGetSize(ps->validMovesRate);
		for(j=0;j<jsz;j++)
		{
			if (fistTime==true)
			{
				max = (*(int *)DoubleLinkedListGet(ps->validMovesRate,j));
				fistTime=false;
			}

			if (max<=(*(int *)DoubleLinkedListGet(ps->validMovesRate,j)))
			{
				max=(*(int *)DoubleLinkedListGet(ps->validMovesRate,j));
				result->x0 = ps->currentPosition.x;
				result->y0 = ps->currentPosition.y;
				result->x1 = ((struct point *)DoubleLinkedListGet(ps->validMoves,j))->x;
				result->y1 = ((struct point *)DoubleLinkedListGet(ps->validMoves,j))->y;
				result->rate = max;
			}
		}
	}

	return result;
}




struct bestmove *ChessAlgorithm::getBestMoveWithSteps(int startStep)
{
	struct bestmove *result;
	time_t secs1, secs2;

	min_limit = -1000000;
	max_limit =  1000000;
	secs1 = time(NULL);
	result = getBestMoveWithSteps(brd, startStep+1);
	secs2 = time(NULL);

	fprintf(stdout, "\nAgorihtm played with time: %d", secs2-secs1);
	fprintf(stdout,"and rate: %d From:%d %d, To: %d %d", result->rate, result->x0, result->y0, result->x1, result->y1);
	return result;
}



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
struct bestmove *ChessAlgorithm::getBestMoveWithSteps(ChessBoard *cur, int startStep)
{
	struct bestmove *res=NULL;
	struct bestmove *result;
	int i, isz, j, jsz;
	DoubleLinkedList *lst;
	struct bestmove *cur_node;
	enum team_ curteam;
	enum team_ oppcurteam;
	bool alfa_beta_cut=false;

	if(startStep%2==1)
	{
		curteam = BLACK;
		oppcurteam = WHITE;
	}
	else
	{
		curteam = WHITE;
		oppcurteam = BLACK;
	}

	if (startStep>=maxSteps)		/*leaf*/
	{
		int rw ,rb;
		struct bestmove *res;
		/*upgradeValid Moves*/
		cur->upgradeValidMoves(oppcurteam);
		rw=rateBoard(cur,WHITE);
		rb=rateBoard(cur,BLACK);

		res=new struct bestmove();
		res->x0=0;
		res->x1=0;
		res->y0=0;
		res->y1=0;
		
		
		if(team==WHITE)	//GENIKO TEAM
		{
			res->rate=rw-rb;
		}
		else
		{
			res->rate=rb-rw;
		}

		if(res->rate>=1000000 || res->rate<=-1000000){
			fprintf(stderr, "Error: RATE on leaf: %d\n", res->rate);
		}
	/*	if(res->rate!=0)
		{
			printf("\nrate:%d",res->rate);
			cur->print();
		}*/
		return res;
	}

	/*Nodes that are not leaves.*/
	lst = cur->getAllValidMoves(curteam);

	isz = DoubleLinkedListGetSize(lst);
	for (i=0;i<isz;i++)
	{
		struct pownstatus *ps;
		ps = (struct pownstatus *)DoubleLinkedListGet(lst, i);
		jsz = DoubleLinkedListGetSize(ps->validMoves);
		if(jsz==0)
		{
			continue;
		}
		for (j=0;j<jsz;j++)
		{
			ChessBoard *tmp;
			struct point *pt;

						
			pt = (struct point *)DoubleLinkedListGet(ps->validMoves,j);
			//tmp = new ChessBoard(cur->board,ps->currentPosition.x,ps->currentPosition.y,pt->x,pt->y);
			tmp = new ChessBoard(cur->board);
			tmp->moveComputer(ps->currentPosition.x,ps->currentPosition.y,pt->x,pt->y);
			tmp->upgradeValidMoves(oppcurteam);


			/*For the found possible movemets of the current state of the chessboard
				and the current team we are processing, call the same function to 
				calculate the next corresponding movements of the opponent team. Of course
				the current depth will be incresed by one.*/
			//if(res==NULL)	//Fist Time init max and min
			//{

				if(res==NULL && startStep%2==1){
					cur_node = (struct bestmove *)malloc(sizeof(struct bestmove));
					cur_node->rate = -1000000;
				}else if (res==NULL){
					cur_node = (struct bestmove *)malloc(sizeof(struct bestmove));
					cur_node->rate = 1000000;
				}
				res = getBestMoveWithSteps(tmp,startStep+1);
				res->x0 = ps->currentPosition.x;
				res->y0 = ps->currentPosition.y;
				res->x1 = pt->x;
				res->y1 = pt->y;
				/*max_node=res;
				min_node=res;*/
				//result = res;
			//}
			//else
			//{
			//	res = getBestMoveWithSteps(tmp,startStep+1);
			//	res->x0 = ps->currentPosition.x;
			//	res->y0 = ps->currentPosition.y;
			//	res->x1 = pt->x;
			//	res->y1 = pt->y;
			//	
			//	/*if(max_node->rate<=res->rate)
			//	{
			//		max_node=res;
			//	}
			//	if(min_node->rate>res->rate)
			//	{
			//		min_node=res;
			//	}*/

			//	/*Free the appropriate structure.*/
			//	/*if (startStep%2==0)
			//	{
			//		if (max_node!=res) delete res;
			//	}else
			//	{
			//		if (min_node!=res) delete res;
			//	}*/
			//}
			
			/*Alpha-Beta Pruning*/	
			
			if(startStep%2==0 && res->rate < min_limit){ //Prun the rest of the nodes
				cur_node = res;
				alfa_beta_cut = true;
				fprintf(stderr, "PRUN MIN\n");
				break;
			}
			if(startStep%2==1 && res->rate > max_limit){ //Prun the rest of the nodes
				cur_node = res;
				alfa_beta_cut = true;
				fprintf(stderr, "PRUN MAX\n");
				break;
			}
			if(startStep%2==1 && res->rate > cur_node->rate){ //Update min_limit
				fprintf(stderr, "UPDATE MIN\n");
				cur_node = res;
				min_limit = cur_node->rate;
			}else if(startStep%2==0 && res->rate < cur_node->rate){ //Update max_limit
				fprintf(stderr, "UPDATE MAX\n");
				cur_node = res;
				max_limit = cur_node->rate;
			}
			/*End of Alpha-Beta Pruning*/	
			delete tmp;
		}
		if(alfa_beta_cut==true)	
		{
			break;
		}
	}
	
	//if (startStep%2==0)
	//{
	//	if(res->rate>cur_node->rate){
	//		return res;
	//	}else{
	//		return cur_node;
	//	}
	//	//return max_node;
	//}else
	//{
	//	if(res->rate<cur_node->rate){
	//		return res;
	//	}else{
	//		return cur_node;
	//	}
	//	//return min_node;
	//}
	
	if(cur_node->rate>=1000000){
		return cur_node;
	}
	return cur_node;
}
