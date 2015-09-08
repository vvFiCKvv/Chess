/*|============================================================================|*
 *| Chess Application: file ChessBoard.cpp                                     |*
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
#include <stdio.h>
#include "ChessBoard.h"
/*================================================*/


bool ChessBoard::squareIsThreatened(int x, int y, enum team_ tteam)
{
	/*OLD CODE*/
	int i,isz;
	int j,jsz;
	
	DoubleLinkedList *p;
	p=getAllValidMoves(tteam);
	isz=DoubleLinkedListGetSize(p);

	for(i=0;i<isz;i++)
	{
		struct pownstatus *ps;
		ps=(struct pownstatus *)DoubleLinkedListGet(p,i);
		
		jsz=DoubleLinkedListGetSize(ps->validMoves);
		for(j=0;j<jsz;j++)
		{
			struct point *pt;
			pt=(struct point *)DoubleLinkedListGet(ps->validMoves,j);
			if(pt->x==x && pt->y==y)
			{
				return true;
			}
		}
	}
	return false;
	
}

void ChessBoard::addRokeMoves(enum team_ kingteam)
{
	int i;
	int teamside;
	if(kingteam==WHITE)
	{
		teamside=0;
	}
	else
	{
		teamside=BOARD_Y-1;
	}

	if(board[4][teamside]==NULL)
		return;
	
	if(board[4][teamside]->getType()!=KING || board[4][teamside]->noOfMoves!=0)
		return;

	if(board[0][teamside]!=NULL)	
	{
		if(board[0][teamside]->getType()==ROCK && board[0][teamside]->noOfMoves==0)
		{
			for(i=1;i<4;i++)
			{
				if(board[i][teamside]!=NULL)
				{
					break;
				}
			}
			if(i==4)
			{
				for(i=0;i<=4;i++)
				{
					if(kingteam==WHITE)
					{
						if(squareIsThreatened(i,teamside,BLACK)==true)
							break;
					}
					else
					{
						if(squareIsThreatened(i,teamside,WHITE)==true)
							break;
					}
					
				}
				if(i==5)
				{
					int isz;
					DoubleLinkedList *lst;
					lst=getAllValidMoves(kingteam);
					isz=DoubleLinkedListGetSize(lst);
					for(i=0;i<isz;i++)
					{
						struct pownstatus *ps;
						ps=(struct pownstatus *)DoubleLinkedListGet(lst,i);
						if(ps->currentPown->getType()==KING)
						{
							struct point *pt;
							int *a;
							
							pt=new struct point();
							
							a=new int();
							*a=0;
							pt->x=2;
							pt->y=teamside;
							
							DoubleLinkedListAddInTail(ps->validMoves,pt);
							DoubleLinkedListAddInTail(ps->validMovesRate,a);
							
							break;
								
						}
					}
				}
			}
		}
	}

	if(board[BOARD_X-1][teamside]!=NULL)
	{
		if(board[BOARD_X-1][teamside]->getType()==ROCK && board[BOARD_X-1][teamside]->noOfMoves==0)
		{
			for(i=5;i<BOARD_X-1;i++)
			{
				if(board[i][teamside]!=NULL)
				{
					break;
				}
			}
			if(i==BOARD_X-1)
			{
				for(i=4;i<BOARD_X;i++)
				{
					if(kingteam==WHITE)
					{
						if(squareIsThreatened(i,teamside,BLACK)==true)
							break;
					}
					else
					{
						if(squareIsThreatened(i,teamside,WHITE)==true)
							break;
					}
					
				}
				if(i==BOARD_X)
				{
					int isz;
					DoubleLinkedList *lst;
					lst=getAllValidMoves(kingteam);
					isz=DoubleLinkedListGetSize(lst);
					for(i=0;i<isz;i++)
					{
						struct pownstatus *ps;
						ps=(struct pownstatus *)DoubleLinkedListGet(lst,i);
						if(ps->currentPown->getType()==KING)
						{
							struct point *pt;
							int *a;
							pt=new struct point();
							a = new int();
							*a=0;
							pt->x=6;
							pt->y=teamside;
							DoubleLinkedListAddInTail(ps->validMoves,pt);
							DoubleLinkedListAddInTail(ps->validMovesRate,a);
							break;
						}
					}
				}
			}
		}
	}	
}



/*Constructor of the chessboard. It Allocates memory for variables and 
	  structures and initializes them. It uses the two initialization function.
	  It uses default values for several variables. All pieces are placed
	  as in a normal starting of a chess game.
	  For more details see initializeChessBoard6x6() and initializeChessBoard8x8()
	  functions.*/
ChessBoard::ChessBoard(void)
{
	enabledLogFile = false;
	if(BOARD_X==6)
	{
		initializeChessBoard6x6();
	}
	else if(BOARD_X==8)
	{
		initializeChessBoard8x8();
	}
	whiteValidMoves=NULL;
	whiteValidMoves=getAllValidMoves(WHITE);
	blackValidMoves=NULL;
	blackValidMoves=getAllValidMoves(BLACK);
}

/*Constructor of the chessboard. It Allocates memory for variables and 
	  structures and initializes them. It uses the two initialization function.
	  A board[][] is given as argument. In that way the pieces are placed as in the
	  given board.
	  For more details see initializeChessBoard6x6() and initializeChessBoard8x8()
	  functions.*/
