/*|============================================================================|*
 *| Chess Application: file Pown.cpp                                           |*
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
#include "Pown.h"
#include <iostream>
/*=====================================================*/

/*============ General variables ======================*/

/*This variable determines the the type of the chess board
  table in which the game will be played. The board is always
  initializes to 8x8 dimensions, but if this variable is
  6, then the game will occur in a subtable of it with
  6x6 dimensions. This is used to help us to develop a code
  in order to let the user ot choose which type of chess board
  he wants, by selecting it from the console window.*/
int boardSize=8;

/*=====================================================*/



/*================= General Functions ==============================*/

/*Generic constructor for all types of objects*/
Pown::Pown(Point initPosition, enum team_ initTeam)
{
	position=new struct point();
	position->x = initPosition->x;
	position->y = initPosition->y;
	team = initTeam;
	noOfMoves=0;
}

/*Generic constructor for all types of objects*/
Pown::Pown(void)
{	
	position=new struct point();
	noOfMoves=0;
}

/*Generic destructor for all types of objects*/
Pown::~Pown(void)
{
	delete position;
}

/*Gets the current team of the piece and returns it 
		as an enumerationSee enum team_ for more details.*/
enum team_ Pown::getTeam(void)
{
	return team;
}

/*This function is responsible for changing only the current position
	   of the piece into the new one. It is used by the ChessBoard class. It
	   does not check if the requested movement is valid or not. This control
	   is performed by the ChessBoard::moveTo() function.
	   See ChessBoard::moveTo() for more details.*/
void Pown::movePownTo(int x, int y)
{
	position->x = x;
	position->y = y;
	noOfMoves++;
}

/*Gets the current position of the piece in the chessboard table and 
	   returns it as a point structure. See struct point for more details.*/
Point Pown::getPoint(void)
{
	return position;
}

/*This function decreases the number of moves by one.
  This is mainly used by the ChessBoard::cancellastAction() funtion.
  See ChessBoard::cancelLastAction() function and Pown->noOfMoves
  for more details*/
void Pown::decreaseNoOfMoves(void)
{
	noOfMoves--;
}

/*This function decreases the number of moves by the given integer.
  This is mainly used by the ChessBoard::cancellastAction() funtion.
  See ChessBoard::cancelLastAction() function and Pown->noOfMoves
  for more details*/
void Pown::decreaseNoOfMoves(int num)
{
	noOfMoves-=num;
}


/*========== End of General Functions ===============================*/




/*========== Specific Functions =====================================*/

/*---------- KNIGHT functions -------------------------------*/

Knight::Knight(Point initPosition, enum team_ initTeam)
{
	position->x = initPosition->x;
	position->y = initPosition->y;
	team = initTeam;
}
Knight::Knight(void)
{
	position->x = 0;
	position->y = 0;
	team = WHITE;
}

DoubleLinkedList *Knight::getValidMoves(Pown *board[BOARD_MAX][BOARD_MAX])
{
	int x, y;
	struct point *p;

	DoubleLinkedList *lst;

	lst = DoubleLinkedListConstruct();
	
	x = position->x;
	y = position->y;
	
	if (x-2>=0 && y-1>=0)
	{
		p=new struct point();
		p->x = x-2;
		p->y = y-1;
		if (board[p->x][p->y]==NULL || board[p->x][p->y]->getTeam()!=team)
		{
			
			DoubleLinkedListAddInTail(lst, p);
		}
		else
		{
			delete p;
		}
	}

	if (x-2>=0 && y+1<BOARD_Y)
	{
		p=new struct point();
		p->x = x-2;
		p->y = y+1;
		if (board[p->x][p->y]==NULL || board[p->x][p->y]->getTeam()!=team)
		{
			
			DoubleLinkedListAddInTail(lst, p);
		}
		else
		{
			delete p;
		}
	}

	if (x-1>=0 && y+2<BOARD_Y)
	{
		p=new struct point();
		p->x = x-1;
		p->y = y+2;
		if (board[p->x][p->y]==NULL || board[p->x][p->y]->getTeam()!=team)
		{
			
			DoubleLinkedListAddInTail(lst, p);
		}
		else
		{
			delete p;
		}
	}
	
	if (x+1<BOARD_X && y+2<BOARD_Y)
	{
		p=new struct point();
		p->x = x+1;
		p->y = y+2;
		if (board[p->x][p->y]==NULL || board[p->x][p->y]->getTeam()!=team)
		{
			
			DoubleLinkedListAddInTail(lst, p);
		}
		else
		{
			delete p;
		}
	}

	if (x+2<BOARD_X && y+1<BOARD_Y)
	{
		p=new struct point();
		p->x = x+2;
		p->y = y+1;
		if (board[p->x][p->y]==NULL || board[p->x][p->y]->getTeam()!=team)
		{
			
			DoubleLinkedListAddInTail(lst, p);
		}
		else
		{
			delete p;
		}
	}

	if (x+2<BOARD_X && y-1>=0)
	{
		p=new struct point();
		p->x = x+2;
		p->y = y-1;
		if (board[p->x][p->y]==NULL || board[p->x][p->y]->getTeam()!=team)
		{
			
			DoubleLinkedListAddInTail(lst, p);
		}
		else
		{
			delete p;
		}
	}

	if (x+1<BOARD_X && y-2>=0)
	{
		p=new struct point();
		p->x = x+1;
		p->y = y-2;
		if (board[p->x][p->y]==NULL || board[p->x][p->y]->getTeam()!=team)
		{
			
			DoubleLinkedListAddInTail(lst, p);
		}
		else
		{
			delete p;
		}
	}

	if (x-1>=0 && y-2>=0)
	{
		p=new struct point();
		p->x = x-1;
		p->y = y-2;
		if (board[p->x][p->y]==NULL || board[p->x][p->y]->getTeam()!=team)
		{
			
			DoubleLinkedListAddInTail(lst, p);
		}
		else
		{
			delete p;
		}
	}
	
	return lst;
}

