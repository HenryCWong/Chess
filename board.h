#ifndef BOARD_H_INCLUDED
#define BOARD_H_INCLUDED

#include<iostream>
using namespace std;

class Board
{
     char board[8][8];
     char start[8][8];
     bool kingMoved = false;
     //bool inCheckL; //lowercase pieces are in check

public:
  Board()
  {
    char board[8][8];
  }

  void printBoard()
  {
    for(int i=0;i<8;i++)
    {
      cout << i << "||";
      for(int j=0;j<8;j++)
        cout << board[i][j] << " ";
      cout << endl;
    }
    cout << "__________________" << endl;
    cout << "   0 1 2 3 4 5 6 7" << endl;
    cout << endl;
    //cout << "TEST"<< endl;
    //cout << board[7][3] << endl;    //prints q
  }
  void reset(char start[8][8])
  {
     for(int i=0;i<8;i++)
      for(int j=0;j<8;j++)
      {
        board[i][j] = start[i][j];
      }

  }

  bool legalCheckL(int old1,int old2,int new1,int new2)
  {
    char old = board[old1][old2];
    char newc = board[new1][new2];
    if(old == ' ')
    {
      return false;
    }
    else if(old == newc)         //if exact same position, no problems with piece duplicates since those shouldn't be moves anyways
    {
      return false;
    }
    else if(newc == 'r' || newc == 'n' || newc == 'b' || newc =='q' || newc =='k' || newc == 'p')
    {
      return false;
    }
    else
    {
      cerr << "DEBUG OLD: " << old << endl;
      switch(old)
      {
        case 'p':   //pawn
          return evaluatePawnL(old1,old2,new1,new2);//just to make things look cleaner
            break;
        case 'r':    //rook
          return evaluateRook(old1,old2,new1,new2);
          break;
        case 'n':
          return evaluateKnight(old1,old2,new1,new2);
          break;
        case 'b':
          return evaluateBishop(old1,old2,new1,new2);
        case 'k':
          return evaluateKing(old1,old2,new1,new2);
        case 'q':
          return evaluateQueen(old1,old2,new1,new2);
      }
    }
    return false;
  }

  bool legalCheckU(int old1,int old2,int new1,int new2)
  {
    char old = board[old1][old2];
    char newc = board[new1][new2];
    if(old == ' ')
    {
      return false;
    }
    else if(old == newc)         //if exact same position, no problems with piece duplicates since those shouldn't be moves anyways
    {
      return false;
    }
    else if(newc == 'R' || newc == 'N' || newc == 'B' || newc =='Q' || newc =='K' || newc == 'P')
    {
      return false;
    }
    else
    {
      cerr << "DEBUGU OLD: " << old << endl;
      switch(old)
      {
        case 'P':   //pawn
          return evaluatePawnU(old1,old2,new1,new2);//just to make things look cleaner
            break;
        case 'R':    //rook
          return evaluateRook(old1,old2,new1,new2);
          break;
        case 'N':
          return evaluateKnight(old1,old2,new1,new2);
          break;
        case 'B':
          return evaluateBishop(old1,old2,new1,new2);
        case 'K':
          return evaluateKing(old1,old2,new1,new2);
        case 'Q':
          return evaluateQueen(old1,old2,new1,new2);
      }
    }
    return false;
  }

  bool evaluatePawnL(int old1,int old2,int new1,int new2)
  {
    char newc = board[new1][new2];
    if(board[old1-1][old2] != ' ')
      return false;
    if((old1-1 == new1 && old2-1 == new2)&&(old1+1 == new1 && old2-1 == new2)) //user wants to move diagonally for a capture
    {
      //if the capture space is empty or if there is a friendly piece
      if(newc == ' ' || newc=='r' || newc=='k' || newc=='b'||newc=='q'||newc=='p'||newc=='n')
        return false;
      else
      {
        board[new1][new2] = 'p';
        return true;
      }
    }
    else if(old1-1 == new1 && old2 == new2)   //if the pawn is moving forward
    {                                         //empty check was already performed
      return true;
    }
    return false;
  }

  bool evaluatePawnU(int old1,int old2,int new1,int new2)
  {
    cerr << "DEBUG: REACHED EVALUATEPAWNU" << endl;
    cerr << "DEBUG: old1: " << old1 << endl;
    cerr << "DEBUG: old2: " << old2 << endl;
    cerr << "DEBUG: new1: " << new1 << endl;
    cerr << "DEBUG: new2: " << new2 << endl;
    char newc = board[new1][new2];
    if(board[old1+1][old2] != ' ')
      return false;
    if((old1+1 == new1 && old2+1 == new2) || (old1+1 == new1 && old2-1 == new2)) //user wants to move diagonally for a capture
    {
      //cerr <<"DEBUG: U PAWN CAPTURE" << endl;
      board[new1][new2] = 'P';
      return true;

    }
    else if(old1+1 == new1 && old2 == new2)   //if the pawn is moving forward
    {
      //cerr << "DEBUG: U PAWN MOVE FORWARD" << endl;                                         //empty check was already performed
      return true;
    }
    //cerr << "DEBUG: PAWN CANNOT MOVE" << endl;
    return false;
  }

