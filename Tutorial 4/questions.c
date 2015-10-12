/*
 * Tutorial 4 Jeopardy Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, <GROUP MEMBERS>
 * All rights reserved.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "questions.h"


// Initializes the array of questions for the game
void initialize_game(void)
{
	questions[0].category="Programming"; questions[0].question=""; questions[0].answer=""; questions[0].value=200; questions[0].answered=false;
	questions[1].category="Programming"; questions[1].question=""; questions[1].answer=""; questions[1].value=400; questions[1].answered=false;
	questions[2].category="Programming"; questions[2].question=""; questions[2].answer=""; questions[2].value=600; questions[2].answered=false;
	questions[3].category="Programming"; questions[3].question=""; questions[3].answer=""; questions[3].value=800; questions[3].answered=false;
	
	questions[4].category="Algorithms"; questions[4].question=""; questions[4].answer=""; questions[4].value=200; questions[4].answered=false;
	questions[5].category="Algorithms"; questions[5].question=""; questions[5].answer=""; questions[5].value=400; questions[5].answered=false;
	questions[6].category="Algorithms"; questions[6].question=""; questions[6].answer=""; questions[6].value=600; questions[6].answered=false;
	questions[7].category="Algorithms"; questions[7].question=""; questions[7].answer=""; questions[7].value=800; questions[7].answered=false;
	
	questions[8].category="Databases"; questions[8].question=""; questions[8].answer=""; questions[8].value=200; questions[8].answered=false;
	questions[9].category="Databases"; questions[9].question=""; questions[9].answer=""; questions[9].value=400; questions[9].answered=false;
	questions[10].category="Databases"; questions[10].question=""; questions[10].answer=""; questions[10].value=600; questions[10].answered=false;
	questions[11].category="Databases"; questions[11].question=""; questions[11].answer=""; questions[11].value=800 questions[11].answered=false;
    // initialize each question struct and assign it to the questions array
}

// Displays each of the remaining categories and question dollar values that have not been answered
void display_categories(void)
{
    // print categories and dollar values for each unanswered question in questions array
	int i=0;	
	printf("Category\tValue")
	for(i=0;i<NUM_QUESTIONS;i++)
		if questions[i].answered=false{
			printf("%s\t $%d", questions[i].category, questions[i].value);
		}
}

// Displays the question for the category and dollar value
void display_question(char *category, int value)
{

}

// Returns true if the answer is correct for the question for that category and dollar value
bool valid_answer(char *category, int value, char *answer)
{
    // Look into string comparison functions
    return false;
}

// Returns true if the question has already been answered
bool already_answered(char *category, int value)
{
    // lookup the question and see if it's already been marked as answered
    return false;
}