enum powntype Knight::getType(void)
{
	return KNIGHT;
}

/*------------ ROCK functions -----------------------------*/

DoubleLinkedList *Rock::getValidMoves(Pown *board[BOARD_MAX][BOARD_MAX])
{
	int x,y;
	int i;
	struct point *p;
	DoubleLinkedList *lst;

	lst = DoubleLinkedListConstruct();

	x = position->x;
	y = position->y;

	for (i=x-1; i>=0; i--)
	{
		p=new struct point();
		p->x = i;
		p->y = y;
		if (board[p->x][p->y]!=NULL)
		{
			if (board[p->x][p->y]->getTeam()==team)
			{
				delete p;
				break;
			}else
			{
				DoubleLinkedListAddInTail(lst, p);
				break;
			}
		}
		DoubleLinkedListAddInTail(lst, p);
	}

	for (i=x+1; i<BOARD_X; i++)
	{
		p=new struct point();
		p->x = i;
		p->y = y;
		if (board[p->x][p->y]!=NULL)
		{
			if (board[p->x][p->y]->getTeam()==team)
			{
				delete p;
				break;
			}else
			{
				DoubleLinkedListAddInTail(lst, p);
				break;
			}
		}
		DoubleLinkedListAddInTail(lst, p);
	}

	for (i=y-1; i>=0; i--)
	{
		p=new struct point();
		p->x = x;
		p->y = i;
		if (board[p->x][p->y]!=NULL)
		{
			if (board[p->x][p->y]->getTeam()==team)
			{
				delete p;
				break;
			}else
			{
				DoubleLinkedListAddInTail(lst, p);
				break;
			}
		}
		DoubleLinkedListAddInTail(lst, p);
	}

	for (i=y+1; i<BOARD_Y; i++)
	{
		p=new struct point();
		p->x = x;
		p->y = i;
		if (board[p->x][p->y]!=NULL)
		{
			if (board[p->x][p->y]->getTeam()==team)
			{
				delete p;
				break;
			}else
			{
				DoubleLinkedListAddInTail(lst, p);
				break;
			}
		}
		DoubleLinkedListAddInTail(lst, p);
	}

	return lst;
		
}

Rock::Rock(Point initPosition, enum team_ initTeam)
{
	position->x = initPosition->x;
	position->y = initPosition->y;
	team = initTeam;	
}

Rock::Rock(void)
{
	position->x = 0;
	position->y = 0;
	team = WHITE;
}
enum powntype Rock::getType(void)
{
	return ROCK;
}

