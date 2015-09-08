/*|============================================================================|*
 *| Chess Application: file objectGraphics.cpp                                 |*
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
#include "objectGraphics.h"
#include "Rasters.h"
/*================================================*/

/*Globals*/
/*Rasters Of Bishop*/
GLubyte BishopRaster [RASTER_HEIGHT][RASTER_WIDTH][3];
/*Rasters Of Pawn*/
GLubyte PawnRaster [RASTER_HEIGHT][RASTER_WIDTH][3];
/*Rasters Of King*/
GLubyte KingRaster [RASTER_HEIGHT][RASTER_WIDTH][3];
/*Rasters Of Queen*/
GLubyte QueenRaster [RASTER_HEIGHT][RASTER_WIDTH][3];
/*Rasters Of Knight*/
GLubyte KnightRaster [RASTER_HEIGHT][RASTER_WIDTH][3];
/*Rasters Of Rock*/
GLubyte RockRaster [RASTER_HEIGHT][RASTER_WIDTH][3];


bool rasterIsFixed=false;

/*General functions*/
void drawRaster(GLubyte raster[RASTER_HEIGHT][RASTER_WIDTH][3] , int x,int y,int dim, struct color clr);
void drawRaster(GLubyte raster[RASTER_HEIGHT][RASTER_WIDTH][3] , int x,int y,int dim, struct color clr ,int smooth);
void objectGraphicsInit()	/*Loading Rasters From Rasters.h*/
{
	int i,j;
	if(rasterIsFixed==true)
		return;
	rasterIsFixed=true;
	for(i=RASTER_HEIGHT-1;i>=0;i--)
	{
		for(j=0;j<RASTER_WIDTH;j++)
		{
			HEADER_PIXEL(Queen_data,QueenRaster[i][j]);
			/**/
			HEADER_PIXEL(Pawn_data,PawnRaster[i][j]);
			HEADER_PIXEL(King_data,KingRaster[i][j]);
			HEADER_PIXEL(Knight_data,KnightRaster[i][j]);
			HEADER_PIXEL(Rock_data,RockRaster[i][j]);
			HEADER_PIXEL(Bishop_data,BishopRaster[i][j]);
		}
	}
}
void drawPixel(int x, int y, struct color clr)
{
	int h, w;
	float x0, y0;

	h = glutGet(GLUT_WINDOW_HEIGHT);
	w = glutGet(GLUT_WINDOW_WIDTH);

	x0 = (float)x/(float)w;	
	y0 = (float)y/(float)h;

	glColor3d(clr.red, clr.green, clr.blue);

	glBegin(GL_POINTS);
	glVertex2f(x0, y0);
	glEnd();
	glFlush();
}

void drawRaster(GLubyte raster[RASTER_HEIGHT][RASTER_WIDTH][3] , int x,int y,int dim, struct color clr)
{
	drawRaster(raster ,x,y,dim,clr ,160);
}

