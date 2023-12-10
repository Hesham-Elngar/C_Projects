#ifndef TIC_TAC_c
#define TIC_TAC_c
#include "tic_tac.h"

static uint8_t board[][MAX_SIZE]={{'1','2','3'},
                                   {'4','5','6'},
                                   {'7','8','9'}
                                   };

static uint8_t Player=PLAYER1_TURN;
static uint8_t numberOfTurns=0;
static char playerOfX[50];
static char playerOfO[50];

/***********************Helper Functions Declarations*********************/
static void start_game(uint8_t arr[][MAX_SIZE]);
static void play_single_mode(uint8_t arr[][MAX_SIZE]);
static void AI_turn(uint8_t arr[][MAX_SIZE]);
static void Game_Rules();
static void enter_players_names();
static void swap_player();
static uint8_t Play_Again();
static return_status is_empty(uint8_t arr[][MAX_SIZE],uint32_t cell);
static uint32_t input_cell_postion(uint8_t arr[][MAX_SIZE]);
static void board_init(uint8_t arr[][MAX_SIZE]);
static void print_Board(uint8_t arr[][MAX_SIZE]);
static return_status check_for_winner(uint8_t arr[][MAX_SIZE]);
static return_status check_column(uint8_t arr[][MAX_SIZE]);
static return_status check_diagonal(uint8_t arr[][MAX_SIZE]);
static return_status check_row(uint8_t arr[][MAX_SIZE]);
static return_status Is_Full(uint8_t arr[][MAX_SIZE]);
static void loading_bar();


/**************************Function Definitions**************************/

/*Function to start game in multi player mode*/
static void start_game(uint8_t arr[][MAX_SIZE])
{
    enter_players_names();
    board_init(arr);
    while(1)
    {
        print_Board(arr);
        input_cell_postion(arr);
        if(check_for_winner(arr))
        {
            print_Board(arr);
            switch(Player)
            {
            case 1:
                printf("congratulations ,%s,you are the winner !! \n",playerOfX);
                break;
            case 2:
                printf("congratulations ,%s,you are the winner !! \n",playerOfO);
                break;
            }
            if(Play_Again())
            {
                start_game(arr);
            }
            else
            {
                main_menu();
                break;
            }
        }
        else if(Is_Full(arr))
        {
            printf("D R A W !!\n");
            if(Play_Again())
            {
                start_game(arr);
            }
            else
            {
                main_menu();
                break;
            }
        }
        numberOfTurns++;
        swap_player();
    }
}

/*Function to start game in single player mode*/
static void play_single_mode(uint8_t arr[MAX_SIZE][MAX_SIZE])
{
    board_init(arr);
    char user_name[50];
    printf("ENTER YOUR NAME :");
    scanf(" %[^\n]s",user_name);
    strcpy(playerOfX,user_name);
    while(1)
    {
        print_Board(arr);
        if(Player==PLAYER1_TURN)
        {
            input_cell_postion(arr);
        }
        else if(Player==PLAYER2_TURN)
        {
            AI_turn(arr);
        }
        if(check_for_winner(arr))
        {
             switch(Player)
            {
            case 1:
                print_Board(arr);
                printf("congratulations ,%s,you are the winner !! \n",user_name);
                break;
            case 2:
                print_Board(arr);
                printf("HARD LUCK,%s...AI HAS WON !! \n",user_name);
                break;
            }
             if(Play_Again())
            {
                play_single_mode(arr);
            }
            else
            {
                main_menu();
                break;
            }
        }
        else if(Is_Full(arr))
        {
            printf("D R A W !!\n");

            if(Play_Again())
            {
                play_single_mode(arr);
            }
            else
            {
               main_menu();
                break;
            }
        }
        numberOfTurns++;
        swap_player();
        system("cls");
    }
}