/*---------- KING functions ------------------------------*/
DoubleLinkedList *King::getValidMoves(Pown *board[BOARD_MAX][BOARD_MAX])
{
	struct point *p;
	int x, y, i, j;
	DoubleLinkedList *lst;

	lst = DoubleLinkedListConstruct();
	x = position->x;
	y = position->y;

	for (i=x-1, j=y-1; i>=0 && j>=0; i--, j--)
	{
		p=new struct point();
		p->x = i;
		p->y = j;
		if (board[p->x][p->y]!=NULL)
		{
			if (board[p->x][p->y]->getTeam()==team)
			{
				delete p;
				break;
			}else
			{
				DoubleLinkedListAddInTail(lst, p);
				break;
			}
		}
		DoubleLinkedListAddInTail(lst, p);	
		break;
	}

	for (i=x+1, j=y+1; i<BOARD_X && j<BOARD_Y; i++, j++)
	{
		p=new struct point();
		p->x = i;
		p->y = j;
		if (board[p->x][p->y]!=NULL)
		{
			if (board[p->x][p->y]->getTeam()==team)
			{
				delete p;
				break;
			}else
			{
				DoubleLinkedListAddInTail(lst, p);
				break;
			}
		}
		DoubleLinkedListAddInTail(lst, p);	
		break;
	}

	for (i=x+1, j=y-1; i<BOARD_X && j>=0; i++, j--)
	{
		p=new struct point();
		p->x = i;
		p->y = j;
		if (board[p->x][p->y]!=NULL)
		{
			if (board[p->x][p->y]->getTeam()==team)
			{
				delete p;
				break;
			}else
			{
				DoubleLinkedListAddInTail(lst, p);
				break;
			}
		}
		DoubleLinkedListAddInTail(lst, p);	
		break;
	}

	for (i=x-1, j=y+1; i>=0 && j<BOARD_Y; i--, j++)
	{
		p=new struct point();
		p->x = i;
		p->y = j;
		if (board[p->x][p->y]!=NULL)
		{
			if (board[p->x][p->y]->getTeam()==team)
			{
				delete p;
				break;
			}else
			{
				DoubleLinkedListAddInTail(lst, p);
				break;
			}
		}
		DoubleLinkedListAddInTail(lst, p);	
		break;
	}

	for (i=x-1; i>=0; i--)
	{
		p=new struct point();
		p->x = i;
		p->y = y;
		if (board[p->x][p->y]!=NULL)
		{
			if (board[p->x][p->y]->getTeam()==team)
			{
				delete p;
				break;
			}else
			{
				DoubleLinkedListAddInTail(lst, p);
				break;
			}
		}
		DoubleLinkedListAddInTail(lst, p);
		break;
	}

	for (i=x+1; i<BOARD_X; i++)
	{
		p=new struct point();
		p->x = i;
		p->y = y;
		if (board[p->x][p->y]!=NULL)
		{
			if (board[p->x][p->y]->getTeam()==team)
			{
				delete p;
				break;
			}else
			{
				DoubleLinkedListAddInTail(lst, p);
				break;
			}
		}
		DoubleLinkedListAddInTail(lst, p);
		break;
	}

	for (i=y-1; i>=0; i--)
	{
		p=new struct point();
		p->x = x;
		p->y = i;
		if (board[p->x][p->y]!=NULL)
		{
			if (board[p->x][p->y]->getTeam()==team)
			{
				delete p;
				break;
			}else
			{
				DoubleLinkedListAddInTail(lst, p);
				break;
			}
		}
		DoubleLinkedListAddInTail(lst, p);
		break;
	}

	for (i=y+1; i<BOARD_Y; i++)
	{
		p=new struct point();
		p->x = x;
		p->y = i;
		if (board[p->x][p->y]!=NULL)
		{
			if (board[p->x][p->y]->getTeam()==team)
			{
				delete p;
				break;
			}else
			{
				DoubleLinkedListAddInTail(lst, p);
				break;
			}
		}
		DoubleLinkedListAddInTail(lst, p);
		break;
	}

	return lst;

	
}

King::King(Point initPosition, enum team_ initTeam)
{
	position->x = initPosition->x;
	position->y = initPosition->y;
	team = initTeam;	
}

King::King(void)
{
	position->x = 0;
	position->y = 0;
	team = WHITE;	
}
enum powntype King::getType(void)
{
	return KING;
}
/*----------- QUEEN functions ----------------------------------*/