void drawRaster(GLubyte raster[RASTER_HEIGHT][RASTER_WIDTH][3] , int x,int y,int dim, struct color clr ,int smooth)
{
	float x0, y0;
	int h, w;
	int i,j;
	h = glutGet(GLUT_WINDOW_HEIGHT);
	w = glutGet(GLUT_WINDOW_WIDTH);
	for(j=0;j<RASTER_HEIGHT;j++)
	{
		for(i=0;i<RASTER_WIDTH;i++)
		{
			if(raster[j][i][0]<smooth || raster[j][i][1]<smooth || raster[j][i][2]<smooth)
			{
				struct color cl1;
				float volume;
					cl1.red=clr.green;
					cl1.green=clr.blue;
					cl1.blue=clr.red;
					volume=0.2+(i+j)/300.0;

				
				cl1=alternateColor(clr,cl1,volume);
				glColor3d(cl1.red,cl1.green,cl1.blue);
				x0 = (float)(x+i-dim)/((float)w/2.0f);	
				y0 = (float)(y+j-dim)/((float)h/2.0f);
				glBegin(GL_POINTS);
				glVertex2f(x0,y0);
				glEnd();
				//drawPixel(2*(x+i-dim), 2*(y+j-dim), cl1);
			}
		}
	}
	glFlush();
}
void drawPown(int x, int y, int dim, struct color clr,int typeofpown)
{
	switch(typeofpown)
	{
		case SSOLDIER:
			{
				drawRaster(PawnRaster,x,y,dim,clr,210);
				break;
			}
		case SKING:
			{
				drawRaster(KingRaster,x,y,dim,clr);
				break;
			}
		case SQUEEN:
			{
				drawRaster(QueenRaster,x,y,dim,clr);
				break;
			}
		case SKNIGHT:
			{
				drawRaster(KnightRaster,x,y,dim,clr);
				break;
			}
		case SBISHOP:
			{
				drawRaster(BishopRaster,x,y,dim,clr);
				break;
			}
		case SROCK:
			{
				drawRaster(RockRaster,x,y,dim,clr);
				break;
			}
		default:
		{
			
		}
	
	}	
}
void drawSquare(int x, int y, int dim, struct color clr)
{
	float x0, y0;
	int h, w;

	h = glutGet(GLUT_WINDOW_HEIGHT);
	w = glutGet(GLUT_WINDOW_WIDTH);

	glColor3d(clr.red, clr.green, clr.blue);

	glBegin(GL_POLYGON);

	x0 = (float)(x-dim)/((float)w/2.0f);	
	y0 = (float)(y-dim)/((float)h/2.0f);
	glVertex2f(x0, y0);

	x0 = (float)(x-dim)/((float)w/2.0f);	
	y0 = (float)(y+dim)/((float)h/2.0f);
	glVertex2f(x0, y0);

	x0 = (float)(x+dim)/((float)w/2.0f);	
	y0 = (float)(y+dim)/((float)h/2.0f);
	glVertex2f(x0, y0);

	x0 = (float)(x+dim)/((float)w/2.0f);	
	y0 = (float)(y-dim)/((float)h/2.0f);
	glVertex2f(x0, y0);
	
	glEnd();
	glFlush();
}

/*Class Shape functions*/

Shape::Shape(void)
{
	canBeMoved = false;
}

Shape::Shape(int x, int y, int dim, unsigned char colortype)
{
	setColor(colortype);
	default_clr.red=clr.red;
	default_clr.green=clr.green;
	default_clr.blue=clr.blue;
	canBeMoved = false;
	cX = x;
	cY = y;
	dimension = dim;	
}

Shape::Shape(int x, int y, int dim, float red, float green, float blue)
{
	setColor(red, green, blue);
	default_clr.red=clr.red;
	default_clr.green=clr.green;
	default_clr.blue=clr.blue;
	canBeMoved = false;
	cX = x;
	cY = y;
	dimension = dim;
}

Shape::~Shape(void)
{
	;
}

int Shape::getCenterX(void)
{
	return cX;
}

int Shape::getCenterY(void)
{
	return cY;
}

int Shape::getDimension(void)
{
	return dimension;
}

struct color Shape::getColor(void)
{
	return clr;
}

void Shape::setColor(float red, float green, float blue)
{
	clr.red = red;
	clr.green = green;
	clr.blue = blue;
}

void Shape::resetColor(void)
{
	setColor(default_clr.red, default_clr.green, default_clr.blue);
}

void Shape::setColor(unsigned char colortype)
{
	switch (colortype)
	{
	case CLR_RED:
		setColor(1.0f, 0.0f, 0.0f);
		break;
	case CLR_BLUE:
		setColor(0.0f, 0.0f, 1.0f);
		break;
	case CLR_GREEN:
		setColor(0.0f, 1.0f, 0.0f);
		break;
	case CLR_BLACK:
		setColor(0.0f, 0.0f, 0.0f);
		break;
	case CLR_WHITE:
		setColor(1.0f, 1.0f, 1.0f);
		break;
	case CLR_MAGENTA:
		setColor(1.0f, 0.0f, 1.0f);
		break;
	case CLR_YELLOW:
		setColor(1.0f, 1.0f, 0.0f);
		break;
	case CLR_CYAN:
		setColor(0.0f, 1.0f, 1.0f);
		break;
	default:
		break;
	}
}


