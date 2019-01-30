#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct player {
    char name[80];
    int number;
    float avg_points;
    int year;
    struct player *next;
} bb_player;

FILE *fr;

bb_player* sort(bb_player *players, int total);

int main(int num, char* args[]) {
    char* file_name = args[num-1];
    bb_player *players = NULL;
    bb_player *tmp = NULL;
    int count = 0;
    char line[80];

    fr = fopen (file_name, "rt");
    if (fr == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    while(fgets(line, 80, fr) != NULL) {
        if (strncmp(line, "DONE\n", 80) == 0) break;

        char player_name[80];
        int player_number;
        float player_points;
        int player_year;
        
        sscanf(line, "%s", player_name);
        fgets(line, 80, fr);
        sscanf(line, "%d", &player_number);
        fgets(line, 80, fr);
        sscanf(line, "%f", &player_points);
        fgets(line, 80, fr);
        sscanf(line, "%d", &player_year);
       
        bb_player *player = (bb_player*) malloc(sizeof(bb_player));
        strcpy(player->name, player_name);
        player->number = player_number;
        player->avg_points = player_points;
        player->year = player_year;
        player->next = NULL;

        if(players == NULL) {
            players = player;
            tmp = player;
        }
        else {
            tmp->next = player;
            tmp = tmp->next;
        }
        count++;
    }

    players = sort(players, count);

    tmp = players;
    while (tmp != NULL) {
        printf("%s %d %d\n", tmp->name, tmp->number, tmp->year);
        tmp = tmp->next;
    }

    //ISSUE: fix this
    tmp = players;
    while (tmp != NULL) {
        bb_player *t = tmp;
        tmp = tmp->next;
        free (t);
    }

    while (players != NULL) {
        bb_player *tmp = players;
        players = players->next;
        free(tmp);
    }

    fclose(fr);
    return 0;
}

bb_player* sort(bb_player *players, int total) {
    if (total <= 1) return players;
    bb_player *head = players;
    while (players != NULL) {
        if (players->next->avg_points > players->avg_points) {
            bb_player *tmp = players->next;
            players->next = players;
            players = tmp;
        }
        players = players->next;
    }
    return head;
}