  //TODO: Rook cannot move back more than 1 step
  bool evaluateRook(int old1, int old2, int new1, int new2)
  {
    //same position and empty old have already been tested
    int dy = old1 - new1;
    int dx = old2 - new2;

    //check for valid horizontal and vertical movement (i.e no knight moves on the rook)
    if(!(old1 == new1 || old2 == new2))
    {
      //cerr << "DEBUG: Error by non horizontal or non vertical movement" << endl;
      //cerr << "DEBUG: old1: " << old1 << endl;
      //cerr << "DEBUG: old2: " << old2 << endl;
      //cerr << "DEBUG: new1: " << new1 << endl;
     // cerr << "DEBUG: new2: " << new2 << endl;
      return false;
    }
    //object detection
    if(dy>0)
    {
      for(int i=1;i<dy;i++)
      {
        if(board[old1-i][old2] != ' ')
        {
          cerr << "DEBUG: Error by object in path" << endl;
          return false;
        }
      }
    }
    else if(dy<0)
    {
      for(int i=-1;i<dy;i--)
      {
        //cerr << "DEBUG ITER: " << i << endl;
        //cerr << "DEBUG IN: " << board[old1-i][old2] << endl;
        if(board[old1-i][old2] != ' ')
        {
          //cerr << "DEBUG: Error by object in path1" << endl;
          return false;
        }
      }
    }
    else if(dx>0)
    {
      for(int j=1;j<dx;j++)
      {
        if(board[old1][old2-j] != ' ')
        {
          //cerr << "DEBUG: Error by object in path" << endl;
          return false;
        }
      }
    }
    else if(dx<0)
    {
      for(int j =-1;j<dx;j--)
      {
        if(board[old1][old2-j] != ' ')
        {
          //cerr << "DEBUG: Error by object in path" << endl;
          return false;
        }
      }
    }
    return true;
  }

  bool evaluateKnight(int old1, int old2, int new1, int new2)
  {
    if((new2!=old2+1)&&(new2!=old2+2)&&(new2!=old2-1)&&(new2!=old2-2))
    {
      //cerr << "DEBUG: Error by not long L movement" << endl;
      return false;
    }
    else if((new1!=old1+1)&&(new1!=old1+2)&&(new1!=old1-1)&&(new1!=old1-2))
    {
      //cout << "DEBUG: Error by not wide L movement" << endl;
      return false;
    }
    else if((new1==old1+2 && new2==old2+2) || (new1==old1-2 && new2==old2-2))
    {
      //cout << "DEBUG: Error by 2x2 square movement" << endl;
      return false;
    }
    else if((new1==old1+1 && new2==old2+1) || (new1==old1-1 && new2==old2-1))
    {
      //cout << "DEBUG: Error by 1x1 square movement" << endl;
      return false;
    }
    return true;
  }

  bool evaluateBishop(int old1,int old2, int new1, int new2)
  {
    int dy = old1 - new1;
    int dx = old2 - new2;

    //cerr << "DEBUG: DX: " << dx << endl;
    //cerr << "DEBUG: DY: " << dy << endl;
    int ady = abs(dy);
    int adx = abs(dx);
      //TODO:Absolute value dx and dy just for the first case below
    if(ady != adx)
    {
      return false;
    }
    //Start object detection
    if(dy>0 && dx >0)    //NW
    {
      for(int i=1;i<dy;i++)
      {
        if(board[old1-i][old2-i] != ' ')
        {
          cerr << "OBJECT FOUND NW" << endl;
          return false;
        }
      }
    }
    else if(dy>0 && dx<0)   //NE
    {
      for(int i=1;i<dy;i++)
      {
        if(board[old1-i][old2+i] != ' ')
        {
          cerr << "OBJECT FOUND NE" << endl;
          return false;
        }
      }
    }
    else if(dy<0 && dx>0)   //SW
    {
      for(int i=1;i<dx;i++)
      {
        if(board[old1+i][old2-i] != ' ')
        {
          cerr << "OBJECT FOUND SW" << endl;
          return false;
        }
      }
    }
    else if(dy<0&&dx<0)   //SE
    {
      for(int i=1;i<dx;i--)
      {
        if(board[old1-i][old2-i] != ' ')
        {
          cerr << "OBJECT FOUND SE" << endl;
          return false;
        }
      }
    }
    return true;
  }

