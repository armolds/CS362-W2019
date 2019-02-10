/* -----------------------------------------------------------------------
 * Unit Test for Steward Card
 *GOALS:
*	1.Current Player receives one of the following:
*		1a. +2 Cards to their hand
*			a. Cards should be from players own deck
*			b. Hand count should increase
*		1b. +2 Coins to current turn
*			a. Coin count should increase for correct player
*			b. Hand counts should stay the same
*		1c. Trash 2 cards from hand
*			a. Cards trashed should come from own hand
*			b. Trashed card count should increase
*	2. Steward should move to played cards pile
*	3. No state change occurs for other players.
*	4. No state change should occur to the victory card piles and kingdom card piles OTHER THAN when Adventurer is gained.
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
	int i, j, m, n;
    int seed = 1000;
    int numPlayer = 2;
    int otherPlayer = 1;
    int r;
    int stewardPos;
    int failure;
    int failureCount = 0;
    int flag = 0;
    int matches[3] = {0, 0, 0};
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, steward};
    struct gameState G, copyG;
    printf ("TESTING Steward:\n");

        memset(&G, 23, sizeof(struct gameState));   // clear the game state
        r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
        if (r == 0) {
        	//test for each option of steward
        	for(m = 1; m < 4; m++) {
        		i = 0;
#if (NOISY_TEST == 1)
        		printf("-------------------------\n");
        		printf("Testing Steward Option %d.\n", m);
#endif

        		//add steward to players hand
        		gainCard(steward, &G, 2, i);

#if (NOISY_TEST == 1)
        		printf("Added Steward to current hand. Hand Count = %d.\n", G.handCount[i]);
#endif

        		//copy entire game to compare to later
        		memcpy(&copyG, &G, sizeof(struct gameState));

        		//was supply pile decreased?
        		if(assertTrue(copyG.supplyCount[steward], G.supplyCount[steward]))
        		{
#if (NOISY_TEST == 1)
        			printf("Steward supply count decreased by 1. \n");
#endif
        		}
        		else
        		{
#if (NOISY_TEST == 1)
        			printf("Steward supply count did not decrease by 1. TEST FAILED %d %s\n", __LINE__, __FILE__);
#endif
        			failure = 1;
        			failureCount++;
        		}

        		//Find steward's position
        	    stewardPos = -1;
        	    for (j = 0; j < numHandCards(&G); j++) {
        	    	if (handCard(j, &G) == steward)
        	    stewardPos = j;
        	    }

        	    //Play steward
        	    int success = 0;
#if (NOISY_TEST == 1)
        	    printf("Playing Steward...\n");
#endif
        	    success = playCard(stewardPos, m, 1, 2, &G);
        		if (assertTrue(success, 0))
        		{
#if (NOISY_TEST == 1)
        			printf("Steward was played successfully.\n");
#endif
        		}
        			else
        			{
#if (NOISY_TEST == 1)
        			printf("Steward was NOT played successfully. TEST FAILED %d %s\n", __LINE__, __FILE__);
#endif
        			failure = 1;
        			failureCount++;
        			}

        		//steward should not be in hand (is now discarded to "played cards")
        	    stewardPos = -1;
        	    for (j = 0; j < numHandCards(&G); j++) {
        	    	if (handCard(j, &G) == steward)
        	    stewardPos = j;
        	    }
        	    if (assertTrue(stewardPos, -1))
        	    {
#if (NOISY_TEST == 1)
        	    	printf("Steward is no longer in player's hand.\n");
#endif
        	    	//check to make sure it's in Played pile
        	    	for(j = 0; j < G.playedCardCount; j++)
        	    	{
        	    		if(G.playedCards[j] == steward)
        	    		{
#if (NOISY_TEST == 1)
        	    			printf("Steward is in played card pile.\n");
#endif
        	    			flag = 1;
        	    		}
        	    	}

        	    	if(flag == 0)
        	    	{
#if (NOISY_TEST == 1)
        	    		printf("Steward is not in played card pile. TEST FAILED %d, %s\n", __LINE__, __FILE__);
#endif
        	    	failure = 1;
        	    	failureCount++;
        	    	}
        	    }
        	    	else
        	    	{
#if (NOISY_TEST == 1)
        	    	printf("Steward remains in player's hand. TEST FAILED %d, %s\n", __LINE__, __FILE__);
#endif
        	    	failure = 1;
        	    	failureCount++;
        	    	}
        	    flag = 0;

        	    //if m == 1 then +2 Cards
        	    if(m == 1)
        	    {
        	    	//does player have 2 more cards? (original hand count - steward + 2)
        	    	if(assertTrue(copyG.handCount[i] + 1, G.handCount[i]))
        	    	{
#if (NOISY_TEST == 1)
        	    		printf("Player drew 2 cards successfully.\n");
#endif
        	    	}
        	    	else
        	    	{
#if (NOISY_TEST == 1)
        	    		printf("Player DID NOT draw 2 cards successfully. TEST FAILED %d, %s\n", __LINE__, __FILE__);
#endif
        	    	}


        	    	//were they from player's original deck?
        	    	flag = 0;
        			for(j = 0; j < 3; j++)
        			{
        				matches[j] = 0;
        			}

        		for(n = (copyG.handCount[i] - 1); n < G.handCount[i]; n++)
        		{
        			for(j = 0; j < copyG.deckCount[i]; j++)
        			{
        				if(G.hand[i][n] == copyG.deck[i][j])
        					matches[n] = 1;
        			}
        			if(assertTrue(matches[n], 0))
        			{
#if (NOISY_TEST == 1)
        				printf("New Card %d does NOT come from original deck. TEST FAILED %d %s\n", G.hand[i][n], __LINE__, __FILE__);
#endif
        				failure = 1;
        				flag = 1;
        			}
        		}

#if (NOISY_TEST == 1)
        		if(flag == 0)
        		{
        			printf("New cards come from original deck.\n");
        		}
#endif

        	    }


        	    //if m == 2 then +2 Coins
        	    if (m == 2)
        	    {
        	    	flag = 0;

        	    	//Should have 2 new coins
        	    	if(assertTrue(copyG.coins + 2, G.coins))
        	    	{
#if (NOISY_TEST == 1)
        	    		printf("Player gained 2 coins.\n");
#endif
        	    	}
        	    	else
        	    	{
#if (NOISY_TEST == 1)
        	    		printf("Player DID NOT gain 2 coins. Has %d coins (should be %d). TEST FAILED %d %s\n", G.coins, copyG.coins + 2, __LINE__, __FILE__);
#endif
        	    		failure = 1;
        	    		failureCount++;
        	    	}


        	    	//Compare all counts (hand, deck, discard, trash)
        	    	//HAND COUNT
        	    	if(assertTrue(copyG.handCount[i] - 1, G.handCount[i]))
        	    	{
#if (NOISY_TEST == 1)
        	    		printf("Hand count decreased by 1 (Steward).\n");
#endif
        	    	}
        	    	else
        	    	{
#if (NOISY_TEST == 1)
        	    			printf("Hand count did not decrease or decreased incorrectly. TEST FAILED %d %s\n", __LINE__, __FILE__);
#endif
        	    		failure = 1;
        	    		failureCount++;
        	    	}

        	    	//DECK COUNT
        	    	if(assertTrue(copyG.deckCount[i], G.deckCount[i]))
        	    	{
#if (NOISY_TEST == 1)
        	    		printf("Deck count stayed the same.\n");
#endif
        	    	}
        	    	else
        	    	{
#if (NOISY_TEST == 1)
        	    			printf("Deck count DID NOT stay the same. TEST FAILED %d %s\n", __LINE__, __FILE__);
#endif
        	    		failure = 1;
        	    		failureCount++;
        	    	}

        	    	//DISCARD COUNT
        	    	if(assertTrue(copyG.discardCount[i], G.discardCount[i]))
        	    	{
#if (NOISY_TEST == 1)
        	    		printf("Discard count stayed the same.\n");
#endif
        	    	}
        	    	else
        	    	{
#if (NOISY_TEST == 1)
        	    			printf("Discard count DID NOT stay the same. TEST FAILED %d %s\n", __LINE__, __FILE__);
#endif
        	    		failure = 1;
        	    		failureCount++;
        	    	}

        	    }

        	    //if m == 3 then Trash 2 cards
        	    if (m == 3)
        	    {
        	    	//cards removed from hand
        	    	if(assertTrue(copyG.handCount[i] - 3, G.handCount[i]))
        	    	{
#if (NOISY_TEST == 1)
        	    		printf("2 Cards + Steward were removed from hand. \n");
#endif
        	    	}
        	    	else
        	    	{
#if (NOISY_TEST == 1)
        	    		printf("Cards were not removed from hand. TEST FAILED %d %s\n", __LINE__, __FILE__);
#endif
        	    		failure = 1;
        	    		failureCount++;
        	    	}


        	    	//Discard Count
        	    	if(assertTrue(copyG.discardCount[i] + 3, G.discardCount[i]))
        	    	{
#if (NOISY_TEST == 1)
        	    		printf("2 Cards + Steward were added to discard. \n");
#endif
        	    	}
        	    	else
        	    	{
#if (NOISY_TEST == 1)
        	    		printf("2 Cards + Steward were NOT added to discard. TEST FAILED %d %s\n", __LINE__, __FILE__);
#endif
        	    		failure = 1;
        	    		failureCount++;
        	    	}

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

        	endTurn(&G); //end player 0's turn
        	endTurn(&G); //end player 1's turn (back to player 0 to use same code again)
        	}
        }

        if(failure == 0)
        	printf("All tests passed!\n");
        else
        	printf("%d test(s) failed.\n", failureCount);

    return 0;
}
