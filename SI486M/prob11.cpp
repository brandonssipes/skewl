//Problem 11 Sipes
#include <stdio.h>
#include <ctime>
#include <cstdlib>

class Tennis {
  private:
    int P1prob;
    int P2prob;
    int P1score = 0;
    int P2score = 0;
    int turn = 0;

    void player(int &X,int &Y,int prob){//generic match
      if ((std::rand()%100) < prob)
        X ++;
      else
        Y ++;
    }

    int _play(){
      if((P1score > 7 || P2score > 7) && (abs(P1score-P2score) >= 2)){
        return P1score + P2score;
      }
      else{
        if ((turn%4) < 2){
          player(P1score,P2score,P1prob);
        }else{
          player(P2score,P1score,P2prob);
        }
        turn ++;
      }
      return _play();
    }


  public:
    Tennis(int p1,int p2){
      P1prob = p1;
      P2prob = p2;
    }

    int play(){
      if ((std::rand()%2) == 0){//should still be even
        player(P1score,P2score, P1prob);//player1
        turn = 2;//player2's turn
      }else{
        player(P2score,P1score,P2prob);//player2
        turn = 0;//player1's turn
      }
      return _play();
    }


};

int main(){
  std::srand(std::time(nullptr));//randint for the start player
  int player1;
  int player2;
  printf("Enter in player1 server advantage = ");
  scanf("%d",&player1);
  printf("Enter in player2 server advantage = ");
  scanf("%d",&player2);

  int count;
  printf("How many games should we play = ");
  scanf("%d", &count);
  int sipes = count;
  int sum = 0;
  while (count > 0){
    Tennis game(player1,player2);
    sum += game.play();
    count --;
  }
  printf("%d\n",sum/sipes);

  return 0;
}
