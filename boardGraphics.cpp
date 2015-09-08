/*|============================================================================|*
 *| Chess Application: file boardGraphics.cpp                                  |*
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
#include "boardGraphics.h"
#include "objectGraphics.h"
#include "ChessAlgorithm.h"
#include "ChessBoard.h"
#include "lib/DoubleLinkedList.h"
#include <stdio.h>
/*================================================*/

#define ASCII_ESCAPE 27
#define ASCII_CTRL_Z 26

/*Menu Identifiers*/
#define CANCEL_LAST_ACTION 1001
#define EXIT_APPLICATION   1010
#define END_GAME           1011

DoubleLinkedList *objectList;
ChessBoard *board;
bool turn;
bool singleplay=true;
bool playerSide=true;
bool gameover=false;


/*Main window handler*/
int wid;

/*Captured pieces window handler*/
int capwid;


struct selectedShape {
	int pX;
	int pY;
	Shape *toMove;
};

/* Keeps the selected shape, in order function move() to know
 * which shape (pawn) will move. Otherwise all objects can be moved
 * on each mouse down event.
 */
struct selectedShape sels;


int getWindowSquareCenterX(int i);
int getWindowSquareCenterY(int i);
int getChessBoardSquareX(int x);
int getChessBoardSquareY(int y);
void changeFocusedColor(int x, int y, struct color clr);

void loadObjects(void);
void finilizeWindow(void);
void initializeWindow(char *title, int pos_X, int pos_Y, int width, int height);
void initializeWindow(char *title, int pos_X, int pos_Y,bool single,bool white,bool board8x8);
void initializeWindow(char *title, int pos_X, int pos_Y,bool single,bool white);
void initializeWindow(char *title, int pos_X, int pos_Y,bool single);
void initializeMenu(void);
void display(void);
void displayCapturedPieces(void);
void loadBoardSquares(void);
void loadPowns(void);
void updatePowns(void);

void handle_mouse_click(int button, int state, int lx, int ly);
void handle_mouse_motion(int lx, int ly);
void handle_window_reshape(int x,int y);
void handle_captured_window_reshape(int x, int y);
void handle_keyboard(unsigned char key, int x, int y);
void handle_main_menu(int v);



void idle(void);
/*void hanlde_mouse_movement(int lx, int ly);
*/
void handle_mouse_motion(int lx, int ly)
{
	int h, w;
	h = glutGet(GLUT_WINDOW_HEIGHT);
	w = glutGet(GLUT_WINDOW_WIDTH);
	if(sels.toMove==NULL)
		return;

	sels.toMove->move(lx-w/2,h/2-ly);
	glutPostRedisplay();
}
void setSelectedPawn(int x, int y)
{
	/*Initialize selected Pawn*/
				{
					Shape *sh;
					int h, w;
					int sz,i;
					h = glutGet(GLUT_WINDOW_HEIGHT);
					w = glutGet(GLUT_WINDOW_WIDTH);
					sz=DoubleLinkedListGetSize(objectList);
					for(i=0;i<sz;i++)
					{
						sh=(Shape *)DoubleLinkedListGet(objectList,i);
						if(sh->checkIfInside(x,y)==true && sh->movementIsAvailable())	
						{
							sels.pX=sh->getCenterX();
							sels.pY=sh->getCenterY();
							sels.toMove=sh;
							break;
						}
					}
				}
}

DoubleLinkedList *promotionList; 
int promotionType=-1;
int promotionWindow;
int promotionParentWindow;

void promotionDel(void)
{
	int i,isz;
	isz=DoubleLinkedListGetSize(promotionList);
	for(i=0;i<isz;i++)
	{
		ShapePown *p;
		p=(ShapePown *)DoubleLinkedListGet(promotionList,i);
		delete p;
	}
	DoubleLinkedListDrop(promotionList);
	
}

void promotionFreeWindow(void)
{
	promotionDel();
	glutDestroyWindow(promotionWindow);
	
}

