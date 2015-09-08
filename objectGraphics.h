/*|============================================================================|*
 *| Chess Application: file objectGraphics.h                                   |*
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


#include <windows.h>

#include "GL/glut.h"
#include "GL/gl.h"
#include "ChessBoard.h"
/*================================================*/


/*========== Libraries used ======================*/
#pragma comment(lib, "GL/opengl32.lib")
//#pragma comment(lib, "GL/glut32.lib")
#pragma comment(lib, "GL/x64/glut32.lib")

/*================================================*/


#define CLR_RED     10
#define CLR_GREEN   11
#define CLR_BLUE    12
#define CLR_BLACK   13
#define CLR_CYAN    14
#define CLR_WHITE   15
#define CLR_YELLOW  16
#define CLR_MAGENTA 17


#ifndef _OBJECTGRAPHICS_H_
	#define  _OBJECTGRAPHICS_H_


enum shapepowntype {SSOLDIER, SKING, SQUEEN, SKNIGHT, SROCK, SBISHOP};

struct color {
	float red;
	float green;
	float blue;
};
extern struct color alternateColor(struct color clr,struct color cl1,float f1);

extern void objectGraphicsInit();

class Shape
{
protected:
	int cX;
	int cY;
	int dimension;
	bool canBeMoved;
	struct color default_clr;
	struct color clr;

public:
	Shape(void);
	Shape(int x, int y, int dim, unsigned char colortype);
	Shape(int x, int y, int dim, float red, float green, float blue);
	~Shape(void);

	int getCenterX(void);
	int getCenterY(void);
	int getDimension(void);
	struct color getColor(void);
	void setColor(float red, float green, float blue);
	void setColor(unsigned char colortype);
	void resetColor(void);
	void move(int x, int y);
	bool movementIsAvailable(void);
	virtual void draw(void) = 0;
	virtual bool checkIfInside(int x, int y) = 0;
};

class Square : public Shape
{
public:
	Square(int x, int y, int dim, unsigned char colortype);
	Square(int x, int y, int dim, float red, float green, float blue);

	void draw(void);
	bool checkIfInside(int x, int y);
};


class ShapePown : public Shape
{
	enum team_ team;
public:

	ShapePown(int x, int y, int dim, unsigned char colortype,enum shapepowntype type, enum team_ pteam);
	ShapePown(int x, int y, int dim, float red, float green, float blue,enum shapepowntype type, enum team_ pteam);

	void draw(void);
	enum team_ getTeam(void);
	bool checkIfInside(int x, int y);
	int typeofpown;
};

#endif
