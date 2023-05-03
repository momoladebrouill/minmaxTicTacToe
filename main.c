#include <stdio.h>
#include <stdlib.h>

#define VIDE 0
#define CROA 1
#define ROND 2

#define AT(X,Y) 2*X+6*Y

typedef signed long int plateau;

plateau put_at(plateau p,int x, int y,int v){
    return p | (v+1)<<AT(x,y);
}

int get_at(plateau p,int x,int y){
    return (p>>AT(x,y)) & 0b11;
}

int is_winning(plateau  plat){
    // if someone is winning, his/her name else 0
    for(int i=0;i<3;i++){
        // colonnz
        if(get_at(plat,i,0) == get_at(plat,i,1) && get_at(plat,i,2) == get_at(plat,i,1))
            return get_at(plat,i,0);
        // lignz
        if(get_at(plat,0,i) == get_at(plat,1,i) && get_at(plat,2,i) == get_at(plat,1,i))
            return get_at(plat,0,i);
    }
    if(get_at(plat,0,0)==get_at(plat,1,1) && get_at(plat,2,2) == get_at(plat,0,0))
        return get_at(plat,0,0);
    if(get_at(plat,0,2)==get_at(plat,1,1) && get_at(plat,0,2) == get_at(plat,2,0))
        return get_at(plat,0,2);
    return 0;
}

int minmax(plateau plat,int turn,int * bestx,int * besty){
    if(is_winning(plat))
        return is_winning(plat) == ROND ? 1 : -1;
    int score = -999;
    int new_score;
    for(int y=0;y<3;y++)
        for(int x=0;x<3;x++)
            if(!get_at(plat,x,y)) // if it's somewhere intersting
                if(score < (new_score = minmax(put_at(plat,x,y,turn),!turn,NULL,NULL))){
                    if(bestx && besty){
                      *bestx = x;
                      *besty = y;
                    } // if it gives a better score, keep it
                    score = new_score;
                }
    return score; // return the score
}

/*void print_plato(plateau  plat){
    for(int y=0;y<3;y++){
        for(int x=0;x<3;x++)
            printf("%c ", " XO"[get_at(plat,x,y)]);
        printf("\n");
     }
}*/
void print_plato(plateau plat){
    printf("   0 1 2\n");
    printf("  +-+-+-+\n");
    for(int y=0;y<3;y++){
        printf("%d |", y);
        for(int x=0;x<3;x++)
            printf("%c|", " XO"[get_at(plat,x,y)]);
        printf("\n");
        printf("  +-+-+-+\n");
     }
}
int main(void){
  plateau plato = 0;
  // REPL
  int turn = 1;
  int bestx,besty;
  int x;
  int y;
  while(1){
      print_plato(plato);
      turn = !turn;
      printf(" x> ");
      scanf("%d",&x);
      printf(" y> ");
      scanf("%d",&y);
      plato = put_at(plato,x,y,turn);
      print_plato(plato);
      printf("--- Computer plays :\n");
      turn = !turn;
      minmax(plato,turn,&bestx,&besty);
      plato = put_at(plato,bestx,besty,turn);

  }
}