void promotion_mouse_click(int button, int state, int lx, int ly)
{
	int i,isz;
	int h, w;
	if (state == GLUT_DOWN)
		return;
	h = glutGet(GLUT_WINDOW_HEIGHT);
	w = glutGet(GLUT_WINDOW_WIDTH);
	isz=DoubleLinkedListGetSize(promotionList);
	for(i=0;i<isz;i++)
	{
		ShapePown *p;
		p=(ShapePown *)DoubleLinkedListGet(promotionList,i);
		if(p->checkIfInside(lx-w/2, h/2-ly)==true)
		{
			glutSetWindow(promotionWindow);
			promotionFreeWindow();
			glutSetWindow(promotionParentWindow);
			promotionType=i;
			break;	
		}
	}
}
void promotionDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	int i,isz;
	isz=DoubleLinkedListGetSize(promotionList);
	for(i=0;i<isz;i++)
	{
		ShapePown *p;
		p=(ShapePown *)DoubleLinkedListGet(promotionList,i);
		p->draw();
	}
	glutSwapBuffers();
	glutSetWindow(wid);
}

void promotionCreateWindow(void)
{
	
	ShapePown *p;
	promotionParentWindow=glutGetWindow();
	promotionType=-1;
	promotionWindow=glutCreateSubWindow(promotionParentWindow,WWIDTH/2-250,WHEIGHT/2-100,500,100);
	glutSetWindow(promotionWindow);
	//glutMainLoop();
	glutDisplayFunc(promotionDisplay);
	glutMouseFunc(promotion_mouse_click);
	//define the background color
	glClearColor (0.5f, 0.0f, 0.2f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	
	promotionList=DoubleLinkedListConstruct();
	p=new ShapePown(-90, 0, 30,CLR_GREEN,SQUEEN, WHITE);
	DoubleLinkedListAddInTail(promotionList,p);
	
	p=new ShapePown(-30, 0, 30,CLR_GREEN,SROCK, WHITE);
	DoubleLinkedListAddInTail(promotionList,p);
	
	p=new ShapePown(30, 0, 30,CLR_GREEN,SBISHOP, WHITE);
	DoubleLinkedListAddInTail(promotionList,p);
	
	p=new ShapePown(90, 0, 30,CLR_GREEN,SKNIGHT, WHITE);
	DoubleLinkedListAddInTail(promotionList,p);
	glutMainLoop();
	glutSetWindow(promotionParentWindow);
}

void capturedPiecesCreateWindow(int pX, int pY)
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(CWWIDTH, CWHEIGHT);
	glutInitWindowPosition(pX,pY);
	capwid = glutCreateWindow("Captured Pieces");

	glutSetWindow(capwid);	
	glutReshapeFunc(handle_captured_window_reshape);
	glutDisplayFunc(displayCapturedPieces);

	glClearColor(0.0,0.0,0.0,0.0);

	glutMainLoop();
	glutSetWindow(wid);
}

void refreshPowns()
{
	int i,isz;
	
	isz=DoubleLinkedListGetSize(objectList);
	for(i=0;i<isz;i++)
	{
		Shape *sh=(Shape *)DoubleLinkedListGet(objectList,i);
		if(sh->movementIsAvailable()==true)
		{
			delete sh;
			DoubleLinkedListDel(objectList,i);
			i--;
			isz--;
		}
	}

	loadPowns();
}

void opponentPlay(void )
{
	/*Opponent Algorithm*/
	
	struct bestmove *move;
	ChessAlgorithm *play;
	if(playerSide==true)
	{
		play =new ChessAlgorithm(board,BLACK);
	}
	else
	{
		play=new ChessAlgorithm(board,WHITE);
	}
		
	move=play->getBestMove();//WithSteps(0);
	//move=play->getBestMoveWithSteps(0);
	if(board->move(move->x0,move->y0,move->x1,move->y1)==true)
	{
		int x0,y0;
		int x1,y1;
		x0=getWindowSquareCenterX(move->x0);
		y0=getWindowSquareCenterY(move->y0);
		setSelectedPawn(x0,y0);
		x1=getWindowSquareCenterX(move->x1);
		y1=getWindowSquareCenterX(move->y1);
		sels.toMove->move(x1,y1);
		
		board->upgradeValidMoves();
		updatePowns();
		delete move;//free(move);
		delete play;
		turn =!turn;
		if(((ShapePown *)(sels.toMove))->typeofpown==SKING)
		{
			refreshPowns();
		}									
	}
	else
	{
		delete play;
		unsigned char status;
		if(turn==true)
		{
			status = board->isMatOrPat(WHITE);
		}
		else
		{
			status = board->isMatOrPat(BLACK);
		}

		switch (status)
		{
		case IS_MAT:
			if(turn==true)
			{
				MessageBox(NULL,"BLACK Wins with MAT!","MAT",MB_OK);
			}
			else
			{
				MessageBox(NULL,"WHITE Wins with MAT!","MAT",MB_OK);
			}
			gameover=true;
			break;
		case IS_PAT:
			MessageBox(NULL,"The game is PAT!","PAT",MB_OK);
			gameover=true;
			break;
		case IS_OK:
			printf("\nWrong move!");	
			break;
		default:
			printf("\nError: gamithike!");
			break;
		}
		
		turn =!turn;
	}

	/*Set the selected object to NULL, in order any button click in the window
	  will not affect any state of the chessboard and the graphics.*/
	sels.toMove=NULL;			
}

