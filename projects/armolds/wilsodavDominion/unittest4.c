/* -----------------------------------------------------------------------
 * Unit Test for gainCard function
 *GOALS:
*Assumption: InitializeGame is working correctly and creates an original deck.
*Assumption: SupplyCount function works correctly
*	1. Card in game is chosen to be added to:
*		1a. Discard pile
*		1b. Player's Deck
*		1c. Player's Hand
*	2. Should decrease card from supply pile
*	3. If a supply pile is empty, return -1
*	4. If a card is not used in game, return -1
*	5. Other player's discard, deck, and hand should remain the same
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
	int i, j, m;
    int seed = 1000;
    int numPlayer = 2;
    int r;
    int cardToDraw = 0;
    int cardUsed = 0;
    int usedCards[3] = {0, 0, 0};
    //int originalDeck[MAX_DECK];
    //int originalHand[MAX_HAND];
    //int originalDiscard[MAX_DECK];
    int originalDeckCount, originalHandCount, originalDiscardCount = 0;
    int newDeckCount, newHandCount, newDiscardCount = 0;
    int otherDeckCount1, otherHandCount1, otherDiscardCount1;
    int supplyPileCount = 0;
    int currentPlayer, otherPlayer = 0;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
    printf ("TESTING gainCard():\n");
	srand(time(NULL));
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

        		//reset used cards for each player
        		for(m = 0; m < 3; m++)
        		{
        			usedCards[m] = 0;
        		}

        		//setting other players info for comparison
        		otherDeckCount1 = G.deckCount[otherPlayer];
        		otherHandCount1 = G.handCount[otherPlayer];
        		otherDiscardCount1 = G.discardCount[otherPlayer];

        		for(j = 0; j < 3; j++) {
        		//testing 3 *DIFFERENT* cards per player
        		do{
        		cardToDraw = k[rand() % 10];
        		cardUsed = hasBeenUsed(cardToDraw, usedCards);
        		}while(cardUsed == 1);
        		usedCards[j] = cardToDraw;
        		supplyPileCount = G.supplyCount[cardToDraw];
        		originalDeckCount = G.deckCount[i];
        		originalHandCount = G.handCount[i];
        		originalDiscardCount = G.discardCount[i];

        		//Save original Deck, Hand, and Discard to compare to later
        		for(m = 0; m < G.deckCount[i]; m++)
        		{
        		//	originalDeck[m] = G.deck[i][m];
        		}
        		for(m = 0; m < G.handCount[i]; m++)
        		{
        		//	originalHand[m] = G.hand[i][m];
        		}
        		for(m = 0; m < G.discardCount[i]; m++)
        		{
        		//	originalDiscard[m] = G.discard[i][m];
        		}

#if (NOISY_TEST == 1)
        		if(j == 0){
        		printf("Player %d's Starting Info:\n", i);
        		printf("Number of Cards in Deck: %d\n", originalDeckCount);
        		printf("Number of Cards in Hand: %d\n", originalHandCount);
        		printf("Number of Cards in Discard: %d\n", originalDiscardCount);
        		}

        		printf("Card to draw ID: %d\n", cardToDraw);
        		printf("Starting Supply Pile: %d\n", supplyPileCount);
        		printf("--------------------------------\n");

#endif
        		//Add to Player's Hand (Flag 2)
        		gainCard(cardToDraw, &G, 2, i);
        		newHandCount = G.handCount[i];

        		//new card in hand
        		assert(newHandCount > originalHandCount);
        		//supply count has decreased
        		assert(G.supplyCount[cardToDraw] < supplyPileCount);
        		supplyPileCount--; //for next test
        		//deck didn't change
        		assert(G.deckCount[i] == originalDeckCount);
        		//discard didn't change
        		assert(G.discardCount[i] == originalDiscardCount);

#if (NOISY_TEST == 1)
        		printf("	Added card ID %d to player's hand. \n", cardToDraw);
        		printf("	Player's hand increased to %d cards.\n", newHandCount);
        		printf("	Supply count of card is now: %d\n", G.supplyCount[cardToDraw]);
        		printf("	Deck count did not change.\n");
        		printf("	Discard count did not change.\n");
        		printf("--------------------------------\n");
#endif

        		//Add to Player's Deck (Flag 1)
        		gainCard(cardToDraw, &G, 1, i);
        		newDeckCount = G.deckCount[i];

        		//new card in deck
        		assert(newDeckCount > originalDeckCount);
        		//supply count has decreased
        		assert(G.supplyCount[cardToDraw] < supplyPileCount);
        		supplyPileCount--;
        		//hand didn't change
        		assert(G.handCount[i] == newHandCount);
        		//discard didn't change
        		assert(G.discardCount[i] == originalDiscardCount);

#if (NOISY_TEST == 1)
        		printf("	Added card ID %d to player's deck. \n", cardToDraw);
        		printf("	Player's deck increased to %d cards.\n", newHandCount);
        		printf("	Supply count of card is now: %d\n", G.supplyCount[cardToDraw]);
        		printf("	Hand count did not change.\n");
        		printf("	Discard count did not change.\n");
        		printf("--------------------------------\n");
#endif

        		//Add to Player's Discard (Flag 0)
        		gainCard(cardToDraw, &G, 0, i);
        		newDiscardCount = G.discardCount[i];

        		//new card in deck
        		assert(newDiscardCount > originalDiscardCount);
        		//supply count has decreased
        		assert(G.supplyCount[cardToDraw] < supplyPileCount);
        		supplyPileCount--; //for next test
        		//hand didn't change
        		assert(G.handCount[i] == newHandCount);
        		//deck didn't change
        		assert(G.deckCount[i] == newDeckCount);

#if (NOISY_TEST == 1)
        		printf("	Added card ID %d to player's deck. \n", cardToDraw);
        		printf("	Player's discard increased to %d cards.\n", newHandCount);
        		printf("	Supply count of card is now: %d\n", G.supplyCount[cardToDraw]);
        		printf("	Hand count did not change.\n");
        		printf("	Deck count did not change.\n");
        		printf("--------------------------------\n");
#endif

        		//Did the other player's info change?
        		assert(otherDeckCount1 == G.deckCount[otherPlayer]);
        		assert(otherHandCount1 == G.handCount[otherPlayer]);
        		assert(otherDiscardCount1 == G.discardCount[otherPlayer]);

#if (NOISY_TEST == 1)
        		printf("	Other Players Deck is the same.\n");
        		printf("	Other Players Hand is the same.\n");
        		printf("	Other Players Discard is the same.\n");
        		printf("--------------------------------\n");

#endif
        		}
#if (NOISY_TEST == 1)
        		printf("Player %d's Ending Info:\n", i);
        		printf("Number of Cards in Deck: %d\n", G.deckCount[i]);
        		printf("Number of Cards in Hand: %d\n", G.handCount[i]);
        		printf("Number of Cards in Discard: %d\n", G.discardCount[i]);
        		printf("Cards Tested: \n");
        		for(m = 0; m < 3; m++){
        			printf("%d\n", usedCards[m]);
        		}
        		printf("--------------------------------\n");
#endif
		endTurn(&G);
        	}

        	//Empty Supply Pile
        	supplyPileCount = 0;
        	supplyPileCount = G.supplyCount[7];
        	G.supplyCount[7] = 0;
        	//setting adventurer card supply count = 0
        	//try to add card to player 0's hand
        	int successfullyAdded = 0;
        	successfullyAdded = gainCard(7, &G, 2, 0);
        	assert(successfullyAdded == -1);

#if (NOISY_TEST == 1)
        	printf("Testing adding a card from an empty supply pile: \n");
        	printf("Original Supply Count of Adventurer: %d\n", supplyPileCount);
        	printf("Supply Count of Adventurer: %d\n", G.supplyCount[7]);
        	if(successfullyAdded == -1)
        	{
            	printf("Card was NOT successfully added.\n");
        	}
        	printf("--------------------------------\n");
#endif

        	//Card Not In Game
        	//trying to add ambassador to game, was not a kingdom card declared at the top
        	successfullyAdded = 0;
        	successfullyAdded = gainCard(20, &G, 1, 0);
        	assert(successfullyAdded == -1);
#if (NOISY_TEST == 1)
        	printf("Testing adding a card not included in game: \n");
        	printf("Trying to add ambassador...\n");
        	if(successfullyAdded == -1)
        	{
            	printf("Card was NOT successfully added.\n");
        	}
        	printf("--------------------------------\n");
#endif
	
        }

    printf("All tests passed!\n");

    return 0;
}
