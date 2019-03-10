TESTING Adventurer:
-------------------------
Testing Player 0.
Added Adventurer to current hand. Hand Count = 6.
Adventurer supply count decreased by 1. 
Playing Adventurer...
Adventurer was played successfully.
Adventurer remains in player's hand. TEST FAILED 149, cardtest2.c
Player should have 7 cards in their hand (original hand 6 - Adventurer + 2 Treasure)
Player has 8 cards in their hand. TEST FAILED 169 cardtest2.c 
Player has 0 card(s) in their played card pile. TEST FAILED 186 cardtest2.c
Player has 3 card(s) in their deck (used to have 5). 
Cards added were Treasure cards. 
New Card 7 does NOT come from original deck. TEST FAILED 270 cardtest2.c
Other player's state did not change. 
Supply Counts of all Victory Cards remained the same. 
Supply Counts of all Kingdom Cards remained the same. 
3 test(s) failed.
-------------
 
File 'dominion.c'
Lines executed:30.69% of 567
Creating 'dominion.c.gcov'

-------------
 
Function 'updateCoins'
Lines executed:81.82% of 11

Function 'gainCard'
Lines executed:61.54% of 13

Function 'discardCard'
Lines executed:0.00% of 13

Function 'cardGreatHall'
Lines executed:0.00% of 6

Function 'cardVillage'
Lines executed:0.00% of 6

Function 'cardSmithy'
Lines executed:0.00% of 6

Function 'cardCouncilRoom'
Lines executed:0.00% of 10

Function 'cardAdventurer'
Lines executed:88.24% of 17

Function 'cardEffect'
Lines executed:4.29% of 210

Function 'getCost'
Lines executed:0.00% of 30

Function 'drawCard'
Lines executed:95.45% of 22

Function 'getWinners'
Lines executed:0.00% of 24

Function 'scoreFor'
Lines executed:0.00% of 24

Function 'isGameOver'
Lines executed:0.00% of 10

Function 'endTurn'
Lines executed:95.00% of 20

Function 'whoseTurn'
Lines executed:100.00% of 2

Function 'fullDeckCount'
Lines executed:0.00% of 9

Function 'supplyCount'
Lines executed:100.00% of 2

Function 'handCard'
Lines executed:100.00% of 3

Function 'numHandCards'
Lines executed:100.00% of 2

Function 'buyCard'
Lines executed:0.00% of 13

Function 'playCard'
Lines executed:71.43% of 14

Function 'shuffle'
Lines executed:100.00% of 16

Function 'initializeGame'
Lines executed:83.87% of 62

Function 'kingdomCards'
Lines executed:0.00% of 13

Function 'newGame'
Lines executed:0.00% of 3

Function 'compare'
Lines executed:100.00% of 6

File 'dominion.c'
Lines executed:30.69% of 567
Creating 'dominion.c.gcov'

-------------
 
File 'dominion.c'
Lines executed:30.69% of 567
Branches executed:30.46% of 417
Taken at least once:20.86% of 417
Calls executed:22.00% of 100
Creating 'dominion.c.gcov'

-------------
 
        -:    0:Source:dominion.c
        -:    0:Graph:dominion.gcno
        -:    0:Data:dominion.gcda
        -:    0:Runs:3
        -:    0:Programs:2
        -:    1:#include "dominion.h"
        -:    2:#include "dominion_helpers.h"
        -:    3:#include "rngs.h"
        -:    4:#include <stdio.h>
        -:    5:#include <math.h>
        -:    6:#include <stdlib.h>
        -:    7:
function compare called 71407 returned 100% blocks executed 100%
    71407:    8:int compare(const void* a, const void* b) {
    71407:    9:  if (*(int*)a > *(int*)b)
branch  0 taken 50% (fallthrough)
branch  1 taken 50%
    35701:   10:    return 1;
    35706:   11:  if (*(int*)a < *(int*)b)
branch  0 taken 44% (fallthrough)
branch  1 taken 56%
    15723:   12:    return -1;
    19983:   13:  return 0;
        -:   14:}
        -:   15:
function newGame called 0 returned 0% blocks executed 0%
    #####:   16:struct gameState* newGame() {
    #####:   17:  struct gameState* g = malloc(sizeof(struct gameState));
    #####:   18:  return g;
        -:   19:}
        -:   20:
function kingdomCards called 0 returned 0% blocks executed 0%
    #####:   21:int* kingdomCards(int k1, int k2, int k3, int k4, int k5, int k6, int k7,
        -:   22:		  int k8, int k9, int k10) {
    #####:   23:  int* k = malloc(10 * sizeof(int));
    #####:   24:  k[0] = k1;
    #####:   25:  k[1] = k2;
    #####:   26:  k[2] = k3;
    #####:   27:  k[3] = k4;
    #####:   28:  k[4] = k5;
    #####:   29:  k[5] = k6;
    #####:   30:  k[6] = k7;
    #####:   31:  k[7] = k8;
    #####:   32:  k[8] = k9;
    #####:   33:  k[9] = k10;
    #####:   34:  return k;
        -:   35:}
        -:   36:
function initializeGame called 2 returned 100% blocks executed 88%
        2:   37:int initializeGame(int numPlayers, int kingdomCards[10], int randomSeed,
        -:   38:		   struct gameState *state) {
        -:   39:
        -:   40:  int i;
        -:   41:  int j;
        -:   42:  int it;
        -:   43:  //set up random number generator
        2:   44:  SelectStream(1);
call    0 returned 100%
        2:   45:  PutSeed((long)randomSeed);
call    0 returned 100%
        -:   46:
        -:   47:  //check number of players
        2:   48:  if (numPlayers > MAX_PLAYERS || numPlayers < 2)
branch  0 taken 100% (fallthrough)
branch  1 taken 0%
branch  2 taken 0% (fallthrough)
branch  3 taken 100%
        -:   49:    {
    #####:   50:      return -1;
        -:   51:    }
        -:   52:
        -:   53:  //set number of players
        2:   54:  state->numPlayers = numPlayers;
        -:   55:
        -:   56:  //check selected kingdom cards are different
       22:   57:  for (i = 0; i < 10; i++)
branch  0 taken 91%
branch  1 taken 9% (fallthrough)
        -:   58:    {
      220:   59:      for (j = 0; j < 10; j++)
branch  0 taken 91%
branch  1 taken 9% (fallthrough)
        -:   60:        {
      200:   61:	  if (j != i && kingdomCards[j] == kingdomCards[i])
branch  0 taken 90% (fallthrough)
branch  1 taken 10%
branch  2 taken 0% (fallthrough)
branch  3 taken 100%
        -:   62:	    {
    #####:   63:	      return -1;
        -:   64:	    }
        -:   65:        }
        -:   66:    }
        -:   67:
        -:   68:
        -:   69:  //initialize supply
        -:   70:  ///////////////////////////////
        -:   71:
        -:   72:  //set number of Curse cards
        2:   73:  if (numPlayers == 2)
branch  0 taken 100% (fallthrough)
branch  1 taken 0%
        -:   74:    {
        2:   75:      state->supplyCount[curse] = 10;
        -:   76:    }
    #####:   77:  else if (numPlayers == 3)
branch  0 never executed
branch  1 never executed
        -:   78:    {
    #####:   79:      state->supplyCount[curse] = 20;
        -:   80:    }
        -:   81:  else
        -:   82:    {
    #####:   83:      state->supplyCount[curse] = 30;
        -:   84:    }
        -:   85:
        -:   86:  //set number of Victory cards
        2:   87:  if (numPlayers == 2)
branch  0 taken 100% (fallthrough)
branch  1 taken 0%
        -:   88:    {
        2:   89:      state->supplyCount[estate] = 8;
        2:   90:      state->supplyCount[duchy] = 8;
        2:   91:      state->supplyCount[province] = 8;
        -:   92:    }
        -:   93:  else
        -:   94:    {
    #####:   95:      state->supplyCount[estate] = 12;
    #####:   96:      state->supplyCount[duchy] = 12;
    #####:   97:      state->supplyCount[province] = 12;
        -:   98:    }
        -:   99:
        -:  100:  //set number of Treasure cards
        2:  101:  state->supplyCount[copper] = 60 - (7 * numPlayers);
        2:  102:  state->supplyCount[silver] = 40;
        2:  103:  state->supplyCount[gold] = 30;
        -:  104:
        -:  105:  //set number of Kingdom cards
       42:  106:  for (i = adventurer; i <= treasure_map; i++)       	//loop all cards
branch  0 taken 95%
branch  1 taken 5% (fallthrough)
        -:  107:    {
      330:  108:      for (j = 0; j < 10; j++)           		//loop chosen cards
branch  0 taken 94%
branch  1 taken 6% (fallthrough)
        -:  109:	{
      310:  110:	  if (kingdomCards[j] == i)
branch  0 taken 6% (fallthrough)
branch  1 taken 94%
        -:  111:	    {
        -:  112:	      //check if card is a 'Victory' Kingdom card
       20:  113:	      if (kingdomCards[j] == great_hall || kingdomCards[j] == gardens)
branch  0 taken 90% (fallthrough)
branch  1 taken 10%
branch  2 taken 11% (fallthrough)
branch  3 taken 89%
        -:  114:		{
        8:  115:		  if (numPlayers == 2){
branch  0 taken 100% (fallthrough)
branch  1 taken 0%
        4:  116:		    state->supplyCount[i] = 8;
        -:  117:		  }
    #####:  118:		  else{ state->supplyCount[i] = 12; }
        -:  119:		}
        -:  120:	      else
        -:  121:		{
       16:  122:		  state->supplyCount[i] = 10;
        -:  123:		}
       20:  124:	      break;
        -:  125:	    }
        -:  126:	  else    //card is not in the set choosen for the game
        -:  127:	    {
      290:  128:	      state->supplyCount[i] = -1;
        -:  129:	    }
        -:  130:	}
        -:  131:
        -:  132:    }
        -:  133:
        -:  134:  ////////////////////////
        -:  135:  //supply intilization complete
        -:  136:
        -:  137:  //set player decks
        6:  138:  for (i = 0; i < numPlayers; i++)
branch  0 taken 67%
branch  1 taken 33% (fallthrough)
        -:  139:    {
        4:  140:      state->deckCount[i] = 0;
       16:  141:      for (j = 0; j < 3; j++)
branch  0 taken 75%
branch  1 taken 25% (fallthrough)
        -:  142:	{
       12:  143:	  state->deck[i][j] = estate;
       12:  144:	  state->deckCount[i]++;
        -:  145:	}
       32:  146:      for (j = 3; j < 10; j++)
branch  0 taken 88%
branch  1 taken 13% (fallthrough)
        -:  147:	{
       28:  148:	  state->deck[i][j] = copper;
       28:  149:	  state->deckCount[i]++;
        -:  150:	}
        -:  151:    }
        -:  152:
        -:  153:  //shuffle player decks
        6:  154:  for (i = 0; i < numPlayers; i++)
branch  0 taken 67%
branch  1 taken 33% (fallthrough)
        -:  155:    {
        4:  156:      if ( shuffle(i, state) < 0 )
call    0 returned 100%
branch  1 taken 0% (fallthrough)
branch  2 taken 100%
        -:  157:	{
    #####:  158:	  return -1;
        -:  159:	}
        -:  160:    }
        -:  161:
        -:  162:  //draw player hands
        6:  163:  for (i = 0; i < numPlayers; i++)
branch  0 taken 67%
branch  1 taken 33% (fallthrough)
        -:  164:    {
        -:  165:      //initialize hand size to zero
        4:  166:      state->handCount[i] = 0;
        4:  167:      state->discardCount[i] = 0;
        -:  168:      //draw 5 cards
        -:  169:      // for (j = 0; j < 5; j++)
        -:  170:      //	{
        -:  171:      //	  drawCard(i, state);
        -:  172:      //	}
        -:  173:    }
        -:  174:
        -:  175:  //set embargo tokens to 0 for all supply piles
       56:  176:  for (i = 0; i <= treasure_map; i++)
branch  0 taken 96%
branch  1 taken 4% (fallthrough)
        -:  177:    {
       54:  178:      state->embargoTokens[i] = 0;
        -:  179:    }
        -:  180:
        -:  181:  //initialize first player's turn
        2:  182:  state->outpostPlayed = 0;
        2:  183:  state->phase = 0;
        2:  184:  state->numActions = 1;
        2:  185:  state->numBuys = 1;
        2:  186:  state->playedCardCount = 0;
        2:  187:  state->whoseTurn = 0;
        2:  188:  state->handCount[state->whoseTurn] = 0;
        -:  189:  //int it; move to top
        -:  190:
        -:  191:  //Moved draw cards to here, only drawing at the start of a turn
       12:  192:  for (it = 0; it < 5; it++){
branch  0 taken 83%
branch  1 taken 17% (fallthrough)
       10:  193:    drawCard(state->whoseTurn, state);
call    0 returned 100%
        -:  194:  }
        -:  195:
        2:  196:  updateCoins(state->whoseTurn, state, 0);
call    0 returned 100%
        -:  197:
        2:  198:  return 0;
        -:  199:}
        -:  200:
