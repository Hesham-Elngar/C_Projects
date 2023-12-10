#ifndef VOTING_H
#define VOTING_H
#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include<windows.h>
#include "std_types.h"

/*========================macro declarations========================*/
#define NUMBER_OF_LANGUAGES 4
#define LANGUAGE_SIZE 50
#define C_INDEX 0
#define CPP_INDEX 1
#define JAVA_INDEX 2
#define PYTHON_INDEX 3

/*========================Function like macros========================*/
#define PERCTENTANGE(X,Y) (X/Y)*100

struct choice
{
    uint32_t counter;
    char language[LANGUAGE_SIZE];
    f4 result;
};
choice* theLanguages[NUMBER_OF_LANGUAGES];

void init_choices(choice* x[]);
void display_choices(choice* x[]);
void make_your_choice(choice* x[]);
void calculating_votes(choice* x[],uint32_t numberOfVoters);
void display_results(choice* x[]);
void check_for_winner(choice* x[]);
void loading_bar();
void votesCount();
void getLeadingLanguage();
void starting_vote();
void Good_Bye();
#endif // VOTING_H

