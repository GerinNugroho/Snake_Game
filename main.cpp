#include <iostream>
#include <stdlib.h>
#include <windows.h>
#include <unistd.h>
#include <conio.h>
using namespace std;

int width, height, X, Y, score;
char dir;

struct Fruit
{
 int X;
 int Y;
} fruit;

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
 X = (width - 2) / 2;
 Y = (height - 2) / 2;
 fruit.X = rand() % width;
 fruit.Y = rand() % height;
 score = 0;
 // hideCursor();
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

   if (i == Y && j == X)
   {
    cout << "O";
   }
   else if (i == fruit.Y && j == fruit.X)
   {
    cout << "C";
   }
   else
   {
    cout << " ";
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
void movement()
{
 switch (dir)
 {
 case 'w':
  Y--;
  break;
 case 's':
  Y++;
  break;
 case 'a':
  X--;
  break;
 case 'd':
  X++;
  break;
 default:
  break;
 }
}

int main()
{
 ShowCursor(false);
 setup();
 while (true)
 {
  draw();
  cout << endl;
  control();
  movement();
  Sleep(80);
 }
 return 0;
}