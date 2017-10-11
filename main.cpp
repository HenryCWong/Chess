#include <iostream>
#include <cstdlib>
#include "board.h"
using namespace std;

int main()
{
  int old1=0;
  int old2=0;
  int new1=0;
  int new2=0;
  int kingx=0;
  int kingy=0;
  bool x;
  bool check;
  char start[8][8] = {'R','N','B','Q','K','B','N','R',
                      'P','P','P','P','P','P','P','P',
                      ' ',' ',' ',' ',' ',' ',' ',' ',
                      ' ',' ',' ',' ',' ',' ',' ',' ',
                      ' ',' ',' ',' ',' ',' ',' ',' ',
                      ' ',' ',' ',' ',' ',' ',' ',' ',
                      'p','p','p','p','p','p','p','p',
                      'r','n','b','q','k','b','n','r'};

  Board b;
  b.reset(start);
  b.printBoard();
  //cout << "You play bottom" << endl;
  while(true)
  {
    cout << "LOWER CASE PLAYS" << endl;
    cout << "y and x" << endl;
    cin >> old1 >> old2;
    cout << "\nnew y and new x" << endl;
    cin >> new1 >> new2;

    //for lower case
    x = b.legalCheckL(old1,old2,new1,new2);
    if(x==true)
    {
      cout << "move legal!" << endl;
      b.updatePiece(old1,old2,new1,new2);
      cerr << "DEBUG: old1, old2, new1,new2: " << old1 << old2 << new1 << new2 << endl;
    }
    else
    {
      cout << "move illegal!" << endl;
    }

    //for lower case
    b.findPiece('k',kingy,kingx);
    check = b.checkChecker(kingy,kingx);
    if(check == true)
    {
      cout << "CHECK!" << endl;
    }
    else
    {
      cout << "YOU'RE GOOD" << endl;
    }
    b.printBoard();
    cout << "____________________________" << endl;

    //for upper case
    cout << "UPPER CASE PLAYS" << endl;
    cout << "y and x" << endl;
    cin >> old1 >> old2;
    cout << "\nnew y and new x" << endl;
    cin >> new1 >> new2;
    x = b.legalCheckU(old1,old2,new1,new2);
    if(x==true)
    {
      cout << "move legal!" << endl;
      b.updatePiece(old1,old2,new1,new2);
    }
    else
    {
      cout << "move illegal!" << endl;
    }
    //TODO:Castling for upper case
    b.printBoard();




  }


}
