// Class definition for XO_Board class
// Author:  Mohammad El-Ramly
// Date:    10/10/2022
// Version: 1
// code editing ......
// implementation minimax and best move methods
// Author:  Ayman Antar
// Date:    11/17/2022
#include <iostream>
#include <random>
#include <iomanip>
#include <algorithm>
#include "../include/XO_Classes.hpp"
using namespace std;

// Return true  if move is valid and put it on board
// within board boundaries in empty cell
// Return false otherwise
bool Board::update_board (int x, int y, char mark){
   // Only update if move is valid
   if (!(x < 0 || x > 2 || y < 0 || y > 2) && (board[x][y] == 0)) {
      board[x][y] = toupper(mark);
      n_moves++;
      return true;
   }
   else
      return false;
}

// Display the board and the pieces on it
void Board::display_board() {
   for (int i: {0,1,2}) {
      cout << "\n| ";
      for (int j: {0,1,2}) {
         cout << "(" << i << "," << j << ")";
         cout << setw(2) << board [i][j] << " |";
      }
      cout << "\n-----------------------------";
   }
   cout << endl;
}

// Returns true if there is any winner
// either X or O
// Written in a complex way. DO NOT DO LIKE THIS.
bool Board::is_winner() {
    char row_win[3], col_win[3], diag_win[2];
    for (int i:{0,1,2}) {
        row_win[i] = board[i][0] & board[i][1] & board[i][2];
        col_win[i] = board[0][i] & board[1][i] & board[2][i];
    }
    diag_win[0] = board[0][0] & board[1][1] & board[2][2];
    diag_win[1] = board[2][0] & board[1][1] & board[0][2];

    for (int i:{0,1,2}) {
        if ( (row_win[i] && (row_win[i] == board[i][0])) ||
             (col_win[i] && (col_win[i] == board[0][i])) )
            {return true;}
    }
    if ((diag_win[0] && diag_win[0] == board[1][1]) ||
        (diag_win[1] && diag_win[1] == board[1][1]))
        {return true;}
    return false;
}
bool Board::is_draw() {
    return (n_moves == 9 && !is_winner());
}
int Board::minimax(bool isMax)
{
	if (this->is_winner())
    {
        if (isMax)
        {
            return -1 ;
        }
        else
        {
            return 1;
        }
    }
	if (this->is_draw())
    {
        return 0 ;
    }

	if (isMax)
	{
		int best = -10;
		for (int i = 0; i<3; i++)
		{
			for (int j = 0; j<3; j++)
			{
				if (board[i][j]==0)
				{
					board[i][j] = 'O';
					n_moves ++;
					best = max( best,minimax (!isMax) );
					board[i][j] = 0 ;
                    n_moves --;
				}
			}
		}
		return best;
	}
	else
	{
		int best = 10;
		for (int i = 0; i<3; i++)
		{
			for (int j = 0; j<3; j++)
			{
				if (board[i][j]==0)
				{
					board[i][j] = 'X';
                    n_moves ++;
					best = min(best,minimax(!isMax));
					board[i][j] = 0;
                    n_moves --;
				}
			}
		}
		return best;
	}
}
pair <int ,int > Board::BestMove()
{
	int Val = -10;
	pair<int , int > Move;
	Move.first = -1;
	Move.second = -1;

	for (int i = 0; i<3; i++)
	{
		for (int j = 0; j<3; j++)
		{
			if (board[i][j]==0)
			{
				board[i][j] = 'O';
                n_moves ++;
				int movee = minimax(false);
				board[i][j] = 0;
                n_moves --;
				Val = max ( movee , Val );
				if (Val==movee)
                {
					Move.first = i;
					Move.second= j;
                }
			}
		}
	}

	return Move;
}



