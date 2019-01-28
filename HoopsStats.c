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

int sort(bb_player *players, int count);
int merge(bb_player *players, int count);
// int swap(bb_player* players, bb_player a, bb_player b, int loc);

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

    sort(players, count);

    tmp = players;
    while (tmp != NULL) {
        printf("%s %d %d\n", tmp->name, tmp->number, tmp->year);
        tmp = tmp->next;
    }

    while (players != NULL) {
        bb_player *tmp = players;
        players = players->next;
        free(tmp);
    }

    fclose(fr);
    return 0;
}

//Use MergeSort
int sort(bb_player *players, int count) {
    if (count <= 1) return 0;
    int current = 0;
    int middle = count/2;
    
    bb_player *first = players;
    bb_player *tmp1;
    while (current <= middle) {
        tmp1 = players; //check line
        players = players->next;
        current++;
    }
    sort(first, current-1);
    merge(first, count);

    bb_player *second = players;
    bb_player *tmp2;
    while (current < count) {
        tmp2 = players;
        players = players->next;
    }
    sort(second, middle);
    merge(second, count);
}

int merge (bb_player *players, int count) {
    if (count == 1) return 0;
    
    while (players->next != NULL) {
        if (players->next->next->avg_points > players->next->avg_points) {
            bb_player *temp = players->next;
            players->next = players->next->next;
            players->next->next = temp;
        }
         if (players->next->next->avg_points == players->next->avg_points) {
             if (strncmp(players->next->next->name, players->next->name, 80) < 0) {
                 bb_player *temp = players->next;
                players->next = players->next->next;
                players->next->next = temp;
             }
         }
        players = players->next;
    }

    return 0;
}