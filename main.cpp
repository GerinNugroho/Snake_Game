#include <iostream>
#include <stdlib.h>
#include <windows.h>
#include <unistd.h>
#include <conio.h>
using namespace std;

int width, height, score, ntail;
char dir;

struct StructOfCoordinates
{
 int X;
 int Y;
} fruit, player, tail[100];

void hideCursor();
void setup();
void fruitSpawn();
void draw();
void control();
void logic(bool *game);

int main()
{
 bool game = true;
 ShowCursor(false);
 setup();
 while (game)
 {
  draw();
  cout << endl;
  control();
  logic(&game);
  Sleep(80);
 }
 cout << "Game Over" << endl;
 return 0;
}

void hideCursor()
{
 HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
 CONSOLE_CURSOR_INFO cursorInfo;
 GetConsoleCursorInfo(consoleHandle, &cursorInfo);
 cursorInfo.bVisible = false;
 SetConsoleCursorInfo(consoleHandle, &cursorInfo);
}

void setup()
{
 width = 50;
 height = 10;
 player.X = (width - 2) / 2;
 player.Y = (height - 2) / 2;
 fruitSpawn();
 score = 0;
 // hideCursor();
}
void fruitSpawn()
{
 fruit.X = rand() % width;
 fruit.Y = rand() % height;
}

void draw()
{
 system("cls");
 for (int i = 0; i < width + 2; i++)
 {
  cout << "*";
 }
 cout << endl;

 for (int i = 0; i < height; i++)
 {
  for (int j = 0; j < width; j++)
  {
   if (j == 0)
   {
    cout << "*";
   }

   if (i == player.Y && j == player.X)
   {
    cout << "O";
   }
   else if (i == fruit.Y && j == fruit.X)
   {
    cout << "C";
   }
   else
   {
    bool space = true;
    for (int k = 0; k < ntail; k++)
    {
     if (i == tail[k].Y && j == tail[k].X)
     {
      cout << "o";
      space = false;
     }
    }
    if (space)
    {
     cout << " ";
    }
   }

   if (j == width - 1)
   {
    cout << "*";
   }
  }
  cout << endl;
 }
 for (int i = 0; i < width + 2; i++)
 {
  cout << "*";
 }
 cout << endl;
 cout << "Score: " << score;
}

void control()
{
 char newDir;
 if (_kbhit())
 {
  switch (_getch())
  {
  case 'w':
   newDir = 'w';
   break;
  case 's':
   newDir = 's';
   break;
  case 'a':
   newDir = 'a';
   break;
  case 'd':
   newDir = 'd';
   break;
  default:
   break;
  }
 }

 if (newDir == 'w' && dir != 's')
 {
  dir = 'w';
 }
 else if (newDir == 's' && dir != 'w')
 {
  dir = 's';
 }
 else if (newDir == 'a' && dir != 'd')
 {
  dir = 'a';
 }
 else if (newDir == 'd' && dir != 'a')
 {
  dir = 'd';
 }
}
void logic(bool *game)
{
 int prevX = tail[0].X;
 int prevY = tail[0].Y;
 int tmpX, tmpY;
 tail[0].X = player.X;
 tail[0].Y = player.Y;
 for (int i = 1; i < ntail; i++)
 {
  tmpX = tail[i].X;
  tmpY = tail[i].Y;
  tail[i].X = prevX;
  tail[i].Y = prevY;
  prevX = tmpX;
  prevY = tmpY;
  cout << tail[i].X << " " << prevX << endl;
 }
 switch (dir)
 {
 case 'w':
  player.Y--;
  break;
 case 's':
  player.Y++;
  break;
 case 'a':
  player.X--;
  break;
 case 'd':
  player.X++;
  break;
 default:
  break;
 }

 if ((player.X > width || player.X < 0) || (player.Y > height || player.Y < 0))
 {
  *game = false;
 }

 if (player.X == fruit.X && player.Y == fruit.Y)
 {
  score += 10;
  fruitSpawn();
  ntail++;
 }
}