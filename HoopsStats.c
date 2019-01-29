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
bb_player* getLast(bb_player *players);
bb_player* findMax(bb_player *players, bb_player *min, bb_player *max);

bb_player* players;

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
    
    bb_player *head = getFirst(players);
    bb_player *last = getLast(players);
    bb_player *tmp = head;
    int count = 1;

    while (count < total) {
        bb_player *current_max = findMax(players, last, tmp);
        bb_player *t = (bb_player*) malloc(sizeof(bb_player));

        strcpy(t->name, current_max->name);
        t->number = current_max->number;
        t->avg_points = current_max->avg_points;
        t->year = current_max->year;
        t->next = NULL;

        tmp->next = t;
        tmp = tmp->next;
        count++;
        
        bb_player *f = t;
        free(f);
    }
    // //ISSUE: leak - need to free space i malloced
    // while (players != NULL) {
    //     bb_player *tmp = players;
    //     players = players->next;
    //     free(tmp);
    // }
    return head;
}

bb_player* getFirst(bb_player *players) {
    bb_player *first = players;
    while (players != NULL) {
        if (players->avg_points > first->avg_points) {
            first = players;
        }
        if (players->avg_points == first->avg_points && strncmp(players->name, first->name, 80) < 0) {
            first = players;
        }
        players = players->next;
    }
    return first;
}

bb_player* getLast(bb_player *players) {
    bb_player *last = players;
    while (players != NULL) {
        if (players->avg_points < last->avg_points) {
            last = players;
        }
        if (players->avg_points == last->avg_points && strncmp(players->name, last->name, 80) > 0) {
            last = players;
        }
        players = players->next;
    }
    return last;
}

bb_player* findMax(bb_player *players, bb_player *min, bb_player *max) {
    bb_player *new_max = min;
    while (players != NULL) {
        if (players->next == NULL) {
            if (players->avg_points > max->avg_points || 
            players->avg_points == max->avg_points && strncmp(players->name, max->name, 80) == 0) 
                break;
        }
        if (players->avg_points > new_max->avg_points) {
            new_max = players;
        }
        else if (players->avg_points == new_max->avg_points && strncmp(players->name, new_max->name, 80) < 0) {
            new_max = players;
        }
        players = players->next;
    }
    return new_max;
}