ChessBoard::ChessBoard(Pown *pboard[BOARD_MAX][BOARD_MAX])
{
	int i,j;
	enabledLogFile = false;

	/*Allocate memory for all the used lists.*/
	whitePowns=DoubleLinkedListConstruct();
	blackPowns=DoubleLinkedListConstruct();
	logFile=DoubleLinkedListConstruct();
	capturedList=DoubleLinkedListConstruct();

	/*Places the pieces in the noard, according to the given board.*/
	for(j=0;j<BOARD_Y;j++)
	{
		for(i=0;i<BOARD_X;i++)
		{
			Pown *a=NULL;
			Pown *old;
			old=pboard[i][j];
			if(old==NULL)
			{
				board[i][j]=NULL;
				continue;
			}
			switch(old->getType())
			{
				case SOLDIER:
					{
						
						struct point tmp;
						tmp.x=old->getPoint()->x;
						tmp.y=old->getPoint()->y;
						a=new Soldier(&tmp,old->getTeam());
					}
				break;
				case BISHOP:
					{
						struct point tmp;
						tmp.x=old->getPoint()->x;
						tmp.y=old->getPoint()->y;
						a=new Bishop(&tmp,old->getTeam());
					}
				break;
				case KNIGHT:
					{
						struct point tmp;
						tmp.x=old->getPoint()->x;
						tmp.y=old->getPoint()->y;
						a=new Knight(&tmp,old->getTeam());
					}
				break;
				case ROCK:
					{	
						struct point tmp;
						tmp.x=old->getPoint()->x;
						tmp.y=old->getPoint()->y;
						a=new Rock(&tmp,old->getTeam());
			
					}
				break;
				case QUEEN:
					{
						struct point tmp;
						tmp.x=old->getPoint()->x;
						tmp.y=old->getPoint()->y;
						a=new Queen(&tmp,old->getTeam());
					}
				break;
				case KING:
					{
						struct point tmp;
						tmp.x=old->getPoint()->x;
						tmp.y=old->getPoint()->y;
						a=new King(&tmp,old->getTeam());
						if(old->getTeam()==WHITE)
						{
							whiteKing=a;
						}
						else
						{
							blackKing=a;
						}

					}
				break;
				default:
				break;
			}
			board[i][j]=a;
			if(old->getTeam()==WHITE)
			{
				DoubleLinkedListAddInTail(whitePowns,a);
			}
			else
			{
				DoubleLinkedListAddInTail(blackPowns,a);
			}
		}
	}

	/*Initialize lists and get all the simple valid moves.*/
	whiteValidMoves=NULL;
	whiteValidMoves=getAllValidMovesSimple(WHITE);
	blackValidMoves=NULL;
	blackValidMoves=getAllValidMovesSimple(BLACK);
}

ChessBoard::ChessBoard(Pown *pboard[BOARD_MAX][BOARD_MAX],int x0,int y0,int x1,int y1)
{
	int i,j;
	enabledLogFile = false;

	/*Allocate memory for all the used lists.*/
	whitePowns=DoubleLinkedListConstruct();
	blackPowns=DoubleLinkedListConstruct();
	logFile=DoubleLinkedListConstruct();
	capturedList=DoubleLinkedListConstruct();


	Pown *pwn;
	struct point *pt;
	pt = new struct point();
	pt->x = x1;
	pt->y = y1;
	
	switch(pboard[x0][y0]->getType())
	{
	case KING:
		pwn = new King(pt,pboard[x0][y0]->getTeam());
		if (pwn->getTeam()==WHITE)
		{
			whiteKing = pwn;
		}else
		{
			blackKing = pwn;
		}
		break;
	case QUEEN:
		pwn = new Queen(pt,pboard[x0][y0]->getTeam());
		break;
	case BISHOP:
		pwn = new Bishop(pt,pboard[x0][y0]->getTeam());
		break;
	case KNIGHT:
		pwn = new Knight(pt,pboard[x0][y0]->getTeam());
		break;
	case ROCK:
		pwn = new Rock(pt,pboard[x0][y0]->getTeam());
		break;
	case SOLDIER:
		pwn = new Soldier(pt,pboard[x0][y0]->getTeam());
		break;
	default:
		break;
	}
	pwn->noOfMoves--;
	board[x0][y0]=NULL;
	board[x1][y1]=pwn;
	if (pwn->getTeam()==WHITE)
	{
		DoubleLinkedListAddInTail(whitePowns, pwn);
	}else
	{
		DoubleLinkedListAddInTail(blackPowns, pwn);
	}


	/*Places the pieces in the noard, according to the given board.*/
	for(j=0;j<BOARD_Y;j++)
	{
		for(i=0;i<BOARD_X;i++)
		{
			if(board[i][j]==pwn || (i==x0 && j==y0)) 
			{
				continue;
			}else
			{
				Pown *a=NULL;
				Pown *old;
				old=pboard[i][j];
				if(old==NULL)
				{
					board[i][j]=NULL;
					continue;
				}
				switch(old->getType())
				{
					case SOLDIER:
						{
							
							struct point tmp;
							tmp.x=old->getPoint()->x;
							tmp.y=old->getPoint()->y;
							a=new Soldier(&tmp,old->getTeam());
						}
					break;
					case BISHOP:
						{
							struct point tmp;
							tmp.x=old->getPoint()->x;
							tmp.y=old->getPoint()->y;
							a=new Bishop(&tmp,old->getTeam());
						}
					break;
					case KNIGHT:
						{
							struct point tmp;
							tmp.x=old->getPoint()->x;
							tmp.y=old->getPoint()->y;
							a=new Knight(&tmp,old->getTeam());
						}
					break;
					case ROCK:
						{	
							struct point tmp;
							tmp.x=old->getPoint()->x;
							tmp.y=old->getPoint()->y;
							a=new Rock(&tmp,old->getTeam());
				
						}
					break;
					case QUEEN:
						{
							struct point tmp;
							tmp.x=old->getPoint()->x;
							tmp.y=old->getPoint()->y;
							a=new Queen(&tmp,old->getTeam());
						}
					break;
					case KING:
						{
							struct point tmp;
							tmp.x=old->getPoint()->x;
							tmp.y=old->getPoint()->y;
							a=new King(&tmp,old->getTeam());
							if(old->getTeam()==WHITE)
							{
								whiteKing=a;
							}
							else
							{
								blackKing=a;
							}

						}
					break;
					default:
					break;
				}

				board[i][j]=a;
				if(old->getTeam()==WHITE)
				{
					DoubleLinkedListAddInTail(whitePowns,a);
				}
				else
				{
					DoubleLinkedListAddInTail(blackPowns,a);
				}
			}
		}
	}

	whiteValidMoves=NULL;
	blackValidMoves=NULL;
	if (pboard[x0][y0]->getTeam()==WHITE)
	{
		whiteValidMoves=getAllValidMoves(BLACK);
		addRokeMoves(BLACK);
	}else
	{
		whiteValidMoves=getAllValidMoves(WHITE);
		addRokeMoves(WHITE);
	}
}

/*Destructor of the chessboard. Deallocates all used memory used by the
	  ChessBoard class.*/
