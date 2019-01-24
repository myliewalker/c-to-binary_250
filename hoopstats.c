#include <stdio.h>
#include <stdlib.h>

typedef struct player {
    char name[80];
    int number;
    float avg_points;
    int year;
} bb_player;

int sort(bb_player* players, bb_player low, bb_player high, int start, int remaining);
int swap(bb_player* players, bb_player a, bb_player b, int loc);

int main() {
    bb_player* players;
    int count = 0;
    
    FILE *file;
    file = fopen ("./HoopsStats statsfile.txt", "r");

    char str[99];
    while(fscanf(file, "%s", str) != "DONE")
    {
        players = (char*)malloc(1*__SIZEOF_INT__);
        sscanf (file, "%s", &players[count].name);
        sscanf(file, "%d", &players[count].number);
        sscanf(file, "%f", &players[count].avg_points);
        sscanf(file, "%d", &players[count].year);
        players++;
        count++;
    }
    fclose(file);

    sort(players, players[0], players[1], 0, count-1);

    for (int i = 0; i < count; i++) {
        printf("%s %d %d\n", players[i].name, players[i].number, players[i].year);
    }
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

    sort(players, players[start+1], players[start+2], remaining-1);
    return 0;
}

int swap(bb_player* players, bb_player a, bb_player b, int loc) {
    bb_player temp;
    temp.name = a.name;
    temp.number = a.number;
    temp.avg_points = a.avg_points;
    temp.year = a.year;

    players[loc] = players[loc+1];
    players[loc+1] = temp;

    return 0;
}