#include<iostream>
#include<stdlib.h>
#include<conio.h>
#include<ctime>
#include<fstream>
#include<stdio.h>
#include<windows.h>
#define _WIN32_WINNT 0x05232

using namespace std;

class getScore
{
	public:
	int score,highScore;
	getScore()
	{
		score=highScore=0;
	}
};

// Declaring all the required function

void run();
void printMap();
void initMap();
void move(int dx, int dy);
void update();
void generateFood();
char getMapValue(int value);
void changeDirection();
void flashColor();
void gotoxy(short x,short y);
void maxConsoleScreen(void);
void hideCur();
void displayS(int x, int y);
void displayN(int x, int y);
void displayA(int x, int y);
void displayK(int x, int y);
void displayE(int x, int y);
int getScreenSize();
void displaySnake1();
void displaySnake();
void displayCredits();
void saveScores();
void displayScores();
int checkChoice(char ans[100],int ,int );
void menuScreen();
void forScore();
void printInstruction();

// Map dimensions
const int mapwidth = 35;
const int mapheight = 68;

const int size = mapwidth * mapheight;

// The tile values for the map
int map[size];

// Snake head details
int headxpos;
int headypos;
int direction;

// Amount of food the snake has (How long the body is)
int food = 3;

//For score
int score1 = 0;

// For level up
int levelUp = 0;

// Determine if game is running
bool running;

long sizes;
int rows,cols;
	
void gotoxy(short x,short y) //This is to declare gotoxy() function is a Turbo-C++ Function not a ANSI function
{
	COORD pos = {x,y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
}

void maxConsoleScreen(void) //To maximize the console screen
{
	HWND consoleWindow = GetConsoleWindow(); //This gets the value Windows uses to identify the output window
	ShowWindow(consoleWindow,SW_SHOWMAXIMIZED); //This mimics the clicking on it's maximized button
}

void hideCur() //To hide the cursor on the screen
{
	HANDLE cmd;
	CONSOLE_CURSOR_INFO cur;
	char *str=(char*)malloc(32);
	cur.dwSize=1;
	cur.bVisible=FALSE;
	cmd=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorInfo(cmd,&cur);
}

int getScreenSize() //To get the size of the console screen
{
	int col,row,total;
	maxConsoleScreen();
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),&csbi);
	col=csbi.srWindow.Right-csbi.srWindow.Left+1;
	row=csbi.srWindow.Bottom-csbi.srWindow.Top+1;
	total=col*1000+row;
	return total;
}

// Main game function
void run()
{
	forScore();
	gotoxy(rows+75,cols+16);	
	cout<<"Score : "<<score1;
    // Initialize the map
    initMap();
    running = true;
    while (running)
	{
        // If a key is pressed
        if (kbhit())
		{
            // Change to direction determined by key pressed
            changeDirection();
        }
        // Update the map
        update();

        // Clear the screen
        system("cls");

        // Print the map
        printMap();

        // wait 0.25 seconds for maintaining speed of snake
        _sleep(250);
        
        // Saves the scores
		saveScores();
    }
	flashColor();
    // Print out game over text
    gotoxy(rows+9,cols+36);cols++;
    cout<<"___________________________________________________";
	gotoxy(rows+30,cols+36); cols+=2;
    cout << "|Game over|"; gotoxy(rows+25,cols+36); cols+=2;
	cout<<"Press ANY key to end.";
    // Stop console from closing instantly
    getch();
}

void flashColor()
{
	system("COLOR 10"); _sleep(55);
	system("COLOR 20"); _sleep(55);
	system("COLOR 30"); _sleep(55);
	system("COLOR 40"); _sleep(55);
	system("COLOR 50"); _sleep(55);
	system("COLOR 60"); _sleep(55);
	system("COLOR 70"); _sleep(55);
}

void forScore() //For display position of score during gameplay.
{
	sizes=getScreenSize();
	rows=sizes%1000;
	cols=sizes/1000;
	cols=cols/15;
	rows=(44*rows)/45+5;
}

