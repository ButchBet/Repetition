#include <stdio.h>
#include <stdbool.h>

/* The simply call clrscr(). On windows, it will use conio.h's clrscr(), and on linux, It will use Ansi scape codes. */
#ifdef _WIN32
#include <conio.h>
#else
#include <stdio.h>
#define clrscr() printf("\e[1; 1H\e[2J");
#endif

// Prototype functions
char name_registration(void);
void draw_board(void);
int verify();
void require_position(int inx);


// variables to use
char position_mark[3][3] = {{"A", "B", "C"},{"D", "E", "F"}, {"G", "H", "I"}}; // Position to mark X or O in each case
/*NOTE: We use the * to have an array of strings-characters and not a simple character.*/
char *p_mark; // postion mark pointer
p_mark = &position_mark;
char names[2][30]; // players name to don't use pi and p2 as reference

char* choose[1] = {"N"};
char p_ch; // choose pointer
p_ch = &choose;

bool id  = true; /* Used to can require position to each player and don't repit a reding*/
bool change = false; /* Used to can stop a nested loop when the readed character had been changed */ 

int main(void){
  printf("\n\n");
  printf("Wellcome to tiki's game.");
  name_registration();
}

// Name registration function
char name_registration(){
  printf("\nEnter the players name -->"); scanf("%s %s", &names[0][0], &names[1][0]);
  printf("\n\n");

  draw_board();
}

// Drawing board function
void draw_board(){
  for(int i = 0; i < 3; i++){
    for(int j = 0; j < 3; j++){
      printf("     %c    ", *position_mark[i][j]); /*Here we are using 
      characters as references to can change it for X or O in the respective
      case. */
    }printf("\n\n");
  }

  /* conditional to can verify if player 1 or 2 had won, make draw or any
     case */
  if(verify() == 0){ // 1 winer or draw
    printf("%s is the winer, congratulation.", names[0]);
    printf("\n");
  }
  else if(verify() == 1){
    printf("%s is the winer, congratulation.", names[1]);
    printf("\n");
  }
//  else if(verify() == 2 ){
//    printf("This is a draw.");
//    printf("\n");
//  }
  else{
    if(id){
      require_position(0); // require position to p1
    }
    else{
      require_position(1); // require position to p2
    }
  }
}

// verify game status
int verify(){ // We have to evalueate 8 differetn cases
  if(position_mark[0][0] == "X" && position_mark[0][1] == "X" && position_mark[0][2] == "X" || position_mark[1][0] == "X" && position_mark[1][1] == "X" && position_mark[1][2] == "X" || position_mark[2][0] == "X" && position_mark[2][1] == "X" && position_mark[2][2] == "X" || position_mark[0][0] == "X" && position_mark[1][0] == "X" && position_mark[2][0] == "X" || position_mark[0][1] == "X" && position_mark[1][1] == "X" && position_mark[2][1] == "X" || position_mark[0][2] == "X" && position_mark[1][2] == "X" && position_mark[2][2] == "X" || position_mark[0][0] == "X" && position_mark[1][1] == "X" && position_mark[2][2] == "X" || position_mark[0][2] == "X" && position_mark[1][1] == "X" && position_mark[2][0] == "X"){
    return 0;
  }
  else if(position_mark[0][0] == "O" && position_mark[0][1] == "O" && position_mark[0][2] == "O" || position_mark[1][0] == "O" && position_mark[1][1] == "O" && position_mark[1][2] == "O" || position_mark[2][0] == "O" && position_mark[2][1] == "O" && position_mark[2][2] == "O" || position_mark[0][0] == "O" && position_mark[1][0] == "O" && position_mark[2][0] == "O" || position_mark[0][1] == "O" && position_mark[1][1] == "O" && position_mark[2][1] == "O" || position_mark[0][2] == "O" && position_mark[1][2] == "O" && position_mark[2][2] == "O" || position_mark[0][0] == "O" && position_mark[1][1] == "O" && position_mark[2][2] == "X" || position_mark[0][2] == "O" && position_mark[1][1] == "O" && position_mark[2][0] == "O"){
    return 1;
  }
//  else{
//    return 2;
//  }
}


// Get player 1 and 2 options to change it for X or O respectively
void require_position(int inx){
  printf("%s please choose -->.", names[inx]);
  scanf("%c", choose[0]);

  // Here we are verifying that choose is insithe the range
  if(choose[0] == "A" || choose[0] == "B" || choose[0] == "C" || choose[0] == "D" || choose[0] == "E" || choose[0] == "F" || choose[0] == "G" || choose[0] == "H" || choose[0] == "I"){
    // compare choose with each position_mark character to change it to X or O in each case
    for(int i = 0; i < 3; i++){
      for(int j = 0; j < 3; j++){
	if(choose[0] == position_mark[i][j]){
	  switch(inx){ // to change for X or O y in the case
	  case 0:
	    position_mark[i][j] = "X";
	    id = false;
	    change = true;
	    break;
	  case 1:
	    position_mark[i][j] = "O";
	    id = true;
	    change = true;
	    break;
	  }
	}
	else if(change){
	  break;
	}else{}
      }
      if(change){
	break;
	clrscr(); // clean screen
	draw_board(); // draw the board with the new data
      }
    }
  }
  else{
    printf("Invalid choose, please thy again.\n");
    require_position(inx);
  }
}
