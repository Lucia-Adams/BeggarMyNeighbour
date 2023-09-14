# BeggarMyNeighbour
Simulates the card game 'Beggar My Neighbour' using a Riffle Shuffle, with statistical analysis on the game and the shuffle


## Shuffling (riffle)

This is a function to shuffle items in an array in a random order, emulating a Riffle Shuffle.

Here's how it works:
 
- In a computer implementation of the riffle shuffle, the array to be shuffled is divided into two halves, say A and B, and then reassembled into a new array. 

 - The first item in the new array will be the first item from one of the two half arrays, chosen with an equal probability; that is, there is a 50% chance that it is the first item of array A and 50% chance that it is the first item from array B. 

 - Likewise, each successive item in the shuffled array is, with equal probability, the next available item of A or B.

`demo_shuffle.c` demonstrates the function on an array of integers 1-20 and an array of Greek letter names.

**How many riffles are needed to properly shuffle the array?**

`quality.c` demonstrates this by calculating the average shuffle quality on an array of length 50

> Note: Define the quality of a shuffle as the fraction of times the second item of two adjacent items is larger than the first. Thus the sorted array {0, 1, 2, 3, 4, 5, 6} has a quality 6/6 = 1 because every item after the first is greater than the previous one; that is 1 > 0, 2 > 1, 3 > 2, 4 > 3, 5>4and6>5. Ontheotherhand,thearray{1, 4, 2, 3, 6, 5, 0}hasaquality3/6=0.5 because the pairs (1,4),(2,3),(3,6) have the second element greater than the first, but the other pairs (4, 2), (6, 5), (5, 0) do not. A well-shuffled array will have a quality close to 0.5.


## Beggar My Neighbour (a card game)

This uses our above implementation of the Riffle Shuffle to play and output a demonstartion of the game Beggar My Neighbour

> In the card game beggar-your-neighbour, a standard 52-card deck is dealt to the players. Each player places their cards face down on the table. The first player lays down her top card face up, and the next player plays her top card, face up, on it. This continues for each player in turn until a penalty card (Jack, Queen, King or Ace) is laid.

> If a player plays a penalty card the next player has to pay a penalty by laying down additional cards: 4 cards for an Ace, 3 for a King, 2 cards for a Queen and 1 for a Jack. When the penalty has been paid the player who laid the penalty card takes all the cards in the pile and places them under her cards. Play continues with the player following the player who picked up the cards, who lays a new card face up. However, if the player who is paying the penalty turns up a penalty card herself, then her payment ceases and the next player in turn must pay the penalty indicated by the new penalty card.

> A player leaves the game when they have no cards left and the game is won by the player who eventually has all the cards.

It might be possible that a game of beggar-your-neighbour goes on forever because the cards keep being passed back and forth between the players. Whether an infinite game exists is an open question

`byn.c` he maximum number of players and the number of trials and looks at the shortest, longest and average game lengths to dig into this question

