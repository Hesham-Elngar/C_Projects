#include"voting.h"

/**********************HELPER FUNCTIONS DEFINTIONS*********************/
static uint32_t numberOfSubmissions=0;

static uint32_t max_counter(choice* x[],uint32_t n)
{
    uint32_t max=x[0]->counter;
    for(uint32_t i=CPP_INDEX; i<n; i++)
    {
        if(x[i]->counter>max) max=x[i]->counter;
    }
    return max;
}

static uint32_t max_index(choice* x[],uint32_t n)
{
    uint32_t max=x[0]->counter;
    uint32_t index=C_INDEX;
    for(uint32_t i=CPP_INDEX; i<n; i++)
    {
        if(x[i]->counter>max) index=i;
    }
    return index;
}

/**********************MAIN FUNCTION DEFINTIONS*********************/
void init_choices(choice* x[])
{
    for(int index=C_INDEX; index<NUMBER_OF_LANGUAGES; index++)
    {
        choice *ptr=(choice*)malloc(sizeof(choice));
        ptr->counter=0;
        ptr->result=0.0;
        if(index==C_INDEX)
        {
            strcpy(ptr->language,"C");
            x[C_INDEX]=ptr;
        }
        if(index==CPP_INDEX)
        {
            strcpy(ptr->language,"CPP");
            x[CPP_INDEX]=ptr;
        }
        if(index==JAVA_INDEX)
        {
            strcpy(ptr->language,"JAVA");
            x[JAVA_INDEX]=ptr;
        }
        if(index==PYTHON_INDEX)
        {
            strcpy(ptr->language,"PYTHON");
            x[PYTHON_INDEX]=ptr;
        }
    }
}

void display_choices(choice *x[])
{
    for(uint32_t i=C_INDEX; i<NUMBER_OF_LANGUAGES; i++)
    {
        printf("[%i] - %s\n",i+1,x[i]->language);
    }
}

void make_your_choice(choice *x[])
{
    printf("PLEASE ENTER THE NAME OR THE NUMBER OF FAVOURITE PROGRAMMING LANGUAGE : \n");
    char user_choice[LANGUAGE_SIZE];
    scanf(" %[^\n]s",user_choice);
    int num=atoi(user_choice);
    strupr(user_choice);
    uint32_t flag=0;
    for(uint32_t i=C_INDEX; i<NUMBER_OF_LANGUAGES; i++)
    {
        if(!strcmp(user_choice,x[i]->language)||num==(i+1))
        {
            (x[i]->counter)++;
            ++numberOfSubmissions;
            flag=1;
            printf("you have voted for %s\n",x[i]->language);
            //system("cls");
        }
    }
    if(!flag)
    {
        printf("TNVALID CHOICE ,PLEASE TRY AGAIN\n");
        make_your_choice(x);
    }
}

void calculating_votes(choice* x[],uint32_t numberOfSubmissions)
{
    for(int i=C_INDEX; i<NUMBER_OF_LANGUAGES; i++)
    {
        printf("%d\n",x[i]->counter);
        x[i]->result=PERCTENTANGE((x[i]->counter),((float)numberOfSubmissions));
    }
}

void display_results(choice* x[])
{
    for(uint32_t i=C_INDEX; i<NUMBER_OF_LANGUAGES; i++)
    {
        printf("%s LANGUAGE %.1f%%\n",x[i]->language,x[i]->result);
    }
}

void check_for_winner(choice* x[])
{
    uint32_t mx_counter=max_counter(x,NUMBER_OF_LANGUAGES);
    uint32_t mx_index=max_index(x,NUMBER_OF_LANGUAGES);
    uint32_t numberOfWinners=0;
    uint32_t indicies[NUMBER_OF_LANGUAGES];
    uint32_t index=0;
    choice *arrOfWinners[NUMBER_OF_LANGUAGES];
    for(int i=C_INDEX; i<=PYTHON_INDEX; i++)
    {
        if(mx_counter==x[i]->counter)
        {
            arrOfWinners[numberOfWinners++]=x[i];
            indicies[index++]=i;
        }
    }
    printf("\t\t\t\t\t=========================\n\t\t\t\t\t");
    if(numberOfWinners==CPP_INDEX)
    {
        switch(indicies[0])
        {
        case C_INDEX:
            printf("C LANGUAGE IS THE BEST\n");
            break;
        case CPP_INDEX:
            printf("CPP LANGUAGE IS THE BEST\n");
            break;
        case JAVA_INDEX:
            printf("JAVA LANGUAGE IS THE BEST\n");
            break;
        case PYTHON_INDEX:
            printf("PYTHON LANGUAGE IS THE BEST\n");
            break;
        }
    }
    else if(numberOfWinners==C_INDEX)
    {
        printf("THE VOTING SYSTEM HASN'T BEEN STARTED YET\n");
    }
    else if(numberOfWinners>C_INDEX&&numberOfWinners<=PYTHON_INDEX)
    {
        for(int i=0; i<index; i++)
        {
            printf("%s ",x[indicies[i]]->language);
            if(i!=index-1) printf("&& ");
        }
        printf("ARE THE BEST LANGUAGES\n");

    }
    else
    {
        printf("ALL LANGUAGES HAS THS SAME POPULARITY\n");
    }
    printf("\t\t\t\t\t=========================\n\t\t\t\t\t");

}

void loading_bar()
{
    char a=177;
    char b =219;
    system("cls");
    printf("\t\t\t\t\t\tPLEASE WAIT...\n");
    for(int i=0; i<26; i++)
        printf("%c",a);
    printf("\t\t");

    for(int i=0; i<30; i++)
    {
        printf("%c",b);
        Sleep(20);
    }
    system("cls");
}

void Good_Bye()
{
    printf("\t\t\t\tGOOD BYE...PLEASE PRESS ANY BUTTON TO EXIT \n");
    return 0;
}

void castVote()
{
    display_choices(theLanguages);
    make_your_choice(theLanguages);
}

void votesCount()
{
    loading_bar();
    calculating_votes(theLanguages,numberOfSubmissions);
    display_results(theLanguages);
}

void getLeadingLanguage()
{
    loading_bar();
    check_for_winner(theLanguages);

}


void starting_vote()
{
    int32_t _choice =-1;
    do
    {
        printf("\n\n [1] - Cast the Vote");
        printf("\n [2] - Find Vote Count");
        printf("\n [3] - Find leading LANGUAGE");
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
            printf("\n Error: Invalid Choice");
        }
    }
    while(_choice);
}
