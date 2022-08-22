/*
  TicTacToeDisplayExample.ino - Example for how to use the TicTacToeDisplay library
  Created by Preston J. Rooker, January 2, 2022.  
*/

//Before you start, make sure that you have installed the Adafruit_GFX.h library and Adafruit_SSD1306.h libraries, as they are neccesary for TicTacToeDisplay library 

//Make sure to include the library :)
#include <TicTacToeDisplay.h>

void(* resetFunc) (void) = 0;
//Start off by making a TicTacToeDisplay object
TicTacToeDisplay display; 
int VRX = A0;
int VRY = A1;
int SW = 3;
int pos = 4;
int vrxValue = 500;
int vryValue = 500;
int swValue = 1;

const int MAX_STAY_IN_PLACE_THRESHOLD = 1000;
const int MIN_STAY_IN_PLACE_THRESHOLD = 20;
int fullness = 0;
char grid[9] = {'.', '.', '.', '.', '.', '.', '.', '.', '.'};
void move(char player) {
  if (player == 'O')
    display.drawLargeText("O is\nUp");
  else 
    display.drawLargeText("X is\nUp");
  for(;;) {
   display.selectSquare(pos);
   vrxValue = analogRead(VRX);
   vryValue = analogRead(VRY);
   swValue = digitalRead(SW);
   
   Serial.print(swValue);
   if (swValue == 0) {
   //display.drawSmallText("Attempt to move");
   Serial.print(grid[pos]);
      if (grid[pos] == '.') {
       grid[pos] = player;
       if (player == 'O') {
        display.drawO(pos);
        delay(500);
       }
       else
        display.drawX(pos);
       fullness++;
       break;
       //display.drawBoard();
      }
      else {
        continue;
      }
    }
     
    if (vryValue < MIN_STAY_IN_PLACE_THRESHOLD) 
      if (pos - 3 > -1) {
        display.deselectSquare(pos);
        pos -= 3;
      }
    if (vryValue > MAX_STAY_IN_PLACE_THRESHOLD) 
      if (pos + 3 < 9) {
        display.deselectSquare(pos);
        pos += 3;
      }
    if (vrxValue < MIN_STAY_IN_PLACE_THRESHOLD) 
      if (pos - 1  > -1) {
        display.deselectSquare(pos);
        pos --;
      }
    if (vrxValue > MAX_STAY_IN_PLACE_THRESHOLD) 
      if (pos + 1 < 9) {
        display.deselectSquare(pos);  
        pos ++;
      }
  } 
}

bool checkVictory() {
  if (grid[0] == grid[1] && grid[1] == grid[2] && grid[1] != '.') {
    display.drawVictoryLine(0,2);
    String victory = "  ";
    victory += grid[0];
    victory += "       Wins!";
    display.drawLargeText(victory);
    display.flashScreen();
    delay(500);
    return true;
  }
  if (grid[3] == grid[4] && grid[4] == grid[5] && grid[4] != '.') {
    display.drawVictoryLine(3,5);
    String victory = "  ";
    victory += grid[4];
    victory += "       Wins!";
    display.drawLargeText(victory);
    display.flashScreen();
    delay(500);
    return true;
  }
  if (grid[6] == grid[7] && grid[7] == grid[8] && grid[7] != '.') {
    display.drawVictoryLine(6,8);
    String victory = "  ";
    victory += grid[7];
    victory += "       Wins!";
    display.drawLargeText(victory);
    display.flashScreen();
    delay(500);
    return true;
  }
   if (grid[0] == grid[3] && grid[3] == grid[6] && grid[3] != '.') {
    display.drawVictoryLine(0,6);
    String victory = "  ";
    victory += grid[3];
    victory += "       Wins!";
    display.drawLargeText(victory);
    display.flashScreen();
    delay(500);
    return true;
  }
  if (grid[1] == grid[4] && grid[4] == grid[7] && grid[4] != '.') {
    display.drawVictoryLine(3,5);
    String victory = "  ";
    victory += grid[4];
    victory += "       Wins!";
    display.drawLargeText(victory);
    display.flashScreen();
    delay(500);
    return true;
  }
  if (grid[2] == grid[5] && grid[5] == grid[8] && grid[5] != '.') {
    display.drawVictoryLine(2,8);
    String victory = "  ";
    victory += grid[5];
    victory += "       Wins!";
    display.drawLargeText(victory);
    display.flashScreen();
    delay(500);
    return true;
  }
  if (grid[0] == grid[4] && grid[4] == grid[8] && grid[4] != '.') {
    display.drawVictoryLine(0,8);
    String victory = "  ";
    victory += grid[4];
    victory += "       Wins!";
    display.drawLargeText(victory);
    display.flashScreen();
    delay(500);
    return true;
  }
  if (grid[2] == grid[4] && grid[4] == grid[6] && grid[4] != '.') {
    display.drawVictoryLine(2,6);
    String victory = "  ";
    victory += grid[4];
    victory += "       Wins!";
    display.drawLargeText(victory);
    display.flashScreen();
    delay(500);
    return true;
  }
  return false;
}

