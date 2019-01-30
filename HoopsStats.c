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
bb_player* getFirst(bb_player *players);
bb_player* seen(bb_player *original, bb_player *current_max);

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

    // printf("count is %d", count);
    players = sort(players, count);
    // players = bubble(players, count);

    tmp = players;
    while (tmp != NULL) {
        printf("%s %d %d\n", tmp->name, tmp->number, tmp->year);
        tmp = tmp->next;
    }

    //ISSUE: fix this
    // tmp = players;
    // while (tmp != NULL) {
    //     bb_player *t = tmp;
    //     tmp = tmp->next;
    //     free (t);
    // }

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

    bb_player *start = (bb_player*) malloc(sizeof(bb_player));
    bb_player *t = getFirst(players);
    strcpy(start->name, t->name);
    start->avg_points = t->avg_points;
    start->number = t->number;
    start->year = t->year;
    start->next = NULL;

    bb_player *tmp = start;
    bb_player *original = seen(players, start);

    int count = 1;

    while (count < total) {
        bb_player *current_max = getFirst(original);
        original = seen(original, current_max);

        bb_player *t = (bb_player*) malloc(sizeof(bb_player));

        strcpy(t->name, current_max->name);
        t->number = current_max->number;
        t->avg_points = current_max->avg_points;
        t->year = current_max->year;
        t->next = NULL;

        //ISSUE: next line modifies original and makes it only 2 elements
        tmp->next = t;
        tmp = tmp->next;
        count++;
    }
    return start;
}

bb_player* getFirst(bb_player *players) {
    bb_player *max = players;
    bb_player *tmp = players;
    while (tmp != NULL) {
        if (tmp->avg_points > max->avg_points) {
            max = tmp;
        }
        if (tmp->avg_points == max->avg_points && strcmp(tmp->name, max->name) < 0) {
                // printf("statement registered\n");
            max = tmp;
        }
        // printf("first max %s\n", max->name);
        tmp = tmp->next;
    }
    return max;
}

bb_player* seen(bb_player *original, bb_player *current_max) {
    bb_player *head = original;
    bb_player *tmp = head;
    while (tmp != NULL) {
        if (strcmp(tmp->name, current_max->name) == 0) {
            tmp->avg_points = -1;
        }
        tmp = tmp->next;
    }
    return head;
}