#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct player {
    char name[80];
    int number;
    float avg_points;
    int year;
} bb_player;

struct Node {
    bb_player info;
    struct Node *next;
};

FILE *fr;

int sort(bb_player* players, bb_player low, bb_player high, int start, int remaining);
int swap(bb_player* players, bb_player a, bb_player b, int loc);

int main(int num, char* args[]) {
    char* file_name = args[num-1];
    struct Node first;
    struct Node last = first;
    int count = 0;
    char line[80];

    fr = fopen (file_name, "rt");
    if (fr == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    while(fgets(line, 80, fr) != NULL) {
        if (strncmp(line, "DONE", 80) == 0 || strncmp(line, "DONE\n", 80) == 0) break;
        char temp_name[80];
        int temp_num;
        float temp_points;
        int temp_year;
        bb_player p;
        
        sscanf(line, "%s", p.name);
        fgets(line, 80, fr);
        sscanf(line, "%d", &temp_num);
        fgets(line, 80, fr);
        sscanf(line, "%f", &temp_points);
        fgets(line, 80, fr);
        sscanf(line, "%d", &temp_year);
       
        p.number = temp_num;
        p.avg_points = temp_points;
        p.year = temp_year;

        printf("%s %d %f %d \n", p.name, temp_num, temp_points, temp_year);

        struct Node t;
        t.info = p;
        if(count == 0) {
            first.info = p;
            last.info = p;
        }
        else {
            // last.next = (struct Node)malloc(sizeof(struct Node));
            (*last.next).info = p;
            last = *last.next;
        }
        // printf("%s %d %f %d \n", last.name, last.number, last.avg_points, last.year);
        // players[count] = p;
        count++;
    }

    // sort(players, players[0], players[1], 0, count-1);

    last = first;
    while (! isempty(last)) {
        printf("%s %d %d", last.info.name, last.info.number, last.info.year);
        last = *last.next;
    }

    // players = first;

    // free(players);
    // while (players != NULL) {
    //     bb_player *last = players;
    //     players = players->next;
    //     free(last);
    // }
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