/*Function to make AI moves in single* mode/
static void AI_turn(uint8_t arr[][MAX_SIZE])
{
    /*Check for a winning move for AI or block any way for user to win*/
    for(uint8_t row_counter=ROW_START_INDEX; row_counter<MAX_SIZE; row_counter++)
    {
        for(uint8_t col_counter=COL_START_INDEX; col_counter<MAX_SIZE; col_counter++)
        {
            if(arr[row_counter][col_counter]==' ')
            {
                arr[row_counter][col_counter]=PLAYER2_SYMBOL;
                if(check_for_winner(arr))
                {
                    return;
                }
                arr[row_counter][col_counter]=' ';
                arr[row_counter][col_counter]=PLAYER1_SYMBOL;
                if(check_for_winner(arr))
                {
                    arr[row_counter][col_counter]=PLAYER2_SYMBOL;
                    return;
                }
                arr[row_counter][col_counter]=' ';
            }
        }
    }
    /*If no winning or blocking way, make a random move*/
     for(uint8_t row_counter=0; row_counter<MAX_SIZE; row_counter++)
    {
        for(uint8_t col_counter=0; col_counter<MAX_SIZE; col_counter++)
        {
            if(arr[row_counter][col_counter]==' ')
            {
                arr[row_counter][col_counter]=PLAYER2_SYMBOL;
                return;
            }
        }
    }
}

/*static function to help users to be aware of the rules of the game*/
static void Game_Rules()
{
    //int *ptr;
    int32_t x=-1;
    printf("PLEASE MAKE YOUR CHOICE \n");
    printf("[1] THE SYMBOL OF EVERY TEAM \n[2] WINNIG CONDITIONS  \n");
    scanf("%d",&x);
    if(1==x)
    {
        printf("PLAYER%d PLAYS WITH SYMBOL 'X' \nPLAYER%d PLAYS WITH SYMBOL 'O'\n",PLAYER1_TURN,PLAYER2_TURN);

    }
    else if(2==x)
    {
        printf("WINNIG CONDITIONS ARE : \n");
        printf("=> Horizontal Wins: A player wins if they have three of their symbols (either X or O) in a row horizontally.\n\
=>Vertical Wins: A player wins if they have three of their symbols in a column vertically.\n\
=>Diagonal Wins: A player wins if they have three of their symbols diagonally.\n");
    }
    else
    {
        printf("invalid number,please try again:\n");
        Game_Rules();
    }
    printf("================================================================\n");
}


/*static function to take turn between the two players*/
static void enter_players_names()
{
    printf("PLEASE ENTER THE NAME OF PLAYER OF [X] SYMBOL :");
    scanf(" %[^\n]s",playerOfX);
    printf("PLEASE ENTER THE NAME OF PLAYER OF [O] SYMBOL :");
    scanf(" %[^\n]s",playerOfO);
    printf("\n\n");
}

static void swap_player()
{
    if(PLAYER1_TURN==Player) Player=PLAYER2_TURN;
    else if(PLAYER2_TURN==Player) Player=PLAYER1_TURN;
}

static uint8_t Play_Again()
{
    numberOfTurns=0;
    Player=PLAYER1_TURN;
    uint8_t choice;
    printf("ARE YOU WANT TO PLAY AGIAN?\n");
    printf("[1]-YES\n");
    printf("[0]-NO\n");
    scanf("%d", &choice);
    return choice;
}

/*static function to check if the board is empty or not*/
static return_status is_empty(uint8_t arr[][MAX_SIZE],uint32_t cell)
{
    return_status ret =r_nok;
    if(Player==PLAYER1_TURN)
    {
        switch(cell)
        {
        case 1:
            cell=arr[0][0];
            break;
        case 2:
            cell=arr[0][1];
            break;
        case 3:
            cell=arr[0][2];
            break;
        case 4:
            cell=arr[1][0];
            break;
        case 5:
            cell=arr[1][1];
            break;
        case 6:
            cell=arr[1][2];
            break;
        case 7:
            cell=arr[2][0];
            break;
        case 8:
            cell=arr[2][1];
            break;
        case 9:
            cell=arr[2][2];
            break;
        }
    }
    else if(Player==PLAYER2_TURN)
    {
        switch(cell)
        {
        case 1:
            cell=arr[0][0];
            break;
        case 2:
            cell=arr[0][1];
            break;
        case 3:
            cell=arr[0][2];
            break;
        case 4:
            cell=arr[1][0];
            break;
        case 5:
            cell=arr[1][1];
            break;
        case 6:
            cell=arr[1][2];
            break;
        case 7:
            cell=arr[2][0];
            break;
        case 8:
            cell=arr[2][1];
            break;
        case 9:
            cell=arr[2][2];
            break;
        }
    }
    if(cell==' ')
    {
        ret=r_ok;
    }
    return ret;
}