ChessBoard::~ChessBoard()
{
	int i, isz;
	
	isz = DoubleLinkedListGetSize(whitePowns);
	for (i=0;i<isz;i++)
	{
		Pown *p;
		p = (Pown *)DoubleLinkedListGet(whitePowns, i);
		delete p;

	}
	DoubleLinkedListDrop(whitePowns);

	isz = DoubleLinkedListGetSize(blackPowns);
	for (i=0;i<isz;i++)
	{
		Pown *p;
		p = (Pown *)DoubleLinkedListGet(blackPowns, i);
		delete p;
	}
	DoubleLinkedListDrop(blackPowns);

	freeValidMovesLists();

	isz = DoubleLinkedListGetSize(capturedList);
	for (i=0;i<isz;i++)
	{
		delete (Pown *)DoubleLinkedListGet(capturedList, i);
	}
	DoubleLinkedListDrop(capturedList);

	isz = DoubleLinkedListGetSize(logFile);
	for (i=0;i<isz;i++)
	{
		delete (struct action *)DoubleLinkedListGet(logFile, i);
	}
	DoubleLinkedListDrop(logFile);	
}


/*This functions delallocates the memory that has been reserved for the
	  valid moves lists. It is used frequently, when updating the valid moves
	  lists.*/
void ChessBoard::freeValidMovesLists(void)
{
	int i,isz;
	int j,jsz;
	DoubleLinkedList *p;
	p=getAllValidMovesSimple(WHITE);
	isz=DoubleLinkedListGetSize(p);
	for(i=0;i<isz;i++)
	{
		struct pownstatus *ps;
		ps=(struct pownstatus *)DoubleLinkedListGet(p,i);
		
		jsz=DoubleLinkedListGetSize(ps->validMoves);
		
		for(j=0;j<jsz;j++)
		{
			struct point *pt;
			int *a;
			pt=(struct point *)DoubleLinkedListGet(ps->validMoves,j);
			a = (int *)DoubleLinkedListGet(ps->validMovesRate,j);
			if(a!=NULL) delete a;//free(a);
			if(pt!=NULL) delete pt;//free(pt);
		}
		DoubleLinkedListDrop(ps->validMoves);
		DoubleLinkedListDrop(ps->validMovesRate);
		if(ps!=NULL) delete ps;//free(ps);
	}
	DoubleLinkedListDrop(p);

	p=getAllValidMovesSimple(BLACK);
	isz=DoubleLinkedListGetSize(p);
	for(i=0;i<isz;i++)
	{
		struct pownstatus *ps;
		ps=(struct pownstatus *)DoubleLinkedListGet(p,i);
		
		jsz=DoubleLinkedListGetSize(ps->validMoves);
		for(j=0;j<jsz;j++)
		{
			struct point *pt;
			int *a;

			pt=(struct point *)DoubleLinkedListGet(ps->validMoves,j);
			a = (int *)DoubleLinkedListGet(ps->validMovesRate,j);
			if(a!=NULL) delete a;//free(a);
			if(pt!=NULL) delete pt;//free(pt);
		}
		DoubleLinkedListDrop(ps->validMoves);
		DoubleLinkedListDrop(ps->validMovesRate);
		if(ps!=NULL) delete ps ;//free(ps);
	}
	DoubleLinkedListDrop(p);
	blackValidMoves=NULL;
	whiteValidMoves=NULL;
}

/*This function returns a pointer to the piece that was found. Arguments
	  represent the position in the board[i][j] that we want to get the
	  piece pointer. i and j must not be negative or greater than the BOARD_X
	  and BOARD_Y defined variables.*/
Pown *ChessBoard::getPown(int i, int j)
{
	if(i<0||j<0 || i>BOARD_X|| j>BOARD_Y)
		return NULL;
	return board[i][j];
}

DoubleLinkedList *ChessBoard::getValidMoves(int x,int y)
{
	int i, isz;
	Pown *p;
	p=getPown(x,y);

	if (p==NULL) return NULL;

	if (p->getTeam()==WHITE)
	{
		isz = DoubleLinkedListGetSize(whiteValidMoves);
		for (i=0;i<isz;i++)
		{
			struct pownstatus *ps;

			ps = (struct pownstatus *)DoubleLinkedListGet(whiteValidMoves, i);
			if (ps->currentPown==p)
			{
				return ps->validMoves;
			}

		}
	}else
	{
		isz = DoubleLinkedListGetSize(blackValidMoves);
		for (i=0;i<isz;i++)
		{
			struct pownstatus *ps;

			ps = (struct pownstatus *)DoubleLinkedListGet(blackValidMoves, i);
			if (ps->currentPown==p)
			{
				return ps->validMoves;
			}
		}
	}

	return NULL;
}




/*This function initializes all variables and structures if the 
	  game is 6x6.*/
void ChessBoard::initializeChessBoard6x6(void)
{
	int i,j;
	DoubleLinkedList *teamPowns=NULL;
	whitePowns   = DoubleLinkedListConstruct();
	blackPowns   = DoubleLinkedListConstruct();
	logFile      = DoubleLinkedListConstruct();
	capturedList = DoubleLinkedListConstruct();


	/*Initialization of the board. This loop is used only in the
	  initialization of the 6x6 chess board table, in order to avoid
	  illegal actions and errors in the execution of the application
	  if there is any action occured in the table squares outside the 
	  6x6 dimensions.*/
	for (i=BOARD_X;i<BOARD_MAX;i++)
	{
		for (j=BOARD_Y;j<BOARD_MAX;j++)
		{
			board[i][j] = NULL;
		}
	}

	/*Algorithm for placing the pieces in their right positions in the
	  chess board table. If a square does not contain a piece it is
	  set to NULL.*/
	for(j=0;j<BOARD_Y;j++)
	{
		for(i=0;i<BOARD_X;i++)
		{
			struct point tmp;
			tmp.x=i;
			tmp.y=j;
			enum team_ myteam = WHITE;
			if(j<=1)
			{
				myteam=WHITE;
				teamPowns=whitePowns;
			}
			else if(j>=BOARD_Y-2)
			{
				myteam=BLACK;
				teamPowns=blackPowns;
			}

			if(j==1 || j==BOARD_Y-2)
			{
				board[i][j] = new Soldier(&tmp,myteam);
			}
			else if(j==0 || j==BOARD_Y-1)
			{
				if(i==0||i==BOARD_X-1)
				{
					board[i][j] = new Rock(&tmp,myteam);
				}else if(i==1|| i==BOARD_X-2)
				{
					board[i][j] = new Knight(&tmp,myteam);
				}
				else if(i==BOARD_X - 3 )
				{
					board[i][j] = new Queen(&tmp,myteam);
				}
				else
				{
					board[i][j] = new King(&tmp,myteam);
					if(myteam==WHITE)
					{
						whiteKing=board[i][j];
					}
					else
					{
						blackKing=board[i][j];
					}
				}
			}
			else
			{
				board[i][j] = NULL;
			}
			if(board[i][j]!=NULL)
			{
				DoubleLinkedListAddInTail(teamPowns,board[i][j]);
			}
		}
	}

}