DoubleLinkedList *Queen::getValidMoves(Pown *board[BOARD_MAX][BOARD_MAX])
{
	int x,y;
	int i, j;
	struct point *p;
	DoubleLinkedList *lst;

	lst = DoubleLinkedListConstruct();

	x = position->x;
	y = position->y;

	for (i=x-1, j=y-1; i>=0 && j>=0; i--, j--)
	{
		p=new struct point();
		p->x = i;
		p->y = j;
		if (board[p->x][p->y]!=NULL)
		{
			if (board[p->x][p->y]->getTeam()==team)
			{
				delete p;
				break;
			}else
			{
				DoubleLinkedListAddInTail(lst, p);
				break;
			}
		}
		DoubleLinkedListAddInTail(lst, p);		
	}

	for (i=x+1, j=y+1; i<BOARD_X && j<BOARD_Y; i++, j++)
	{
		p=new struct point();
		p->x = i;
		p->y = j;
		if (board[p->x][p->y]!=NULL)
		{
			if (board[p->x][p->y]->getTeam()==team)
			{
				delete p;
				break;
			}else
			{
				DoubleLinkedListAddInTail(lst, p);
				break;
			}
		}
		DoubleLinkedListAddInTail(lst, p);		
	}

	for (i=x+1, j=y-1; i<BOARD_X && j>=0; i++, j--)
	{
		p=new struct point();
		p->x = i;
		p->y = j;
		if (board[p->x][p->y]!=NULL)
		{
			if (board[p->x][p->y]->getTeam()==team)
			{
				delete p;
				break;
			}else
			{
				DoubleLinkedListAddInTail(lst, p);
				break;
			}
		}
		DoubleLinkedListAddInTail(lst, p);		
	}

	for (i=x-1, j=y+1; i>=0 && j<BOARD_Y; i--, j++)
	{
		p=new struct point();
		p->x = i;
		p->y = j;
		if (board[p->x][p->y]!=NULL)
		{
			if (board[p->x][p->y]->getTeam()==team)
			{
				delete p;
				break;
			}else
			{
				DoubleLinkedListAddInTail(lst, p);
				break;
			}
		}
		DoubleLinkedListAddInTail(lst, p);		
	}

	for (i=x-1; i>=0; i--)
	{
		p=new struct point();
		p->x = i;
		p->y = y;
		if (board[p->x][p->y]!=NULL)
		{
			if (board[p->x][p->y]->getTeam()==team)
			{
				delete p;
				break;
			}else
			{
				DoubleLinkedListAddInTail(lst, p);
				break;
			}
		}
		DoubleLinkedListAddInTail(lst, p);
	}

	for (i=x+1; i<BOARD_X; i++)
	{
		p=new struct point();
		p->x = i;
		p->y = y;
		if (board[p->x][p->y]!=NULL)
		{
			if (board[p->x][p->y]->getTeam()==team)
			{
				delete p;
				break;
			}else
			{
				DoubleLinkedListAddInTail(lst, p);
				break;
			}
		}
		DoubleLinkedListAddInTail(lst, p);
	}

	for (i=y-1; i>=0; i--)
	{
		p=new struct point();
		p->x = x;
		p->y = i;
		if (board[p->x][p->y]!=NULL)
		{
			if (board[p->x][p->y]->getTeam()==team)
			{
				delete p;
				break;
			}else
			{
				DoubleLinkedListAddInTail(lst, p);
				break;
			}
		}
		DoubleLinkedListAddInTail(lst, p);
	}

	for (i=y+1; i<BOARD_Y; i++)
	{
		p=new struct point();
		p->x = x;
		p->y = i;
		if (board[p->x][p->y]!=NULL)
		{
			if (board[p->x][p->y]->getTeam()==team)
			{
				delete p;
				break;
			}else
			{
				DoubleLinkedListAddInTail(lst, p);
				break;
			}
		}
		DoubleLinkedListAddInTail(lst, p);
	}

	return lst;
}

Queen::Queen(Point initPosition, enum team_ initTeam)
{
	position->x = initPosition->x;
	position->y = initPosition->y;
	team = initTeam;		
}

Queen::Queen(void)
{
	position->x = 0;
	position->y = 0;
	team = WHITE;
}
enum powntype Queen::getType(void)
{
	return QUEEN;
}

/*------------ SOLDIER functions ---------------------------*/