void setup() {
  
  /////////////////////////////////////////////////
  //////////////// SETUP FUNCTIONS ////////////////
  /////////////////////////////////////////////////
  
  //First, make sure you call the begin() function
  //if screen doesn't work from the start its likely because you forgot display.begin(), or because you are using too much memory
  display.begin();
  pinMode(VRX, INPUT);
  pinMode(VRY, INPUT);
  pinMode(SW, INPUT_PULLUP); 
  Serial.begin(9600);
  //You can start off by drawing the tictactoe board with drawBoard()
  display.drawBoard();
  delay(500); //you can always add delays between drawings with the delay(milliseconds) function



  /////////////////////////////////////////////////
  ////////////// Drawing X's and O's //////////////
  /////////////////////////////////////////////////

/*
  //Now that we have our board, we can draw X's and O's
  //to draw an X or O, we have to choose the square to draw it in. The squares are indexed from 0 to 8
  //    0|1|2
  //    -----
  //    3|4|5
  //    -----
  //    6|7|8
  
  display.drawX(0); //this draws an X at square 0, which is the top left
  delay(500);
  display.drawO(4); //this draws an O at square 4, which is the middle
  delay(500);
  display.drawX(1); //this draws an X at square 1, which is the top center
  delay(500);
  display.drawO(6); //this draws an O at square 6, which is the bottom left
  delay(500);
  display.drawX(2); //this draws an X at square 2, which is the top right
  delay(500);
*/
  

  
  /////////////////////////////////////////////////
  //////////////// Writing Text ///////////////////
  /////////////////////////////////////////////////

  /*//Now that the game is over, let's learn how to write text so that we can show who won
  //There are two sizes of text, small and large

  //lets start with small text, which is written with drawSmallText(stringMessage)
  //small text can have 88 characters max, with 11 characters per line horizontally, and 8 lines max vertically
  //lets use small text to congratulate player X
  display.drawSmallText("Congratulations Player X! You win!");
  delay(2000);
  //that doesn't look so good because of spacing, lets try again, this time spacing things out so there are 11 characters in each line
  display.drawSmallText("Congrats              Player X!             You Win!");
  delay(2000); 
  //that looks much better!

  //now lets try writing large text with drawLargeText(stringMessage)
  //large text can have 20 characters max with 5 characters per line horizontally, and 4 lines max vertically
  display.drawLargeText("Player X Wins!");
  delay(2000);
  //again because of spacing this doesn't look great, lets try again with shorter words and better spacing
  display.drawLargeText("  X       Wins!");
  delay(2000);
  //keep in mind that whenever you draw text, it automatically erases whatever text was there beforehand */

  
  /////////////////////////////////////////////////
  //////////////// Clearing Functions /////////////
  /////////////////////////////////////////////////

  //you can always redraw the board with another call to drawBoard()
  display.drawBoard(); 
  delay(500);

  /////////////////////////////////////////////////
  /////////////// Selecting Functions /////////////
  /////////////////////////////////////////////////

  //if we want to mark a square as selected, we can use selectSquare(squareNum)
  //this colors in the corners of a square to show that it's selected
  //lets use a for loop to select each square on the board
  for(int i = 0; i<9; i++){
    display.selectSquare(i);
    delay(200);
  }

  //to deselect a square thats marked as selected, we can use deselectSquare(squareNum)
  //lets use a for loop to deselect each square on the board
  for(int i = 0; i<9; i++){
    display.deselectSquare(i);
    delay(200);
  }
  delay(4000);
}

void loop() {
  if (checkVictory()) {
    display.drawSmallText("Restarting the Game");
    delay(2000);
    resetFunc();
  }
  
  move('O');
 
  if(checkVictory()) {
    display.drawSmallText("Restarting the Game");
    delay(2000);
    resetFunc();
  }
  else if (fullness == 9) {
    display.drawLargeText("A    Draw!");
    display.flashScreen();
    delay(500);
    display.drawSmallText("Restarting the Game");
    delay(2000);
    resetFunc();
  }
  move('X');
}
