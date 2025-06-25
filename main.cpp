#include <iostream>
#include <stdlib.h>
#include <windows.h>
#include <fstream>
#include <conio.h>
#include <string>
#define SIZE 10
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

struct Queue
{
 int score[SIZE];
 int head = 0;
 int tail = 0;
} queue;

void showCursor(bool status)
{
 HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
 CONSOLE_CURSOR_INFO cursorInfo;
 GetConsoleCursorInfo(consoleHandle, &cursorInfo);
 cursorInfo.bVisible = status;
 SetConsoleCursorInfo(consoleHandle, &cursorInfo);
}

bool isEmpty()
{
 return queue.tail < 1 ? true : false;
}

bool isFull()
{
 return queue.tail == SIZE ? true : false;
}

void SearchScore(int input)
{
 if (!isEmpty())
 {
  for (int i = queue.head; i < queue.tail; i++)
  {
   if (queue.score[i] == input)
   {
    if (queue.score[i] > 100)
    {
     cout << "Wah hebat!" << endl;
     cout << "Your Score : " << queue.score[i] << endl;
     return;
    }
    else if (queue.score[i] >= 50)
    {
     cout << "Bolehlah!" << endl;
     cout << "Your Score : " << queue.score[i] << endl;
     return;
    }
    else
    {
     cout << "Noob!" << endl;
     cout << "Your Score : " << queue.score[i] << endl;
     return;
    }
   }
  }
  cout << "Score tidak ditemukan!" << endl;
 }
 else
 {
  cout << "Yuk! Mulai cetak score terbaikmu" << endl;
 }
}

void enQueue(int input)
{
 if (!isFull())
 {
  queue.score[queue.tail] = input;
  queue.tail++;
 }
 else
 {
  cout << "Penyimpanan sudah full!" << endl;
 }
}

void saveScore()
{
 ofstream file("score.txt");
 if (file.is_open() && !isEmpty())
 {
  string buffer;
  for (int i = queue.head; i < queue.tail; i++)
  {
   buffer += to_string(queue.score[i]) + "\n";
  }
  file << buffer;
 }
}

void loadScores()
{
 ifstream file("score.txt");
 if (file.is_open())
 {
  string myData;
  while (getline(file, myData))
  {
   enQueue(stoi(myData));
  }
  file.close();
 }
}

void sortDescending()
{
 for (int i = 1; i < 10; i++)
 {
  int tmp = queue.score[i];
  int insert_index = i;
  int j = i - 1;
  while (j >= 0 && tmp > queue.score[j])
  {
   queue.score[j + 1] = queue.score[j];
   insert_index = j;
   j--;
  }
  queue.score[insert_index] = tmp;
 }
}

void printQueue()
{
 if (!isEmpty())
 {
  for (int i = queue.head; i < queue.tail; i++)
  {
   cout << i + 1 << ". " << queue.score[i] << endl;
  }
 }
 else
 {
  cout << "Ayo! cetak score terbaikmu" << endl;
 }
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
 showCursor(false);
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
 loadScores();
menu:
 system("cls");
 cout << "=============================" << endl;
 cout << "||       Snake Game        ||" << endl;
 cout << "=============================" << endl;

 cout << "\n1. Play Game" << endl;
 cout << "2. Score" << endl;
 cout << "3. Search Score" << endl;
 cout << "4. Exit" << endl;

 cout << "\nYour choose [1..3] : ";
 cin >> choose;
 switch (choose)
 {
 case '1':
  game = true;
  setup();
  while (game)
  {
   draw();
   cout << endl;
   control();
   logic(&game);
   Sleep(80);
  }
  enQueue(score);
  showCursor(true);
  cout << "Game Over" << endl;
  system("pause");
  goto menu;
  break;
 case '2':
  system("cls");
  cout << "Your Score" << endl;
  cout << "_____________" << endl;
  sortDescending();
  printQueue();
  system("pause");
  system("cls");
  goto menu;
  break;
 case '3':
  int input;
  system("cls");
  cout << "Search Score" << endl;
  cout << "______________" << endl;
  cout << "Input Score: ";
  cin >> input;
  SearchScore(input);
  system("pause");
  goto menu;
  break;
 case '4':
  sortDescending();
  saveScore();
  break;
 default:
  cout << "Pilihan tidak tersedia!" << endl;
  system("pause");
  goto menu;
  break;
 }
 return 0;
}
