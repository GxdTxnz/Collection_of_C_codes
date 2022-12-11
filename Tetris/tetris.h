#ifndef _TETRIS_H_
#define _TETRIS_H_


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include <signal.h>
#include <string.h>

#define WIDTH	10
#define HEIGHT	22
#define NOTHING	0
#define QUIT	'q'
//
#define SPACE	55
#define NUM_OF_SHAPE	7
#define NUM_OF_ROTATE	4
#define BLOCK_HEIGHT	4
#define BLOCK_WIDTH	4
#define BLOCK_NUM	2

// menu
#define MENU_PLAY '1'
#define MENU_RANK '2'
#define MENU_EXIT '4'
#define MENU_HARD '5'

//
#define NAMELEN 16

#define CHILDREN_MAX 36
//
#define MAX(x,y) (x>y ? x : y)

typedef struct _RecNode
{
	int lv,score;
	char (*f)[WIDTH];
	struct _RecNode *c[CHILDREN_MAX];
}RecNode;

const char block[NUM_OF_SHAPE][NUM_OF_ROTATE][BLOCK_HEIGHT][BLOCK_WIDTH] =
{
	{/*[0][][][]					▩▩▩▩*/
		{/*[][0][][]*/
			{0, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}
		},
		{/*[][1][][]*/
			{0, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 0, 0}			
		},
		{/*[][2][][]*/
			{0, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}			
		},
		{/*[][3][][]*/
			{0, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 0, 0}
		}
	},
	{/*[1][][][];					  ▩▩▩*/
		{/*[][0][][]				      ▩*/
			{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 1, 1, 1}, {0, 0, 0, 1}
		},
		{/*[][1][][]*/
			{0, 0, 0, 0}, {0, 0 ,1, 1}, {0, 0, 1, 0}, {0, 0, 1, 0}
		},
		{/*[][2][][]*/
			{0, 0, 0, 0}, {0, 1, 0, 0}, {0, 1, 1, 1}, {0, 0, 0, 0}
		},
		{/*[][3][][]*/
			{0, 0, 0, 0}, {0, 0, 1, 0}, {0, 0, 1, 0}, {0, 1, 1, 0}
		}
	},
	{/*[2][][][];					  ▩▩▩*/
		{/*[][0][][]				  ▩*/
			{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 1, 1, 1}, {0, 1, 0, 0}
		},
		{/*[][1][][]*/
			{0, 0, 0, 0}, {0, 0, 1, 0}, {0, 0, 1, 0}, {0, 0, 1, 1}
		},
		{/*[][2][][]*/
			{0, 0, 0, 0}, {0, 0, 0, 1}, {0, 1, 1, 1}, {0, 0, 0, 0}
		},
		{/*[][3][][]*/
			{0, 0, 0, 0}, {0, 1, 1, 0}, {0, 0, 1, 0}, {0, 0, 1, 0}
		}
	},
	{/*[3][][][];					  ▩▩▩*/
		{/*[][0][][]				    ▩*/
			{0, 0, 0, 0}, {0, 1, 0, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}
		},
		{/*[][1][][]*/
			{0, 0, 0, 0}, {0, 1, 0, 0}, {1, 1, 0, 0}, {0, 1, 0, 0}
		},
		{/*[][2][][]*/
			{0, 0, 0, 0}, {0, 0, 0, 0}, {1, 1, 1, 0}, {0, 1, 0, 0}
		},
		{/*[][3][][]*/
			{0, 0, 0, 0}, {0, 1, 0, 0}, {0, 1, 1, 0}, {0, 1, 0, 0}
		}
	},
	{/*[4][][][];					  ▩▩*/
		{/*[][0][][]				  ▩▩*/
			{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 1, 1, 0}, {0, 1, 1, 0}
		},
		{/*[][1][][]*/
			{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 1, 1, 0}, {0, 1, 1, 0}
		},
		{/*[][2][][]*/
			{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 1, 1, 0}, {0, 1, 1, 0}
		},
		{/*[][3][][]*/
			{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 1, 1, 0}, {0, 1, 1, 0}
		}
	},
	{/*[5][][][];					  ▩▩*/
		{/*[][0][][]				▩▩*/
			{0, 0, 0, 0}, {0, 0, 1, 1}, {0, 1, 1, 0}, {0, 0, 0, 0}
		},
		{/*[][1][][]*/
			{0, 0, 0, 0}, {0, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 1, 0}			
		},
		{/*[][2][][]*/
			{0, 0, 0, 0}, {0, 0, 1, 1}, {0, 1, 1, 0}, {0, 0, 0, 0}			
		},
		{/*[][3][][]*/
			{0, 0, 0, 0}, {0, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 1, 0}			
		}
	},
	{/*[6][][][];					▩▩*/
		{/*[][0][][]				  ▩▩*/
			{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 1, 1, 0}, {0, 0, 1, 1}
		},
		{/*[][1][][]*/
			{0, 0, 0, 0}, {0, 0, 1, 0}, {0, 1, 1, 0}, {0, 1, 0, 0}
		},
		{/*[][2][][]*/
			{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 1, 1, 0}, {0, 0, 1, 1}
		},
		{/*[][3][][]*/
			{0, 0, 0, 0}, {0, 0, 1, 0}, {0, 1, 1, 0}, {0, 1, 0, 0}
		}
	}
};

char field[HEIGHT][WIDTH];
int nextBlock[BLOCK_NUM];

char field[HEIGHT][WIDTH];
int nextBlock[BLOCK_NUM];
int blockRotate,blockY,blockX;
int score;
int gameOver=0;
int timed_out;
int recommendR,recommendY,recommendX;
RecNode *recRoot;


void InitTetris();
void DrawOutline();

int GetCommand();

int ProcessCommand(int command);

void BlockDown(int sig);

int CheckToMove(char f[HEIGHT][WIDTH],int currentBlock,int blockRotate, int blockY, int blockX);

void DrawChange(char f[HEIGHT][WIDTH],int command,int currentBlock,int blockRotate, int blockY, int blockX);

void DrawField();

void AddBlockToField(char f[HEIGHT][WIDTH],int currentBlock,int blockRotate, int blockY, int blockX);

int DeleteLine(char f[HEIGHT][WIDTH]);

void gotoyx(int y, int x);

void DrawNextBlock(int *nextBlock);
void PrintScore(int score);

void DrawBox(int y,int x, int height, int width);

void DrawBlock(int y, int x, int blockID,int blockRotate,char tile);

void DrawShadow(int y, int x, int blockID,int blockRotate);

void play();
void hardplay();

char menu();
void createRankList();

typedef struct _Node *treePointer;
typedef struct _Node
{
	char name[NAMELEN];
	int score;
	treePointer left,right;
}Node;

treePointer make_node();
int get_height(treePointer node);
int balanced_num(treePointer node);

treePointer LL(treePointer parent);
treePointer LR(treePointer parent);
treePointer RR(treePointer parent);
treePointer RL(treePointer parent);
treePointer rotate(treePointer *node);

treePointer insert(treePointer *root, char *name, int score);
void delete_node();

void inorderTraversal(FILE *fp, int *count, treePointer node, int x,int y,int deleteFlag);
void inorderTraversal_name(char *name, treePointer node);

treePointer ROOT=NULL;
int node_num=0;

void rank();
void rank_1();
void rank_2();
int find_num=0;
void rank_3();
treePointer CURR=NULL, PAR=NULL;
int writeFlag=0;
void rank_4();

void writeRankFile();

void newRank(int score);

int recommend(RecNode *root);

void recommendedPlay();

#endif
