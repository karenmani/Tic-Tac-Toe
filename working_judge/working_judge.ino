#include <Wire.h>

boolean game_end = false;
int board_counter = 0;
char board[9] = {'-', '-', '-', '-', '-', '-', '-', '-', '-'}; 
char p1, p2 = 0;
boolean player1 = true; 
boolean player2 = false; 

void setup() {
  Serial.begin(9600);  // start serial for output
  Wire.begin();        // join i2c bus
}

void loop() {
/*
 * counter for number of turns taken on the board and while game is going on
*/
  while(!game_end && board_counter < 9) { 
    move1(); //player 1's turn 
    move2(); 
  }
}

/*
 * Player 1's turn 
*/
void move1(){
  Wire.requestFrom(7, 1);    // request 1 byte1 from slave device #7
    while (Wire.available() && player1) { 
      int c = Wire.read(); // receive a byte as int
      if (c > 0) { //only executes if user inputs 1-9 
       spotFull1(c-1); //function to check if the spot user wants to input a character in is taken 
       board[c-1] = 'X'; //sets an X where user inputs #'s 1-9 (c-1 due to array indexing)
       
       printBoard(); 
       board_counter++; 

/*
 * Win conditions for Player 1
*/
       if(
          (board[0] == 'X' && board[1] == 'X' && board[2] == 'X') || //horizontals
          (board[3] == 'X' && board[4] == 'X' && board[5] == 'X') ||
          (board[6] == 'X' && board[7] == 'X' && board[8] == 'X') ||
          (board[0] == 'X' && board[3] == 'X' && board[6] == 'X') || //verticals
          (board[1] == 'X' && board[4] == 'X' && board[7] == 'X') ||
          (board[2] == 'X' && board[5] == 'X' && board[8] == 'X') ||
          (board[0] == 'X' && board[4] == 'X' && board[8] == 'X') || //diagonals
          (board[2] == 'X' && board[4] == 'X' && board[6] == 'X')) {
              Serial.print("Player 1 wins!");
              game_end = true;
       }

      boardFull(); //checks for ties
/*
 * Tells game that it is no longer player 1's turn and now player 2 can go
*/
      player1 = false;
      player2 = true; 
    }
  }
}

/*
 * Player 2's turn 
*/
void move2(){
    Wire.requestFrom(8, 1);    // request 1 bytes from slave device #8
    while (Wire.available() && player2) { 
      int b = Wire.read(); // receive a byte as int
      
      if (b > 0) { //only executes if user inputs 1-9 
        spotFull2(b-1); //function to check if the spot user wants to input a character in is taken 
        board[b-1] = 'O'; //sets an X where user inputs #'s 1-9 (b-1 due to array indexing)
        
        printBoard(); 
        board_counter++; 
        
/*
 * Win conditions for Player 2
*/
        if(
          (board[0] == 'O' && board[1] == 'O' && board[2] == 'O') || //horizontals
          (board[3] == 'O' && board[4] == 'O' && board[5] == 'O') ||
          (board[6] == 'O' && board[7] == 'O' && board[8] == 'O') ||
          (board[0] == 'O' && board[3] == 'O' && board[6] == 'O') || //verticals
          (board[1] == 'O' && board[4] == 'O' && board[7] == 'O') ||
          (board[2] == 'O' && board[5] == 'O' && board[8] == 'O') ||
          (board[0] == 'O' && board[4] == 'O' && board[8] == 'O') || //diagonals
          (board[2] == 'O' && board[4] == 'O' && board[6] == 'O')) {
              Serial.print("Player 2 wins!");
              game_end = true;
        }
        
        boardFull(); //checks for ties 
/*
 * Tells game that it is no longer player 2's turn and now player 1 can go
 */
        player2 = false; 
        player1 = true; 
    }
  }
}

/* 
 * Checks if player 1 is trying to put an input at a non-empty slot, where empty slots are denoted
 * by dashes, and then recalls player 1's turn
*/
void spotFull1(char position) {
  if(board[position] != '-') {
         Serial.println("That spot is taken! Please try again.");
        move1();
  }
}

/* 
 * Checks if player 2 is trying to put an input at a non-empty slot, where empty slots are denoted
 * by dashes, and then recalls player 2's turn
*/
void spotFull2(char position) {
  if(board[position] != '-') {
      Serial.println("That spot is taken! Please try again.");
      move2();
    }   
}

/*
 * Checks if the board is full by comparing the board counter, which is supposed to increment after
 * each player's turn. If the board is full and no win conditions are met, a tie is called
 */
void boardFull() { 
     if(board_counter == 9) {
      game_end = true;
      Serial.print("Tie!");
     } 
}

/*
 * Prints the board after each turn 
*/
void printBoard() { 
  Serial.print("[");
  Serial.print(board[0]);
  Serial.print("] ");
  Serial.print("[");
  Serial.print(board[1]);
  Serial.print("] "); 
  Serial.print("[");
  Serial.print(board[2]);
  Serial.println("] ");
  
  Serial.print("[");
  Serial.print(board[3]);
  Serial.print("] ");
  Serial.print("[");
  Serial.print(board[4]);
  Serial.print("] "); 
  Serial.print("[");
  Serial.print(board[5]);
  
  Serial.println("] ");
  Serial.print("[");
  Serial.print(board[6]);
  Serial.print("] ");
  Serial.print("[");
  Serial.print(board[7]);
  Serial.print("] "); 
  Serial.print("[");
  Serial.print(board[8]);
  Serial.println("] ");

  Serial.println(""); 
}