function shuffle called 86 returned 100% blocks executed 100%
       86:  201:int shuffle(int player, struct gameState *state) {
        -:  202:
        -:  203:
        -:  204:  int newDeck[MAX_DECK];
       86:  205:  int newDeckPos = 0;
        -:  206:  int card;
        -:  207:  int i;
        -:  208:
       86:  209:  if (state->deckCount[player] < 1)
branch  0 taken 48% (fallthrough)
branch  1 taken 52%
       41:  210:    return -1;
       45:  211:  qsort ((void*)(state->deck[player]), state->deckCount[player], sizeof(int), compare);
call    0 returned 100%
        -:  212:  /* SORT CARDS IN DECK TO ENSURE DETERMINISM! */
        -:  213:
    10236:  214:  while (state->deckCount[player] > 0) {
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
    10146:  215:    card = floor(Random() * state->deckCount[player]);
call    0 returned 100%
    10146:  216:    newDeck[newDeckPos] = state->deck[player][card];
    10146:  217:    newDeckPos++;
   929397:  218:    for (i = card; i < state->deckCount[player]-1; i++) {
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
   919251:  219:      state->deck[player][i] = state->deck[player][i+1];
        -:  220:    }
    10146:  221:    state->deckCount[player]--;
        -:  222:  }
    10191:  223:  for (i = 0; i < newDeckPos; i++) {
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
    10146:  224:    state->deck[player][i] = newDeck[i];
    10146:  225:    state->deckCount[player]++;
        -:  226:  }
        -:  227:
       45:  228:  return 0;
        -:  229:}
        -:  230:
function playCard called 2 returned 100% blocks executed 73%
        2:  231:int playCard(int handPos, int choice1, int choice2, int choice3, struct gameState *state)
        -:  232:{
        -:  233:  int card;
        2:  234:  int coin_bonus = 0; 		//tracks coins gain from actions
        -:  235:
        -:  236:  //check if it is the right phase
        2:  237:  if (state->phase != 0)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
        -:  238:    {
    #####:  239:      return -1;
        -:  240:    }
        -:  241:
        -:  242:  //check if player has enough actions
        2:  243:  if ( state->numActions < 1 )
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
        -:  244:    {
    #####:  245:      return -1;
        -:  246:    }
        -:  247:
        -:  248:  //get card played
        2:  249:  card = handCard(handPos, state);
call    0 returned 100%
        -:  250:
        -:  251:  //check if selected card is an action
        2:  252:  if ( card < adventurer || card > treasure_map )
branch  0 taken 100% (fallthrough)
branch  1 taken 0%
branch  2 taken 0% (fallthrough)
branch  3 taken 100%
        -:  253:    {
    #####:  254:      return -1;
        -:  255:    }
        -:  256:
        -:  257:  //play card
        2:  258:  if ( cardEffect(card, choice1, choice2, choice3, state, handPos, &coin_bonus) < 0 )
call    0 returned 100%
branch  1 taken 0% (fallthrough)
branch  2 taken 100%
        -:  259:    {
    #####:  260:      return -1;
        -:  261:    }
        -:  262:
        -:  263:  //reduce number of actions
        2:  264:  state->numActions--;
        -:  265:
        -:  266:  //update coins (Treasure cards may be added with card draws)
        2:  267:  updateCoins(state->whoseTurn, state, coin_bonus);
call    0 returned 100%
        -:  268:
        2:  269:  return 0;
        -:  270:}
        -:  271:
function buyCard called 0 returned 0% blocks executed 0%
    #####:  272:int buyCard(int supplyPos, struct gameState *state) {
        -:  273:  int who;
        -:  274:  if (DEBUG){
        -:  275:    printf("Entering buyCard...\n");
        -:  276:  }
        -:  277:
        -:  278:  // I don't know what to do about the phase thing.
        -:  279:
    #####:  280:  who = state->whoseTurn;
        -:  281:
    #####:  282:  if (state->numBuys < 1){
branch  0 never executed
branch  1 never executed
        -:  283:    if (DEBUG)
        -:  284:      printf("You do not have any buys left\n");
    #####:  285:    return -1;
    #####:  286:  } else if (supplyCount(supplyPos, state) <1){
call    0 never executed
branch  1 never executed
branch  2 never executed
        -:  287:    if (DEBUG)
        -:  288:      printf("There are not any of that type of card left\n");
    #####:  289:    return -1;
    #####:  290:  } else if (state->coins < getCost(supplyPos)){
call    0 never executed
branch  1 never executed
branch  2 never executed
        -:  291:    if (DEBUG)
        -:  292:      printf("You do not have enough money to buy that. You have %d coins.\n", state->coins);
    #####:  293:    return -1;
        -:  294:  } else {
    #####:  295:    state->phase=1;
        -:  296:    //state->supplyCount[supplyPos]--;
    #####:  297:    gainCard(supplyPos, state, 0, who); //card goes in discard, this might be wrong.. (2 means goes into hand, 0 goes into discard)
call    0 never executed
        -:  298:
    #####:  299:    state->coins = (state->coins) - (getCost(supplyPos));
call    0 never executed
    #####:  300:    state->numBuys--;
        -:  301:    if (DEBUG)
        -:  302:      printf("You bought card number %d for %d coins. You now have %d buys and %d coins.\n", supplyPos, getCost(supplyPos), state->numBuys, state->coins);
        -:  303:  }
        -:  304:
        -:  305:  //state->discard[who][state->discardCount[who]] = supplyPos;
        -:  306:  //state->discardCount[who]++;
        -:  307:
    #####:  308:  return 0;
        -:  309:}
        -:  310:
function numHandCards called 32 returned 100% blocks executed 100%
       32:  311:int numHandCards(struct gameState *state) {
       32:  312:  return state->handCount[ whoseTurn(state) ];
call    0 returned 100%
        -:  313:}
        -:  314:
