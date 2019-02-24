/* -----------------------------------------------------------------------
 * Unit Test for Adventurer Card
 *GOALS:
*	1. Current player ends up with 2 Treasure cards
*	2. Discard pile should increase
*	3. Hand should increase by 2
*	4. Played should increase by 1
*	5. No state change occurs for other players.
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

int checkAdventurerCard(int p, struct gameState *post) {
	  struct gameState pre;
	  memcpy (&pre, post, sizeof(struct gameState));

	  int r, handPos, failureCount, op;

	  if (p == 0)
	  {
		  op = 1;
	  }
	  else op = 0;

	  failureCount = 0;
	//   printf ("Adventurer PRE: p %d HC %d DeC %d DiC %d Act %d\n",
	//  	  p, pre.handCount[p], pre.deckCount[p], pre.discardCount[p], pre.numActions);

	  	  handPos = floor(Random() * pre.handCount[p]);

	    //printf("About to run cardEffect.\n");
	    r = cardEffect (adventurer, 0, 0, 0, post, handPos, 0);

	//  printf ("Adventurer POST: p %d HC %d DeC %d DiC %d Act %d\n",
	//        p, post->handCount[p], post->deckCount[p], post->discardCount[p], post->numActions);


//No Errors in Playing the Card
	  if (assertTrue(r, 0) == 0)
	  {
#if NOISY_TEST
		 printf("cardEffect Failed.\n");
#endif
		 failureCount = 1;
	  }

//Should have 2 Treasure Cards
	  int postHandCount = post->handCount[p];
	  int preHandCount = pre.handCount[p];
	  for(int i = 0; i < postHandCount; i++) {
		  if(i < preHandCount)
		  {
			  if(assertTrue(post->hand[p][i], pre.hand[p][i]) == 0)
				  printf("Cards do not match.\n");
		  }
		  else
		  {
			  if(assertTrue(post->hand[p][i], copper) == 0 &&
					  assertTrue(post->hand[p][i], silver) == 0 &&
					  assertTrue(post->hand[p][i], gold) == 0){
#if NOISY_TEST
						  printf("New Card is Treasure Failed.\n");
#endif
						  failureCount = 1;
					  }
		  }
	  }

//Should have 2 new cards
	  postHandCount = post->handCount[p];
	  if(assertTrue(postHandCount, (pre.handCount[p] + 2)) == 0)
	  {
#if NOISY_TEST
		 printf("Number of Cards in Hand Failed.\n");
		 printf("Should be: %i, Actual: %i.\n", (pre.handCount[p] + 1), postHandCount);
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

//other player should not be effected
	  if(assertTrue(post->handCount[op], pre.handCount[op]) == 0 ||
			  assertTrue(post->deckCount[op], pre.deckCount[op]) == 0 ||
			  assertTrue(post->discardCount[op], pre.discardCount[op]) == 0)
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

  printf ("Testing Adventurer.\n");

  printf ("RANDOM TESTS.\n");

  SelectStream(2);
  PutSeed(3);

  for (n = 0; n < NUM_TESTS; n++) {
    for (i = 0; i < sizeof(struct gameState); i++) {
      ((char*)&G)[i] = floor(Random() * 256);
    }
    p = floor(Random() * 2);
    G.whoseTurn = p;
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

	  //need to have real cards!
      int j, randomCard;
	  for(j = 0; j < G.deckCount[p]; j++) {
		  randomCard = floor(Random() * 26);
		  G.deck[p][j] = randomCard;
	  }

	  for(j = 0; j < G.handCount[p]; j++) {
		  randomCard = floor(Random() * 26);
		  G.hand[p][j] = randomCard;
	  }

	  for(j = 0; j < G.discardCount[p]; j++) {
		  randomCard = floor(Random() * 26);
		  G.discard[p][j] = randomCard;
	  }

	  //make sure at least 2 in deck are Treasures
	  for(j = 0; j < 2; j++)
	  {
		  randomCard = floor(Random() * G.deckCount[p]);
		  G.deck[p][randomCard] = floor(Random() * 6) + 4;
	  }

#if PRINT_COUNTER
    printf("Current test #: %i.\n", n);
#endif

    failCount += checkAdventurerCard(p, &G);
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
