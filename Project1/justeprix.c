#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>


int main() {
    int test = 0;
    int exit = 0; 

    printf("**---------------------------------------------------**\n**-------------------Le juste prix-------------------**\n");
    
    while (exit != 3)
    {
        test = 0;
        while (test != 1)
        {
            printf("\n**  Que souhaitez vous faire ?\n**  (1)jouer | (2)voir l'historique des parties | (3)quiter\n**  >> ");
            test = scanf_s("%d", &exit);
            if (test != 1 || !(exit >= 1 && exit <= 3))
            {
                printf("**  /!\\ choisissez l'une des 3 options !! /!\\\n");
                test = 0;
                while (getchar() != '\n');
            }
        }
        if (exit == 1)
        {
            int nbref;
            int nbchoix = 0;
            int plage[2];
            int* essais = NULL;
            int coups = 0;
            FILE* file = fopen("parties.txt", "a");


            while (test != 1)
            {
                printf("**  Definition nombre initial rand\n**  veuillez incerer un nombre aleatoire :\n**  >> ");
                int init;
                test = scanf_s("%d", &init);
                if (test != 1)
                {
                    printf("**  /!\\ le format que vous avez utilise est incorrect! /!\\\n");
                    test = 0;
                    while (getchar() != '\n');
                }
                else
                {
                    srand((unsigned int)time(NULL) + init);
                }
            }
    
            while (test != 2)
            {
                printf("\n**  Choix de l'intervalle de jeu\n**  veuillez incerer une chaine au format 0,1000 :\n**  >> ");
                test = scanf_s("%d,%d", &plage[0], &plage[1]);
                if (test != 2 || (plage[1] - plage[0]) < 2)
                {
                    printf("**  /!\\ le format que vous avez utilise est incorrect! /!\\\n");
                    test = 0;
                    while (getchar() != '\n');
                }
            }
            printf("\n**  le jeu sera dans l'intervalle %d a %d !!\n", plage[0], plage[1]);

    
            nbref = plage[0] + (rand() % (plage[1] - plage[0]));

            while (nbchoix != nbref) {
                printf("\n**  Quel nombre propose tu ?\n**  >> ");
                scanf_s("%d", &nbchoix);
                if (nbchoix > plage[0] && nbchoix < plage[1])
                {
                    essais = realloc(essais, (coups + 1) * sizeof(int));
                    essais[coups] = nbchoix;
                    coups++;
                    if (nbchoix > nbref)
                    {
                        printf("**  c moins");
                    }
                    else if (nbchoix < nbref)
                    {
                        printf("**  c plus");
                    }
                    else
                    {
                        printf("**  c gagne");
                    }
                }
                else
                {
                    printf("**  bah t con, on ta dit ça tte a l'heure:\n**  le jeu sera dans l'intervalle %d a %d !!\n", plage[0], plage[1]);
                }
            }


            fprintf(file, "**---------------------**\n");
            fprintf(file, "**----Le juste prix----**\n");
            fprintf(file, "** intervale: %d,%d\n", plage[0], plage[1]);
            fprintf(file, "** nombre choisi: %d\n", nbref);
            int i;
            for (i = 0; i < coups; i++) {
                fprintf(file, "** >> %d\n", essais[i]);
            }
            fprintf(file, "**---------------------**\n\n\n");
            fclose(file);

            free(essais);

        }
        else if(exit == 2)
        {
            FILE* file = fopen("parties.txt", "r");
            if (file != NULL) {
                char line[30];

                while (fgets(line, sizeof(line), file) != NULL) {
                    printf("%s", line);
                }

                fclose(file);
            }
            else {
                printf("Impossible d'ouvrir le fichier.\n");
            }
            printf("historique result");
        }
    }


    return 0;
}