/*static function that lets players to choose the cell and check if input number is suitable or not*/
static uint32_t input_cell_postion(uint8_t arr[][MAX_SIZE])
{
    int32_t x=-1;
    switch(Player)
    {
    case 1:
        printf(" %s <X>,ENTER CELL POSTION(1:9):\n",playerOfX);
        break;
    case 2:
        printf(" %s <O>,ENTER CELL POSTION(1:9):\n",playerOfO);
        break;
    }

    scanf("%d",&x);
    if(x>SQUARE(MAX_SIZE)||x<=0)
    {
        printf("invalid number,please try again:\n");
        x= input_cell_postion(arr);
    }
    if(!(is_empty(arr,x)))
    {
        printf("this cell is already occupied,please try again :\n");
        x=input_cell_postion(arr);
    }
    else
    {
        switch(Player)
        {
        case 1:
            printf(" %s <X>,ENTER CELL POSTION(1:9):\n",playerOfX);
            break;
        case 2:
            printf(" %s <O>,ENTER CELL POSTION(1:9):\n",playerOfO);
            break;
        }
        if(Player==PLAYER1_TURN)
        {
            switch(x)
            {
            case 1:
                arr[0][0]='X';
                break;
            case 2:
                arr[0][1]='X';
                break;
            case 3:
                arr[0][2]='X';
                break;
            case 4:
                arr[1][0]='X';
                break;
            case 5:
                arr[1][1]='X';
                break;
            case 6:
                arr[1][2]='X';
                break;
            case 7:
                arr[2][0]='X';
                break;
            case 8:
                arr[2][1]='X';
                break;
            case 9:
                arr[2][2]='X';
                break;
            }
        }
        else if(Player==PLAYER2_TURN)
        {
            switch(x)
            {
            case 1:
                arr[0][0]='O';
                break;
            case 2:
                arr[0][1]='O';
                break;
            case 3:
                arr[0][2]='O';
                break;
            case 4:
                arr[1][0]='O';
                break;
            case 5:
                arr[1][1]='O';
                break;
            case 6:
                arr[1][2]='O';
                break;
            case 7:
                arr[2][0]='O';
                break;
            case 8:
                arr[2][1]='O';
                break;
            case 9:
                arr[2][2]='O';
                break;
            }
        }
    }system("cls");  /*built in function using to clear screen at once*/
    return x;
}


/*this function to initialize the board to start the game*/
static void board_init(uint8_t arr[][MAX_SIZE])
{
    for(uint32_t row_counter=ROW_START_INDEX; row_counter<MAX_SIZE; row_counter++)
    {
        for(uint32_t col_counter=COL_START_INDEX; col_counter<MAX_SIZE; col_counter++ )
        {
            arr[row_counter][col_counter]=' ';
        }
    }
}

/*this function to display the board for user*/
static void print_Board(uint8_t arr[][MAX_SIZE])
{
    for(uint32_t row_counter=ROW_START_INDEX; row_counter<MAX_SIZE;row_counter++)
    {
        printf("\t\t\t\t\t\t");
        for(uint32_t col_counter=COL_START_INDEX; col_counter<MAX_SIZE; col_counter++)
        {
            printf("%c ",arr[row_counter][col_counter]);
            if(col_counter!=2)
            {
                printf("| ");
            }
        }
        if(row_counter!=2)
            printf("\n\t\t\t\t\t\t----------\n");
    }
    printf("\n");
}

/*this function to check who is the winner*/
static return_status check_for_winner(uint8_t arr[][MAX_SIZE])
{
    return_status ret=r_nok;
    if(check_column(arr)||check_row(arr)||check_diagonal(arr))
    {
        ret=r_ok;
    }

    return ret;
}