function handCard called 30 returned 100% blocks executed 100%
       30:  315:int handCard(int handPos, struct gameState *state) {
       30:  316:  int currentPlayer = whoseTurn(state);
call    0 returned 100%
       30:  317:  return state->hand[currentPlayer][handPos];
        -:  318:}
        -:  319:
function supplyCount called 2 returned 100% blocks executed 100%
        2:  320:int supplyCount(int card, struct gameState *state) {
        2:  321:  return state->supplyCount[card];
        -:  322:}
        -:  323:
function fullDeckCount called 0 returned 0% blocks executed 0%
    #####:  324:int fullDeckCount(int player, int card, struct gameState *state) {
        -:  325:  int i;
    #####:  326:  int count = 0;
        -:  327:
    #####:  328:  for (i = 0; i < state->deckCount[player]; i++)
branch  0 never executed
branch  1 never executed
        -:  329:    {
    #####:  330:      if (state->deck[player][i] == card) count++;
branch  0 never executed
branch  1 never executed
        -:  331:    }
        -:  332:
    #####:  333:  for (i = 0; i < state->handCount[player]; i++)
branch  0 never executed
branch  1 never executed
        -:  334:    {
    #####:  335:      if (state->hand[player][i] == card) count++;
branch  0 never executed
branch  1 never executed
        -:  336:    }
        -:  337:
    #####:  338:  for (i = 0; i < state->discardCount[player]; i++)
branch  0 never executed
branch  1 never executed
        -:  339:    {
    #####:  340:      if (state->discard[player][i] == card) count++;
branch  0 never executed
branch  1 never executed
        -:  341:    }
        -:  342:
    #####:  343:  return count;
        -:  344:}
        -:  345:
function whoseTurn called 4068 returned 100% blocks executed 100%
     4068:  346:int whoseTurn(struct gameState *state) {
     4068:  347:  return state->whoseTurn;
        -:  348:}
        -:  349:
function endTurn called 2 returned 100% blocks executed 93%
        2:  350:int endTurn(struct gameState *state) {
        -:  351:  int k;
        -:  352:  int i;
        2:  353:  int currentPlayer = whoseTurn(state);
call    0 returned 100%
        -:  354:
        -:  355:  //Discard hand
       18:  356:  for (i = 0; i < state->handCount[currentPlayer]; i++){
branch  0 taken 89%
branch  1 taken 11% (fallthrough)
       16:  357:    state->discard[currentPlayer][state->discardCount[currentPlayer]++] = state->hand[currentPlayer][i];//Discard
       16:  358:    state->hand[currentPlayer][i] = -1;//Set card to -1
        -:  359:  }
        2:  360:  state->handCount[currentPlayer] = 0;//Reset hand count
        -:  361:
        -:  362:  //Code for determining the player
        2:  363:  if (currentPlayer < (state->numPlayers - 1)){
branch  0 taken 100% (fallthrough)
branch  1 taken 0%
        2:  364:    state->whoseTurn = currentPlayer + 1;//Still safe to increment
        -:  365:  }
        -:  366:  else{
    #####:  367:    state->whoseTurn = 0;//Max player has been reached, loop back around to player 1
        -:  368:  }
        -:  369:
        2:  370:  state->outpostPlayed = 0;
        2:  371:  state->phase = 0;
        2:  372:  state->numActions = 1;
        2:  373:  state->coins = 0;
        2:  374:  state->numBuys = 1;
        2:  375:  state->playedCardCount = 0;
        2:  376:  state->handCount[state->whoseTurn] = 0;
        -:  377:
        -:  378:  //int k; move to top
        -:  379:  //Next player draws hand
       12:  380:  for (k = 0; k < 5; k++){
branch  0 taken 83%
branch  1 taken 17% (fallthrough)
       10:  381:    drawCard(state->whoseTurn, state);//Draw a card
call    0 returned 100%
        -:  382:  }
        -:  383:
        -:  384:  //Update money
        2:  385:  updateCoins(state->whoseTurn, state , 0);
call    0 returned 100%
        -:  386:
        2:  387:  return 0;
        -:  388:}
        -:  389:
function isGameOver called 0 returned 0% blocks executed 0%
    #####:  390:int isGameOver(struct gameState *state) {
        -:  391:  int i;
        -:  392:  int j;
        -:  393:
        -:  394:  //if stack of Province cards is empty, the game ends
    #####:  395:  if (state->supplyCount[province] == 0)
branch  0 never executed
branch  1 never executed
        -:  396:    {
    #####:  397:      return 1;
        -:  398:    }
        -:  399:
        -:  400:  //if three supply pile are at 0, the game ends
    #####:  401:  j = 0;
    #####:  402:  for (i = 0; i < 25; i++)
branch  0 never executed
branch  1 never executed
        -:  403:    {
    #####:  404:      if (state->supplyCount[i] == 0)
branch  0 never executed
branch  1 never executed
        -:  405:	{
    #####:  406:	  j++;
        -:  407:	}
        -:  408:    }
    #####:  409:  if ( j >= 3)
branch  0 never executed
branch  1 never executed
        -:  410:    {
    #####:  411:      return 1;
        -:  412:    }
        -:  413:
    #####:  414:  return 0;
        -:  415:}
        -:  416:
function scoreFor called 0 returned 0% blocks executed 0%
    #####:  417:int scoreFor (int player, struct gameState *state) {
        -:  418:
        -:  419:  int i;
    #####:  420:  int score = 0;
        -:  421:  //score from hand
    #####:  422:  for (i = 0; i < state->handCount[player]; i++)
branch  0 never executed
branch  1 never executed
        -:  423:    {
    #####:  424:      if (state->hand[player][i] == curse) { score = score - 1; };
branch  0 never executed
branch  1 never executed
    #####:  425:      if (state->hand[player][i] == estate) { score = score + 1; };
branch  0 never executed
branch  1 never executed
    #####:  426:      if (state->hand[player][i] == duchy) { score = score + 3; };
branch  0 never executed
branch  1 never executed
    #####:  427:      if (state->hand[player][i] == province) { score = score + 6; };
branch  0 never executed
branch  1 never executed
    #####:  428:      if (state->hand[player][i] == great_hall) { score = score + 1; };
branch  0 never executed
branch  1 never executed
    #####:  429:      if (state->hand[player][i] == gardens) { score = score + ( fullDeckCount(player, 0, state) / 10 ); };
branch  0 never executed
branch  1 never executed
call    2 never executed
        -:  430:    }
        -:  431:
        -:  432:  //score from discard
    #####:  433:  for (i = 0; i < state->discardCount[player]; i++)
branch  0 never executed
branch  1 never executed
        -:  434:    {
    #####:  435:      if (state->discard[player][i] == curse) { score = score - 1; };
branch  0 never executed
branch  1 never executed
    #####:  436:      if (state->discard[player][i] == estate) { score = score + 1; };
branch  0 never executed
branch  1 never executed
    #####:  437:      if (state->discard[player][i] == duchy) { score = score + 3; };
branch  0 never executed
branch  1 never executed
    #####:  438:      if (state->discard[player][i] == province) { score = score + 6; };
branch  0 never executed
branch  1 never executed
    #####:  439:      if (state->discard[player][i] == great_hall) { score = score + 1; };
branch  0 never executed
branch  1 never executed
    #####:  440:      if (state->discard[player][i] == gardens) { score = score + ( fullDeckCount(player, 0, state) / 10 ); };
branch  0 never executed
branch  1 never executed
call    2 never executed
        -:  441:    }
        -:  442:
        -:  443:  //score from deck
    #####:  444:  for (i = 0; i < state->discardCount[player]; i++)
branch  0 never executed
branch  1 never executed
        -:  445:    {
    #####:  446:      if (state->deck[player][i] == curse) { score = score - 1; };
branch  0 never executed
branch  1 never executed
    #####:  447:      if (state->deck[player][i] == estate) { score = score + 1; };
branch  0 never executed
branch  1 never executed
    #####:  448:      if (state->deck[player][i] == duchy) { score = score + 3; };
branch  0 never executed
branch  1 never executed
    #####:  449:      if (state->deck[player][i] == province) { score = score + 6; };
branch  0 never executed
branch  1 never executed
    #####:  450:      if (state->deck[player][i] == great_hall) { score = score + 1; };
branch  0 never executed
branch  1 never executed
    #####:  451:      if (state->deck[player][i] == gardens) { score = score + ( fullDeckCount(player, 0, state) / 10 ); };
branch  0 never executed
branch  1 never executed
call    2 never executed
        -:  452:    }
        -:  453:
    #####:  454:  return score;
        -:  455:}
        -:  456:
function getWinners called 0 returned 0% blocks executed 0%
    #####:  457:int getWinners(int players[MAX_PLAYERS], struct gameState *state) {
        -:  458:  int i;
        -:  459:  int j;
        -:  460:  int highScore;
        -:  461:  int currentPlayer;
        -:  462:
        -:  463:  //get score for each player
    #####:  464:  for (i = 0; i < MAX_PLAYERS; i++)
branch  0 never executed
branch  1 never executed
        -:  465:    {
        -:  466:      //set unused player scores to -9999
    #####:  467:      if (i >= state->numPlayers)
branch  0 never executed
branch  1 never executed
        -:  468:	{
    #####:  469:	  players[i] = -9999;
        -:  470:	}
        -:  471:      else
        -:  472:	{
    #####:  473:	  players[i] = scoreFor (i, state);
call    0 never executed
        -:  474:	}
        -:  475:    }
        -:  476:
        -:  477:  //find highest score
    #####:  478:  j = 0;
    #####:  479:  for (i = 0; i < MAX_PLAYERS; i++)
