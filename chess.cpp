/*|============================================================================|*
 *| Chess Application: file Chess.cpp                                          |*
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
#include <stdio.h>
/*================================================*/

#define EOL {char ch;while(scanf("%c",&ch)&& ch!='\n');}



int menu()
{
	char single;
	char side;
	char type;
	char title[100];

	do
	{
		
		printf("\nPress :");
		printf("\n1\tto start a single play game");
		printf("\n2\tto start a multy play game");
		printf("\n0\tto Exit");
		printf("\n=>");
		scanf("%c",&single);
	}while(single!='1' && single!='2' && single !='0');
	EOL
	if(single=='0')
	{
		return 0;
	}
	else if(single=='1')
	{
		do
		{
			printf("\nPress :");
			printf("\n1\tfor white pawns");
			printf("\n2\tfor black pawns");
			printf("\n0\tto go back");
			printf("\n=>");
			scanf("%c",&side);
		}while(side!='1' && side!='2' && side !='0');
		EOL
		if(side=='0')
		{
			return menu();	
		}
	}
	

	{
		do
		{
			printf("\nPress :");
			printf("\n1\tfor 6x6 Chess board");
			printf("\n2\tfor 8x8 Chess board");
			printf("\n0\tto go back");
			printf("\n=>");
			scanf("%c",&type);
		}while(type!='1' && type!='2' && type !='0');
		if(type=='0')
		{
			EOL
			return menu();	
		}

	}


	if(single=='1' && side=='1' && type=='1')
	{
		sprintf(title, "ChessWar 6x6 - Single Player");
		initializeWindow(title, 0, 0,true, true,false);
	}
	else if(single=='1' && side=='1' && type=='2')
	{
		sprintf(title, "ChessWar 6x6 - Single Player");
		initializeWindow(title, 0, 0,true, true,true);
	}
	else if(single=='1' && side=='2' && type=='1')
	{
		sprintf(title, "ChessWar 6x6 - Single Player");
		initializeWindow(title, 0, 0,true, false,false);
	}
	else if(single=='1' && side=='2' && type=='2')
	{
		sprintf(title, "ChessWar 8x8 - Single Player");
		initializeWindow(title, 0, 0,true, false,true);
	}
	else if(type=='1')
	{
		sprintf(title, "ChessWar 6x6 - Two Players");
		initializeWindow(title, 0, 0,false,true,false);
	}		
	else
	{
		sprintf(title, "ChessWar 8x8 - Two Players");
		initializeWindow(title, 0, 0,false,true,true);
	}
	return 1;
}
int main()
{
	while(1)
	{
		if(menu()==0)
			exit(0);
	}
}