/*This function initializes all variables and structures if the 
	  game is 8x8.*/
void ChessBoard::initializeChessBoard8x8(void)
{
	int i,j;
	DoubleLinkedList *teamPowns=NULL;
	whitePowns   = DoubleLinkedListConstruct();
	blackPowns   = DoubleLinkedListConstruct();
	logFile      = DoubleLinkedListConstruct();
	capturedList = DoubleLinkedListConstruct();

	for(j=0;j<BOARD_Y;j++)
	{
		for(i=0;i<BOARD_X;i++)
		{
			struct point tmp;
			tmp.x=i;
			tmp.y=j;
			enum team_ myteam=WHITE;
			if(j<=1)
			{
				myteam=WHITE;
				teamPowns=whitePowns;
			}
			else if(j>=BOARD_Y-2)
			{
				myteam=BLACK;
				teamPowns=blackPowns;
			}

			if(j==1 || j==BOARD_Y-2)
			{
				board[i][j] = new Soldier(&tmp,myteam);
			}
			else if(j==0 || j==BOARD_Y-1)
			{
				if(i==0||i==BOARD_X-1)
				{
					board[i][j] = new Rock(&tmp,myteam);
				}else if(i==1|| i==BOARD_X-2)
				{
					board[i][j] = new Knight(&tmp,myteam);
				}
				else if(i==BOARD_X - 5)
				{
					board[i][j] = new Queen(&tmp,myteam);
				}
				else if(i==2 || i==BOARD_X-3)
				{
					board[i][j] = new Bishop(&tmp,myteam);
				}
				else
				{
					board[i][j] = new King(&tmp,myteam);
					if(myteam==WHITE)
					{
						whiteKing=board[i][j];
					}
					else
					{
						blackKing=board[i][j];
					}
				}
			}
			else
			{
				board[i][j] = NULL;
			}
			if(board[i][j]!=NULL)
			{
				DoubleLinkedListAddInTail(teamPowns,board[i][j]);
			}
		}
	}
}

void ChessBoard::upgradeValidMovesSimple(void)
{	
	freeValidMovesLists();

	whiteValidMoves=NULL;
	whiteValidMoves=getAllValidMovesSimple(WHITE);

	blackValidMoves=NULL;
	blackValidMoves=getAllValidMovesSimple(BLACK);

//	addRokeMoves(WHITE);
//	addRokeMoves(BLACK);
}

bool ChessBoard::moveComputer(int x0,int y0,int x1,int y1)
{
	int sz;
	int i;
	DoubleLinkedList *lst=NULL;
	bool flg;
	struct action *act;
	

	if(x0<0 || y0<0 || x1<0 || y1<0  || x0>=BOARD_X || y0>=BOARD_Y || x1>=BOARD_X || y1>=BOARD_Y || board[x0][y0]==NULL )
		return false;
	
	

	if (enabledLogFile==true)
	{
		act=new struct action();
		act->actionType=SIMPLE_ACT;
		act->fromPosition.x=x0;
		act->fromPosition.y=y0;
		act->toPosition.x=x1;
		act->toPosition.y=y1;
		act->team=board[x0][y0]->getTeam();
		act->attacked=NULL;
	}

	flg = false;
	
	if (board[x1][y1]!=NULL)
	{
		if (board[x0][y0]->getTeam() == WHITE)
		{
			int j, jsz;
			jsz = DoubleLinkedListGetSize(blackPowns);
			for (j=0;j<jsz;j++)
			{
				if (((Pown *)DoubleLinkedListGet(blackPowns, j))->getPoint()->x==x1 && ((Pown *)DoubleLinkedListGet(blackPowns, j))->getPoint()->y==y1)
				{
					/*Add the attacked piece in the capturedList*/
					DoubleLinkedListAddInTail(capturedList,board[x1][y1]);
						
					if (enabledLogFile==true) act->attacked=board[x1][y1];
							
					DoubleLinkedListDel(blackPowns, j);
					j--;
					jsz--;
					break;
				}
			}
		}else
		{
			int j, jsz;
			jsz = DoubleLinkedListGetSize(whitePowns);
			for (j=0;j<jsz;j++)
			{
				if (((Pown *)DoubleLinkedListGet(whitePowns, j))->getPoint()->x==x1 && ((Pown *)DoubleLinkedListGet(whitePowns, j))->getPoint()->y==y1)
				{
					/*Add the attacked piece in the capturedList*/
					DoubleLinkedListAddInTail(capturedList,board[x1][y1]);
					if (enabledLogFile==true) act->attacked=board[x1][y1];
					
					DoubleLinkedListDel(whitePowns, j);
					j--;
					jsz--;
				}
			}
		}
	}
	if(board[x0][y0]->getType()==KING)
	{
		if(x1-x0==2 || x0-x1==2)
		{
			if(x1>x0)
			{
				board[BOARD_X-1][y0]->movePownTo(x1-1,y1);
				board[x1-1][y1] = board[BOARD_X-1][y0];
				board[BOARD_X-1][y0] = NULL;
					/*Action is kingside roke movement.*/
				if (enabledLogFile==true) act->actionType=KING_ROKE_ACT;			
			}
			else
			{
				board[0][y0]->movePownTo(x1+1,y1);
				board[x1+1][y1] = board[0][y0];
				board[0][y0] = NULL;
		
				/*Action is queenside roke movement.*/
				if (enabledLogFile==true) act->actionType=QUEEN_ROKE_ACT;
			}
		}
	}
	board[x0][y0]->movePownTo(x1, y1);
	board[x1][y1] = board[x0][y0];
	board[x0][y0] = NULL;
	flg= true;
	/*A move was succesful; add the coresponding action to the
	  logFile list.*/
	if (enabledLogFile==true) DoubleLinkedListAddInTail(logFile,act);
	return flg;
}



