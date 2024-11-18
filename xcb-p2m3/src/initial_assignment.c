#include "onecard.h"

Tran initial_assignment(Card *card_fetch, Card *card_discard, Player *player, Result result,Tran trans)
{
    int t1 = 0, t2 = 0;
    for (int i = 0; i < result.cards; i++)
    {
        for (int j = 0; j < result.players; j++)
        {
            player->card[i] = malloc(sizeof(Card));
            if (player->card[i] == NULL)
            {
                fprintf(stderr, "Memory allocation failed for player[%d]->card[%d]\n", j, i);
                exit(EXIT_FAILURE);
            }
            player->card[i]->rank = card_fetch[t1].rank;
            player->card[i]->suit = card_fetch[t1].suit;
            card_fetch[t1].rank = 0;
            card_fetch[t1].suit = 0;
            t1++;
            player=player->next;
        }
    }
    int mini = 0, minrank = 15, minsuit = 0;
    for (int i = 0; i < result.players; i++)
    {
        player->first->rank = card_fetch[t1].rank;
        player->first->suit = card_fetch[t1].suit;
        card_fetch[t1].rank = 0;
        card_fetch[t1].suit = 0;
        card_discard[t2].rank = player->first->rank;
        card_discard[t2].suit = player->first->suit;
        if ((player->first->rank < minrank) || ((player->first->rank == minrank) && (player->first->suit < minsuit)))
        {
            minrank = player->first->rank;
            minsuit = player->first->suit;
            mini = i;
        }
        t1++;
        t2++;
        player=player->next;
    }
    trans.t1=t1;
    trans.t2= t2;
    trans.mini = mini;
    printf("Dealing cards...\n");
    // sleep(2);
    for (int i = 0; i < result.players; i++)
    {
        sort(player);
        player=player->next;
    }
    if (result.demo_mode == 1)
    {
        for (int i = 0; i < result.players; i++)
        {
            printf("Player %d: ", i+1);
            cards_output(player,player->number);
            player=player->next;
        }
    }
    printf("\n");
    printf("Determining the playing order...\n");
    // sleep(2);
    for (int i = 0; i < result.players; i++)
    {
        printf("Player %d: ", i+1);
        card_output(player->first->suit, player->first->rank);
        printf("\n");
        free(player->first);
        player=player->next;
    }
    printf("The game will start with player %d\n\n", mini);
    return trans;
}