void printInstruction() //How to play game
{
	system("cls");
	displaySnake1();
	long size;
	int row,col;
	size=getScreenSize();
	row=size%1000;
	col=size/1000;
	col=(col/3)-5;
	row=row/2;
	gotoxy(col-1,row); cout<<"Classic snake game! Player can move the snake all around the enclosed box."; row++;
	gotoxy(col,row); cout<<"Player can use WASD keys or the arrow keys to control the snake. Press W ";row++;
	gotoxy(col-1,row); cout<<"or up arrow key to go up, press A or left arrow key to go left, press S or"; row++;
	gotoxy(col,row); cout<<"down arrow key to go down, press D or right arrow key to go right. It is"; row++;
	gotoxy(col,row); cout<<"highly recommended to use WASD keys instead of arrows keys as there is a "; row++;
	gotoxy(col-1,row); cout<<"slight problem with the arrows keys. Bonus food appears only after player"; row++;
	gotoxy(col+6,row); cout<<" eats 10 noraml food. Bonus food adds up 3 points.";row++;
	gotoxy(col+9,row+3); cout<<"_______________________________________________"; 
	gotoxy(col+14,row+5); cout<<"Press ANY key to return to main menu";
	getch();
	menuScreen();
}

void changeDirection() // Changes snake direction from input
{
	forScore();
	gotoxy(rows+75,cols+16);	
	cout<<"Score : "<<score1;
    /*
      W
    A + D
      S
	 and arrow keys
    */

    switch (getch()) 
	{
    case 'w':
        if (direction != 2) direction = 0;
        break;
    case 'd':
        if (direction != 3) direction = 1;
        break;
    case 's':
        if (direction != 4) direction = 2;
        break;
    case 'a':
        if (direction != 5) direction = 3;
        break;
    case 'W':
        if (direction != 2) direction = 0;
        break;
    case 'D':
        if (direction != 3) direction = 1;
        break;
    case 'S':
        if (direction != 4) direction = 2;
        break;
    case 'A':
        if (direction != 5) direction = 3;
        break;
     case 75: //ASCII code for left
        if (direction != 5) direction = 3;       
   		break;
    case 77: //ASCII code for right
        if (direction != 3) direction = 1;                           
        break;
    case 72: //ASCII code for up
        if (direction != 2) direction = 0;                           
        break;
	case 80:  //ASCII code for down
        if (direction != 4) direction = 2;                           
        break;  
    case 27:
    	gotoxy(rows+20,cols+16);
    	cout<<"Paused. Press ANY key to continue.";
		getch();
		break;    
	}                
}

// Moves snake head to new location
void move(int dx, int dy) 
{
	forScore();
	gotoxy(rows+75,cols+16);
	cout<<"Score : "<<score1;
    // determine new head position
    int newx = headxpos + dx;
    int newy = headypos + dy;

    // Check if there is food at location
    if (map[newx + newy * mapwidth] == -2)
	{
        // Increase food value (body length)
        { 
			food++; levelUp++;
			if(levelUp==11 && (map[newx + newy * mapwidth] == -2))
			{
				levelUp=0;
				score1=score1+3;
			}
			else 
				score1++;
		}
		
        // Generate new food on map
        generateFood();
    }

    // Check location is free
    else if (map[newx + newy * mapwidth] != 0) 
	{
        running = false;
    }

    // Move head to new location
    headxpos = newx;
    headypos = newy;
    map[headxpos + headypos * mapwidth] = food + 1;

}

// Generates new food on map
void generateFood()
{
	forScore();
	gotoxy(rows+75,cols+16);	
	cout<<"Score : "<<score1;
	srand(time(0));
    int x = 0;
    int y = 0;
    do {
        // Generate random x and y values within the map
        x = rand() % (mapwidth - 2) + 1;
        y = rand() % (mapheight - 2) + 1;

        // If location is not free try again
    } while (map[x + y * mapwidth] != 0);

    // Place new food
    map[x + y * mapwidth] = -2;
}

// Updates the map
void update()
{
	forScore();
	gotoxy(rows+75,cols+16);	
	cout<<"Score : "<<score1;
    // Move in direction indicated
    switch (direction)
	{
    case 0: move(-1, 0);
        break;
    case 1: move(0, 1);
        break;
    case 2: move(1, 0);
        break;
    case 3: move(0, -1);
        break;
    }

    // Reduce snake values on map by 1
    for (int i = 0; i < size; i++) 
	{
        if (map[i] > 0) map[i]--;
    }
}

// Initializes map
void initMap()
{
	forScore();
	gotoxy(rows+75,cols+16);	
	cout<<"Score : "<<score1;
    // Places the initual head location in middle of map
    headxpos = mapwidth / 2;
    headypos = mapheight / 2;
    map[headxpos + headypos * mapwidth] = 1;

    // Places top and bottom walls 
    for (int x = 0; x < mapwidth; ++x) 
	{
        map[x] = -1;
        map[x + (mapheight - 1) * mapwidth] = -1;
    }

    // Places left and right walls
    for (int y = 0; y < mapheight; y++) 
	{
        map[0 + y * mapwidth] = -1;
        map[(mapwidth - 1) + y * mapwidth] = -1;
    }

    // Generates first food
    generateFood();
}