void ValidSquareFocus(int lx, int ly , int w,int h)
{
	/*Drow Valid Square for selected pawn*/
	int i, j, size, k;
	Pown *focpown;
	DoubleLinkedList *p;
	i = getChessBoardSquareX(lx-w/2);
	j = getChessBoardSquareY(h/2-ly);
	focpown=board->getPown(i,j);
	{
		struct color tmp1;
		if(focpown!=NULL)
		{
			if (focpown->getTeam()==WHITE)
			{
				tmp1.red=0;
				tmp1.green=1;
				tmp1.blue=1;
				if(turn ==false)
				{
					sels.toMove=NULL;
					return;
				}
			}else
			{
				tmp1.red=1;
				tmp1.green=1;
				tmp1.blue=0;
				if(turn==true)
				{
					sels.toMove=NULL;
					return;
				}
			}
			changeFocusedColor(lx-w/2, h/2-ly, tmp1);
		}
	}
	p=board->getValidMoves(i,j);

	size = DoubleLinkedListGetSize(p);
	for (k=0;k<size;k++)
	{
		struct point *tmp;
		tmp = (struct point *)DoubleLinkedListGet(p, k);
		i = getWindowSquareCenterX(tmp->x);
		j = getWindowSquareCenterY(tmp->y);
		{
			struct color tmp1;
			if(focpown!=NULL)
			{
				if(focpown->getTeam()==WHITE)
				{
					tmp1.red=0;
					tmp1.green=0;
					tmp1.blue=1;
				}
				else
				{
					tmp1.red=1;
					tmp1.green=0;
					tmp1.blue=0;
				}
			}
			else
			{
				tmp1.red=0;
				tmp1.green=1;
				tmp1.blue=0;
			}
			changeFocusedColor(i,j,tmp1);
		}
	}
	setSelectedPawn(lx-w/2,h/2-ly);
}				
void handle_mouse_click(int button, int state, int lx, int ly)
{
int h, w;
h = glutGet(GLUT_WINDOW_HEIGHT);
w = glutGet(GLUT_WINDOW_WIDTH);
switch (button)
{
case GLUT_LEFT_BUTTON:
{
	if (state == GLUT_DOWN)
	{
		ValidSquareFocus(lx,ly,w,h);
	}
	else
	{
	{/*Reset Objects To defaut Colors*/
		int i,sz;
		sz=DoubleLinkedListGetSize(objectList);
		for(i=0;i<sz;i++)
		{
			Shape *sh;
			sh=(Shape *)DoubleLinkedListGet(objectList,i);
			sh->resetColor();
		}
	}
	{/*Try To Move Selected Pawn*/
		int i0,i1,j0,j1;
		if (sels.toMove==NULL) break;
		
		i0=getChessBoardSquareX(sels.pX);
		i1=getChessBoardSquareX(sels.toMove->getCenterX());
		j0=getChessBoardSquareY(sels.pY);
		j1=getChessBoardSquareY(sels.toMove->getCenterY());
		if(board->move(i0,j0,i1,j1)==true)
		{
			int x0,y0;
			x0=getWindowSquareCenterX(i1);
			y0=getWindowSquareCenterX(j1);
			sels.toMove->move(x0,y0);
			
			board->upgradeValidMoves();
			updatePowns();
			
			if(((ShapePown *)(sels.toMove))->typeofpown==SKING)
			{
				refreshPowns();
			}
			sels.toMove=NULL;
			if(turn==true)
			{
				if(board->isPromote(WHITE)==true)
				{
					promotionCreateWindow();
					
				}
			}
			else
			{
				if(board->isPromote(BLACK)==true)
				{
					promotionCreateWindow();	
				}
			}
				
			turn =!turn;
			
			if(singleplay==true)
			{
				opponentPlay();
			}
		}
		else
		{
			unsigned char status;
			if(turn==true)
			{
				status = board->isMatOrPat(WHITE);
			}
			else
			{
				status = board->isMatOrPat(BLACK);
			}
			switch (status)
			{
			case IS_MAT:
				if(turn==true)
				{
					MessageBox(NULL,"BLACK Wins with MAT!","MAT",MB_OK);
				}
				else
				{
					MessageBox(NULL,"WHITE Wins with MAT!","MAT",MB_OK);
				}
				gameover=true;
				break;
			case IS_PAT:
				MessageBox(NULL,"The Game End with PAT!","PAT",MB_OK);
				gameover=true;
				break;
			case IS_OK:
				printf("\nWrong move!");	
				break;
			default:
				printf("\nError: gamithike!");
				break;
			}
			sels.toMove->move(sels.pX,sels.pY);
			sels.toMove=NULL;
		}
	}
	}
	break;
}	
case GLUT_RIGHT_BUTTON:
	break;
default:
	break;
}
glutPostRedisplay();
}