DoubleLinkedList *Soldier::getValidMoves(Pown *board[BOARD_MAX][BOARD_MAX])
{
	int x, y;
	struct point *p;
	DoubleLinkedList *lst;

	lst = DoubleLinkedListConstruct();


	x = position->x;	
	y = position->y;

	if (team==WHITE)
	{	
		if (y+1<BOARD_Y && board[x][y+1]==NULL)
		{
			p=new struct point();
			p->x = x;
			p->y = y+1;
			DoubleLinkedListAddInTail(lst, p);
		}
		if (y+1<BOARD_Y && x+1<BOARD_X && board[x+1][y+1]!=NULL)
		{
			if (board[x+1][y+1]->getTeam()==BLACK)
			{
				p=new struct point();
				p->x = x+1;
				p->y = y+1;
				DoubleLinkedListAddInTail(lst, p);	
			}
		}
		if (y+1<BOARD_Y && x-1>=0 && board[x-1][y+1]!=NULL)
		{
			if (board[x-1][y+1]->getTeam()==BLACK)
			{
				p=new struct point();
				p->x = x-1;
				p->y = y+1;
				DoubleLinkedListAddInTail(lst, p);		
			}
		}
		if (y==1)
		{
			if (board[x][y+1]==NULL && board[x][y+2]==NULL)
			{
				p=new struct point();
				p->x = x;
				p->y = y+2;
				DoubleLinkedListAddInTail(lst, p);
			}
		}
	}else if (team==BLACK)
	{
		if (y-1>=0 && board[x][y-1]==NULL)
		{
			p=new struct point();
			p->x = x;
			p->y = y-1;
			DoubleLinkedListAddInTail(lst, p);
		}
		if (y-1>=0 && x+1<BOARD_X && board[x+1][y-1]!=NULL)
		{
			if (board[x+1][y-1]->getTeam()==WHITE)
			{
				p=new struct point();
				p->x = x+1;
				p->y = y-1;
				DoubleLinkedListAddInTail(lst, p);	
			}
		}
		if (y-1>=0 && x-1>=0 && board[x-1][y-1]!=NULL)
		{
			if (board[x-1][y-1]->getTeam()==WHITE)
			{
				p=new struct point();
				p->x = x-1;
				p->y = y-1;
				DoubleLinkedListAddInTail(lst, p);		
			}
		}
		if (y==BOARD_Y-2)
		{
			if (board[x][y-1]==NULL && board[x][y-2]==NULL)
			{
				p=new struct point();
				p->x = x;
				p->y = y-2;
				DoubleLinkedListAddInTail(lst, p);
			}
		}
	}

	return lst;
}

Soldier::Soldier(Point initPosition, enum team_ initTeam)
{
	position->x = initPosition->x;
	position->y = initPosition->y;
	team = initTeam;	
}

Soldier::Soldier(void)
{
	position->x = 0;
	position->y = 0;
	team = WHITE;
}

enum powntype Soldier::getType(void)
{
	return SOLDIER;
}


/*------------ Bishop functions -----------------------------------*/

Bishop::Bishop(Point initPosition, enum team_ initTeam)
{
	position->x = initPosition->x;
	position->y = initPosition->y;
	team = initTeam;	
}

Bishop::Bishop(void)
{
	position->x = 0;
	position->y = 0;
	team = WHITE;
}

enum powntype Bishop::getType(void)
{
	return BISHOP;
}

DoubleLinkedList *Bishop::getValidMoves(Pown *board[BOARD_MAX][BOARD_MAX])
{
	int x,y;
	int i, j;
	struct point *p;
	DoubleLinkedList *lst;

	lst = DoubleLinkedListConstruct();

	x = position->x;
	y = position->y;

	for (i=x-1, j=y-1; i>=0 && j>=0; i--, j--)
	{
		p=new struct point();
		p->x = i;
		p->y = j;
		if (board[p->x][p->y]!=NULL)
		{
			if (board[p->x][p->y]->getTeam()==team)
			{
				delete p;
				break;
			}else
			{
				DoubleLinkedListAddInTail(lst, p);
				break;
			}
		}
		DoubleLinkedListAddInTail(lst, p);		
	}

	for (i=x+1, j=y+1; i<BOARD_X && j<BOARD_Y; i++, j++)
	{
		p=new struct point();
		p->x = i;
		p->y = j;
		if (board[p->x][p->y]!=NULL)
		{
			if (board[p->x][p->y]->getTeam()==team)
			{
				delete p;
				break;
			}else
			{
				DoubleLinkedListAddInTail(lst, p);
				break;
			}
		}
		DoubleLinkedListAddInTail(lst, p);		
	}

	for (i=x+1, j=y-1; i<BOARD_X && j>=0; i++, j--)
	{
		p=new struct point();
		p->x = i;
		p->y = j;
		if (board[p->x][p->y]!=NULL)
		{
			if (board[p->x][p->y]->getTeam()==team)
			{
				delete p;
				break;
			}else
			{
				DoubleLinkedListAddInTail(lst, p);
				break;
			}
		}
		DoubleLinkedListAddInTail(lst, p);		
	}

	for (i=x-1, j=y+1; i>=0 && j<BOARD_Y; i--, j++)
	{
		p=new struct point();
		p->x = i;
		p->y = j;
		if (board[p->x][p->y]!=NULL)
		{
			if (board[p->x][p->y]->getTeam()==team)
			{
				delete p;
				break;
			}else
			{
				DoubleLinkedListAddInTail(lst, p);
				break;
			}
		}
		DoubleLinkedListAddInTail(lst, p);		
	}

	return lst;
}


/*=========== End of Specific Functions ==================================*/