  bool evaluateKing(int old1,int old2, int new1, int new2)
  {
    int dy = old1 - new1;
    int dx = old2 - new2;
    bool castling;

    //cerr << "DEBUG: DX: " << dx << endl;
    //cerr << "DEBUG: DY: " << dy << endl;

    if(dy!=1 && dx!=1 && dy!=-1 && dx!=-1)   //check if the king is only moving one spot
    {
      if(new2 == old2+2 && new1 == 7)
      {
        //cerr << "DEBUG: REACHED CASTLECHECK" << endl;
        castling = castleCheck(7,7);   //Rook on the right
        if(castling)
        {
          //board[old1][old2] = ' ';
          board[old1][old1] = ' ';
          board[new1][new2-1] = 'r';
          //board[new1][new2] = 'k';
          cerr << "DEBUG new1, new2: " << new1 << " " << new2 << endl;
          return true;
        }

      }
      else if(new2 == old2-2 && new1 == 7)
      {
        castling = castleCheck(7,0);  //rook on the left
        if(castling)
        {
          //board[old1][old2] = ' ';
          board[old1][old2-4] = ' ';
          board[new1][new2+1] = 'r';
          //board[new1][new2] = 'k';
          cerr << "DEBUG new1, new2: " << new1 << " " << new2 << endl;
          return true;
        }
      }
      return false;
    }

    kingMoved = true;
    return true;
  }

  bool evaluateQueen(int old1,int old2,int new1,int new2)
  {
     if(old1==new1 || old2==new2)
      return evaluateRook(old1,old2,new1,new2);
     else
      return evaluateBishop(old1,old2,new1,new2);
  }

  //bool evaluateCastle(int old1,int old2, new1, int new2)

  void updatePiece(int old1,int old2,int new1,int new2)
  {
    char tmp = board[old1][old2];
    board[new1][new2] = tmp;
    board[old1][old2] = ' ';
    return;
  }

  bool upperCasePiece(char a)
  {
    if(a=='R'||a=='K'||a=='B'||a=='Q'||a=='K'||a=='P')
      return true;
    else
      return false;
  }

  //might need to pass in king for checkmate
  bool checkChecker(int kingy, int kingx)
  {
    bool check;
    //cerr << "MADE IT IN" << endl;
    //cerr << "DEBUG: kingy: " << kingy << endl;
    //cerr << "DEBUG: kingx: " << kingx <<  endl;
    //cerr << "FOUND THE KING" << endl;
    for(int i=0;i<8;i++)
    {
      for(int j=0;j<8;j++)
      {
        if(upperCasePiece(board[i][j]))
        {
          switch(board[i][j])  //no king evaluation since a king can't take another king
          {
            case 'R':
               check = evaluateRook(i,j,kingy,kingx);
               break;
            case 'N':
              check = evaluateKnight(i,j,kingy,kingx);
              break;
            case 'B':
              check = evaluateBishop(i,j,kingy,kingx);
              break;
            case 'Q':
              check =  evaluateQueen(i,j,kingy,kingx);
              break;
            case 'P':
              check = evaluatePawnL(i,j,kingy,kingx);
          }
          if(check == true)
            return true;
        }
      }
    }
    return false;
  }


  //TODO: Make sure the Rook can't move in order to castle
  bool castleCheck(int rooky,int rookx)
  {
    int kingx,kingy;
    findPiece('k',kingy,kingx);
    cerr << "DEBUG: rooky: " << rooky << endl;
    cerr << "DEBUG: rookx: " << rookx << endl;
    bool inCheck = checkChecker(kingy,kingx);
    cerr << "DEBUG: kingy: " << kingy << endl;
    cerr << "DEBUG: kingx: " << kingx << endl;
    bool moveable = evaluateRook(rooky,rookx,7,4);
    if(board[rooky][rookx] != 'r')  //if there is no actual rook there
    {
      cout << "No rook in where you want to castle!" << endl;
      return false;
    }

    if(kingMoved) //the king cannot have moved and the king must not be in check in order to castle
    {
      cout << "The King has already moved!" << endl;
      return false;
    }
    else if(inCheck)
    {
      cout << "You are in Check, you cannot Castle!" << endl;
      return false;
    }
    else if(!moveable)
    {
      cout << "The path for the rook and the king is not clear!" << endl;
      return false;
    }
    //cerr << "TRUE" << endl;
    return true;
  }

  bool findPiece(char piece,int &y,int &x)
  {
    for(int i=0;i<8;i++)
    {
      for(int j=0;j<8;j++)
      {
        if(board[i][j] == piece)
        {
          y = i;
          x = j;
          return true;
        }
      }
    }
    return false;
  }
};


#endif // BOARD_H_INCLUDED