void handle_keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'q':
	case ASCII_ESCAPE:
		finilizeWindow();
		break;
	case ASCII_CTRL_Z:
		bool status;

		status = board->cancelLastMove();
		board->upgradeValidMoves();
		refreshPowns();
		glutPostRedisplay();

		if (status==true)
		{
			turn=!turn;
		}
		break;
	default:
		break;
	}
}

void initializeMenu(void)
{
	int mainmenuid;
//	glutSetWindow(wid);
	mainmenuid = glutCreateMenu(handle_main_menu);

	glutAddMenuEntry("Cancel Last Action", CANCEL_LAST_ACTION);
	glutAddMenuEntry("End Game", END_GAME);
	glutAddMenuEntry("Exit", EXIT_APPLICATION);

	glutAttachMenu(GLUT_RIGHT_BUTTON);	
}

void finilizeWindow(void)
{
	int i,isz;
	
	if(objectList==NULL)
		return;
	isz=DoubleLinkedListGetSize(objectList);
	for(i=0;i<isz;i++)
	{
		delete (Shape *)DoubleLinkedListGet(objectList,i);
	}
	DoubleLinkedListDrop(objectList);
	delete board;

	glutDestroyWindow(wid);
	glutDestroyWindow(capwid);

	objectList=NULL;

	throw "GLUT_TERMINATE";
}



void initializeWindow(char *title, int pos_X, int pos_Y,bool single)
{
	singleplay=single;
	playerSide=true;
	initializeWindow(title, pos_X,  pos_Y);
}

