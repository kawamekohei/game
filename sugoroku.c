#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>

#define TRUE 1
#define FALSE 0
//Field size
#define WIDTH 4
#define HIEGHT 20
//player num
#define MAX 4
//Field States
#define EMPTY 0
#define GOAL -1
#define WALL -2
//Player States
#define DOUBLE 1

typedef struct {
  int num;
  int x;
  int y;
  int pow_up;
  int pow_down;
  int dice_num;
} player;

void game();
void p_init(player p[]);
void f_init(int field[][WIDTH], player p[], int entry);
void field_disp(int field[][WIDTH]);
void dice(player p[],int entry);
int walk(player p[], int field[][WIDTH], int player);

int main(void)
{
	char c;
	int Continue = TRUE;
  srand((unsigned)time(NULL));
  
  while (Continue == TRUE) {
	  game();
	  puts("");
	  printf("Continue? (y/n) :");
	  scanf("%c", &c);
	  scanf("%c", &c);
	  if (c == 'n') {
		  Continue = FALSE;
	  }
  }

  return 0;
}

void game()
{
	int i;
	int field[HIEGHT][WIDTH];
	int entry;
	int flag = FALSE;
	int dice_num;
	int count;
	int dummy;

	player p[MAX];

	printf("Number of entry (MAX:4) : ");
	scanf("%d", &entry);

	p_init(p);
	f_init(field,p,entry);

	system("clear");

	//ゴールするまでループ
	while (flag != TRUE) {
	  dice(p, entry);
	  //参加プレイヤーの数だけループ
	  for (i = 0; i < entry; i++) {
	    //ダイスの数だけループ（プレイヤー移動中）
	    for (dice_num = p[i].dice_num; dice_num > 0; dice_num--) {
	      printf("Payer%d Turn\n", i+1);
	      printf("Your remainig num : %d\n",dice_num);
	      field_disp(field);
	      flag = walk(p,field,i);
	      system("clear");
	      if (flag == TRUE) {
		printf("Player%d WIN!!!!!\n", i + 1);
		break;
	      }
	    }
	    if (flag == TRUE) {
	      break;
	    }
	  }
	}
	
}

void p_init(player p[])
{
	int i;
	int r1, r2;
	int keep;

	for (i = 0; i < MAX; i++) {
		p[i].num = i + 1;
		p[i].x = i;
		p[i].y = 0;
		p[i].pow_up = EMPTY;
		p[i].pow_down = EMPTY;
		p[i].dice_num = 0;

	}

	//Player Position Shufful
	for (i = 0; i < MAX; i++) {
		r1 = rand() % 4;
		r2 = rand() % 4;
		keep = p[r1].x;
		p[r1].x = p[r2].x;
		p[r2].x = keep;
	}
}

void f_init(int field[][WIDTH], player p[], int entry)
{
	int i, j;

	for (i = 0; i < HIEGHT; i++) {
		for (j = 0; j < WIDTH; j++) {
			field[i][j] = EMPTY;
		}
	}
	//Wall set
	for (i = 1; i < HIEGHT-1; i++) {
		if (i % 2 == 0) {
			for (j = 0; j < rand() % 3 + 1; j++) {
				field[i][rand() % 4] = WALL;
			}
		}
	}
	//Player set
	for (i = 0; i < entry; i++) {
		field[p[i].y][p[i].x] = p[i].num;
	}
	//Goal set
	field[HIEGHT-1][rand() % 4] = GOAL;
}

void field_disp(int field[][WIDTH])
{
	int i, j;

	for (i = 0; i < HIEGHT; i++) {
		for (j = 0; j < WIDTH; j++) {
			switch (field[i][j])
			{
			case EMPTY :
				printf("□");
				break;
			case 1 :
				printf("１");
				break;
			case 2:
				printf("２");
				break;
			case 3:
				printf("３");
				break;
			case 4:
				printf("４");
				break;
			case GOAL :
				printf("★");
				break;
			case WALL :
				printf("■");
				break;
			default:
				break;
			}
		}
		puts("");
	}
}

void dice(player p[], int entry)
{
	int i;

	for (i = 0; i < entry; i++) {
		p[i].dice_num = rand() % 6 + 1;
	}
}

int walk(player p[], int field[][WIDTH], int player)
{
	int key;
	int error = TRUE;
	int x, y;

	x = p[player].x;
	y = p[player].y;

	field[y][x] = EMPTY;

	while (error == TRUE) {
		x = p[player].x;
		y = p[player].y;
		scanf("%d", &key);

		switch (key)
		{
		case 8:
			y--;
			if (y >= 0) { error = FALSE; }
			break;
		case 2:
			y++;
			if (y < HIEGHT) { error = FALSE; }
			break;
		case 4:
			x--;
			if (x >= 0) { error = FALSE; }
			break;
		case 6:
			x++;
			if (x < WIDTH) { error = FALSE; }
			break;
		default:
			break;
		}

		if (field[y][x] == WALL) {
			error = TRUE;
		}
		if (field[y][x] > 0) {
			error = TRUE;
		}
	}

	p[player].x = x;
	p[player].y = y;

	if (field[p[player].y][p[player].x] == GOAL) {
		return TRUE;
	}

	field[y][x] = p[player].num;

	return FALSE;
}