branch  0 never executed
branch  1 never executed
        -:  480:    {
    #####:  481:      if (players[i] > players[j])
branch  0 never executed
branch  1 never executed
        -:  482:	{
    #####:  483:	  j = i;
        -:  484:	}
        -:  485:    }
    #####:  486:  highScore = players[j];
        -:  487:
        -:  488:  //add 1 to players who had less turns
    #####:  489:  currentPlayer = whoseTurn(state);
call    0 never executed
    #####:  490:  for (i = 0; i < MAX_PLAYERS; i++)
branch  0 never executed
branch  1 never executed
        -:  491:    {
    #####:  492:      if ( players[i] == highScore && i > currentPlayer )
branch  0 never executed
branch  1 never executed
branch  2 never executed
branch  3 never executed
        -:  493:	{
    #####:  494:	  players[i]++;
        -:  495:	}
        -:  496:    }
        -:  497:
        -:  498:  //find new highest score
    #####:  499:  j = 0;
    #####:  500:  for (i = 0; i < MAX_PLAYERS; i++)
branch  0 never executed
branch  1 never executed
        -:  501:    {
    #####:  502:      if ( players[i] > players[j] )
branch  0 never executed
branch  1 never executed
        -:  503:	{
    #####:  504:	  j = i;
        -:  505:	}
        -:  506:    }
    #####:  507:  highScore = players[j];
        -:  508:
        -:  509:  //set winners in array to 1 and rest to 0
    #####:  510:  for (i = 0; i < MAX_PLAYERS; i++)
branch  0 never executed
branch  1 never executed
        -:  511:    {
    #####:  512:      if ( players[i] == highScore )
branch  0 never executed
branch  1 never executed
        -:  513:	{
    #####:  514:	  players[i] = 1;
        -:  515:	}
        -:  516:      else
        -:  517:	{
    #####:  518:	  players[i] = 0;
        -:  519:	}
        -:  520:    }
        -:  521:
    #####:  522:  return 0;
        -:  523:}
        -:  524:
function drawCard called 33447 returned 100% blocks executed 92%
    33447:  525:int drawCard(int player, struct gameState *state)
        -:  526:{	int count;
        -:  527:  int deckCounter;
    33447:  528:  if (state->deckCount[player] <= 0){//Deck is empty
branch  0 taken 1% (fallthrough)
branch  1 taken 99%
        -:  529:
        -:  530:    //Step 1 Shuffle the discard pile back into a deck
        -:  531:    int i;
        -:  532:    //Move discard to deck
    10147:  533:    for (i = 0; i < state->discardCount[player];i++){
branch  0 taken 99%
branch  1 taken 1% (fallthrough)
    10106:  534:      state->deck[player][i] = state->discard[player][i];
    10106:  535:      state->discard[player][i] = -1;
        -:  536:    }
        -:  537:
       41:  538:    state->deckCount[player] = state->discardCount[player];
       41:  539:    state->discardCount[player] = 0;//Reset discard
        -:  540:
        -:  541:    //Shufffle the deck
       41:  542:    shuffle(player, state);//Shuffle the deck up and make it so that we can draw
call    0 returned 100%
        -:  543:
        -:  544:    if (DEBUG){//Debug statements
        -:  545:      printf("Deck count now: %d\n", state->deckCount[player]);
        -:  546:    }
        -:  547:
       41:  548:    state->discardCount[player] = 0;
        -:  549:
        -:  550:    //Step 2 Draw Card
       41:  551:    count = state->handCount[player];//Get current player's hand count
        -:  552:
        -:  553:    if (DEBUG){//Debug statements
        -:  554:      printf("Current hand count: %d\n", count);
        -:  555:    }
        -:  556:
       41:  557:    deckCounter = state->deckCount[player];//Create a holder for the deck count
        -:  558:
       41:  559:    if (deckCounter == 0)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:  560:      return -1;
        -:  561:
       41:  562:    state->hand[player][count] = state->deck[player][deckCounter - 1];//Add card to hand
       41:  563:    state->deckCount[player]--;
       41:  564:    state->handCount[player]++;//Increment hand count
        -:  565:  }
        -:  566:
        -:  567:  else{
    33406:  568:    int count = state->handCount[player];//Get current hand count for player
        -:  569:    int deckCounter;
        -:  570:    if (DEBUG){//Debug statements
        -:  571:      printf("Current hand count: %d\n", count);
        -:  572:    }
        -:  573:
    33406:  574:    deckCounter = state->deckCount[player];//Create holder for the deck count
    33406:  575:    state->hand[player][count] = state->deck[player][deckCounter - 1];//Add card to the hand
    33406:  576:    state->deckCount[player]--;
    33406:  577:    state->handCount[player]++;//Increment hand count
        -:  578:  }
        -:  579:
    33447:  580:  return 0;
        -:  581:}
        -:  582:
function getCost called 0 returned 0% blocks executed 0%
    #####:  583:int getCost(int cardNumber)
        -:  584:{
    #####:  585:  switch( cardNumber )
branch  0 never executed
branch  1 never executed
branch  2 never executed
branch  3 never executed
branch  4 never executed
branch  5 never executed
branch  6 never executed
branch  7 never executed
branch  8 never executed
branch  9 never executed
branch 10 never executed
branch 11 never executed
branch 12 never executed
branch 13 never executed
branch 14 never executed
branch 15 never executed
branch 16 never executed
branch 17 never executed
branch 18 never executed
branch 19 never executed
branch 20 never executed
branch 21 never executed
branch 22 never executed
branch 23 never executed
branch 24 never executed
branch 25 never executed
branch 26 never executed
branch 27 never executed
        -:  586:    {
        -:  587:    case curse:
    #####:  588:      return 0;
        -:  589:    case estate:
    #####:  590:      return 2;
        -:  591:    case duchy:
    #####:  592:      return 5;
        -:  593:    case province:
    #####:  594:      return 8;
        -:  595:    case copper:
    #####:  596:      return 0;
        -:  597:    case silver:
    #####:  598:      return 3;
        -:  599:    case gold:
    #####:  600:      return 6;
        -:  601:    case adventurer:
    #####:  602:      return 6;
        -:  603:    case council_room:
    #####:  604:      return 5;
        -:  605:    case feast:
    #####:  606:      return 4;
        -:  607:    case gardens:
    #####:  608:      return 4;
        -:  609:    case mine:
    #####:  610:      return 5;
        -:  611:    case remodel:
    #####:  612:      return 4;
        -:  613:    case smithy:
    #####:  614:      return 4;
        -:  615:    case village:
    #####:  616:      return 3;
        -:  617:    case baron:
    #####:  618:      return 4;
        -:  619:    case great_hall:
    #####:  620:      return 3;
        -:  621:    case minion:
    #####:  622:      return 5;
        -:  623:    case steward:
    #####:  624:      return 3;
        -:  625:    case tribute:
    #####:  626:      return 5;
        -:  627:    case ambassador:
    #####:  628:      return 3;
        -:  629:    case cutpurse:
    #####:  630:      return 4;
        -:  631:    case embargo:
    #####:  632:      return 2;
        -:  633:    case outpost:
    #####:  634:      return 5;
        -:  635:    case salvager:
    #####:  636:      return 4;
        -:  637:    case sea_hag:
    #####:  638:      return 4;
        -:  639:    case treasure_map:
    #####:  640:      return 4;
        -:  641:    }
        -:  642:
    #####:  643:  return -1;
        -:  644:}
        -:  645:
function cardEffect called 2002 returned 100% blocks executed 3%
     2002:  646:int cardEffect(int card, int choice1, int choice2, int choice3, struct gameState *state, int handPos, int *bonus)
        -:  647:{
        -:  648:  int i;
        -:  649:  int j;
        -:  650:  int k;
        -:  651:  int x;
        -:  652:  int index;
     2002:  653:  int currentPlayer = whoseTurn(state);
call    0 returned 100%
     2002:  654:  int nextPlayer = currentPlayer + 1;
        -:  655:
     2002:  656:  int tributeRevealedCards[2] = {-1, -1};
        -:  657:  int temphand[MAX_HAND];// moved above the if statement
        -:  658:  //int drawntreasure=0;
        -:  659:  //int cardDrawn;
        -:  660:  //int z = 0;// this is the counter for the temp hand
     2002:  661:  if (nextPlayer > (state->numPlayers - 1)){
branch  0 taken 51% (fallthrough)
branch  1 taken 49%
     1013:  662:    nextPlayer = 0;
        -:  663:  }
        -:  664:
        -:  665:
        -:  666:  //uses switch to select card and perform actions
     2002:  667:  switch( card )
branch  0 taken 100%
branch  1 taken 0%
branch  2 taken 0%
branch  3 taken 0%
branch  4 taken 0%
branch  5 taken 0%
branch  6 taken 0%
branch  7 taken 0%
branch  8 taken 0%
branch  9 taken 0%
branch 10 taken 0%
branch 11 taken 0%
branch 12 taken 0%
branch 13 taken 0%
branch 14 taken 0%
branch 15 taken 0%
branch 16 taken 0%
branch 17 taken 0%
branch 18 taken 0%
branch 19 taken 0%
branch 20 taken 0%
        -:  668:    {
        -:  669:    case adventurer:
     2002:  670:      cardAdventurer(state);
call    0 returned 100%
     2002:  671:      return 0;
        -:  672:      break;
        -:  673:
        -:  674:    case council_room:
    #####:  675:      cardCouncilRoom(state, handPos);
call    0 never executed
    #####:  676:      return 0;
        -:  677:      break;
        -:  678:
        -:  679:    case feast:
        -:  680:      //gain card with cost up to 5
        -:  681:      //Backup hand
    #####:  682:      for (i = 0; i <= state->handCount[currentPlayer]; i++){
branch  0 never executed
branch  1 never executed
    #####:  683:	temphand[i] = state->hand[currentPlayer][i];//Backup card
    #####:  684:	state->hand[currentPlayer][i] = -1;//Set to nothing
        -:  685:      }
        -:  686:      //Backup hand
        -:  687:
        -:  688:      //Update Coins for Buy
    #####:  689:      updateCoins(currentPlayer, state, 5);
call    0 never executed
    #####:  690:      x = 1;//Condition to loop on
    #####:  691:      while( x == 1) {//Buy one card
branch  0 never executed
branch  1 never executed
    #####:  692:	if (supplyCount(choice1, state) <= 0){
call    0 never executed
branch  1 never executed
branch  2 never executed
        -:  693:	  if (DEBUG)
        -:  694:	    printf("None of that card left, sorry!\n");
        -:  695:
        -:  696:	  if (DEBUG){
        -:  697:	    printf("Cards Left: %d\n", supplyCount(choice1, state));
        -:  698:	  }
        -:  699:	}
    #####:  700:	else if (state->coins < getCost(choice1)){
