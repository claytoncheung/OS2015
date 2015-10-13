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
	  // initialize each question struct and assign it to the questions array
	strcpy(questions[0].category, categories[0]); strcpy(questions[0].question,""); strcpy(questions[0].answer,""); questions[0].value=200; questions[0].answered=false;
	strcpy(questions[1].category, categories[0]); strcpy(questions[1].question, ""); strcpy(questions[1].answer, ""); questions[1].value=400; questions[1].answered=false;
	strcpy(questions[2].category, categories[0]); strcpy(questions[2].question, ""); strcpy(questions[2].answer, ""); questions[2].value=600; questions[2].answered=false;
	strcpy(questions[3].category, categories[0]); strcpy(questions[3].question, ""); strcpy(questions[3].answer, ""); questions[3].value=800; questions[3].answered=false;
	
	strcpy(questions[4].category, categories[1]); strcpy(questions[4].question, ""); strcpy(questions[4].answer, ""); questions[4].value=200; questions[4].answered=false;
	strcpy(questions[5].category, categories[1]); strcpy(questions[5].question, ""); strcpy(questions[5].answer, ""); questions[5].value=400; questions[5].answered=false;
	strcpy(questions[6].category, categories[1]); strcpy(questions[6].question, ""); strcpy(questions[6].answer, ""); questions[6].value=600; questions[6].answered=false;
	strcpy(questions[7].category, categories[1]); strcpy(questions[7].question, ""); strcpy(questions[7].answer, ""); questions[7].value=800; questions[7].answered=false;
	
	strcpy(questions[8].category, categories[2]); strcpy(questions[8].question, ""); strcpy(questions[8].answer, ""); questions[8].value=200; questions[8].answered=false;
	strcpy(questions[9].category, categories[2]); strcpy(questions[9].question, ""); strcpy(questions[9].answer, ""); questions[9].value=400; questions[9].answered=false;
	strcpy(questions[10].category, categories[2]); strcpy(questions[10].question, ""); strcpy(questions[10].answer, ""); questions[10].value=600; questions[10].answered=false;
	strcpy(questions[11].category, categories[2]); strcpy(questions[11].question, ""); strcpy(questions[11].answer, ""); questions[11].value=800; questions[11].answered=false;	
}

// Displays each of the remaining categories and question dollar values that have not been answered
void display_categories(void)
{
    // print categories and dollar values for each unanswered question in questions array
	int i;	
	printf("Category\tValue");
	for(i=0;i<NUM_QUESTIONS;i++) {
		if (questions[i].answered==false)	{
			printf("%s\t $%d", questions[i].category, questions[i].value);
		}
	}
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
	char *correctAnswer = questions[qNum].answer;
	
	if (strcmp(correctAnswer, answer) == 0)
		return true;
	else
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
