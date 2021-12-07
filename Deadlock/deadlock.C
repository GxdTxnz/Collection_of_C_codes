#include <stdio.h>
#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>
#define MAIN_COLOR 1
#define RED_COLOR 2
int count_program = 0;
int count_algoritm_first = -1;
int count_render = -1;
int count_algoritm_second = -1;
int count_color = -1;
int count_string = -1;

typedef struct 
{
    int x;
    int y;
}
position;

void render(int* T, int* A, int R[4][4], int C[4][4])
{
    clear();
    for(int i = 0; i < 4; i++)
    {
        if(T[i] == -1)
        {
            mvaddch(6, 10 + i, '_');
        }
        else
        {

            mvprintw(6, 10 + i, "%d", T[i]);
           
        }
        if(i == 3)
        {
            mvaddch(6, 5, 'T');
            mvaddch(6, 7, '=');
            mvaddch(6, 9, '(');
            mvaddch(6, 14, ')');
        }
    }
    
    mvaddch(10, 5, 'C');
    mvaddch(10, 7, '=');
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            if(C[i][j] == -1)
            {
                mvaddch(10 + i, 10 + j, '0');
            }
            else
            {
                mvprintw(10 + i, 10 + j, "%d", C[i][j]);
            }
        }
        mvaddch(10 + i, 9, '(');
        mvaddch(10 + i, 14, ')');
    }

    for(int i = 0; i < 4; i++)
    {
        if(A[i] == 0)
        {
            mvaddch(6, COLS - 12 + i, '0');
        }
        else
        {

            mvprintw(6, COLS - 12 + i, "%d", A[i]);
           
        }
        if(i == 3)
        {
            mvaddch(6, COLS - 17, 'A');
            mvaddch(6, COLS - 15, '=');
            mvaddch(6, COLS - 13, '(');
            mvaddch(6, COLS - 8, ')');
        }
    }
    
    mvaddch(10, COLS - 17, 'R');
    mvaddch(10, COLS - 15, '=');

    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            if(R[i][j] == -1)
            {
                mvaddch(10 + i, COLS - 12 + j, '_');
            }
            else
            {
                if(count_string == i)
                {

                    if(count_color == 1 && R[i][j] != 0)
                    {
                        color_set(RED_COLOR, NULL);
                     
                    }
                }
                mvprintw(10 + i, COLS - 12 + j, "%d", R[i][j]);
                color_set(MAIN_COLOR, NULL);
            }
        }
        mvaddch(10 + i, COLS - 13, '(');
        mvaddch(10 + i, COLS - 8, ')');
    }

    

    refresh();
}

position count_position(position data, int key)
{
    position new_data;
    new_data.y = data.y;
    new_data.x = data.x;
    if(new_data.x > 9 && new_data.x < 14 && new_data.y == 6)
    {
        if(key == KEY_LEFT){
            new_data.x--;
        }
        if(key == KEY_RIGHT){
            new_data.x++;
        }
    }
    if(new_data.x > 9 && new_data.x < 14 && new_data.y == 6)
    {
        return new_data;
    }
    else{
        if(new_data.x == 14 || new_data.y == 7)
        {
            new_data.x = COLS - 12;
            new_data.y = 10;
            return new_data;
        }
        if(new_data.x == 9 && new_data.y == 6)
        {
            new_data.x = 10;
            new_data.y = 6;
            return new_data;
        }
    }

    if(new_data.x > COLS - 13 && new_data.x < COLS - 8 && new_data.y > 9 && new_data.y < 14)
    {
        if(key == KEY_LEFT)
        {
            new_data.x--;
        }
        if(key == KEY_RIGHT)
        {
            new_data.x++;
        }
        if(key == KEY_DOWN)
        {
            new_data.y++;
        }
        if(key == KEY_UP)
        {
            new_data.y--;
        }
    }
    if(new_data.x > COLS - 13 && new_data.x < COLS - 8 && new_data.y > 9 && new_data.y < 14)
    {
        return new_data;
    }
    else
    {
        if((new_data.x == COLS - 13 && new_data.y == 10) || (new_data.y == 9 && new_data.x == COLS - 12))
        {
            new_data.x = 13;
            new_data.y = 6;
            return new_data;
        }
        else
        {
            new_data.x = data.x;
            new_data.y = data.y;
            return new_data;
        }
    }
}