call    0 never executed
branch  1 never executed
branch  2 never executed
    #####:  701:	  printf("That card is too expensive!\n");
call    0 never executed
        -:  702:
        -:  703:	  if (DEBUG){
        -:  704:	    printf("Coins: %d < %d\n", state->coins, getCost(choice1));
        -:  705:	  }
        -:  706:	}
        -:  707:	else{
        -:  708:
        -:  709:	  if (DEBUG){
        -:  710:	    printf("Deck Count: %d\n", state->handCount[currentPlayer] + state->deckCount[currentPlayer] + state->discardCount[currentPlayer]);
        -:  711:	  }
        -:  712:
    #####:  713:	  gainCard(choice1, state, 0, currentPlayer);//Gain the card
call    0 never executed
    #####:  714:	  x = 0;//No more buying cards
        -:  715:
        -:  716:	  if (DEBUG){
        -:  717:	    printf("Deck Count: %d\n", state->handCount[currentPlayer] + state->deckCount[currentPlayer] + state->discardCount[currentPlayer]);
        -:  718:	  }
        -:  719:
        -:  720:	}
        -:  721:      }
        -:  722:
        -:  723:      //Reset Hand
    #####:  724:      for (i = 0; i <= state->handCount[currentPlayer]; i++){
branch  0 never executed
branch  1 never executed
    #####:  725:	state->hand[currentPlayer][i] = temphand[i];
    #####:  726:	temphand[i] = -1;
        -:  727:      }
        -:  728:      //Reset Hand
        -:  729:
    #####:  730:      return 0;
        -:  731:
        -:  732:    case gardens:
    #####:  733:      return -1;
        -:  734:
        -:  735:    case mine:
    #####:  736:      j = state->hand[currentPlayer][choice1];  //store card we will trash
        -:  737:
    #####:  738:      if (state->hand[currentPlayer][choice1] < copper || state->hand[currentPlayer][choice1] > gold)
branch  0 never executed
branch  1 never executed
branch  2 never executed
branch  3 never executed
        -:  739:	{
    #####:  740:	  return -1;
        -:  741:	}
        -:  742:
    #####:  743:      if (choice2 > treasure_map || choice2 < curse)
branch  0 never executed
branch  1 never executed
branch  2 never executed
branch  3 never executed
        -:  744:	{
    #####:  745:	  return -1;
        -:  746:	}
        -:  747:
    #####:  748:      if ( (getCost(state->hand[currentPlayer][choice1]) + 3) > getCost(choice2) )
call    0 never executed
call    1 never executed
branch  2 never executed
branch  3 never executed
        -:  749:	{
    #####:  750:	  return -1;
        -:  751:	}
        -:  752:
    #####:  753:      gainCard(choice2, state, 2, currentPlayer);
call    0 never executed
        -:  754:
        -:  755:      //discard card from hand
    #####:  756:      discardCard(handPos, currentPlayer, state, 0);
call    0 never executed
        -:  757:
        -:  758:      //discard trashed card
    #####:  759:      for (i = 0; i < state->handCount[currentPlayer]; i++)
branch  0 never executed
branch  1 never executed
        -:  760:	{
    #####:  761:	  if (state->hand[currentPlayer][i] == j)
branch  0 never executed
branch  1 never executed
        -:  762:	    {
    #####:  763:	      discardCard(i, currentPlayer, state, 0);
call    0 never executed
    #####:  764:	      break;
        -:  765:	    }
        -:  766:	}
        -:  767:
    #####:  768:      return 0;
        -:  769:
        -:  770:    case remodel:
    #####:  771:      j = state->hand[currentPlayer][choice1];  //store card we will trash
        -:  772:
    #####:  773:      if ( (getCost(state->hand[currentPlayer][choice1]) + 2) > getCost(choice2) )
call    0 never executed
call    1 never executed
branch  2 never executed
branch  3 never executed
        -:  774:	{
    #####:  775:	  return -1;
        -:  776:	}
        -:  777:
    #####:  778:      gainCard(choice2, state, 0, currentPlayer);
call    0 never executed
        -:  779:
        -:  780:      //discard card from hand
    #####:  781:      discardCard(handPos, currentPlayer, state, 0);
call    0 never executed
        -:  782:
        -:  783:      //discard trashed card
    #####:  784:      for (i = 0; i < state->handCount[currentPlayer]; i++)
branch  0 never executed
branch  1 never executed
        -:  785:	{
    #####:  786:	  if (state->hand[currentPlayer][i] == j)
branch  0 never executed
branch  1 never executed
        -:  787:	    {
    #####:  788:	      discardCard(i, currentPlayer, state, 0);
call    0 never executed
    #####:  789:	      break;
        -:  790:	    }
        -:  791:	}
        -:  792:
        -:  793:
    #####:  794:      return 0;
        -:  795:
        -:  796:    case smithy:
    #####:  797:      cardSmithy(state, handPos);
call    0 never executed
    #####:  798:      return 0;
        -:  799:      break;
        -:  800:
        -:  801:    case village:
    #####:  802:      cardVillage(state, handPos);
call    0 never executed
    #####:  803:      return 0;
        -:  804:      break;
        -:  805:
        -:  806:    case baron:
    #####:  807:      state->numBuys++;//Increase buys by 1!
    #####:  808:      if (choice1 > 0){//Boolean true or going to discard an estate
branch  0 never executed
branch  1 never executed
    #####:  809:	int p = 0;//Iterator for hand!
    #####:  810:	int card_not_discarded = 1;//Flag for discard set!
    #####:  811:	while(card_not_discarded){
branch  0 never executed
branch  1 never executed
    #####:  812:	  if (state->hand[currentPlayer][p] == estate){//Found an estate card!
branch  0 never executed
branch  1 never executed
    #####:  813:	    state->coins += 4;//Add 4 coins to the amount of coins
    #####:  814:	    state->discard[currentPlayer][state->discardCount[currentPlayer]] = state->hand[currentPlayer][p];
    #####:  815:	    state->discardCount[currentPlayer]++;
    #####:  816:	    for (;p < state->handCount[currentPlayer]; p++){
branch  0 never executed
branch  1 never executed
    #####:  817:	      state->hand[currentPlayer][p] = state->hand[currentPlayer][p+1];
        -:  818:	    }
    #####:  819:	    state->hand[currentPlayer][state->handCount[currentPlayer]] = -1;
    #####:  820:	    state->handCount[currentPlayer]--;
    #####:  821:	    card_not_discarded = 0;//Exit the loop
        -:  822:	  }
    #####:  823:	  else if (p > state->handCount[currentPlayer]){
branch  0 never executed
branch  1 never executed
        -:  824:	    if(DEBUG) {
        -:  825:	      printf("No estate cards in your hand, invalid choice\n");
        -:  826:	      printf("Must gain an estate if there are any\n");
        -:  827:	    }
    #####:  828:	    if (supplyCount(estate, state) > 0){
call    0 never executed
branch  1 never executed
branch  2 never executed
    #####:  829:	      gainCard(estate, state, 0, currentPlayer);
call    0 never executed
    #####:  830:	      state->supplyCount[estate]--;//Decrement estates
    #####:  831:	      if (supplyCount(estate, state) == 0){
call    0 never executed
branch  1 never executed
branch  2 never executed
    #####:  832:		isGameOver(state);
call    0 never executed
        -:  833:	      }
        -:  834:	    }
    #####:  835:	    card_not_discarded = 0;//Exit the loop
        -:  836:	  }
        -:  837:
        -:  838:	  else{
    #####:  839:	    p++;//Next card
        -:  840:	  }
        -:  841:	}
        -:  842:      }
        -:  843:
        -:  844:      else{
    #####:  845:	if (supplyCount(estate, state) > 0){
call    0 never executed
branch  1 never executed
branch  2 never executed
    #####:  846:	  gainCard(estate, state, 0, currentPlayer);//Gain an estate
call    0 never executed
    #####:  847:	  state->supplyCount[estate]--;//Decrement Estates
    #####:  848:	  if (supplyCount(estate, state) == 0){
call    0 never executed
branch  1 never executed
branch  2 never executed
    #####:  849:	    isGameOver(state);
call    0 never executed
        -:  850:	  }
        -:  851:	}
        -:  852:      }
        -:  853:
        -:  854:
    #####:  855:      return 0;
        -:  856:
        -:  857:    case great_hall:
    #####:  858:      cardGreatHall(state, handPos);