void initializeWindow(char *title, int pos_X, int pos_Y,bool single,bool white)
{	
	singleplay=single;
	playerSide=white;
	initializeWindow(title, pos_X,  pos_Y);
}
void initializeWindow(char *title, int pos_X, int pos_Y,bool single,bool white,bool board8x8)
{	
	singleplay=single;
	playerSide=white;
	if(board8x8==false)
	{
		boardSize=6;
	}
	else
	{
		boardSize=8;
	}
	initializeWindow(title, pos_X,  pos_Y);
}
void initializeWindow(char *title, int pos_X, int pos_Y)
{
	board = new ChessBoard();
	board->enableLogKeeping();

	//create a window
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(WWIDTH, WHEIGHT);
	glutInitWindowPosition(pos_X, pos_Y);
	wid = glutCreateWindow(title);
	
	
	loadObjects();
	turn = true;
	gameover=false;
	if(singleplay==true && playerSide==false)
	{
		opponentPlay();
	}
	

	glutDisplayFunc(display);
	glutMouseFunc(handle_mouse_click);
	glutReshapeFunc(handle_window_reshape);
//	glutPassiveMotionFunc(handle_mouse_movement);
	glutMotionFunc(handle_mouse_motion);
	glutKeyboardFunc(handle_keyboard);

	initializeMenu();


	//define the background color
	glClearColor (0.0, 0.0, 0.0, 0.0);
   	glClear(GL_COLOR_BUFFER_BIT);
	glutIdleFunc(idle);



	try {
		capturedPiecesCreateWindow(pos_X+WWIDTH+MORE_SPACE,pos_Y);
		glutMainLoop();
	}catch(const char *msg)
	{
		if (strcmp(msg, "GLUT_TERMINATE")==0)
		{
			return;
		}
	}
	
}
void idle(void)
{

	if(gameover==true)
	{
		finilizeWindow();
	}
	if(promotionType==-1)
	{
		glutSetWindow(capwid);
		glutPostRedisplay();
		glutSetWindow(wid);
		Sleep(10);
		return;
	}
	switch(promotionType)
	{
		case 0:
			board->promote(WHITE,QUEEN);
			board->promote(BLACK,QUEEN);
			break;
		case 1:
			board->promote(WHITE,ROCK);
			board->promote(BLACK,ROCK);
			
			break;
		case 2:
			board->promote(WHITE,BISHOP);
			board->promote(BLACK,BISHOP);
			break;
		case 3:
			board->promote(WHITE,KNIGHT);
			board->promote(BLACK,KNIGHT);
			break;
		default :
		{
			printf("idle:Gamithike!!!");
			return;
		}
	}
	promotionType=-1;
	sels.toMove=NULL;
	refreshPowns();
	turn =!turn;
	if(singleplay==true)
	{
		opponentPlay();
	}
}

void display(void)
{
	int i, size;
   	
	glClear(GL_COLOR_BUFFER_BIT);
	size = DoubleLinkedListGetSize(objectList);

	for (i=0;i<size;i++)
	{
		((Shape *)DoubleLinkedListGet(objectList, i))->draw();
	}
	
	glutSwapBuffers();

}
void handle_window_reshape(int x,int y)
{
	glutReshapeWindow(WWIDTH,WHEIGHT);
}

void handle_captured_window_reshape(int x,int y)
{
	glutReshapeWindow(CWWIDTH,CWHEIGHT);
}

void loadObjects(void)
{
	
	objectList=DoubleLinkedListConstruct();
	loadBoardSquares();
	loadPowns();
	objectGraphicsInit();
	
}

void loadBoardSquares(void)
{
	int  w;
	int i,j;
	int sqDim;

	
	
	w=glutGet(GLUT_WINDOW_HEIGHT);
	sqDim=w/BOARD_X;
	for(j=0;j<BOARD_Y;j++)
	{
		for(i=0;i<BOARD_X;i++)
		{
			Shape *sq;
			if((i+j)%2==1)
			{
				sq = new Square(i*(sqDim)-w/2 + sqDim/2, j*(sqDim)-w/2 + sqDim/2, sqDim/2, CLR_WHITE);	
			}
			else
			{
				sq = new Square(i*(sqDim)-w/2 + sqDim/2, j*(sqDim)-w/2 + sqDim/2, sqDim/2, CLR_BLACK);	
			}
			DoubleLinkedListAddInTail(objectList,sq);
		}
	}

}

int getWindowSquareCenterX(int i)
{
	int w;
	w=glutGet(GLUT_WINDOW_HEIGHT);
	return i*(w/BOARD_X)+(w/(2*BOARD_X)) - w/2;
}
int getWindowSquareCenterY(int i)
{
	int h;
	h=glutGet(GLUT_WINDOW_WIDTH);
	return i*(h/BOARD_Y)+(h/(2*BOARD_Y)) -h/2;
}
int getChessBoardSquareX(int x)
{
	int i,   w;


	w = glutGet(GLUT_WINDOW_WIDTH);
	x=x+w/2;
	

	for (i=0;i<BOARD_X;i++)
	{
		if (x>i*(w/BOARD_X) && x<(i+1)*(w/BOARD_X))
		{
			return i;
		}	
	}

	return -1;
}

int getChessBoardSquareY(int y)
{
	int i,  w;

	w = glutGet(GLUT_WINDOW_WIDTH);
	y=y+w/2;

	
	for (i=0;i<BOARD_Y;i++)
	{
		if (y>i*(w/BOARD_Y) && y<(i+1)*(w/BOARD_Y))
		{
			return i;
		}	
	}



	return -1;
}

