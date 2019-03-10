/* -----------------------------------------------------------------------
 * Unit Test for Village Card
 *GOALS:
*	1. Current Player receives +1 card and +2 actions
*	2. Village should move to played cards pile
*	3. Deck should decrease by 1
*	4. Hand count should stay the same (+1 card - 1 village)
*	5. No state change occurs for other players.
*	6. No state change should occur to the victory card piles and kingdom card piles OTHER THAN when Village is gained.
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
#define PLAYS 2


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
	int i, j;
    int seed = 1000;
    int numPlayer = 2;
    int currentPlayer = 0;
    int otherPlayer = 1;
    int r;
    int villagePos;
    int failure;
    int failureCount = 0;
    int flag = 0;
    int handFailure = 0;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, steward};
    struct gameState G, copyG;
    printf ("TESTING Village:\n");

        memset(&G, 23, sizeof(struct gameState));   // clear the game state
        r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
        if (r == 0) {
        	//test for each option of steward
        	for(i = 0; i < PLAYS; i++) {
        		handFailure = 0;
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

        		//add village to players hand
        		gainCard(village, &G, 2, i);

#if (NOISY_TEST == 1)
        		printf("Added Village to current hand. Hand Count = %d.\n", G.handCount[i]);
#endif

        		//copy entire game to compare to later
        		memcpy(&copyG, &G, sizeof(struct gameState));

        		//was supply pile decreased?
        		if(assertTrue(copyG.supplyCount[village], G.supplyCount[village]))
        		{
#if (NOISY_TEST == 1)
        			printf("Village supply count decreased by 1. \n");
#endif
        		}
        		else
        		{
#if (NOISY_TEST == 1)
        			printf("Village supply count did not decrease by 1. TEST FAILED %d %s\n", __LINE__, __FILE__);
#endif
        			failure = 1;
        			failureCount++;
        		}

        		//Find village's position
        	    villagePos = -1;
        	    for (j = 0; j < numHandCards(&G); j++) {
        	    	if (handCard(j, &G) == village)
        	    villagePos = j;
        	    }

        	    //Play steward
        	    int success = 0;
#if (NOISY_TEST == 1)
        	    printf("Playing Village...\n");
#endif
        	    success = playCard(villagePos, 0, 0, 0, &G);
        		if (assertTrue(success, 0))
        		{
#if (NOISY_TEST == 1)
        			printf("Village was played successfully.\n");
#endif
        		}
        			else
        			{
#if (NOISY_TEST == 1)
        			printf("Village was NOT played successfully. TEST FAILED %d %s\n", __LINE__, __FILE__);
#endif
        			failure = 1;
        			failureCount++;
        			}

        		//village should not be in hand (is now discarded to "played cards")
        	    villagePos = -1;
        	    for (j = 0; j < numHandCards(&G); j++) {
        	    	if (handCard(j, &G) == village)
        	    villagePos = j;
        	    }
        	    if (assertTrue(villagePos, -1))
        	    {
#if (NOISY_TEST == 1)
        	    	printf("Village is no longer in player's hand.\n");
#endif
        	    	//check to make sure it's in Played pile
        	    	for(j = 0; j < G.playedCardCount; j++)
        	    	{
        	    		if(G.playedCards[j] == village)
        	    		{
#if (NOISY_TEST == 1)
        	    			printf("Village is in played card pile.\n");
#endif
        	    			flag = 1;
        	    		}
        	    	}

        	    	if(flag == 0)
        	    	{
#if (NOISY_TEST == 1)
        	    		printf("Village is not in played card pile. TEST FAILED %d, %s\n", __LINE__, __FILE__);
#endif
        	    	failure = 1;
        	    	failureCount++;
        	    	}
        	    }
        	    	else
        	    	{
#if (NOISY_TEST == 1)
        	    	printf("Village remains in player's hand. TEST FAILED %d, %s\n", __LINE__, __FILE__);
#endif
        	    	failure = 1;
        	    	failureCount++;
        	    	handFailure = 1;
        	    	}
        	    flag = 0;

        	    //+1 Card
        	    if(assertTrue(copyG.handCount[i], G.handCount[i]) && (handFailure == 0))
        	    {
#if (NOISY_TEST == 1)
        	    	printf("Player received one new card. \n");
#endif
        	    }
        	    else
        	    {
#if (NOISY_TEST == 1)
        	    	if(handFailure == 0)
        	    	{
        	    	printf("Player has %d cards in hand. Should have %d. TEST FAILED %d, %s\n", G.handCount[i], copyG.handCount[i], __LINE__, __FILE__);
        	    	}
        	    	else
        	    	{
        	    	printf("Player did NOT receive a new card.  Kept Village in hand. TEST FAILED %d, %s\n", __LINE__, __FILE__);
        	    	}
#endif
        	    	failure = 1;
        	    	failureCount++;
        	    }

        	    //+2 Actions
        	    if(assertTrue(copyG.numActions + 1, G.numActions))
        	    {
#if (NOISY_TEST == 1)
        	    	printf("Player has 2 more actions.\n");
#endif
        	    }
        	    else
        	    {
#if (NOISY_TEST == 1)
        	    	printf("Player has %d actions.  Should have 2. TEST FAILED %d, %s\n", G.numActions, __LINE__, __FILE__);
#endif
        	    	failure = 1;
        	    	failureCount++;
        	    }


    	    	//other player state the same
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

    	    	//victory cards the same
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

    	    	//kingdom cards the same
    		flag = 0;
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
    				flag = 1;
    			}
    		}

    		if(flag == 0)
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
