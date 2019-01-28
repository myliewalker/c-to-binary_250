#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct player {
    char name[80];
    int number;
    float avg_points;
    int year;
    struct player *next;
} bb_player;

FILE *fr;

int sort(bb_player* players, bb_player low, bb_player high, int start, int remaining);
int swap(bb_player* players, bb_player a, bb_player b, int loc);

int main(int num, char* args[]) {
    char* file_name = args[num-1];
    bb_player* players = NULL;
    bb_player* start = players;
    bb_player* tmp = NULL;
    int count = 0;
    char line[80];

    fr = fopen (file_name, "rt");
    if (fr == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    while(fgets(line, 80, fr) != NULL) {
        if (strncmp(line, "DONE\n", 80) == 0) break;
        //can we assume done will end with a new line??

        char temp_name[80];
        int temp_num;
        float temp_points;
        int temp_year;
        bb_player* p = (bb_player*)malloc(sizeof(bb_player));
        
        sscanf(line, "%s", p[0].name);
        fgets(line, 80, fr);
        sscanf(line, "%d", &temp_num);
        fgets(line, 80, fr);
        sscanf(line, "%f", &temp_points);
        fgets(line, 80, fr);
        sscanf(line, "%d", &temp_year);
       
        p[0].number = temp_num;
        p[0].avg_points = temp_points;
        p[0].year = temp_year;

        // printf("%s %d %f %d \n", p[0].name, temp_num, temp_points, temp_year);
        // players = p;
        // count++;
        // break;

        if(players == NULL) {
            players = p;
            tmp = p;
        }
        else {
            tmp->next = p;
            tmp = tmp->next;
        }
        count++;
    }

    // sort(players, players[0], players[1], 0, count-1);

    for (int i = 0; i < count; i++) {
        printf("%s %d %d\n", players[i].name, players[i].number, players[i].year);
    }
    // while (players != NULL) {
    //     printf(players.name, players.number, players.year);
    // }

    players = start;

    // free(players);
    while (players != NULL) {
        bb_player *tmp = players;
        players = players->next;
        free(tmp);
    }
    fclose(fr);
    return 0;
}

int sort(bb_player* players, bb_player low, bb_player high, int start, int remaining) {
    if (remaining == 0) return 0;

    if (low.avg_points == high.avg_points) {
        if (low.name > high.name) {
            swap(players, low, high, start);
        }
    }
    if (low.avg_points < high.avg_points) {
        swap(players, low, high, start);
    }

    sort(players, players[start+1], players[start+2], start+1, remaining-1);
    return 0;
}

int swap(bb_player* players, bb_player a, bb_player b, int loc) {
    bb_player temp;
    for (int i = 0; i < sizeof(a.name)/sizeof(a.name[0]); i++) {
        temp.name[i] = a.name[i];
    }
    temp.number = a.number;
    temp.avg_points = a.avg_points;
    temp.year = a.year;

    players[loc] = players[loc+1];
    players[loc+1] = temp;

    return 0;
}