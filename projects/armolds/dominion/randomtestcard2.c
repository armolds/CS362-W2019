/* -----------------------------------------------------------------------
 * Random Test for Council Room Card
 *ASSERT:
*	1. Current Player receives +4 card to hand
*	2. Current Player receives +1 buy
*	3. Other Player draws a card (+1 to hand)
*	4. Current Player deck -4 cards
*	5. Played card count increases by 1
* -----------------------------------------------------------------------*/


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <math.h>

#define DEBUG 0
#define NOISY_TEST 0
#define PRINT_COUNTER 0
#define NUM_TESTS 2000

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

int checkVillageCard(int p, struct gameState *post) {
	  struct gameState pre;
	  memcpy (&pre, post, sizeof(struct gameState));

	  int r, handPos, failureCount, op;

	  if (p == 0)
	  {
		  op = 1;
	  }
	  else op = 0;

	  failureCount = 0;
	//   printf ("Council Room PRE: p %d HC %d DeC %d DiC %d Act %d\n",
	//  	  p, pre.handCount[p], pre.deckCount[p], pre.discardCount[p], pre.numActions);

	    handPos = floor(Random() * pre.handCount[p]);

	    //printf("About to run cardEffect.\n");
	    r = cardEffect (council_room, 0, 0, 0, post, handPos, 0);

	//  printf ("Council Room POST: p %d HC %d DeC %d DiC %d Act %d\n",
	//        p, post->handCount[p], post->deckCount[p], post->discardCount[p], post->numActions);


//No Errors in Playing the Card
	  if (assertTrue(r, 0) == 0)
	  {
#if NOISY_TEST
		 printf("cardEffect Failed.\n");
#endif
		 failureCount = 1;
	  }

//Should have 1 more buy
	  if(assertTrue(post->numBuys, (pre.numBuys + 1)) == 0)
	  {
#if NOISY_TEST
		 printf("Number of Buys Failed.\n");
#endif
		 failureCount = 1;
	  }

//Should have 4 new card, but 1 card discarded, so same amount in hand
	  int postHandCount = post->handCount[p];
	  if(assertTrue(postHandCount, (pre.handCount[p] + 3)) == 0)
	  {
#if NOISY_TEST
		 printf("Number of Cards in Hand Failed.\n");
#endif
		 failureCount = 1;
	  }

//Should have 1 more played card
	  if(assertTrue(post->playedCardCount, (pre.playedCardCount + 1)) == 0)
	  {
#if NOISY_TEST
		 printf("Played Card Count Failed.\n");
#endif
		 failureCount = 1;
	  }

//Should have 4 cards less in deck
  	  if(assertTrue(post->deckCount[p], (pre.deckCount[p] - 4)) == 0)
  	  {
#if NOISY_TEST
  		 printf("Deck Card Count Failed.\n");
#endif
  		 failureCount = 1;
  	  }

//other player should have 1 new card
	  if(assertTrue(post->handCount[op], (pre.handCount[op] + 1)) == 0)
	  {
#if NOISY_TEST
		 printf("Other Player State Changed Failed.\n");
#endif
		 failureCount = 1;
	  }

	  return failureCount;
}

int main () {

  int i, n, p, p2, failCount;
  failCount = 0;
  //int k[10] = {adventurer, council_room, feast, gardens, mine,
	    //   remodel, smithy, village, baron, great_hall};

  struct gameState G;

  printf ("Testing Council Room.\n");

  printf ("RANDOM TESTS.\n");

  SelectStream(2);
  PutSeed(3);

  for (n = 0; n < NUM_TESTS; n++) {
    for (i = 0; i < sizeof(struct gameState); i++) {
      ((char*)&G)[i] = floor(Random() * 256);
    }
    p = floor(Random() * 2);
    G.whoseTurn = p;
    G.numPlayers = 2;
    //setting "sane" values for both players
    if(p == 0)
    {
    	p2 = 1;
    }
    else p2 = 0;
    G.deckCount[p] = floor(Random() * MAX_DECK);
    G.discardCount[p] = floor(Random() * MAX_DECK);
    G.handCount[p] = floor(Random() * MAX_HAND);
    G.deckCount[p2] = floor(Random() * MAX_DECK);
    G.discardCount[p2] = floor(Random() * MAX_DECK);
    G.handCount[p2] = floor(Random() * MAX_HAND);
    G.playedCardCount = floor(Random() * MAX_DECK); //was causing problems in discardCard without a good value

    //Both players need to have real cards because they will both draw
    int j, randomCard;
	  for(j = 0; j < G.deckCount[p]; j++) {
		  randomCard = floor(Random() * 26);
		  G.deck[p][j] = randomCard;
	  }
	  for(j = 0; j < G.deckCount[p2]; j++) {
		  randomCard = floor(Random() * 26);
		  G.deck[p2][j] = randomCard;
	  }

	  for(j = 0; j < G.handCount[p]; j++) {
		  randomCard = floor(Random() * 26);
		  G.hand[p][j] = randomCard;
	  }
	  for(j = 0; j < G.handCount[p2]; j++) {
		  randomCard = floor(Random() * 26);
		  G.hand[p2][j] = randomCard;
	  }

	  for(j = 0; j < G.discardCount[p]; j++) {
		  randomCard = floor(Random() * 26);
		  G.discard[p][j] = randomCard;
	  }
	  for(j = 0; j < G.discardCount[p2]; j++) {
		  randomCard = floor(Random() * 26);
		  G.discard[p2][j] = randomCard;
	  }

#if PRINT_COUNTER
    printf("Current test #: %i.\n", n);
#endif

    failCount += checkVillageCard(p, &G);
  }

if(failCount > 0)
{
  	  printf("%i test(s) failed out of %i.\n", failCount, NUM_TESTS);
}
else
{
	printf("All Tests Passed!");
}

  return 0;
}
