/*|============================================================================|*
 *| Chess Application: file boardGraphics.h                                    |*
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

/*=========== Other files used =================*/
#include "objectGraphics.h"
/*==============================================*/

/*Defines for the main window dimensions.*/
#define WWIDTH 600
#define WHEIGHT WWIDTH

/*Defines for the captured pieces window dimensions.*/
#define CWWIDTH  370
#define CWHEIGHT 600

/*Is the space that will be added to the sum of x position of the main window
  and the main window's width, in order to create the captured pieces window 
  in the right side of the main window.*/
#define MORE_SPACE 15

/*Glut 3.00 and openGL initialization functions*/
extern void initializeWindow(char *title, int pos_X, int pos_Y);
extern void initializeWindow(char *title, int pos_X, int pos_Y, bool singe);
extern void initializeWindow(char *title, int pos_X, int pos_Y , bool single ,bool white);
extern void initializeWindow(char *title, int pos_X, int pos_Y,bool single,bool white,bool board8x8);