void updatePowns(void)
{
	int i,  sz;

	sz = DoubleLinkedListGetSize(objectList);

	for (i=0; i<sz;i++)
	{
		Shape *sh;

		sh = (Shape *)DoubleLinkedListGet(objectList, i);
		if (sh->movementIsAvailable()==true)
		{
			int x, y, xi, yi;
			ShapePown *shp;
			
			shp = (ShapePown *)sh;
			x = shp->getCenterX();
			y = shp->getCenterY();
			xi = getChessBoardSquareX(x);
			yi = getChessBoardSquareX(y);
			
			if(board->getPown(xi, yi)!=NULL)
			{
				if (board->getPown(xi, yi)->getTeam()!=shp->getTeam())
				{	
					delete shp;
					DoubleLinkedListDel(objectList, i);
					i--;
					sz--;
				}	
			}
		}
	}	
}


void loadPowns(void)
{
	int i,j;
	int dim=30;
	unsigned char clr;
	Shape *sh=NULL;

	for (i=0;i<BOARD_X;i++)
	{
		for (j=0;j<BOARD_Y;j++)
		{
			if (board->getPown(i,j)!=NULL)
			{
				if (board->getPown(i,j)->getTeam()==WHITE)
				{
					clr = CLR_BLUE;
				}else
				{
					clr = CLR_RED;
				}

				switch (board->getPown(i,j)->getType())
				{
				case SOLDIER:
					sh = new ShapePown(getWindowSquareCenterX(i),getWindowSquareCenterY(j),dim,clr,SSOLDIER, board->getPown(i,j)->getTeam());
					break;
				case KNIGHT:
					sh = new ShapePown(getWindowSquareCenterX(i),getWindowSquareCenterY(j),dim,clr,SKNIGHT, board->getPown(i,j)->getTeam());
					break;
				case KING:
					sh = new ShapePown(getWindowSquareCenterX(i),getWindowSquareCenterY(j),dim,clr,SKING, board->getPown(i,j)->getTeam());
					break;
				case QUEEN:
					sh = new ShapePown(getWindowSquareCenterX(i),getWindowSquareCenterY(j),dim,clr,SQUEEN, board->getPown(i,j)->getTeam());
					break;
				case ROCK:
					sh = new ShapePown(getWindowSquareCenterX(i),getWindowSquareCenterY(j),dim,clr,SROCK, board->getPown(i,j)->getTeam());
					break;
				case BISHOP:
					sh = new ShapePown(getWindowSquareCenterX(i),getWindowSquareCenterY(j),dim,clr,SBISHOP, board->getPown(i,j)->getTeam());
					break;
				default:
					break;
				}
				DoubleLinkedListAddInTail(objectList, sh);
			}
		}
			
	}
}

void changeFocusedColor(int x, int y, struct color clr)
{
	int i, size;

	size = DoubleLinkedListGetSize(objectList);

	for (i=0;i<size;i++)
	{
		Shape *s;
		s = (Shape *)DoubleLinkedListGet(objectList, i);
		if (s->checkIfInside(x,y)==true && s->movementIsAvailable()==false)
		{
			struct color cl1;
			cl1=s->getColor();
			
			cl1=alternateColor(cl1,clr,0.5);
			s->setColor(cl1.red,cl1.green,cl1.blue);
		}
	}
}