void input_data(position data, int* T, int R[4][4], int ch)
{
    position now_data;

    now_data.y = data.y;
    now_data.x = data.x;
    int count = 0;
    int count_x = 0;
    int count_y = 0;

    if(count_algoritm_first == -1)
    {
        for(int i = 10; i < 14; i++)
        {
            if(i == now_data.x)
            {
                if(ch == '1')
                {
                    T[count] = 1;
                }
                if(ch == '2')
                {
                    T[count] = 2;
                }
                if(ch == '3')
                {
                    T[count] = 3;
                }
                if(ch == '4')
                {
                    T[count] = 4;
                }
                if(ch == '5')
                {
                    T[count] = 5;
                }
                if(ch == '6')
                {
                    T[count] = 6;
                }
                if(ch == '7')
                {
                    T[count] = 7;
                }
                if(ch == '8')
                {
                    T[count] = 8;
                }
                if(ch == '9')
                {
                    T[count] = 9;
                }
                if(ch == '0')
                {
                    T[count] = 0;
                }
                break;
            }
            else
            {
                count++;
            }
        }
    }

    for(int i = 10; i < 14; i++)
    {
        for(int j = COLS - 12; j < COLS - 8; j++)
        {
            if(j == now_data.x && i == now_data.y)
            {
                if(ch == '1')
                {
                    R[count_y][count_x] = 1;
                }
                if(ch == '2')
                {
                    R[count_y][count_x] = 2;
                }
                if(ch == '3')
                {
                    R[count_y][count_x] = 3;
                }
                if(ch == '4')
                {
                    R[count_y][count_x] = 4;
                }
                if(ch == '5'
                ){
                    R[count_y][count_x] = 5;
                }
                if(ch == '6')
                {
                    R[count_y][count_x] = 6;
                }
                if(ch == '7')
                {
                    R[count_y][count_x] = 7;
                }
                if(ch == '8')
                {
                    R[count_y][count_x] = 8;
                }
                if(ch == '9')
                {
                    R[count_y][count_x] = 9;
                }
                if(ch == '0')
                {
                    R[count_y][count_x] = 0;
                }
                break;
            }
            else
            {
                count_x++;
            }
        }
        count_x = 0;
        count_y++;
    }
    
    

}

int check_data(int* T, int R[4][4]){
    int check = -1;
    int count_correct = 0;
    int count = 0;
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            if(R[i][j] != -1)
            {
                count_correct++;
            }
        }
        if(T[i] != -1)
        {
            count++;
        }
    }
    if(count == 4 && count_correct == 16)
    {
        check = 0;
        return check;
    }
    else{
        check = 1;
        return check;
    }
}

void algoritm_first(int* T, int* A, int R[4][4], int C[4][4])
{
    int memory[4] = {-1, -1, -1, -1};
    int count = 0;
    
    for(int i = 0; i < 4; i++)
    {
        A[i] = T[i];
    }
    for(int i = 0; i < 4; i++)
    {
        
        for(int j = 0; j < 4; j++)
        {
            if(R[i][j] < A[j])
            {
                A[j] = A[j] - R[i][j];
                count++;
            }
        }
        if(count == 4){
            memory[i] = i;
            count_render = 0;
            count_color = 0;
            count_string = i;
            for(int t = 0; t < 4; t++)
            {
                C[i][t] = R[i][t];
            }
        }
        else
        {
            count_string = i;
            count_render = 1;
            count_color = 1;
        }
        
        count = 0;
        sleep(2);
        render(T, A, R, C);
        
    }

    count = 0;

    for(int i = 0; i < 4; i++)
    {
        if(memory[i] != -1)
        {
            count++;
        }
        if(count == 4)
        {
            count_algoritm_first = 0;
        }
        else{
            count_algoritm_first = 1;
        }
    }
        
}

