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
#include "questions.h"


// Initializes the array of questions for the game
void initialize_game(void)
{
	  // initialize each question struct and assign it to the questions array
	strcpy(questions[0].category, categories[0]); strcpy(questions[0].question,"Name a loop type that starts with F: "); strcpy(questions[0].answer,"for loop"); questions[0].value=200; questions[0].answered=false;
	strcpy(questions[1].category, categories[0]); strcpy(questions[1].question, "This language is an example for object oriented programming: "); strcpy(questions[1].answer, "Java"); questions[1].value=400; questions[1].answered=false;
	strcpy(questions[2].category, categories[0]); strcpy(questions[2].question, "In the C programming language, what code is used to open a file: "); strcpy(questions[2].answer, "fopen"); questions[2].value=600; questions[2].answered=false;
	strcpy(questions[3].category, categories[0]); strcpy(questions[3].question, "These are variable that store memory address information of other variables: "); strcpy(questions[3].answer, "pointers"); questions[3].value=800; questions[3].answered=false;
	
	strcpy(questions[4].category, categories[1]); strcpy(questions[4].question, "This method of analysis is used to find the Big O of Merge sort: "); strcpy(questions[4].answer, "recursive"); questions[4].value=200; questions[4].answered=false;
	strcpy(questions[5].category, categories[1]); strcpy(questions[5].question, "This method is used to prove our algorithm is true (2 words): "); strcpy(questions[5].answer, "loop invariants"); questions[5].value=400; questions[5].answered=false;
	strcpy(questions[6].category, categories[1]); strcpy(questions[6].question, "This is a search function that has a recursive algorithm where a = 1 but b = 2: "); strcpy(questions[6].answer, "binary search"); questions[6].value=600; questions[6].answered=false;
	strcpy(questions[7].category, categories[1]); strcpy(questions[7].question, "The final step in checking the correctness of an algorithm is: "); strcpy(questions[7].answer, "termination"); questions[7].value=800; questions[7].answered=false;
	
	strcpy(questions[8].category, categories[2]); strcpy(questions[8].question, "The word for unique entry used to access each table:"); strcpy(questions[8].answer, "key"); questions[8].value=200; questions[8].answered=false;
	strcpy(questions[9].category, categories[2]); strcpy(questions[9].question, "This is the name of a key that can be used to access an outside table: "); strcpy(questions[9].answer, "foreign key"); questions[9].value=400; questions[9].answered=false;
	strcpy(questions[10].category, categories[2]); strcpy(questions[10].question, "In formal relational model, a row is called : "); strcpy(questions[10].answer, "tuple"); questions[10].value=600; questions[10].answered=false;
	strcpy(questions[11].category, categories[2]); strcpy(questions[11].question, "In formal relational model, a column is called : "); strcpy(questions[11].answer, "attribute"); questions[11].value=800; questions[11].answered=false;	
}

// Displays each of the remaining categories and question dollar values that have not been answered
void display_categories(void)
{
    // print categories and dollar values for each unanswered question in questions array
	int i;	
	printf("Category\tValue");
	for(i=0;i<NUM_QUESTIONS;i++) {
		if (questions[i].answered==false)	{
			printf("%s\t $%d\n", questions[i].category, questions[i].value);
		}
	}
	printf("\n");
}

// Displays the question for the category and dollar value
void display_question(char *category, int value)
{
	int qNum = find_question(category, value);
	printf("For $d, %s", questions[qNum].value, questions[qNum].question);
}

// Returns true if the answer is correct for the question for that category and dollar value
bool valid_answer(char *category, int value, char *answer)
{
    // Look into string comparison functions
	int qNum = find_question(category, value);
	char *correctAnswer = NULL;
	correctAnswer = (char *) calloc(256, sizeof(char));
	strcpy(correctAnswer, questions[qNum].answer);
	
	if (strcmp(correctAnswer, answer) == 0)
		free(correctAnswer);
		return true;
	else
		free(correctAnswer);
		return false;
}

// Returns true if the question has already been answered
bool already_answered(char *category, int value)
{
	// lookup the question and see if it's already been marked as answered
	int q=find_question(category, value);
	
	if (questions[q].answered==true)
		return true;
	else
		return false;
}

//Returns the index of the question given category and value
int find_question(char *category, int value)
{
	int qNum; 						//Used as a placeholder to determine the correct index
	
	if (strcmp(category,"Programming"))
		qNum=0;
	else if (strcmp(category,"Algorithms"))
		qNum=4;
	else if (strcmp(category,"Databases"))
		qNum=8;
	
	if (value==200)
		return qNum;
	else if (value==400)
		qNum +=1;
	else if (value==600)
		qNum +=2;
	else if (value==800)
		qNum +=3;
	
	return qNum;
}