bool ChessBoard::move(int x0,int y0,int x1,int y1)
{
	int sz;
	int i;
	DoubleLinkedList *lst=NULL;
	struct point *tmp;
	bool flg;
	struct action *act;
	

	if(x0<0 || y0<0 || x1<0 || y1<0  || x0>=BOARD_X || y0>=BOARD_Y || x1>=BOARD_X || y1>=BOARD_Y || board[x0][y0]==NULL )
		return false;
	
	sz=DoubleLinkedListGetSize(getAllValidMoves(board[x0][y0]->getTeam()));
	
	for(i=0;i<sz;i++)
	{
		struct pownstatus *ps;
		ps=(struct pownstatus *)DoubleLinkedListGet(getAllValidMoves(board[x0][y0]->getTeam()),i);
		if((ps->currentPown->getPoint()->x==getPown(x0,y0)->getPoint()->x)&&(ps->currentPown->getPoint()->y==getPown(x0,y0)->getPoint()->y))
		{
			lst = ps->validMoves;
			break;
		}
	}
	
	if (lst==NULL) return false;

	if (enabledLogFile==true)
	{
		act=new struct action();
		act->actionType=SIMPLE_ACT;
		act->fromPosition.x=x0;
		act->fromPosition.y=y0;
		act->toPosition.x=x1;
		act->toPosition.y=y1;
		act->team=board[x0][y0]->getTeam();
		act->attacked=NULL;
	}

	flg = false;
	sz = DoubleLinkedListGetSize(lst);
	for (i=0;i<sz;i++)
	{
		tmp = (struct point *)DoubleLinkedListGet(lst, i);
		if (tmp->x==x1 && tmp->y==y1)
		{
			if (board[x1][y1]!=NULL)
			{
				if (board[x0][y0]->getTeam() == WHITE)
				{
					int j, jsz;
					jsz = DoubleLinkedListGetSize(blackPowns);
					for (j=0;j<jsz;j++)
					{
						if (((Pown *)DoubleLinkedListGet(blackPowns, j))->getPoint()->x==x1 && ((Pown *)DoubleLinkedListGet(blackPowns, j))->getPoint()->y==y1)
						{
							/*Add the attacked piece in the capturedList*/
							DoubleLinkedListAddInTail(capturedList,board[x1][y1]);
							
							if (enabledLogFile==true) act->attacked=board[x1][y1];
							
							DoubleLinkedListDel(blackPowns, j);
							j--;
							jsz--;
							break;
						}
					}
				}else
				{
					int j, jsz;
					jsz = DoubleLinkedListGetSize(whitePowns);
					for (j=0;j<jsz;j++)
					{
						if (((Pown *)DoubleLinkedListGet(whitePowns, j))->getPoint()->x==x1 && ((Pown *)DoubleLinkedListGet(whitePowns, j))->getPoint()->y==y1)
						{
							/*Add the attacked piece in the capturedList*/
							DoubleLinkedListAddInTail(capturedList,board[x1][y1]);

							if (enabledLogFile==true) act->attacked=board[x1][y1];
							
							DoubleLinkedListDel(whitePowns, j);
							j--;
							jsz--;
							break;
						}
					}
				}
			}
			if(board[x0][y0]->getType()==KING)
			{
				if(x1-x0==2 || x0-x1==2)
				{
					if(x1>x0)
					{
						board[BOARD_X-1][y0]->movePownTo(x1-1,y1);
						board[x1-1][y1] = board[BOARD_X-1][y0];
						board[BOARD_X-1][y0] = NULL;

						/*Action is kingside roke movement.*/
						if (enabledLogFile==true) act->actionType=KING_ROKE_ACT;			
					}
					else
					{
						board[0][y0]->movePownTo(x1+1,y1);
						board[x1+1][y1] = board[0][y0];
						board[0][y0] = NULL;
				
						/*Action is queenside roke movement.*/
						if (enabledLogFile==true) act->actionType=QUEEN_ROKE_ACT;
					}
				}
			}
			board[x0][y0]->movePownTo(x1, y1);
			board[x1][y1] = board[x0][y0];
			board[x0][y0] = NULL;
			flg= true;

			/*A move was succesful; add the coresponding action to the
			  logFile list.*/
			if (enabledLogFile==true) DoubleLinkedListAddInTail(logFile,act);
			break;
		}
	}
	return flg;
}



void ChessBoard::upgradeValidMoves(void)
{
	freeValidMovesLists();

	whiteValidMoves=NULL;
	whiteValidMoves=getAllValidMoves(WHITE);

	blackValidMoves=NULL;
	blackValidMoves=getAllValidMoves(BLACK);	

	addRokeMoves(WHITE);
	addRokeMoves(BLACK);
}
void ChessBoard::upgradeValidMoves(enum team_ tm)
{
	freeValidMovesLists();
	if(tm=WHITE)
	{
		whiteValidMoves=NULL;
		whiteValidMoves=getAllValidMoves(WHITE);
		addRokeMoves(WHITE);
	}
	else
	{
		blackValidMoves=NULL;
		blackValidMoves=getAllValidMoves(BLACK);
		addRokeMoves(BLACK);
	}
}