void displayCapturedPieces(void)
{
	int i, isz, wxi, wyi, bxi, byi;
	unsigned char ahead_status;
	DoubleLinkedList *cpt;

	
	glClear(GL_COLOR_BUFFER_BIT);

	
	ahead_status = board->getFirstCommingTeam();
	switch (ahead_status)
	{
	case WHITE_AHEAD:
		glColor3f(0.8f,0.3f,0.3f);
		
		if (DoubleLinkedListGetSize(board->getCapturedList())==1)
		{
			glutSetWindowTitle("Graveyard: Blue drew the first blood");
		}else
		{
			glutSetWindowTitle("Graveyard: Red Needs Graves");
		}
		break;
	case BLACK_AHEAD:
		glColor3f(0.3f,0.3f,0.8f);
		
		if (DoubleLinkedListGetSize(board->getCapturedList())==1)
		{
			glutSetWindowTitle("Graveyard: Red drew the first blood");
		}else
		{
			glutSetWindowTitle("Graveyard: Blue Needs Graves");
		}
		break;
	case EQUALITY:
		glColor3f(1.0f,1.0f,1.0f);
		if (DoubleLinkedListGetSize(board->getCapturedList())==0)
		{
			glutSetWindowTitle("Graveyard: Waiting the first corpse");
		}else
		{
			glutSetWindowTitle("Graveyard: Same number of graves");
		}
		break;
	}
	

	

	glBegin(GL_POLYGON);
	glVertex2f(-0.35f, -0.06f+0.03f);
	glVertex2f(-0.35f,  0.06f+0.03f);
	glVertex2f( 0.35f,  0.06f+0.03f);
	glVertex2f( 0.35f, -0.06f+0.03f);
	glEnd();
	glFlush();
	
	glBegin(GL_POLYGON);
	glVertex2f(-0.1f,  0.3f);
	glVertex2f( 0.1f,  0.3f);
	glVertex2f( 0.1f, -0.5f);
	glVertex2f(-0.1f, -0.5f);
	glEnd();
	glFlush();
	

	cpt = board->getCapturedList();
	if (cpt==NULL) 
	{
		glutSwapBuffers();
		return;
	}

	isz = DoubleLinkedListGetSize(cpt);
	if (isz==0)
	{
		glutSwapBuffers();
		return;
	}

	for (i=0,bxi=-CWWIDTH/2+30,byi=CWHEIGHT/2-30, wxi=-CWWIDTH/2+30,wyi=-CWHEIGHT/2+30;i<isz;i++)
	{
		ShapePown *sp;
		Pown *p;
		p = (Pown *)DoubleLinkedListGet(cpt, i);
		if (p==NULL) break;

	
		if (p->getTeam()==WHITE)
		{
			switch (p->getType())
			{
			case SOLDIER:
				sp = new ShapePown(wxi,wyi,30,CLR_BLUE,SSOLDIER,WHITE);
				break;
			case QUEEN:
				sp = new ShapePown(wxi,wyi,30,CLR_BLUE,SQUEEN,WHITE);
				break;
			case ROCK:
				sp = new ShapePown(wxi,wyi,30,CLR_BLUE,SROCK,WHITE);
				break;
			case KNIGHT:
				sp = new ShapePown(wxi,wyi,30,CLR_BLUE,SKNIGHT,WHITE);
				break;
			case BISHOP:
				sp = new ShapePown(wxi,wyi,30,CLR_BLUE,SBISHOP,WHITE);
				break;
			}
			wxi+=70;

		}else
		{
			switch (p->getType())
			{
			case SOLDIER:
				sp = new ShapePown(bxi,byi,30,CLR_RED,SSOLDIER,BLACK);
				break;
			case QUEEN:
				sp = new ShapePown(bxi,byi,30,CLR_RED,SQUEEN,BLACK);
				break;
			case ROCK:
				sp = new ShapePown(bxi,byi,30,CLR_RED,SROCK,BLACK);
				break;
			case KNIGHT:
				sp = new ShapePown(bxi,byi,30,CLR_RED,SKNIGHT,BLACK);
				break;
			case BISHOP:
				sp = new ShapePown(bxi,byi,30,CLR_RED,SBISHOP,BLACK);
				break;
			}
			bxi+=70;
		}

		if (bxi>CWWIDTH/2-30)
		{
			bxi=-CWWIDTH/2+30;
			byi-=65;
		}
		if (wxi>CWWIDTH/2-30)
		{
			wxi=-CWWIDTH/2+30;
			wyi+=65;
		}
		
		sp->draw();
		delete sp;
	}

	glutSwapBuffers();
}

void handle_main_menu(int v)
{
	switch (v)
	{
	case CANCEL_LAST_ACTION:
		{
			bool status;

			status = board->cancelLastMove();
			board->upgradeValidMoves();
			refreshPowns();
			glutPostRedisplay();

			if (status==true)
			{
				turn=!turn;
			}
			break;
		}
	case END_GAME:
		finilizeWindow();
		break;
	case EXIT_APPLICATION:
		exit(EXIT_SUCCESS);
		break;
	default:
		break;
	}
}

