#include <stdio.h>
#include <stdlib.h>
#include "voting.h"
int32_t _choice=-1;

int main()
{
    loading_bar();
    printf("\n");
    printf("\t\t\t\t\tWELCOME IN VOTING SYSTEM\n");
    printf("THE VOTING SYSTEM IS ABOUT THE BEST PROGRAMMING LANGUAGE\n");
    init_choices(theLanguages);
    do
    {
        printf("\n\n [1] - Cast the Vote");
        printf("\n [2] - Find Vote Count");
        printf("\n [3] - Find leading Candidate");
        printf("\n [0] - Exit");

        printf("\n\n Please enter your choice : ");
        scanf("%d", &_choice);
        system("cls");

        switch(_choice)
        {
        case 1:
            castVote();
            break;
        case 2:
            votesCount();
            break;
        case 3:
            getLeadingLanguage();
            break;
        case 0:
            Good_Bye();
            break;
        default:
            printf("\n Error: Invalid Choice,Please try again\n");
            starting_vote();
        }
    }
    while(_choice);

    return 0;
}