call    0 never executed
    #####:  859:      return 0;
        -:  860:      break;
        -:  861:
        -:  862:    case minion:
        -:  863:      //+1 action
    #####:  864:      state->numActions++;
        -:  865:
        -:  866:      //discard card from hand
    #####:  867:      discardCard(handPos, currentPlayer, state, 0);
call    0 never executed
        -:  868:
    #####:  869:      if (choice1)		//+2 coins
branch  0 never executed
branch  1 never executed
        -:  870:	{
    #####:  871:	  state->coins = state->coins + 2;
        -:  872:	}
        -:  873:
    #####:  874:      else if (choice2)		//discard hand, redraw 4, other players with 5+ cards discard hand and draw 4
branch  0 never executed
branch  1 never executed
        -:  875:	{
        -:  876:	  //discard hand
    #####:  877:	  while(numHandCards(state) > 0)
call    0 never executed
branch  1 never executed
branch  2 never executed
        -:  878:	    {
    #####:  879:	      discardCard(handPos, currentPlayer, state, 0);
call    0 never executed
        -:  880:	    }
        -:  881:
        -:  882:	  //draw 4
    #####:  883:	  for (i = 0; i < 4; i++)
branch  0 never executed
branch  1 never executed
        -:  884:	    {
    #####:  885:	      drawCard(currentPlayer, state);
call    0 never executed
        -:  886:	    }
        -:  887:
        -:  888:	  //other players discard hand and redraw if hand size > 4
    #####:  889:	  for (i = 0; i < state->numPlayers; i++)
branch  0 never executed
branch  1 never executed
        -:  890:	    {
    #####:  891:	      if (i != currentPlayer)
branch  0 never executed
branch  1 never executed
        -:  892:		{
    #####:  893:		  if ( state->handCount[i] > 4 )
branch  0 never executed
branch  1 never executed
        -:  894:		    {
        -:  895:		      //discard hand
    #####:  896:		      while( state->handCount[i] > 0 )
branch  0 never executed
branch  1 never executed
        -:  897:			{
    #####:  898:			  discardCard(handPos, i, state, 0);
call    0 never executed
        -:  899:			}
        -:  900:
        -:  901:		      //draw 4
    #####:  902:		      for (j = 0; j < 4; j++)
branch  0 never executed
branch  1 never executed
        -:  903:			{
    #####:  904:			  drawCard(i, state);
call    0 never executed
        -:  905:			}
        -:  906:		    }
        -:  907:		}
        -:  908:	    }
        -:  909:
        -:  910:	}
    #####:  911:      return 0;
        -:  912:
        -:  913:    case steward:
    #####:  914:      if (choice1 == 1)
branch  0 never executed
branch  1 never executed
        -:  915:	{
        -:  916:	  //+2 cards
    #####:  917:	  drawCard(currentPlayer, state);
call    0 never executed
    #####:  918:	  drawCard(currentPlayer, state);
call    0 never executed
        -:  919:	}
    #####:  920:      else if (choice1 == 2)
branch  0 never executed
branch  1 never executed
        -:  921:	{
        -:  922:	  //+2 coins
    #####:  923:	  state->coins = state->coins + 2;
        -:  924:	}
        -:  925:      else
        -:  926:	{
        -:  927:	  //trash 2 cards in hand
    #####:  928:	  discardCard(choice2, currentPlayer, state, 1);
call    0 never executed
    #####:  929:	  discardCard(choice3, currentPlayer, state, 1);
call    0 never executed
        -:  930:	}
        -:  931:
        -:  932:      //discard card from hand
    #####:  933:      discardCard(handPos, currentPlayer, state, 0);
call    0 never executed
    #####:  934:      return 0;
        -:  935:
        -:  936:    case tribute:
    #####:  937:      if ((state->discardCount[nextPlayer] + state->deckCount[nextPlayer]) <= 1){
branch  0 never executed
branch  1 never executed
    #####:  938:	if (state->deckCount[nextPlayer] > 0){
branch  0 never executed
branch  1 never executed
    #####:  939:	  tributeRevealedCards[0] = state->deck[nextPlayer][state->deckCount[nextPlayer]-1];
    #####:  940:	  state->deckCount[nextPlayer]--;
        -:  941:	}
    #####:  942:	else if (state->discardCount[nextPlayer] > 0){
branch  0 never executed
branch  1 never executed
    #####:  943:	  tributeRevealedCards[0] = state->discard[nextPlayer][state->discardCount[nextPlayer]-1];
    #####:  944:	  state->discardCount[nextPlayer]--;
        -:  945:	}
        -:  946:	else{
        -:  947:	  //No Card to Reveal
        -:  948:	  if (DEBUG){
        -:  949:	    printf("No cards to reveal\n");
        -:  950:	  }
        -:  951:	}
        -:  952:      }
        -:  953:
        -:  954:      else{
    #####:  955:	if (state->deckCount[nextPlayer] == 0){
branch  0 never executed
branch  1 never executed
    #####:  956:	  for (i = 0; i < state->discardCount[nextPlayer]; i++){
branch  0 never executed
branch  1 never executed
    #####:  957:	    state->deck[nextPlayer][i] = state->discard[nextPlayer][i];//Move to deck
    #####:  958:	    state->deckCount[nextPlayer]++;
    #####:  959:	    state->discard[nextPlayer][i] = -1;
    #####:  960:	    state->discardCount[nextPlayer]--;
        -:  961:	  }
        -:  962:
    #####:  963:	  shuffle(nextPlayer,state);//Shuffle the deck
call    0 never executed
        -:  964:	}
    #####:  965:	tributeRevealedCards[0] = state->deck[nextPlayer][state->deckCount[nextPlayer]-1];
    #####:  966:	state->deck[nextPlayer][state->deckCount[nextPlayer]--] = -1;
    #####:  967:	state->deckCount[nextPlayer]--;
    #####:  968:	tributeRevealedCards[1] = state->deck[nextPlayer][state->deckCount[nextPlayer]-1];
    #####:  969:	state->deck[nextPlayer][state->deckCount[nextPlayer]--] = -1;
    #####:  970:	state->deckCount[nextPlayer]--;
        -:  971:      }
        -:  972:
    #####:  973:      if (tributeRevealedCards[0] == tributeRevealedCards[1]){//If we have a duplicate card, just drop one
branch  0 never executed
branch  1 never executed
    #####:  974:	state->playedCards[state->playedCardCount] = tributeRevealedCards[1];
    #####:  975:	state->playedCardCount++;
    #####:  976:	tributeRevealedCards[1] = -1;
        -:  977:      }
        -:  978:
    #####:  979:      for (i = 0; i <= 2; i ++){
branch  0 never executed
branch  1 never executed
    #####:  980:	if (tributeRevealedCards[i] == copper || tributeRevealedCards[i] == silver || tributeRevealedCards[i] == gold){//Treasure cards
branch  0 never executed
branch  1 never executed
branch  2 never executed
branch  3 never executed
branch  4 never executed
branch  5 never executed
    #####:  981:	  state->coins += 2;
        -:  982:	}
        -:  983:
    #####:  984:	else if (tributeRevealedCards[i] == estate || tributeRevealedCards[i] == duchy || tributeRevealedCards[i] == province || tributeRevealedCards[i] == gardens || tributeRevealedCards[i] == great_hall){//Victory Card Found
branch  0 never executed
branch  1 never executed
branch  2 never executed
branch  3 never executed
branch  4 never executed
branch  5 never executed
branch  6 never executed
branch  7 never executed
branch  8 never executed
branch  9 never executed
    #####:  985:	  drawCard(currentPlayer, state);
call    0 never executed
    #####:  986:	  drawCard(currentPlayer, state);
call    0 never executed
        -:  987:	}
        -:  988:	else{//Action Card
    #####:  989:	  state->numActions = state->numActions + 2;
        -:  990:	}
        -:  991:      }
        -:  992:
    #####:  993:      return 0;
        -:  994:
        -:  995:    case ambassador:
    #####:  996:      j = 0;		//used to check if player has enough cards to discard
        -:  997:
    #####:  998:      if (choice2 > 2 || choice2 < 0)
branch  0 never executed
branch  1 never executed
branch  2 never executed
branch  3 never executed
        -:  999:	{
    #####: 1000:	  return -1;
        -: 1001:	}
        -: 1002:
    #####: 1003:      if (choice1 == handPos)
branch  0 never executed
branch  1 never executed
        -: 1004:	{
    #####: 1005:	  return -1;
        -: 1006:	}
        -: 1007:
    #####: 1008:      for (i = 0; i < state->handCount[currentPlayer]; i++)
branch  0 never executed
branch  1 never executed
        -: 1009:	{
    #####: 1010:	  if (i != handPos && i == state->hand[currentPlayer][choice1] && i != choice1)
branch  0 never executed
branch  1 never executed
branch  2 never executed
branch  3 never executed
branch  4 never executed
branch  5 never executed
        -: 1011:	    {
    #####: 1012:	      j++;
        -: 1013:	    }
        -: 1014:	}
    #####: 1015:      if (j < choice2)
branch  0 never executed
branch  1 never executed
        -: 1016:	{
    #####: 1017:	  return -1;
        -: 1018:	}
        -: 1019:
        -: 1020:      if (DEBUG)
        -: 1021:	printf("Player %d reveals card number: %d\n", currentPlayer, state->hand[currentPlayer][choice1]);
        -: 1022:
        -: 1023:      //increase supply count for choosen card by amount being discarded
    #####: 1024:      state->supplyCount[state->hand[currentPlayer][choice1]] += choice2;
        -: 1025:
        -: 1026:      //each other player gains a copy of revealed card
    #####: 1027:      for (i = 0; i < state->numPlayers; i++)