/*static function to check on winning conditions in columns*/
static return_status check_column(uint8_t arr[][MAX_SIZE])
{
    return_status ret=r_nok;
    if(arr[0][0]=='X'&&arr[1][0]=='X'&&arr[2][0]=='X')      ret=r_ok;
    else if(arr[0][0]=='O'&&arr[1][0]=='O'&&arr[2][0]=='O') ret=r_ok;
    else if(arr[0][1]=='X'&&arr[1][1]=='X'&&arr[2][1]=='X') ret=r_ok;
    else if(arr[0][1]=='O'&&arr[1][1]=='O'&&arr[2][1]=='O') ret=r_ok;
    else if(arr[0][2]=='X'&&arr[1][2]=='X'&&arr[2][2]=='X') ret=r_ok;
    else if(arr[0][2]=='O'&&arr[1][2]=='O'&&arr[2][2]=='O') ret=r_ok;
    return ret;
}

/*static function to check on winning conditions in rows*/
static return_status check_row(uint8_t arr[][MAX_SIZE])
{
    return_status ret=r_nok;
    if(arr[0][0]=='X'&&arr[0][1]=='X'&&arr[0][2]=='X')      ret=r_ok;
    else if (arr[0][0]=='O'&&arr[0][1]=='O'&&arr[0][2]=='O') ret=r_ok;
    else if(arr[1][0]=='X'&&arr[1][1]=='X'&&arr[1][2]=='X')  ret=r_ok;
    else if(arr[1][0]=='O'&&arr[1][1]=='O'&&arr[1][2]=='O')  ret=r_ok;
    else if(arr[2][0]=='X'&&arr[2][1]=='X'&&arr[2][2]=='X')  ret=r_ok;
    else if(arr[2][0]=='O'&&arr[2][1]=='O'&&arr[2][2]=='O')  ret=r_ok;
    return ret;
}


/*static function to check on winning conditions in diagonals*/
static return_status check_diagonal(uint8_t arr[][MAX_SIZE])
{
    return_status ret=r_nok;
    if      (arr[0][0]=='X'&&arr[1][1]=='X'&&arr[2][2]=='X') ret=r_ok;
    else if (arr[0][0]=='O'&&arr[1][1]=='O'&&arr[2][2]=='O') ret=r_ok;
    else if (arr[0][2]=='X'&&arr[2][0]=='X'&&arr[1][1]=='X') ret=r_ok;
    else if (arr[0][2]=='O'&&arr[2][0]=='O'&&arr[1][1]=='O') ret=r_ok;
    return ret;
}


static void loading_bar()
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


/*static function to check on drawing condition*/
static return_status Is_Full(uint8_t arr[][MAX_SIZE])
{
    return_status ret=r_ok;
        for(uint32_t row_counter=ROW_START_INDEX; row_counter<MAX_SIZE;row_counter++)
    {
        for(uint32_t col_counter=COL_START_INDEX; col_counter<MAX_SIZE; col_counter++)
        {
            if(arr[row_counter][col_counter]==' ')
            {
                ret=r_nok;
                break;
            }
        }
    }
    return ret;
}
/*Entry Function to start game*/
void main_menu()
{
    printf("\n\n\t\t\t\t======================TIC TAC TOE======================\n\n");
    printf("\t\t\t\t\t\t\tWELCOME !! \n\n");
    while(1)
    {
    printf("[1]-MULTI PLAYER\n");
    printf("[2]-SINGLE PLAYER\n");
    printf("[3]-HELP\n");
    printf("[4]-EXIT GAME\n");
    printf("Make Your Choice:");
    uint8_t choice;
    scanf("%d",&choice);
    switch(choice)
    {
    case 1:
        loading_bar();
         printf("Multi player mode selected...\n");
         start_game(board);
         break;
    case 2:
        loading_bar();
        printf("Single player mode selected...\n");
        play_single_mode(board);
        break;
    case 3:
        Game_Rules();
        break;
    case 4:
        printf("GOOD BYE...\n");
        exit(0);
    default:
        printf("Invalid choice. Try again.\n");
    }
    }
}





#endif // TIC_TAC_c