// Prints the map to console
void printMap()
{	
	forScore();
	gotoxy(rows+75,cols+16);
	cout<<"Score : "<<score1;
	long size;
	int row,col;
	size=getScreenSize();
	row=size%1000;
	col=size/1000;
	col=col/15;
	row=(44*row)/45;
    for (int x = 0; x < mapwidth; ++x) 
	{
		
		gotoxy(row+5,col);
        for (int y = 0; y < mapheight; ++y) 
		{
            // Prints the value at current x,y location
            cout << getMapValue(map[x + y * mapwidth]);
        }
        // Ends the line for next x value
        cout << endl; col++;
    }
}

// Returns graphical character for display from map value
char getMapValue(int value)
{
	srand(time(0));
	int randFood;
	
    // Returns a part of snake body
    if (value > 0) return 'o';

	switch(value)
	{
		case -1: // Return wall
			return 'X';
		
		case -2:
			if( levelUp != 10) // Return normal food
				return char(162);
			else if(levelUp == 10) // Return special food
			{
				randFood = rand()%10+1;
				if(randFood==1)
					return char(145);
				if(randFood==2)
					return char(148);	
				if(randFood==3)
					return char(235);	
				if(randFood==4)
					return char(237);	
				if(randFood==5)
					return char(232);	
				if(randFood==6)
					return char(233);	
				if(randFood==7)
					return char(149);	
				if(randFood==8)
					return char(236);	
				if(randFood==9)
					return char(167);
				if(randFood==10)
					return char(234);						
		}
	}
}

void displayS(int x, int y)
{
	gotoxy(x,y); cout<<" ___________"<<endl; ++y;
	gotoxy(x,y); cout<<"|     ______|"<<endl; ++y;
	gotoxy(x,y); cout<<"|    |______"<<endl; ++y;
	gotoxy(x,y); cout<<"|_______    |"<<endl; ++y;
	gotoxy(x,y); cout<<" _______|   |"<<endl; ++y;
	gotoxy(x,y); cout<<"|___________|"<<endl;
}

void displayN(int x, int y)
{
	gotoxy(x,y); cout<<" _________     ____"<<endl; ++y;
	gotoxy(x,y); cout<<"|         \\   |    |"<<endl; ++y;
	gotoxy(x,y); cout<<"|    |\\    \\  |    |"<<endl; ++y;
	gotoxy(x,y); cout<<"|    | \\    \\ |    |"<<endl; ++y;
	gotoxy(x,y); cout<<"|    |  \\    \\|    |"<<endl; ++y;
	gotoxy(x,y); cout<<"|____|   \\_________|"<<endl;
}

void displayA(int x, int y)
{
	gotoxy(x,y); cout<<"  ____________ "<<endl; ++y;
	gotoxy(x,y); cout<<" /    ____    \\"<<endl; ++y;
	gotoxy(x,y); cout<<"|    |____|    |"<<endl; ++y;
	gotoxy(x,y); cout<<"|     ____     |"<<endl; ++y;
	gotoxy(x,y); cout<<"|    |    |    |"<<endl; ++y;
	gotoxy(x,y); cout<<"|____|    |____|"<<endl;
}

void displayK(int x, int y)
{
	gotoxy(x,y); cout<<" ___   _____"<<endl; ++y;
	gotoxy(x,y); cout<<"|   | /    /"<<endl; ++y;
	gotoxy(x,y); cout<<"|   |/    /"<<endl; ++y;
	gotoxy(x,y); cout<<"|        <"<<endl; ++y;
	gotoxy(x,y); cout<<"|   |\\    \\"<<endl; ++y;
	gotoxy(x,y); cout<<"|___| \\____\\"<<endl;
}

void displayE(int x, int y)
{
	gotoxy(x,y); cout<<" _________"<<endl; ++y;
	gotoxy(x,y); cout<<"|   ______|"<<endl; ++y;
	gotoxy(x,y); cout<<"|  |__ "<<endl; ++y;
	gotoxy(x,y); cout<<"|   __|"<<endl; ++y;
	gotoxy(x,y); cout<<"|  |______"<<endl; ++y;
	gotoxy(x,y); cout<<"|_________|"<<endl;
}

void displaySnake1() //To display SNAKE in screen without delay
{
	long size;
	int row,col;
	size=getScreenSize();
	row=size%1000;
	col=size/1000;
	row=row/3;
	col=col/4;
	displayS(col,row);
	displayN(col+19,row);
	displayA(col+45,row);
	displayK(col+67,row); 
	displayE(col+85,row);
}

