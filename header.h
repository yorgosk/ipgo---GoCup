/* File: header.h */
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

void read();
void seki(int, int, int, int, int**, int**, int*, int**);
void placefreehandicap(int, int**, int**, int, unsigned int);
void countlib( int, int**, int**, int**);
void boardsize(int, int**);
int  count(int, int, int, int, int**, int**);
void showboard(int, int**);
int play(int, int**, int**, int**);
int genmove(int, int**, int**, int**, int, int***, unsigned int, int, int, float, int);
void clear(int, int**, int**, int);
void fixedhandicap(int, int**, int**, int);
float final_score(int, int**, int**, int, int**, float);
void undo(int**, int***, int, int);
int checkboard(int**, int);
int ko(int, int**, int***, int, int**, int**, int);
int setfreehandicap(int **, int);
int valid(int, int, int, int, int**, int**, int**, int, int***, int);
float minimax(int, int**, int, int, int*, int*, float, float, int, int **, int, int**, float, int, int***, int, int **, int**,int**);
int isterminal(int**, int, int, int**, int**, int, int***, int);
int heuristic(int, int**, int**, int, int**, float, int);


