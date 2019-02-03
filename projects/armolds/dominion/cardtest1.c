/* -----------------------------------------------------------------------
 * Unit Test for Smithy Card
 *GOALS:
*	1. Current player receives exactly 3 cards.
*	2. 3 cards come from own deck.
*	3. No state change occurs for other players.
*	4. No state change should occur to the victory card piles and kingdom card piles OTHER THAN when Smithy is gained.
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

int assertTrue(int a, int b)
{
	if(a == b)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}


int main() {
	int i, j, m;
    int seed = 1000;
    int numPlayer = 2;
    int r;
    int shouldHaveCards = 0;
    int currentPlayer, otherPlayer = 0;
    int smithyPos;
    int failure;
    int matches[3] = {0, 0, 0};
    int noMatch = 0;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G, copyG;
    printf ("TESTING Smithy:\n");

        memset(&G, 23, sizeof(struct gameState));   // clear the game state
        r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
        if (r == 0) {
        	//test for each player in the game
        	for(i = 0; i < numPlayer; i++) {
        		currentPlayer = i;
        		if(currentPlayer == 0)
        		{
        			otherPlayer = 1;
        		}
        		else
        		{
        			otherPlayer = 0;
        		}
        		printf("-------------------------\n");
        		printf("Testing Player %d.\n", i);

        		//copy entire game to compare to later
        		memcpy(&copyG, &G, sizeof(struct gameState));


        		//add Smithy to players hand
        		gainCard(smithy, &G, 2, i);
        		printf("Added Smithy to current hand. Hand Count = %d.\n", G.handCount[i]);

        		//was supply pile decreased?
        		if(assertTrue(copyG.supplyCount[smithy] - 1, G.supplyCount[smithy]))
        		{
        			printf("Smithy supply count decreased by 1. \n");
        		}
        		else
        		{
        			printf("Smithy supply count did not decrease by 1. TEST FAILED %d %s\n", __LINE__, __FILE__);
        			failure = 1;
        		}

        		//Find smithy's position
        	    smithyPos = -1;
        	    for (j = 0; j < numHandCards(&G); j++) {
        	    	if (handCard(j, &G) == smithy)
        	    smithyPos = j;
        	    }

        	    //Play smithy
        	    int success = 0;
        	    printf("Playing Smithy...\n");
        		success = playCard(smithyPos, 0, 0, 0, &G);
        		if (assertTrue(success, 0))
        			printf("Smithy was played successfully.\n");
        		else
        			{
        			printf("Smithy was NOT played successfully. TEST FAILED %d %s\n", __LINE__, __FILE__);
        			failure = 1;
        			}

        		//smithy should not be in hand (is now discarded to "played cards")
        	    smithyPos = -1;
        	    for (j = 0; j < numHandCards(&G); j++) {
        	    	if (handCard(j, &G) == smithy)
        	    smithyPos = j;
        	    }
        	    if (assertTrue(smithyPos, -1))
        	    	printf("Smithy is no longer in player's hand.\n");
        	    else
        	    	{
        	    	printf("Smithy remains in player's hand. TEST FAILED %d, %s\n", __LINE__, __FILE__);
        	    	failure = 1;
        	    	}

        		//should have 3 new cards in hard
        		shouldHaveCards = copyG.handCount[i] - 1 + 3;
        		printf("Player should have %d cards in their hand (original hand - Smithy + 3)\n", shouldHaveCards);

        		if(assertTrue(G.handCount[i], shouldHaveCards))
        			printf("Player has %d cards in their hand. \n", G.handCount[i]);
        		else
        			{
        			printf("Player has %d cards in their hand. TEST FAILED %d %s \n", G.handCount[i], __LINE__, __FILE__);
        			failure = 1;
        			}


        		//should have 1 new playedCard, card should be Smithy
        		if(assertTrue(copyG.playedCardCount + 1, G.playedCardCount))
        			printf("Player has %d card(s) in their played card pile. \n", G.playedCardCount);
        		else
        		{
        			printf("Player has %d card(s) in their played card pile. TEST FAILED %d %s\n", G.playedCardCount, __LINE__, __FILE__);
        			failure = 1;
        		}
        		for(j = 0; j < G.playedCardCount; j++)
        		{
        			if(G.playedCards[j]== smithy)
        				printf("Played card is a Smithy.\n");
					else
						{
							printf("Played card was NOT a Smithy. TEST FAILED %d %s\n", __LINE__, __FILE__);
							failure = 1;
						}
        		}

        		//should have 3 less deck cards
        		if(assertTrue(copyG.deckCount[i] - 3, G.deckCount[i]))
        			printf("Player has %d card(s) in their deck. \n", G.deckCount[i]);
        		else
        		{
        			printf("Player has %d card(s) in their deck (should be %d). TEST FAILED %d %s\n", G.deckCount[i],
        					copyG.deckCount[i] - 3,__LINE__, __FILE__);
        			failure = 1;
        		}


        		//new cards come from own deck

        			//are new cards from original deck?
        				//resetting array for next check
        			for(j = 0; j < 3; j++)
        			{
        				matches[j] = 0;
        			}

        		for(m = (copyG.handCount[i] - 1); m < G.handCount[i]; m++)
        		{
        			for(j = 0; j < copyG.deckCount[i]; j++)
        			{
        				if(G.hand[i][m] == copyG.deck[i][j])
        					matches[m] = 1;
        			}
        			if(assertTrue(matches[m], 0))
        			{
        				printf("New Card %d does NOT come from original deck. TEST FAILED %d %s\n", G.hand[i][m], __LINE__, __FILE__);
        				failure = 1;
        				noMatch = 1;
        			}
        		}

        		if(assertTrue(noMatch, 0))
        			printf("All new cards came from original deck.\n");

        		//Did the other player's info change?
        		if (assertTrue(copyG.deckCount[otherPlayer], G.deckCount[otherPlayer]) &&
        		assertTrue(copyG.handCount[otherPlayer], G.handCount[otherPlayer]) &&
        		assertTrue(copyG.discardCount[otherPlayer], G.discardCount[otherPlayer]))
        			printf("Other player's state did not change. \n");
        		else
        		{
        			printf("Other player's state changed. TEST FAILED %d %s\n", __LINE__, __FILE__);
        			failure = 1;
        		}

        		//did victory cards change?
        			//Estate, Duchy, Province
        		if(assertTrue(copyG.supplyCount[estate], G.supplyCount[estate]) &&
        			assertTrue(copyG.supplyCount[duchy], G.supplyCount[duchy]) &&
        			assertTrue(copyG.supplyCount[province], G.supplyCount[province]))
					{
        				printf("Supply Counts of all Victory Cards remained the same. \n");
					}
        		else
        		{
        			printf("Victory Card states were changed. TEST FAILED %d %s\n", __LINE__, __FILE__);
        		}

        		//did kingdom cards change?
        		noMatch = 0;
        		for(j = 0; j < 10; j++)
        		{
        			if(assertTrue(copyG.supplyCount[k[j]], G.supplyCount[k[j]]) == 0 &&
        					k[j] != smithy)
        			{
        				printf("Card #%d supply count has changed. TEST FAILED %d %s\n", k[j], __LINE__, __FILE__);
        				failure = 1;
        				noMatch = 1;
        			}
        		}

        		if(noMatch == 0)
        		{
        			printf("Supply Counts of all Kingdom Cards remained the same. \n");
        		}

        		endTurn(&G);

        	}

        }

        if(failure == 0)
        	printf("All tests passed!\n");

    return 0;
}
