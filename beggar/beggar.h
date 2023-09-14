#include <stdio.h>
#include <stdlib.h>
#include "shuffle.h"
#include "queue.h"

int beggar(int Nplayers, int *deck, int talkative);
int pick_up_pile(QUEUE **hand, QUEUE **centre);
int get_top_card(QUEUE *pile);
QUEUE *take_turn(QUEUE **player, QUEUE **centre);
int finished(QUEUE **players, int Nplayers);

