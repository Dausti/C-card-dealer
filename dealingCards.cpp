#include <iostream>
using std::cin;
using std::cout;
using std::endl;
using std::ios;

#include <algorithm>
using std::swap;

#include <fstream>
using std::fstream;

#include <cstring>
#include <cstdlib>
#include <cctype>
#include <ctime>

#define NULL nullptr

struct Card
{
  int value; // 1 = Ace, 2-10, 11 = Jack, 12 = Queen, 13 = King
  int suit; // 0 = Spade, 1 = Club, 2 = Diamond, 3 = Heart
};

void coutCard(Card);

int main()
{
  // identification
  cout << "Daniel Austi\n";
  cout << "Lab 8, dealingCards.8.cpp\n";
  cout << "Created using: Microsoft VS 2012\n";
  cout << "File: " << __FILE__ << "\n";
  cout << "Compiled: " << __DATE__ << " at " << __TIME__ << "\n\n";
  
  srand(time(NULL)); // Seeding random number generator

  Card deck[52];

  // Initialize deck
  int index = 0;
  for (int i = 0; i < 4; i++)
  {
    for (int j = 0; j < 13; j++, index++)
    {
      deck[index].value = j + 1;
      deck[index].suit = i;
    }
  }


  // Shuffle deck
  for (int shuffle = 0; shuffle < 100; shuffle++)
    for (int i = 0; i < 52; i++)
      for (int j = i + 1; j < 52; j++)
        if (rand() % 2 == 0)
          swap(deck[i], deck[j]);

  // Initialize Hand
  Card hand[5] = {deck[0], deck[1], deck[2], deck[3], deck[4]};
  int nextCard = 5; // Card to be swapped in

  //Serialize UP
  fstream fin;
  fin.open("dealingCards.8.dat", ios::binary|ios::in);
  if (fin.good())
  {
    fin.read(reinterpret_cast<char*>(hand), 5 * sizeof(Card));
    fin.read(reinterpret_cast<char*>(deck), 52 * sizeof(Card));
    fin.read(reinterpret_cast<char*>(&nextCard), sizeof(int));
  }
  fin.close();
  
  while (true)
  {
    // Display 5 cards dealt
    cout << "My Hand: \n\n";
    int cardNum = 1;
    for (int i = 0; i < 5; i++, cardNum++)
    {
      cout << cardNum << ". ";
      coutCard(hand[i]);
      cout << endl << endl;
    }

    cout << "Choose a card to recycle [1-5] or Q to quit: ";
    char buf[2];
    cin >> buf;
    cout << endl;
    if (tolower(buf[0]) == 'q') break;
    cardNum = atoi(buf);
   
    if (1 <= cardNum && cardNum <= 5)
    {
      hand[cardNum - 1] = deck[nextCard];
      nextCard++;
      if (nextCard == 52) break;
    }

  }

  // Serialize Down
  fstream fout;
  fout.open("dealingCards.8.dat", ios::binary|ios::out);
  fout.write(reinterpret_cast<char*>(hand), 5 * sizeof(Card));
  fout.write(reinterpret_cast<char*>(deck), 52 * sizeof(Card));
  fout.write(reinterpret_cast<char*>(&nextCard), sizeof(int));
  fout.close();
}

// Function to display cards dealt
void coutCard(Card x)
{
  if (x.value == 1) cout << "Ace";
  else if (2 <= x.value && x.value <= 10) cout << x.value;
  else if (11 <= x.value && x.value < 12) cout << "Jack";
  else if (12 <= x.value && x.value < 13) cout << "Queen";
  else if (x.value == 13) cout << "King";
  cout << " of ";

  if (x.suit == 0) cout << "Spades";
  else if (x.suit == 1) cout << "Clubs";
  else if (x.suit == 2) cout << "Diamonds";
  else if (x.suit == 3) cout << "Hearts";
}