DoubleLinkedList *ChessBoard::getAllValidMoves(enum team_ t)
{
	DoubleLinkedList *lst;
	DoubleLinkedList *teamPowns;
	int size,i, j, jsz;
	int kingX, kingY, tmpX, tmpY;
	bool flg;
	ChessBoard *tmp;
	kingX=kingY=tmpX=tmpY=0;

	switch (t)
	{
	case WHITE:
		{
			teamPowns=whitePowns;
			/*Get the king of the white team.*/
			kingX=whiteKing->getPoint()->x;
			kingY=whiteKing->getPoint()->y;
			tmpX = kingX;
			tmpY = kingY;

			if(whiteValidMoves!=NULL)
				return whiteValidMoves;
			break;
		}
	case BLACK:
		{
			/*Get the king of the white team.*/
			kingX=blackKing->getPoint()->x;
			kingY=blackKing->getPoint()->y;
			tmpX = kingX;
			tmpY = kingY;

			if(blackValidMoves!=NULL)
				return blackValidMoves;
			teamPowns=blackPowns;
			break;
		}
	default:
		return  NULL;
		break;
		
	}
	lst = DoubleLinkedListConstruct();
	size=DoubleLinkedListGetSize(teamPowns);
	for(i=0;i<size;i++)
	{
		struct pownstatus * p;
		
		p= new struct pownstatus();
		if(p==NULL) return NULL;
		p->currentPown=(Pown *)DoubleLinkedListGet(teamPowns,i);
		if(p->currentPown!=NULL)
		{
			p->currentPosition.x=p->currentPown->getPoint()->x;
			p->currentPosition.y=p->currentPown->getPoint()->y;
			p->currentType=p->currentPown->getType();
			p->validMoves=p->currentPown->getValidMoves(board);

			#ifdef INITIALIZE_RATES
			p->validMovesRate=DoubleLinkedListConstruct();
			#endif

			/*Code for removing the king threatening moves from the
			  current piece bvalid moves list. Furthermore it initializes
			  the rate moves list to have each item set to 0.*/
			jsz = DoubleLinkedListGetSize(p->validMoves);
			for (j=0;j<jsz;j++)
			{
				int *a;
				
				/*Remove this movement if it leads to a threatening of the king by the
				  opponent.*/
				struct point *pt;
				pt = (struct point *)DoubleLinkedListGet(p->validMoves, j);

				if (p->currentPown->getType()==KING)
				{
					kingX = pt->x;
					kingY = pt->y;
				}
				tmp = new ChessBoard(board);
				tmp->move(p->currentPosition.x, p->currentPosition.y,pt->x,pt->y);		
				tmp->upgradeValidMovesSimple();

				if (t==WHITE)
				{
					flg = tmp->squareIsThreatened(kingX, kingY, BLACK);
				}else
				{
					flg = tmp->squareIsThreatened(kingX, kingY, WHITE);
				}

				if (flg==true)
				{
					DoubleLinkedListDel(p->validMoves, j);
					j--;
					jsz--;
					delete pt;
					delete tmp;
					kingX = tmpX;
					kingY = tmpY;
					continue;
				}	

				kingX = tmpX;
				kingY = tmpY;		
				delete tmp;	

				#ifdef INITIALIZE_RATES
				/*Add rate 0 to the parallel valid moves rate item.*/
				a=new int[1];
				(*a)=0;
				DoubleLinkedListAddInTail(p->validMovesRate, a);
				#endif
			}

			DoubleLinkedListAddInTail(lst,p);
		}
	}
	return lst;
}

DoubleLinkedList *ChessBoard::getAllValidMovesSimple(enum team_ t)
{
	DoubleLinkedList *lst;
	DoubleLinkedList *teamPowns;
	int size,i, j, jsz;
	switch (t)
	{
	case WHITE:
		{
			teamPowns=whitePowns;
			if(whiteValidMoves!=NULL)
				return whiteValidMoves;
			break;
		}
	case BLACK:
		{
			
			if(blackValidMoves!=NULL)
				return blackValidMoves;
			teamPowns=blackPowns;
			break;
		}
	default:
		return  NULL;
		break;
		
	}
	lst = DoubleLinkedListConstruct();
	size=DoubleLinkedListGetSize(teamPowns);
	for(i=0;i<size;i++)
	{
		struct pownstatus * p;
		
		p= new struct pownstatus();
		if(p==NULL) return NULL;
		p->currentPown=(Pown *)DoubleLinkedListGet(teamPowns,i);
		if(p->currentPown!=NULL)
		{
			p->currentPosition.x=p->currentPown->getPoint()->x;
			p->currentPosition.y=p->currentPown->getPoint()->y;
			p->currentType=p->currentPown->getType();
			p->validMoves=p->currentPown->getValidMoves(board);
		
			#ifdef INITIALIZE_RATES
			p->validMovesRate=DoubleLinkedListConstruct();
			jsz = DoubleLinkedListGetSize(p->validMoves);
			for (j=0;j<jsz;j++)
			{
				int *a;
				a=new int[1];
				(*a)=0;
				DoubleLinkedListAddInTail(p->validMovesRate, a);
			}
			#endif

			DoubleLinkedListAddInTail(lst,p);
		}
	}
	return lst;
}