void algoritm_second(int* T, int* A, int R[4][4], int C[4][4])
{    
    int memory[4] = {-1, -1, -1, -1};
    int count = 0;
    int count_it = 0; 
    int k = 0;

    while(count_it != 4)
    {
		for(int i = 0; i < 4; i++)
		{
			for(int j = 0; j < 4; j++)
			{
				if(memory[j] == i)
				{
					break;
				}
				else
				{
					if(R[i][j] <=A[j])
					{
						count++;
					}
					if(count == 4)
					{
						k = i;
						memory[i] = i;
                        count_render = 0;
                        count_color = 0;
                        count_string = i;
						for(int i = 0; i < 4; i++)
						{
							A[i] = A[i] + C[k][i];
							C[k][i] = 0;
							R[k][i] = 0;
						}

					}
                    else{
                        count_string = i;
                        count_render = 1;
                        count_color = 1;
                    }
				}
			}
			count = 0;
            sleep(2);
            render(T, A, R, C);

		}
		if(memory[0] != -1 && memory[1] != -1 && memory[2] != -1 && memory[3] != -1)
		{
			break;
		}
        count_it++;
	}
    count = 0;
	for(int i = 0; i < 4; i++)
	{
		if(A[i] == T[i])
		{
			count++;
		}
		if(count == 4)
		{
			count_algoritm_second = 0;
		}
		else
		{
			count_algoritm_second = 1;
            count_program = 1;
		}

	}
    
}

int main(){
    int check = -1;
    int count = 0;
    int ch;
    int T[4] = {-1, -1, -1, -1};
    int A[4] = {0, 0, 0, 0};
    int R[4][4] = {{-1, -1, -1, -1}, {-1, -1, -1, -1}, {-1, -1, -1, -1}, {-1, -1, -1, -1}};
    int C[4][4] = {{-1, -1, -1, -1}, {-1, -1, -1, -1}, {-1, -1, -1, -1}, {-1, -1, -1, -1}};
    position data;
    data.x = 10;
    data.y = 6;
    initscr();
	
	noecho();
	keypad(stdscr,TRUE);

    start_color();
    init_pair(MAIN_COLOR, COLOR_WHITE, COLOR_BLACK);
    init_pair(RED_COLOR, COLOR_WHITE, COLOR_RED);
    
    render(T, A, R, C);

    

    while(count_program == 0)
    {
        move(data.y, data.x);
        ch = getch();
        curs_set(0);
        if(ch == 'q')
        {
            count_program = 1;
        }
        if(ch == KEY_RIGHT)
        {
            data = count_position(data, KEY_RIGHT); 
            
        }       
        if(ch == KEY_LEFT)
        {
            data = count_position(data, KEY_LEFT);
   
        }
        if(ch == KEY_UP)
        {
            data = count_position(data, KEY_UP);
   
        }
        if(ch == KEY_DOWN)
        {
            data = count_position(data, KEY_DOWN);
        }
        if(ch == '1')
        {
            input_data(data, T, R, ch);            
        }
        if(ch == '2')
        {
            input_data(data, T, R, ch);            
        }
        if(ch == '3')
        {
            input_data(data, T, R, ch);            
        }
        if(ch == '4')
        {
            input_data(data, T, R, ch);            
        }
        if(ch == '5')
        {
            input_data(data, T, R, ch);            
        }
        if(ch == '6')
        {
            input_data(data, T, R, ch);            
        }
        if(ch == '7')
        {
            input_data(data, T, R, ch);            
        }
        if(ch == '8')
        {
            input_data(data, T, R, ch);            
        }
        if(ch == '9')
        {
            input_data(data, T, R, ch);            
        }
        if(ch == '0')
        {
            input_data(data, T, R, ch);            
        }
        if(ch == ' ')
        {
            check = check_data(T, R);
            if(check == 0)
            {
                count++;
                if(count_algoritm_first == 0 && count == 2)
                {
                    algoritm_second(T, A, R, C);
                    count = 0;
                }
                if(count == 1){
                    algoritm_first(T, A, R, C);
                }
            }
            
            
        }

        render(T, A, R, C);
        curs_set(1);
    }

    refresh();
	getch();
	endwin();
	return 0;

}