void displaySnake() //To display SNAKE in screen
{
	long size;
	int row,col;
	size=getScreenSize();
	row=size%1000;
	col=size/1000;
	row=row/3;
	col=col/4;	 _sleep(300);
	displayS(col,row); _sleep(300);
	displayN(col+19,row); _sleep(300);
	displayA(col+45,row); _sleep(300);
	displayK(col+67,row); _sleep(300);
	displayE(col+85,row);
	gotoxy(col+30,row+17);
	_sleep(300);
	cout<<"Press ANY key to begin........";
	getch();
}

void displayCredits() //To display the credits
{
	displaySnake1();
	long size;
	int row,col;
	size=getScreenSize();
	row=size%1000;
	col=size/1000;
	col=(col/3)-5;
	row=row/2;
	gotoxy(col,row); cout<<"  These are the people because of which this project has been possible."; row++;
	gotoxy(col,row); cout<<"========================================================================="; row+=3;
	gotoxy(col+2,row); cout<<"1. Abhinay Shah"; row++;
	gotoxy(col+2,row); cout<<"2. Hrithik Chaudhary"; row++;
	gotoxy(col+2,row); cout<<"3. Anish Ansari"; row++;
	gotoxy(col+2,row); cout<<"4. Pritam Samanta"; row++;
	gotoxy(col+9,row+3); cout<<"_______________________________________________"; 
	gotoxy(col+14,row+5); cout<<"Press ANY key to return to main menu";
	getch();
	menuScreen();
}

void saveScores() // This will save scores
{
	fstream fSave,fRead;
	getScore scores;
	fRead.open("score.dat",ios::in|ios::binary);
	fRead.read((char*)&scores,sizeof(scores));
	fRead.close();
	if(scores.highScore < score1)
		scores.highScore=score1;
	scores.score=score1;
	fSave.open("score.dat",ios::out|ios::binary);
	fSave.write((char*)&scores,sizeof(scores));
	fSave.close();
}

void displayScores() //To get scores
{
	displaySnake1();
	long size;
	int row,col;
	size=getScreenSize();
	row=size%1000;
	col=size/1000;
	col=(col/3)-5;
	row=row/2;	
	fstream fIn;
	getScore score;
	fIn.open("score.dat",ios::in|ios::binary);
	fIn.read((char*)&score,sizeof(score));
	fIn.close();
	gotoxy(col+18,row+3); cout<<"Score : "<<score.score;
	gotoxy(col+18,row+5); cout<<"High-Score : "<<score.highScore;
	gotoxy(col+9,row+10); cout<<"_______________________________________________"; 
	gotoxy(col+14,row+11); cout<<"Press ANY key to return to main menu";
	getch();
	menuScreen();
}

int checkChoice(char ans[100],int row,int col)
{	
	if(!strcmp(ans,"1"))
		return 1;
	else if(!strcmp(ans,"2"))
		return 2;
	else if(!strcmp(ans,"3"))
		return 3;
	else if(!strcmp(ans,"4"))
		return 4;
	else if(!strcmp(ans,"5"))
		return 5;
	else
	{
		ans[100]=NULL;
		gotoxy(col+3,row+7);
		cout<<"Error. Please enter again";
		_sleep(1500);
		menuScreen();	
	}
}

void menuScreen() // To display menu screen
{
	system("cls");
	displaySnake1();
	long size;
	int select,row,col;
	char ans[100];
	size=getScreenSize();
	row=size%1000;
	col=size/1000;
	col=col/3+8;
	row=row/2;
	gotoxy(col+3,row); cout<<"1. Start the game"; row++;
	gotoxy(col+3,row); cout<<"2. Scores"; row++;
	gotoxy(col+3,row); cout<<"3. Credits"; row++;
	gotoxy(col+3,row); cout<<"4. Instructions"; row++;
	gotoxy(col+3,row); cout<<"5. EXIT"; row++;
	gotoxy(col,row+4); cout<<"Enter your choice : ";
	gets(ans);
	select=checkChoice(ans,row,col);
	switch(select)
	{
		case 1:
			system("cls");
			run();
			getch();
			break;
		
		case 2:
			system("cls");
			displayScores();
			break;
		
		case 3:
			system("cls");
			displayCredits();
			break;
			
		case 4:
			printInstruction();
			break;
			
		case 5:
			system("exit");
			break;				
	}
}

int main()
{
	system("COLOR 70");
	hideCur();
	displaySnake();
	menuScreen();
}