void ChessBoard::printAllValidMoves(DoubleLinkedList *validPowns)
{
	int i,j;
	int isz,jsz;
	isz=DoubleLinkedListGetSize(validPowns);
	for(i=0;i<isz;i++)
	{
		struct pownstatus *p;
		p=(struct pownstatus *)DoubleLinkedListGet(validPowns,i);
		
		jsz = DoubleLinkedListGetSize(p->validMoves);
		for (j=0;j<jsz;j++)
		{
			printf("\n");
			switch (p->currentType)
			{
				case SOLDIER:
				printf("Soldier: ");
				break;
			case KNIGHT:
				printf("Knight: ");
				break;
			case ROCK:
					printf("Rock: ");
				break;
			case KING:
				printf("King: ");
				break;
			case QUEEN:
				printf("Queen: ");
				break;
			default:
				printf("Eimaste malakes");
				break;
			}
			printf("(%d,%d) to (%d,%d)", p->currentPosition.x, p->currentPosition.y, ((struct point *)DoubleLinkedListGet(p->validMoves, j))->x, ((struct point *)DoubleLinkedListGet(p->validMoves, j))->y);
		}
	}
}
void ChessBoard::print()
{
	print(stdout);
}
void ChessBoard::print(FILE *fp)
{

	int i,j;
	for(j=BOARD_Y-1;j>=0;j--)
	{
		fprintf(fp,"\n");
		for(i=0;i<BOARD_X;i++)
		{
			if(board[i][j]==NULL)
			{
				fprintf(fp," ");
				continue;
			}
			switch(board[i][j]->getType())
			{
			case KNIGHT:
				if(board[i][j]->getTeam()==WHITE)
				{
					fprintf(fp,"N");
				}
				else
				{
					fprintf(fp,"n");
				}
				break;
			case SOLDIER:
				if(board[i][j]->getTeam()==WHITE)
				{
					fprintf(fp,"P");
				}
				else
				{
					fprintf(fp,"p");
				}
				break;
			case QUEEN:
				if(board[i][j]->getTeam()==WHITE)
				{
					fprintf(fp,"Q");
				}
				else
				{
					fprintf(fp,"q");
				}
				break;
			case KING:
				if(board[i][j]->getTeam()==WHITE)
				{
					fprintf(fp,"K");
				}
				else
				{
					fprintf(fp,"k");
				}
				break;
			case ROCK:
				if(board[i][j]->getTeam()==WHITE)
				{
					fprintf(fp,"R");
				}
				else
				{
					fprintf(fp,"r");
				}
				break;
			case BISHOP:
				if(board[i][j]->getTeam()==WHITE)
				{
					fprintf(fp,"B");
				}
				else
				{
					fprintf(fp,"b");
				}
				break;
			}

		}
	}
}
bool ChessBoard::isPromote(enum team_ team)
{
	int i;
	if(team==WHITE)
	{
		for(i=0;i<BOARD_X;i++)
		{
			if(board[i][BOARD_Y-1]!=NULL)
			{
				if(board[i][BOARD_Y-1]->getType()==SOLDIER)
				{
					return true;
				}
			}
		}
	}
	else
	{
		for(i=0;i<BOARD_X;i++)
		{
			if(board[i][0]!=NULL)
			{
				if(board[i][0]->getType()==SOLDIER)
				{
					return true;
				}
			}
		}
		
	}
	return false;
}
void ChessBoard::promote(enum team_ team , enum powntype type)
{
	int i=0;
	int isz=0;
	int j=0;
	Pown *res=NULL;
	struct action *act;
	Pown *p;
	p=NULL;
	if(team==WHITE)
	{
		for(i=0;i<BOARD_X;i++)
		{
			if(board[i][BOARD_Y-1]!=NULL)
			{
				if(board[i][BOARD_Y-1]->getType()==SOLDIER)
				{
					p=board[i][BOARD_Y-1];
					j=BOARD_Y-1;
					break;
				}
			}
		}
	}
	else
	{
		for(i=0;i<BOARD_X;i++)
		{
			if(board[i][0]!=NULL)
			{
				if(board[i][0]->getType()==SOLDIER)
				{
					p=board[i][0];
					j=0;
					break;
				}
			}
		}
		
	}
	if(p!=NULL)
	{

		switch(type)
		{
			case QUEEN:
				res=new Queen(p->getPoint(),p->getTeam());
				break;
			case ROCK:
				res=new Rock(p->getPoint(),p->getTeam());
				break;
			case BISHOP:
				res=new Bishop(p->getPoint(),p->getTeam());
				break;
			case KNIGHT:
				res=new Knight(p->getPoint(),p->getTeam());
				break;
			default:
				return ;
		}
		board[i][j]=res;
		/*remove soldier from team list*/
		if(team==WHITE)
		{
			isz=DoubleLinkedListGetSize(whitePowns);
			for(i=0;i<isz;i++)
			{
				Pown *s;
				s=(Pown *)DoubleLinkedListGet(whitePowns,i);
				if((p->getPoint())->x==(s->getPoint())->x && (p->getPoint())->y==(s->getPoint())->y)
				{
					DoubleLinkedListDel(whitePowns,i);
					break;
				}
			}
			DoubleLinkedListAddInTail(whitePowns,res);
		}
		else
		{
			isz=DoubleLinkedListGetSize(blackPowns);
			for(i=0;i<isz;i++)
			{
				Pown *s;
				s=(Pown *)DoubleLinkedListGet(blackPowns,i);
				if((p->getPoint())->x==(s->getPoint())->x && (p->getPoint())->y==(s->getPoint())->y)
				{
					DoubleLinkedListDel(blackPowns,i);
					break;
				}
			}
			DoubleLinkedListAddInTail(blackPowns,res);
		}
		if (enabledLogFile==true)
		{
			act=new struct action();
			act->actionType=PROMOTION_ACT;
			act->attacked=NULL;
			act->team=res->getTeam();
			act->toPosition.x=res->getPoint()->x;
			act->toPosition.y=res->getPoint()->y;
			act->fromPosition.x=res->getPoint()->x;
			act->fromPosition.y=res->getPoint()->y;
			DoubleLinkedListAddInTail(logFile,act);
		}
		delete p;
	}
	upgradeValidMoves();
	return ;
}
unsigned char ChessBoard::isMatOrPat(enum team_ team)
{
	DoubleLinkedList *lst;
	int i, isz, j, jsz;
	int cnt;

	lst = getAllValidMoves(team);

	jsz = DoubleLinkedListGetSize(lst);
	for (j=0, cnt=0;j<jsz;j++)
	{
		cnt += DoubleLinkedListGetSize(((struct pownstatus *)DoubleLinkedListGet(lst,j))->validMoves);
	}
	if (cnt==0)
	{
		if (team==WHITE)
		{
			isz = DoubleLinkedListGetSize(whitePowns);
			for (i=0;i<isz;i++)
			{
				Pown *pwn;
				pwn = (Pown *)DoubleLinkedListGet(whitePowns,i);
				if (pwn->getType()==KING)
				{
					if (squareIsThreatened(pwn->getPoint()->x,pwn->getPoint()->y,BLACK)==true)
					{
						return IS_MAT;
					}else
					{
						return IS_PAT;
					}
				}
			}
		}else
		{
			isz = DoubleLinkedListGetSize(blackPowns);
			for (i=0;i<isz;i++)
			{
				Pown *pwn;
				pwn = (Pown *)DoubleLinkedListGet(blackPowns,i);
				if (pwn->getType()==KING)
				{
					if (squareIsThreatened(pwn->getPoint()->x,pwn->getPoint()->y,WHITE)==true)
					{
						return IS_MAT;
					}else
					{
						return IS_PAT;
					}
				}
			}
		}
	}

	return IS_OK;
}


DoubleLinkedList *ChessBoard::getCapturedList(void)
{
	return capturedList;
}

