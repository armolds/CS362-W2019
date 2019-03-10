/* -----------------------------------------------------------------------
 * Unit Test for getCost function
 *GOALS:
 *Assumption: InitializeGame is working correctly and creates an original deck.
 *	1. getCost() should return correct cost of a specific card
 *	2. Should test for 5 different cards
 *	3. If test is run multiple times, different order should be tested
 * -----------------------------------------------------------------------
 */

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


int hasBeenUsed(int cardNum, int usedCards[])
{
	for(int i = 0; i < 5; i++) {
		if (cardNum == usedCards[i])
		{
			return 1;
		}
	}

	return 0;
}


int main() {
    int i;
    int seed = 1000;
    int numPlayer = 2;
    int cost = 0;
    int costShouldBe = 0;
    int cardNum = 0;
    int used = 0;
    int usedCards[5] = {0, 0, 0, 0, 0};
    int r;
    char* card;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
    srand(time(NULL));
    printf ("TESTING getCost():\n");

        memset(&G, 23, sizeof(struct gameState));   // clear the game state
        r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
        if (r == 0) {

        	for(i = 0; i < 5; i++) {

        		do{
        		cardNum = rand() % 10;
        		used = hasBeenUsed(cardNum, usedCards);
        		}while(used == 1);

        		usedCards[i] = cardNum;


#if (NOISY_TEST == 1)
        		switch(k[cardNum])
        		    {
        			case adventurer:
        			  card = "adventurer";
        		      costShouldBe = 6;
        		      break;
        		    case council_room:
        		    	card = "council room";
        		    	costShouldBe = 5;
        		    	break;
        		    case feast:
        		      card = "feast";
        		      costShouldBe = 4;
        		      break;
        		    case gardens:
        		    	card = "gardens";
        		    	costShouldBe = 4;
        		    	break;
        		    case mine:
        		    	card = "mine";
        		    	costShouldBe = 5;
        		    	break;
        		    case remodel:
        		    	card = "remodel";
        		    	costShouldBe = 4;
        		    	break;
        		    case smithy:
        		    	card = "smithy";
        		    	costShouldBe = 4;
        		    	break;
        		    case village:
        		    	card = "village";
        		    	costShouldBe = 3;
        		    	break;
        		    case baron:
        		    	card = "baron";
        		    	costShouldBe = 4;
        		    	break;
        		    case great_hall:
        		    	card = "great_hall";
        		    	costShouldBe = 3;
        		    	break;
        		    }
                printf("Card %s - Cost Should Be = %d\n", card, costShouldBe);
#endif

        		cost = getCost(k[cardNum]);

#if (NOISY_TEST == 1)
        		printf("Cost returned by function: %d\n", cost);
#endif
        		assert(cost == costShouldBe);
        	}

        	}

    printf("All tests passed!\n");

    return 0;
}
