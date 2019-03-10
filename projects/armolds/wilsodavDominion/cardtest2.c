/* -----------------------------------------------------------------------
 * Unit Test for Adventurer Card
 *GOALS:
*	1. Current player ends up with 2 Treasure cards
*	2. Cards should come from own deck
*	3. Discard pile should increase
*	4. Hand should increase by 2
*	5. Played should increase by 1
*	6. No state change occurs for other players.
*	7. No state change should occur to the victory card piles and kingdom card piles OTHER THAN when Adventurer is gained.
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

// set PLAYS to determine how many times to test (1 or 2)
#define PLAYS 1


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
    int adventurerPos;
    int failure;
    int matches[3] = {0, 0, 0};
    int noMatch = 0;
    int cardIsTreasure = 0;
    int failureCount = 0;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G, copyG;
    printf ("TESTING Adventurer:\n");

        memset(&G, 23, sizeof(struct gameState));   // clear the game state
        r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
        if (r == 0) {
        	//test for each player in the game
        	for(i = 0; i < PLAYS; i++) {
        		currentPlayer = i;
        		if(currentPlayer == 0)
        		{
        			otherPlayer = 1;
        		}
        		else
        		{
        			otherPlayer = 0;
        		}

#if (NOISY_TEST == 1)
        		printf("-------------------------\n");
        		printf("Testing Player %d.\n", i);
#endif

        		//add adventurer to players hand
        		gainCard(adventurer, &G, 2, i);

#if (NOISY_TEST == 1)
        		printf("Added Adventurer to current hand. Hand Count = %d.\n", G.handCount[i]);
#endif

        		//copy entire game to compare to later
        		memcpy(&copyG, &G, sizeof(struct gameState));

        		//was supply pile decreased?
        		if(assertTrue(copyG.supplyCount[adventurer], G.supplyCount[adventurer]))
        		{
#if (NOISY_TEST == 1)
        			printf("Adventurer supply count decreased by 1. \n");
#endif
        		}
        		else
        		{
#if (NOISY_TEST == 1)
        			printf("Adventurer supply count did not decrease by 1. TEST FAILED %d %s\n", __LINE__, __FILE__);
#endif
        			failure = 1;
        			failureCount++;
        		}

        		//Find adventurer's position
        	    adventurerPos = -1;
        	    for (j = 0; j < numHandCards(&G); j++) {
        	    	if (handCard(j, &G) == adventurer)
        	    adventurerPos = j;
        	    }

        	    //Play adventurer
        	    int success = 0;
#if (NOISY_TEST == 1)
        	    printf("Playing Adventurer...\n");
#endif
        	    success = playCard(adventurerPos, 0, 0, 0, &G);
        		if (assertTrue(success, 0))
        		{
#if (NOISY_TEST == 1)
        			printf("Adventurer was played successfully.\n");
#endif
        		}
        			else
        			{
#if (NOISY_TEST == 1)
        			printf("Adventurer was NOT played successfully. TEST FAILED %d %s\n", __LINE__, __FILE__);
#endif
        			failure = 1;
        			failureCount++;
        			}

        		//adventurer should not be in hand (is now discarded to "played cards")
        	    adventurerPos = -1;
        	    for (j = 0; j < numHandCards(&G); j++) {
        	    	if (handCard(j, &G) == adventurer)
        	    adventurerPos = j;
        	    }
        	    if (assertTrue(adventurerPos, -1))
        	    {
#if (NOISY_TEST == 1)
        	    	printf("Adventurer is no longer in player's hand.\n");
#endif
        	    }
        	    	else
        	    	{
#if (NOISY_TEST == 1)
        	    	printf("Adventurer remains in player's hand. TEST FAILED %d, %s\n", __LINE__, __FILE__);
#endif
        	    	failure = 1;
        	    	failureCount++;
        	    	}

        		//should have 2 new cards in hard
        		shouldHaveCards = copyG.handCount[i] - 1 + 2;
#if (NOISY_TEST == 1)
        		printf("Player should have %d cards in their hand (original hand %d - Adventurer + 2 Treasure)\n", shouldHaveCards, copyG.handCount[i]);
#endif
        		if(assertTrue(G.handCount[i], shouldHaveCards))
        		{
#if (NOISY_TEST == 1)
        			printf("Player has %d cards in their hand. \n", G.handCount[i]);
#endif
        		}
        			else
        			{
#if (NOISY_TEST == 1)
        			printf("Player has %d cards in their hand. TEST FAILED %d %s \n", G.handCount[i], __LINE__, __FILE__);
#endif
        			failure = 1;
        			failureCount++;
        			}


        		//should have 1 new playedCard, card should be Adventurer
        		if(assertTrue(copyG.playedCardCount + 1, G.playedCardCount))
        		{
#if (NOISY_TEST == 1)
        			printf("Player has %d card(s) in their played card pile. \n", G.playedCardCount);
#endif
        		}
        		else
        		{
#if (NOISY_TEST == 1)
        			printf("Player has %d card(s) in their played card pile. TEST FAILED %d %s\n", G.playedCardCount, __LINE__, __FILE__);
#endif
        			failure = 1;
        			failureCount++;
        		}
        		for(j = 0; j < G.playedCardCount; j++)
        		{
        			if(G.playedCards[j]== adventurer)
        			{
#if (NOISY_TEST == 1)
        				printf("Played card is a Adventurer.\n");
#endif
        			}
        				else
						{
#if (NOISY_TEST == 1)
							printf("Played card was NOT a Adventurer. TEST FAILED %d %s\n", __LINE__, __FILE__);
#endif
							failure = 1;
							failureCount++;
						}
        		}

        		//should have less deck cards
        		if((G.deckCount[i] < copyG.deckCount[i]))
        		{
#if (NOISY_TEST == 1)
        			printf("Player has %d card(s) in their deck (used to have %d). \n", G.deckCount[i], copyG.deckCount[i]);
#endif
        		}
        		else
        		{
#if (NOISY_TEST == 1)
        			printf("Player has %d card(s) in their deck (should be less than %d). TEST FAILED %d %s\n", G.deckCount[i],
        					copyG.deckCount[i], __LINE__, __FILE__);
#endif
        			failure = 1;
        			failureCount++;
        		}

        		//find out what the new cards are (should be last 2)
        		cardIsTreasure = 1;
        		for(j = G.handCount[i] - 2; j < G.handCount[i]; j++)
        		{
        			if((assertTrue(G.hand[i][j], copper) == 0 && assertTrue(G.hand[i][j], silver) == 0 &&
        					assertTrue(G.hand[i][j], gold) == 0))
        			{
        				cardIsTreasure = 0;
        				failure = 1;
        				failureCount++;
        			}

        		}

#if (NOISY_TEST == 1)
        		if(cardIsTreasure == 1)
        		{
        			printf("Cards added were Treasure cards. \n");
        		}
        		else
        		{
        			printf("Cards added were NOT all Treasure cards. TEST FAILED %d %s\n", __LINE__, __FILE__);
        		}
#endif

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
#if (NOISY_TEST == 1)
        				printf("New Card %d does NOT come from original deck. TEST FAILED %d %s\n", G.hand[i][m], __LINE__, __FILE__);
#endif     
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
        		{
#if (NOISY_TEST == 1)
        			printf("Other player's state did not change. \n");
#endif
        		}
        			else
        		{
#if (NOISY_TEST == 1)
        			printf("Other player's state changed. TEST FAILED %d %s\n", __LINE__, __FILE__);
#endif
        			failure = 1;
        			failureCount++;
        		}

        		//did victory cards change?
        			//Estate, Duchy, Province
        		if(assertTrue(copyG.supplyCount[estate], G.supplyCount[estate]) &&
        			assertTrue(copyG.supplyCount[duchy], G.supplyCount[duchy]) &&
        			assertTrue(copyG.supplyCount[province], G.supplyCount[province]))
					{
#if (NOISY_TEST == 1)
        				printf("Supply Counts of all Victory Cards remained the same. \n");
#endif
					}
        		else
        		{
#if (NOISY_TEST == 1)
        			printf("Victory Card states were changed. TEST FAILED %d %s\n", __LINE__, __FILE__);
#endif
        		}

        		//did kingdom cards change?
        		noMatch = 0;
        		for(j = 0; j < 10; j++)
        		{
        			if(assertTrue(copyG.supplyCount[k[j]], G.supplyCount[k[j]]) == 0 &&
        					k[j] != adventurer)
        			{
#if (NOISY_TEST == 1)
        				printf("Card #%d supply count has changed. TEST FAILED %d %s\n", k[j], __LINE__, __FILE__);
#endif
        				failure = 1;
        				failureCount++;
        				noMatch = 1;
        			}
        		}

        		if(noMatch == 0)
        		{
#if (NOISY_TEST == 1)
        			printf("Supply Counts of all Kingdom Cards remained the same. \n");
#endif
        		}

        		endTurn(&G);
        	}

        }

        if(failure == 0)
        	printf("All tests passed!\n");
        else
        	printf("%d test(s) failed.\n", failureCount);

    return 0;
}