bool ChessBoard::cancelLastMove(void)
{
	struct action *act;
	int x0,y0,x1,y1;
	bool prmt = false;

	if(logFile==NULL ) 
		return false;
	
	act=(struct action *)DoubleLinkedListGetTail(logFile);
	
	if(act==NULL)
		return false;

	x1=act->toPosition.x;
	y1=act->toPosition.y;
	x0=act->fromPosition.x;
	y0=act->fromPosition.y;
	
	switch(act->actionType)
	{
	case SIMPLE_ACT:
		{
			
			
			board[x0][y0]=board[x1][y1];
			board[x0][y0]->movePownTo(x0,y0);
			board[x0][y0]->decreaseNoOfMoves(2);
			if(act->attacked!=NULL)
			{
				board[x1][y1]=act->attacked;
				if(act->attacked->getTeam()==WHITE)
				{
					DoubleLinkedListAddInTail(whitePowns,act->attacked);
				}
				else
				{
					DoubleLinkedListAddInTail(blackPowns,act->attacked);
				}
				DoubleLinkedListDelTail(capturedList);
			}
			else
			{
				board[x1][y1]=NULL;
			}

			break;
		}
	case PROMOTION_ACT:
		{
			enum team_ tm;
			struct point *pt;

			tm=board[x1][y1]->getTeam();

			/*Remove accordingly to its team.*/
			if(tm==WHITE)
			{
				int i, isz;

				/*Find the coresponding pown in the witePowns list*/
				isz = DoubleLinkedListGetSize(whitePowns);
				for (i=0;i<isz;i++)
				{
					Pown *p;
					p = (Pown *)DoubleLinkedListGet(whitePowns,i);

					/*if the requested pown was found*/
					if (p->getPoint()->x==x1 && p->getPoint()->y==y1)
					{
						DoubleLinkedListDel(whitePowns,i);
						break;
					}
				}
			}
			else
			{
				int i, isz;

				/*Find the coresponding pown in the witePowns list*/
				isz = DoubleLinkedListGetSize(blackPowns);
				for (i=0;i<isz;i++)
				{
					Pown *p;
					p = (Pown *)DoubleLinkedListGet(blackPowns,i);

					/*if the requested pown was found*/
					if (p->getPoint()->x==x1 && p->getPoint()->y==y1)
					{
						DoubleLinkedListDel(blackPowns,i);
						break;
					}
				}
			}
			/*Free the board's allocated position, to bring back the old soldier pown.*/
			delete board[x1][y1];

			/*Not its the time to bring back the slodier pown before the
			  promotion occured.*/		
			pt = new struct point();
			pt->x = x1;
			pt->y = y1;
			board[x1][y1] = new Soldier(pt, tm);

			if (tm==WHITE)
			{
				DoubleLinkedListAddInTail(whitePowns, board[x1][y1]);
			}else
			{
				DoubleLinkedListAddInTail(blackPowns, board[x1][y1]);
			}

			prmt=true;

			break;
		}
	case KING_ROKE_ACT:
		{	
			enum team_ tm;

			tm = board[x1][y1]->getTeam();

			if (tm==WHITE)
			{	
				/*Bring back the king.*/
				board[4][0] = board[6][0];
				board[4][0]->movePownTo(4,0);
				board[4][0]->decreaseNoOfMoves(2);
				board[6][0] = NULL;

				/*Bring back the rock.*/
				board[7][0] = board[5][0];
				board[7][0]->movePownTo(7,0);
				board[7][0]->decreaseNoOfMoves(2);
				board[5][0] = NULL;
			}else
			{
				/*Bring back the king.*/
				board[4][BOARD_Y-1] = board[6][BOARD_Y-1];
				board[4][BOARD_Y-1]->movePownTo(4,BOARD_Y-1);
				board[4][BOARD_Y-1]->decreaseNoOfMoves(2);
				board[6][BOARD_Y-1] = NULL;

				/*Bring back the rock.*/
				board[7][BOARD_Y-1] = board[5][BOARD_Y-1];
				board[7][BOARD_Y-1]->movePownTo(7,BOARD_Y-1);
				board[7][BOARD_Y-1]->decreaseNoOfMoves(2);
				board[5][BOARD_Y-1] = NULL;
			}

			break;
		}
	case QUEEN_ROKE_ACT:
		{
			enum team_ tm;
	
			tm = board[x1][y1]->getTeam();

			if (tm==WHITE)
			{	
				/*Bring back the king.*/
				board[4][0] = board[2][0];
				board[4][0]->movePownTo(4,0);
				board[4][0]->decreaseNoOfMoves(2);
				board[2][0] = NULL;

				/*Bring back the rock.*/
				board[0][0] = board[3][0];
				board[0][0]->movePownTo(0,0);
				board[0][0]->decreaseNoOfMoves(2);
				board[3][0] = NULL;
			}else
			{
				/*Bring back the king.*/
				board[4][BOARD_Y-1] = board[2][BOARD_Y-1];
				board[4][BOARD_Y-1]->movePownTo(4,BOARD_Y-1);
				board[4][BOARD_Y-1]->decreaseNoOfMoves(2);
				board[2][BOARD_Y-1] = NULL;

				/*Bring back the rock.*/
				board[0][BOARD_Y-1] = board[3][BOARD_Y-1];
				board[0][BOARD_Y-1]->movePownTo(0,BOARD_Y-1);
				board[0][BOARD_Y-1]->decreaseNoOfMoves(2);
				board[3][BOARD_Y-1] = NULL;
			}

			break;
		}
	default:
		return false;
	}

	/*Free and delete the last action, for it is useless now.*/
	delete act;
	DoubleLinkedListDelTail(logFile);

	if (prmt==true)
	{
		return cancelLastMove();
	}

	/*All things have been done successfully. Ready to return true state.*/
	return true;
}


/*Enables the log file keeping*/
void ChessBoard::enableLogKeeping(void)
{
	enabledLogFile = true;
}

/*Disables the log file keeping*/
void ChessBoard::disableLogKeeping(void)
{
	enabledLogFile = false;
}

unsigned char ChessBoard::getFirstCommingTeam(void)
{
	int i, isz;
	int black, white;

	isz = DoubleLinkedListGetSize(whitePowns);
	for (i=0, white=0;i<isz;i++)
	{
		Pown *p;

		p = (Pown *)DoubleLinkedListGet(whitePowns, i);

		switch (p->getType())
		{
		case QUEEN:
			white += 9;
			break;
		case SOLDIER:
			white += 1;
			break;
		case ROCK:
			white += 4;
			break;
		case BISHOP:
		case KNIGHT:
			white += 3;
			break;
		}
	}

	isz = DoubleLinkedListGetSize(blackPowns);
	for (i=0, black=0;i<isz;i++)
	{
		Pown *p;

		p = (Pown *)DoubleLinkedListGet(blackPowns, i);

		switch (p->getType())
		{
		case QUEEN:
			black += 9;
			break;
		case SOLDIER:
			black += 1;
			break;
		case ROCK:
			black += 4;
			break;
		case BISHOP:
		case KNIGHT:
			black += 3;
			break;
		}
	}

	if (white>black)
	{
		return WHITE_AHEAD;
	}else if (white<black)
	{
		return BLACK_AHEAD;
	}
	
	return EQUALITY;
}




DoubleLinkedList *ChessBoard::getPownsList(enum team_ team)
{
	if(team==WHITE)
	{
		return whitePowns;
	}
	return blackPowns;
}