#include <iostream>
#include <stdlib.h>
#include <windows.h>
#include <unistd.h>
#include <conio.h>
using namespace std;

int width, height, score;
char dir;

struct StructOfCoordinates
{
 int X;
 int Y;
} fruit, player;

struct BodySnake
{
 int X, Y;
 BodySnake *next;
};

BodySnake *tail = NULL;

void hideCursor()
{
 HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
 CONSOLE_CURSOR_INFO cursorInfo;
 GetConsoleCursorInfo(consoleHandle, &cursorInfo);
 cursorInfo.bVisible = false;
 SetConsoleCursorInfo(consoleHandle, &cursorInfo);
}

void fruitSpawn()
{
 fruit.X = rand() % width;
 fruit.Y = rand() % height;
}

void removeLastNode()
{
 if (tail == NULL)
 {
  return;
 }
 if (tail->next == NULL)
 {
  delete tail;
  tail = NULL;
  return;
 }
 BodySnake *prev = NULL;
 BodySnake *curr = tail;

 while (curr->next != NULL)
 {
  prev = curr;
  curr = curr->next;
 }

 delete curr;
 prev->next = NULL;
};

void clearNode()
{
 BodySnake *temp = tail;
 BodySnake *deleteNode;
 int index = 1;
 while (temp != NULL)
 {
  // cout << "Node" << index << ": " << "X : " << temp->X << "Y : " << temp->Y << "Next : " << temp->next << endl;
  deleteNode = temp;
  temp = temp->next;
  delete deleteNode;
  index++;
 }
 tail = NULL;
}

void addNodeBefore(int x, int y, bool grow)
{
 BodySnake *newNode = new BodySnake();
 newNode->X = x;
 newNode->Y = y;
 newNode->next = tail;
 tail = newNode;

 if (!grow)
 {
  removeLastNode();
 }
};

void setup()
{
 width = 50;
 height = 10;
 player.X = (width - 2) / 2;
 player.Y = (height - 2) / 2;
 fruitSpawn();
 score = 0;
 dir = ' ';
 clearNode();
 // hideCursor();
}
void draw()
{
 system("cls");
 // Print border top
 for (int x = 0; x < width + 2; x++)
 {
  cout << "*";
 }
 cout << endl;
 // print border left, right and content
 for (int y = 0; y < height; y++)
 {
  cout << "*";
  for (int x = 0; x < width; x++)
  {
   if (y == player.Y && x == player.X)
   {
    cout << "O";
   }
   else if (y == fruit.Y && x == fruit.X)
   {
    cout << "C";
   }
   else
   {
    bool space = true;
    BodySnake *temp = tail;
    while (temp != NULL)
    {
     if (x == temp->X && y == temp->Y)
     {
      cout << "o";
      space = false;
      break;
     }
     temp = temp->next;
    }
    if (space)
    {
     cout << " ";
    }
   }
  }
  cout << "*" << endl;
 }
 // print border bottom
 for (int x = 0; x < width + 2; x++)
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
 int prevX = player.X;
 int prevY = player.Y;
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

 BodySnake *temp = tail;
 while (temp != NULL)
 {
  if (player.X == temp->X && player.Y == temp->Y)
  {
   *game = false;
   return;
  }
  temp = temp->next;
 }

 bool grow = false;
 if (player.X == fruit.X && player.Y == fruit.Y)
 {
  score += 10;
  fruitSpawn();
  grow = true;
 }
 addNodeBefore(prevX, prevY, grow);
}

int main()
{
 bool game;
 char choose;
menu:
 cout << "=============================" << endl;
 cout << "||       Snake Game        ||" << endl;
 cout << "=============================" << endl;

 cout << "\n1. Play Game" << endl;
 cout << "2. Score" << endl;
 cout << "3. Exit" << endl;

 cout << "\nYour choose [1..3] : ";
 cin >> choose;
 switch (choose)
 {
 case '1':
  game = true;
  ShowCursor(false);
  setup();
  while (game)
  {
   draw();
   cout << endl;
   control();
   logic(&game);
   // clearNode();
   Sleep(80);
  }
  cout << "Game Over" << endl;
  system("pause");
  goto menu;
  break;
 case '2':
  cout << "menu record!" << endl;
  system("pause");
  goto menu;
  break;
 case '3':
  break;
 default:
  cout << "Pilihan tidak tersedia!" << endl;
  system("pause");
  goto menu;
  break;
 }
 return 0;
}