branch  0 never executed
branch  1 never executed
        -: 1028:	{
    #####: 1029:	  if (i != currentPlayer)
branch  0 never executed
branch  1 never executed
        -: 1030:	    {
    #####: 1031:	      gainCard(state->hand[currentPlayer][choice1], state, 0, i);
call    0 never executed
        -: 1032:	    }
        -: 1033:	}
        -: 1034:
        -: 1035:      //discard played card from hand
    #####: 1036:      discardCard(handPos, currentPlayer, state, 0);
call    0 never executed
        -: 1037:
        -: 1038:      //trash copies of cards returned to supply
    #####: 1039:      for (j = 0; j < choice2; j++)
branch  0 never executed
branch  1 never executed
        -: 1040:	{
    #####: 1041:	  for (i = 0; i < state->handCount[currentPlayer]; i++)
branch  0 never executed
branch  1 never executed
        -: 1042:	    {
    #####: 1043:	      if (state->hand[currentPlayer][i] == state->hand[currentPlayer][choice1])
branch  0 never executed
branch  1 never executed
        -: 1044:		{
    #####: 1045:		  discardCard(i, currentPlayer, state, 1);
call    0 never executed
    #####: 1046:		  break;
        -: 1047:		}
        -: 1048:	    }
        -: 1049:	}
        -: 1050:
    #####: 1051:      return 0;
        -: 1052:
        -: 1053:    case cutpurse:
        -: 1054:
    #####: 1055:      updateCoins(currentPlayer, state, 2);
call    0 never executed
    #####: 1056:      for (i = 0; i < state->numPlayers; i++)
branch  0 never executed
branch  1 never executed
        -: 1057:	{
    #####: 1058:	  if (i != currentPlayer)
branch  0 never executed
branch  1 never executed
        -: 1059:	    {
    #####: 1060:	      for (j = 0; j < state->handCount[i]; j++)
branch  0 never executed
branch  1 never executed
        -: 1061:		{
    #####: 1062:		  if (state->hand[i][j] == copper)
branch  0 never executed
branch  1 never executed
        -: 1063:		    {
    #####: 1064:		      discardCard(j, i, state, 0);
call    0 never executed
    #####: 1065:		      break;
        -: 1066:		    }
    #####: 1067:		  if (j == state->handCount[i])
branch  0 never executed
branch  1 never executed
        -: 1068:		    {
    #####: 1069:		      for (k = 0; k < state->handCount[i]; k++)
branch  0 never executed
branch  1 never executed
        -: 1070:			{
        -: 1071:			  if (DEBUG)
        -: 1072:			    printf("Player %d reveals card number %d\n", i, state->hand[i][k]);
        -: 1073:			}
    #####: 1074:		      break;
        -: 1075:		    }
        -: 1076:		}
        -: 1077:
        -: 1078:	    }
        -: 1079:
        -: 1080:	}
        -: 1081:
        -: 1082:      //discard played card from hand
    #####: 1083:      discardCard(handPos, currentPlayer, state, 0);
call    0 never executed
        -: 1084:
    #####: 1085:      return 0;
        -: 1086:
        -: 1087:
        -: 1088:    case embargo:
        -: 1089:      //+2 Coins
    #####: 1090:      state->coins = state->coins + 2;
        -: 1091:
        -: 1092:      //see if selected pile is in play
    #####: 1093:      if ( state->supplyCount[choice1] == -1 )
branch  0 never executed
branch  1 never executed
        -: 1094:	{
    #####: 1095:	  return -1;
        -: 1096:	}
        -: 1097:
        -: 1098:      //add embargo token to selected supply pile
    #####: 1099:      state->embargoTokens[choice1]++;
        -: 1100:
        -: 1101:      //trash card
    #####: 1102:      discardCard(handPos, currentPlayer, state, 1);
call    0 never executed
    #####: 1103:      return 0;
        -: 1104:
        -: 1105:    case outpost:
        -: 1106:      //set outpost flag
    #####: 1107:      state->outpostPlayed++;
        -: 1108:
        -: 1109:      //discard card
    #####: 1110:      discardCard(handPos, currentPlayer, state, 0);
call    0 never executed
    #####: 1111:      return 0;
        -: 1112:
        -: 1113:    case salvager:
        -: 1114:     //+1 buy
    #####: 1115:      state->numBuys++;
        -: 1116:
    #####: 1117:      if (choice1)
branch  0 never executed
branch  1 never executed
        -: 1118:        {
        -: 1119:          //gain coins equal to trashed card
    #####: 1120:          state->coins = state->coins + getCost( handCard(choice1, state) );
call    0 never executed
call    1 never executed
        -: 1121:          //trash card
    #####: 1122:          discardCard(choice1, currentPlayer, state, 1);
call    0 never executed
        -: 1123:        }
        -: 1124:
        -: 1125:      //discard card
    #####: 1126:      discardCard(handPos, currentPlayer, state, 0);
call    0 never executed
    #####: 1127:      return 0;
        -: 1128:
        -: 1129:    case sea_hag:
    #####: 1130:      for (i = 0; i < state->numPlayers; i++){
branch  0 never executed
branch  1 never executed
    #####: 1131:	if (i != currentPlayer){
branch  0 never executed
branch  1 never executed
    #####: 1132:	  state->discard[i][state->discardCount[i]] = state->deck[i][state->deckCount[i]--];			    state->deckCount[i]--;
    #####: 1133:	  state->discardCount[i]++;
    #####: 1134:	  state->deck[i][state->deckCount[i]--] = curse;//Top card now a curse
        -: 1135:	}
        -: 1136:      }
    #####: 1137:      return 0;
        -: 1138:
        -: 1139:    case treasure_map:
        -: 1140:      //search hand for another treasure_map
    #####: 1141:      index = -1;
    #####: 1142:      for (i = 0; i < state->handCount[currentPlayer]; i++)
branch  0 never executed
branch  1 never executed
        -: 1143:	{
    #####: 1144:	  if (state->hand[currentPlayer][i] == treasure_map && i != handPos)
branch  0 never executed
branch  1 never executed
branch  2 never executed
branch  3 never executed
        -: 1145:	    {
    #####: 1146:	      index = i;
    #####: 1147:	      break;
        -: 1148:	    }
        -: 1149:	}
    #####: 1150:      if (index > -1)
branch  0 never executed
branch  1 never executed
        -: 1151:	{
        -: 1152:	  //trash both treasure cards
    #####: 1153:	  discardCard(handPos, currentPlayer, state, 1);
call    0 never executed
    #####: 1154:	  discardCard(index, currentPlayer, state, 1);
call    0 never executed
        -: 1155:
        -: 1156:	  //gain 4 Gold cards
    #####: 1157:	  for (i = 0; i < 4; i++)
branch  0 never executed
branch  1 never executed
        -: 1158:	    {
    #####: 1159:	      gainCard(gold, state, 1, currentPlayer);
call    0 never executed
        -: 1160:	    }
        -: 1161:
        -: 1162:	  //return success
    #####: 1163:	  return 1;
        -: 1164:	}
        -: 1165:
        -: 1166:      //no second treasure_map found in hand
    #####: 1167:      return -1;
        -: 1168:    }
        -: 1169:
    #####: 1170:  return -1;
        -: 1171:}
        -: 1172:
        -: 1173:/***************************************************************************************************
        -: 1174:*                               START INDIVIDUAL CARD IMPLEMENTATIONS
        -: 1175:*       Cards:
        -: 1176:*           Adventurer
        -: 1177:*           Council Room
        -: 1178:*           Smithy
        -: 1179:*           Village
        -: 1180:*           Great Hall
        -: 1181:*
        -: 1182:***************************************************************************************************/
        -: 1183:
function cardAdventurer called 2002 returned 100% blocks executed 94%
     2002: 1184:int cardAdventurer(struct gameState *state) {
     2002: 1185:    int z=0; // this is the counter for the temp hand;
     2002: 1186:    int currentPlayer = whoseTurn(state);    
call    0 returned 100%
     2002: 1187:    int drawntreasure=0;
        -: 1188:    int temphand[MAX_HAND];// moved above the if statement
        -: 1189:    int cardDrawn;
        -: 1190:
    37431: 1191:    while(drawntreasure<2){
branch  0 taken 94%
branch  1 taken 6% (fallthrough)
    33427: 1192:        if (state->deckCount[currentPlayer] <1){//if the deck is empty we need to shuffle discard and add to deck
branch  0 taken 1% (fallthrough)
branch  1 taken 99%
       41: 1193:          shuffle(currentPlayer, state);
call    0 returned 100%
        -: 1194:        }
    33427: 1195:        drawCard(currentPlayer, state);
call    0 returned 100%
    33427: 1196:        cardDrawn = state->hand[currentPlayer][state->handCount[currentPlayer]-1];//top card of hand is most recently drawn card.
    33427: 1197:        if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)
branch  0 taken 96% (fallthrough)
branch  1 taken 4%
branch  2 taken 96% (fallthrough)
branch  3 taken 4%
branch  4 taken 4% (fallthrough)
branch  5 taken 96%
     4004: 1198:          drawntreasure++;
        -: 1199:        else{
    29423: 1200:          temphand[z]=cardDrawn;
    29423: 1201:          state->handCount[currentPlayer]--; //this should just remove the top card (the most recently drawn one).
        -: 1202:        }
        -: 1203:    }
     4004: 1204:    while(z-1>=0){
branch  0 taken 0%
branch  1 taken 100% (fallthrough)
    #####: 1205:        state->discard[currentPlayer][state->discardCount[currentPlayer]++]=temphand[z-1]; // discard all cards in play that have been drawn
    #####: 1206:        z=z-1;
        -: 1207:    }
     2002: 1208:    return 0;
        -: 1209:}
        -: 1210:
        -: 1211:
        -: 1212:
function cardCouncilRoom called 0 returned 0% blocks executed 0%
    #####: 1213:int cardCouncilRoom(struct gameState *state,  int handPos) {
        -: 1214:    //+4 Cards
        -: 1215:    int i;
    #####: 1216:    int currentPlayer = whoseTurn(state);    
call    0 never executed
        -: 1217:
    #####: 1218:    for (i = 0; i > 4; i++)
branch  0 never executed
branch  1 never executed
        -: 1219:    {
    #####: 1220:      drawCard(currentPlayer, state);
call    0 never executed
        -: 1221:    }
        -: 1222:
        -: 1223:    //+1 Buy
    #####: 1224:    state->numBuys++;
        -: 1225:
        -: 1226:      //Each other player draws a card
    #####: 1227:    for (i = 0; i < state->numPlayers; i++)
branch  0 never executed
branch  1 never executed
        -: 1228:    {
    #####: 1229:    if ( i == currentPlayer )
branch  0 never executed
branch  1 never executed
        -: 1230:        {
    #####: 1231:          drawCard(i, state);
call    0 never executed
        -: 1232:        }
        -: 1233:    }
        -: 1234:
        -: 1235:      //put played card in played card pile
    #####: 1236:    discardCard(handPos, currentPlayer, state, 0);
call    0 never executed
        -: 1237:
    #####: 1238:    return 0;
        -: 1239:}
        -: 1240:
function cardSmithy called 0 returned 0% blocks executed 0%
    #####: 1241:int cardSmithy(struct gameState *state, int handPos) {
        -: 1242://+3 Cards
        -: 1243:    int i;
    #####: 1244:    int currentPlayer = whoseTurn(state);
call    0 never executed
        -: 1245:
    #####: 1246:    for (i = 0; i > 3; i++)
branch  0 never executed
branch  1 never executed
        -: 1247:    {
    #####: 1248:      drawCard(currentPlayer, state);
call    0 never executed
        -: 1249:    }
        -: 1250:
        -: 1251:    //discard card from hand
    #####: 1252:    discardCard(handPos, currentPlayer, state, 0);
call    0 never executed
    #####: 1253:    return 0;
        -: 1254:}
        -: 1255:
function cardVillage called 0 returned 0% blocks executed 0%
    #####: 1256:int cardVillage(struct gameState *state,  int handPos) {
    #####: 1257:    int currentPlayer = whoseTurn(state);
call    0 never executed
        -: 1258:
        -: 1259:    //+1 Card
    #####: 1260:    drawCard(currentPlayer, state);
call    0 never executed
        -: 1261:
        -: 1262:    //+2 Actions
    #####: 1263:    state->numActions = state->numActions + 2;
        -: 1264:
        -: 1265:    //discard played card from hand
    #####: 1266:    discardCard(handPos, currentPlayer, state, 0);
call    0 never executed
    #####: 1267:    return 0;
        -: 1268:}
        -: 1269:
function cardGreatHall called 0 returned 0% blocks executed 0%
    #####: 1270:int cardGreatHall(struct gameState *state,  int handPos) {
    #####: 1271:    int currentPlayer = whoseTurn(state);
call    0 never executed
        -: 1272:    //+1 Card
    #####: 1273:    drawCard(currentPlayer, state);
call    0 never executed
        -: 1274:
        -: 1275:    //+1 Actions
    #####: 1276:    state->numBuys++;
        -: 1277:
        -: 1278:    //discard card from hand
    #####: 1279:    discardCard(handPos, currentPlayer, state, 0);
call    0 never executed
    #####: 1280:    return 0;
        -: 1281:}
        -: 1282:
        -: 1283:/***************************************************************************************************
        -: 1284:*                               END INDIVIDUAL CARD IMPLEMENTATIONS
        -: 1285:***************************************************************************************************/
        -: 1286:
        -: 1287:
function discardCard called 0 returned 0% blocks executed 0%
    #####: 1288:int discardCard(int handPos, int currentPlayer, struct gameState *state, int trashFlag)
        -: 1289:{
        -: 1290:
        -: 1291:  //if card is not trashed, added to Played pile
    #####: 1292:  if (trashFlag < 1)
branch  0 never executed
branch  1 never executed
        -: 1293:    {
        -: 1294:      //add card to played pile
    #####: 1295:      state->playedCards[state->playedCardCount] = state->hand[currentPlayer][handPos];
    #####: 1296:      state->playedCardCount++;
        -: 1297:    }
        -: 1298:
        -: 1299:  //set played card to -1
    #####: 1300:  state->hand[currentPlayer][handPos] = -1;
        -: 1301:
        -: 1302:  //remove card from player's hand
    #####: 1303:  if ( handPos == (state->handCount[currentPlayer] - 1) ) 	//last card in hand array is played
branch  0 never executed
branch  1 never executed
        -: 1304:    {
        -: 1305:      //reduce number of cards in hand
    #####: 1306:      state->handCount[currentPlayer]--;
        -: 1307:    }
    #####: 1308:  else if ( state->handCount[currentPlayer] == 1 ) //only one card in hand
branch  0 never executed
branch  1 never executed
        -: 1309:    {
        -: 1310:      //reduce number of cards in hand
    #####: 1311:      state->handCount[currentPlayer]--;
        -: 1312:    }
        -: 1313:  else
        -: 1314:    {
        -: 1315:      //replace discarded card with last card in hand
    #####: 1316:      state->hand[currentPlayer][handPos] = state->hand[currentPlayer][ (state->handCount[currentPlayer] - 1)];
        -: 1317:      //set last card to -1
    #####: 1318:      state->hand[currentPlayer][state->handCount[currentPlayer] - 1] = -1;
        -: 1319:      //reduce number of cards in hand
    #####: 1320:      state->handCount[currentPlayer]--;
        -: 1321:    }
        -: 1322:
    #####: 1323:  return 0;
        -: 1324:}
        -: 1325:
function gainCard called 2 returned 100% blocks executed 70%
        2: 1326:int gainCard(int supplyPos, struct gameState *state, int toFlag, int player)
        -: 1327:{
        -: 1328:  //Note: supplyPos is enum of choosen card
        -: 1329:
        -: 1330:  //check if supply pile is empty (0) or card is not used in game (-1)
        2: 1331:  if ( supplyCount(supplyPos, state) < 1 )
call    0 returned 100%
branch  1 taken 0% (fallthrough)
branch  2 taken 100%
        -: 1332:    {
    #####: 1333:      return -1;
        -: 1334:    }
        -: 1335:
        -: 1336:  //added card for [whoseTurn] current player:
        -: 1337:  // toFlag = 0 : add to discard
        -: 1338:  // toFlag = 1 : add to deck
        -: 1339:  // toFlag = 2 : add to hand
        -: 1340:
        2: 1341:  if (toFlag == 1)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
        -: 1342:    {
    #####: 1343:      state->deck[ player ][ state->deckCount[player] ] = supplyPos;
    #####: 1344:      state->deckCount[player]++;
        -: 1345:    }
        2: 1346:  else if (toFlag == 2)
branch  0 taken 100% (fallthrough)
branch  1 taken 0%
        -: 1347:    {
        2: 1348:      state->hand[ player ][ state->handCount[player] ] = supplyPos;
        2: 1349:      state->handCount[player]++;
        -: 1350:    }
        -: 1351:  else
        -: 1352:    {
    #####: 1353:      state->discard[player][ state->discardCount[player] ] = supplyPos;
    #####: 1354:      state->discardCount[player]++;
        -: 1355:    }
        -: 1356:
        -: 1357:  //decrease number in supply pile
        2: 1358:  state->supplyCount[supplyPos]--;
        -: 1359:
        2: 1360:  return 0;
        -: 1361:}
        -: 1362:
function updateCoins called 6 returned 100% blocks executed 82%
        6: 1363:int updateCoins(int player, struct gameState *state, int bonus)
        -: 1364:{
        -: 1365:  int i;
        -: 1366:
        -: 1367:  //reset coin count
        6: 1368:  state->coins = 0;
        -: 1369:
        -: 1370:  //add coins for each Treasure card in player's hand
       42: 1371:  for (i = 0; i < state->handCount[player]; i++)
branch  0 taken 86%
branch  1 taken 14% (fallthrough)
        -: 1372:    {
       36: 1373:      if (state->hand[player][i] == copper)
branch  0 taken 72% (fallthrough)
branch  1 taken 28%
        -: 1374:	{
       26: 1375:	  state->coins += 1;
        -: 1376:	}
       10: 1377:      else if (state->hand[player][i] == silver)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
        -: 1378:	{
    #####: 1379:	  state->coins += 2;
        -: 1380:	}
       10: 1381:      else if (state->hand[player][i] == gold)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
        -: 1382:	{
    #####: 1383:	  state->coins += 3;
        -: 1384:	}
        -: 1385:    }
        -: 1386:
        -: 1387:  //add bonus
        6: 1388:  state->coins += bonus;
        -: 1389:
        6: 1390:  return 0;
        -: 1391:}
        -: 1392:
        -: 1393:
        -: 1394://end of dominion.c
        -: 1395:
