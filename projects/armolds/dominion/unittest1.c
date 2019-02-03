/* -----------------------------------------------------------------------
 * Unit Test for numHandCards function
 *GOALS:
 *Assumption: InitializeGame is working correctly and creates an original deck.
 *	1. numHandCards should return the correct amount of cards in a player's hand
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

int main() {
    int i;
    int seed = 1000;
    int numPlayer = 2;
    int p, r, handCount;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
    int maxHandCount = 5;
    // arrays of all coppers, silvers, and golds
    int coppers[MAX_HAND];
    int handResult = -1;
    for (i = 0; i < MAX_HAND; i++)
    {
        coppers[i] = copper;
    }

    printf ("TESTING numHandCards():\n");
    //test for each player
    for (p = 0; p < numPlayer; p++)
    {
        memset(&G, 23, sizeof(struct gameState));   // clear the game state
        r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
        if (r == 0) {
        	G.whoseTurn = p; //set players turn
        for (handCount = 1; handCount <= maxHandCount; handCount++)
        {

#if (NOISY_TEST == 1)
                printf("Test player %d with %d card(s) in their hand\n", p, handCount);
#endif
                G.handCount[p] = handCount;                 // set the number of cards on hand
                memcpy(G.hand[p], coppers, sizeof(int) * handCount); // set all the cards to copper, doesn't matter which cards
                handResult = numHandCards(&G);
#if (NOISY_TEST == 1)
                printf("G.handCount = %d, expected = %d\n", G.handCount[p], handCount);
#endif
                assert(handResult == handCount); // check if the number of cards is correct

        }
        }
    }

    printf("All tests passed!\n");

    return 0;
}
