#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
    int hand[3] = {0, 1, 2};/*計算用*/
    int realhand[3] = {0, 2, 5};/*入力用コマンド*/
    int flag = 0;
    int player_hand, handkey, jud;
    unsigned int seed;

    while (1)
    {
        printf("Please enter an integeer \nRock => 0\nScissors => 2\nPaper => 5\n");
        seed = (unsigned int)time(0);

        scanf("%d", &player_hand);

        /*計算用に変換*/
        if(player_hand == 2){
            player_hand = 1;
        }else if(player_hand == 5){
            player_hand = 2;
        }else if(player_hand == 0){
            player_hand = 0;
        }else{
            player_hand = 100;
        }
    
        srand(seed);

        for (int i = 0; i < 3; i++)
        {
            if (hand[i] == player_hand)
            {
                flag = 1;
                break;
            }
        }

        if (flag)
        {
            handkey = (rand() % 3);
            printf("CON: %d VS PLAYER: %d \n", realhand[handkey], realhand[player_hand]);
            jud = (player_hand - hand[handkey] + 3) % 3;
            if (jud == 0)
            {
                printf("TIE ...... Try Again\n");
                flag = 0;
            }
            else if (jud == 1){
                printf("YOU LOSE! \n俺の勝ち！\nContinue?: y or n\n");
                char cont;
                scanf("%s", &cont);
                if (cont == 'y'){
                    flag = 0;
                }
                else if (cont == 'n'){
                    break;
                }
            }
            else{
                printf("YOU WIN!");
                break;
            }
        }else{
            printf("You enter an invalid number ......\nPlease enter a valid number\n");
        }
        }

    return 0;
}