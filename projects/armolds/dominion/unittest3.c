/* -----------------------------------------------------------------------
 * Unit Test for shuffle function
 *GOALS:
*Assumption: InitializeGame is working correctly and creates an original deck.
*	1. Player's cards should be in a different order than original order
*		1a) Found that first shuffle does not necessarily change the order,
*			instead testing for how many times it takes to get to a new order
*	2. Deck Count should not change
*	3. Other Player's cards should not be changed
* -----------------------------------------------------------------------*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <time.h>
#include <stdlib.h>

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

int main() {
    int i, j, m;
    int currentPlayer, otherPlayer;
    int seed = 1000;
    int numPlayer = 2;
    int orderChanged, otherPlayerDifferent = 0;
    int r;
	int originalDeckCount, shuffledDeckCount = 0;
	int otherDeckCount, shuffledOtherDeckCount = 0;
	int originalCardOrder[MAX_DECK];
	int changedCardOrder[MAX_DECK];
	int originalOtherPlayerDeck[MAX_DECK];
	int changedOtherPlayerDeck[MAX_DECK];
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
    srand(time(NULL));
    printf ("TESTING shuffle():\n");

        memset(&G, 23, sizeof(struct gameState));   // clear the game state
        r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
        if (r == 0) {
        	//test for each player in the game
        	for(i = 0; i < numPlayer; i++) {
        		currentPlayer = i;
        			if(currentPlayer == 0)
        				otherPlayer = 1;
        				else
        				otherPlayer = 0;
#if (NOISY_TEST == 1)
        			printf("TESTING PLAYER %d\n", currentPlayer);
#endif
        		//Save Original Deck
        		originalDeckCount = 0;
        		originalDeckCount = G.deckCount[i];

        		for(j = 0; j < originalDeckCount; j++)
        		{
        			originalCardOrder[j] = G.deck[i][j];
        		}

        		//Save Other Player's Deck
        		otherDeckCount = 0;
        		otherDeckCount = G.deckCount[otherPlayer];
        		for(j = 0; j < otherDeckCount; j++)
        		{
        			originalOtherPlayerDeck[j] = G.deck[otherPlayer][j];
        		}

#if (NOISY_TEST == 1)
        		//Print starting deck count and starting card IDs
                printf("Original Deck Count = %d\n", originalDeckCount);
        		for(j = 0; j < originalDeckCount; j++)
        		{
        			printf("Card #%d ID: %d\n", j, originalCardOrder[j]);
        		}
#endif

        		int timesShuffled = 0;
        		//See how many times we need to shuffle before deck changes, found that original doesn't necessarily change deck
        		do{
        		shuffle(i, &G);
        		timesShuffled++;

                //make sure deck count hasn't changed
        		shuffledDeckCount = 0;
        		shuffledDeckCount = G.deckCount[i];

        		assert(shuffledDeckCount == originalDeckCount);

        		//see if any card is in a different order
        		orderChanged = 0;
        		for(j = 0; j < shuffledDeckCount; j++)
        		{
        			changedCardOrder[j] = G.deck[i][j];
        		}

        		for(m = 0; m < originalDeckCount; m++)
        		{
        				if (originalCardOrder[m] != changedCardOrder[m])
        				{
        					orderChanged = 1;
        				}
        		}

        		//compare other player's deck count to original to make sure it's the same
        		shuffledOtherDeckCount = 0;
        		shuffledOtherDeckCount = G.deckCount[otherPlayer];
        		assert(shuffledOtherDeckCount == otherDeckCount);

        		for(j = 0; j < shuffledOtherDeckCount; j++)
        		{
        			changedOtherPlayerDeck[j] = G.deck[otherPlayer][j];
        		}

        		//make sure that other player's deck is the same
        		otherPlayerDifferent = 0;
        		for(m = 0; m < shuffledOtherDeckCount; m++)
        		{
    				if (originalOtherPlayerDeck[m] != changedOtherPlayerDeck[m])
    				{
    					otherPlayerDifferent = 1;
    				}
        		}

        		assert(otherPlayerDifferent == 0);

        		}while(orderChanged == 0);

#if (NOISY_TEST == 1)
                printf("Cards have been shuffled %d times to find a new order.\n", timesShuffled);
                printf("Original Deck Count = %d, Shuffled Deck Count = %d.\n", originalDeckCount, shuffledDeckCount);
        		printf("New Card Order:\n");
        		for(j = 0; j < shuffledDeckCount; j++)
        		{
        			printf("Card #%d ID: %d\n", j, changedCardOrder[j]);
        		}
        		printf("Other player's cards stayed the same.\n");
        		printf("****************************************\n");
#endif
        		assert(orderChanged == 1);

        	}

        	}

    printf("All tests passed!\n");

    return 0;
}