void Shape::move(int x, int y)
{
	cX=x;
	cY=y;
}

bool Shape::movementIsAvailable(void)
{
	return canBeMoved;
}

/*Class Square functions*/

Square::Square(int x, int y, int dim, unsigned char colortype)
{
	setColor(colortype);
	default_clr.red=clr.red;
	default_clr.green=clr.green;
	default_clr.blue=clr.blue;
	canBeMoved = false;
	cX = x;
	cY = y;
	dimension = dim;		
}


Square::Square(int x, int y, int dim, float red, float green, float blue)
{
	setColor(red, green, blue);
	default_clr.red=clr.red;
	default_clr.green=clr.green;
	default_clr.blue=clr.blue;
	canBeMoved = false;
	cX = x;
	cY = y;
	dimension = dim;
}

void Square::draw(void)
{
	drawSquare(cX, cY, dimension, clr);
}

bool Square::checkIfInside(int x, int y)
{
	if ((y>=(cY-dimension) && y<=(cY+dimension)) &&
		(x>=(cX-dimension) && x<=(cX+dimension))    )
	{
		return true;
	}

	return false;
}


/*Class Pown functions*/

ShapePown::ShapePown(int x, int y, int dim, unsigned char colortype,enum shapepowntype type, enum team_ pteam)
{
	setColor(colortype);
	default_clr.red=clr.red;
	default_clr.green=clr.green;
	default_clr.blue=clr.blue;
	canBeMoved = true;
	cX = x;
	cY = y;
	dimension = dim;
	typeofpown=type;
	team = pteam;
}


ShapePown::ShapePown(int x, int y, int dim, float red, float green, float blue,enum shapepowntype type, enum team_ pteam)
{
	setColor(red, green, blue);
	default_clr.red=clr.red;
	default_clr.green=clr.green;
	default_clr.blue=clr.blue;
	canBeMoved = true;
	cX = x;
	cY = y;
	dimension = dim;
	typeofpown=type;
	team = pteam;
}

void ShapePown::draw(void)
{
	//drawSquare(cX, cY, dimension, clr);
	drawPown(cX, cY, dimension, clr,typeofpown);
}

bool ShapePown::checkIfInside(int x, int y)
{
	if ((y>=(cY-dimension) && y<=(cY+dimension)) &&
		(x>=(cX-dimension) && x<=(cX+dimension))    )
	{
		return true;
	}

	return false;
}

enum team_ ShapePown::getTeam(void)
{
	return team;
}

struct color alternateColor(struct color clr,struct color cl1,float f1)
{
	struct color res;
	float fres;
	float f;
	if(f1>1.0 || f1<0.0)
	{
		f=0.2f;
	}
	else
	{
		f=f1;
	}

	fres=clr.red;
	if(fres>0.5)
	{
		if(cl1.red<0.5)
		{
			fres-=f;
		}
	}else
	{
		if(cl1.red>0.5)
		{
			fres+=f;
		}
	}
	res.red=fres;
	
	fres=clr.green;
	if(fres>0.5)
	{
		if(cl1.green<0.5)
		{
			fres-=f;
		}
	}else
	{
		if(cl1.green>0.5)
		{
			fres+=f;
		}
	}
	res.green=fres;

	fres=clr.blue;
	if(fres>0.5)
	{
		if(cl1.blue<0.5)
		{
			fres-=f;
		}
	}else
	{
		if(cl1.blue>0.5)
		{
			fres+=f;
		}
	}
	res.blue=fres;

	
	return res;
}


