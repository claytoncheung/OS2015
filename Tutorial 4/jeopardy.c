/*
 * Tutorial 4 Jeopardy Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, Clayton Cheung, James Morrison, Asmy Sarasan, Malek Mustapha-Abdullah
 * All rights reserved.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "questions.h"
#include "players.h"
#include "jeopardy.h"

// Put macros or constants here using #define
#define BUFFER_LEN 256
#define NUM_PLAYERS 4

// Put global environment variables here

// Processes the answer from the user containing what is or who is and tokenizes it to retrieve the answer.
void tokenize(char *input, char **tokens);

// Displays the game results for each player, their name and final score, ranked from first to last place
void show_results(player *players, int num_players);


int main(int argc, char *argv[])
{
    // An array of 4 players, may need to be a pointer if you want it set dynamically
    player players[NUM_PLAYERS];
	
	//Variable to hold index of random player to go first
	int randPlayer=0;
    char *categChoice = NULL;
	categChoice = (char *) calloc(256, sizeof(char));
	int valueChoice;
	bool qAnswered=false;
	char *playerAnswer = NULL;
	playerAnswer = (char *) calloc(256,sizeof(char));
	
    // Input buffer and and commands
    char buffer[BUFFER_LEN] = { 0 };

    // Display the game introduction and initialize the questions
    initialize_game();

    // Prompt for players names
    printf("Please enter the player names (1 name per line): \n");

    // initialize each of the players in the array
    scanf("%s %s %s %s",players[0].name,players[1].name,players[2].name,players[3].name);
	
	//Initialize scores to 0
	player[0].score=0;
	player[1].score=0;
	player[2].score=0;
	player[3].score=0;

    // Perform an infinite loop getting command input from users until game ends
    while (fgets(buffer, BUFFER_LEN, stdin) != NULL)
    {
		// Call functions from the questions and players source files
	    // Execute the game until all questions are answered

		//Randomly selects a player
		randPlayer = (rand()%4);
		
		
		while (qAnswered==true) {	//Check if selection has been answered already
			display_categories();	//Shows all available categories
		
			printf("%s! Please select a category:\n", players[randPlayer].name);
			scanf("%s", &categChoice);
			printf("Please select a value:\n");
			scanf("%d", &valueChoice);
			
			qAnswered=alreadyAnswered(categChoice,valueChoice);
			
			if (qAnswered==false){
				display_question(categChoice, valueChoice);
			}
			else if (qAnswered==true){
				printf("This question has been answered already. Please select another.");
			}
		}
		
		scanf("%s", &playerAnswer);
		//tokenize and compare here
		//check that the answer starts with "what is" or "who is"

        // Display the final results and exit
    }
	
	free(categChoice);
	free(playerAnswer);
    return EXIT_SUCCESS;
}
