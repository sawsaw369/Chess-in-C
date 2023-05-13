#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define board_size 8

char chess_board[board_size][board_size] = 
{
    {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'},
    {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
    {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'},
};

struct coords
{
    char piece;
    int column;
    int row;
};

void print_board ();
void print_current_player (int current_player);
void choose_piece (int current_player);
void choose_move (int current_player, struct coords start);
void fill_move (struct coords start, struct coords end);

int validate_pawn_move (struct coords start, struct coords end);
int validate_rook_move (struct coords start, struct coords end);
int validate_nite_move (struct coords start, struct coords end);
int validate_bishop_move (struct coords start, struct coords end);
int validate_queen_move (struct coords start, struct coords end);
int validate_king_move (struct coords start, struct coords end);

int main ()
{
    printf("\n\n+---------------------------------------+\n");
    printf("|                                       |\n");
    printf("|           Two player Chess            |\n");
    printf("|              by sawyer                |\n");
    printf("|                                       |\n");
    printf("+---------------------------------------+\n\n");

    printf("\nRandomizing player who goes first...\n");
    
    srand (time(NULL));

    int current_player = rand() % 2;
    if (current_player % 2)
    {
        printf("Red will start\n\n");
    } 
    else
    {
        printf("Blue will start\n\n");
    }

    int is_ready = 0;
    while (!is_ready)
    {
        printf("RULES:\n");
        printf("Do\n");

        printf("\nReady to start? (y/n)\n");
        char response;
        scanf(" %1c", &response);
        
        if (response == 'y')
        {
            is_ready++;

            while (1)
            {
                print_board ();

                print_current_player (current_player);

                choose_piece (current_player);
                
                current_player++;
            }
        }
    }
}

void print_board ()
{
    int offset = 1;
    int last_row = board_size - offset;

    printf("\n    +---+---+---+---+---+---+---+---+\n    | \033[0;32ma\033[0m | \033[0;32mb\033[0m | \033[0;32mc\033[0m | \033[0;32md\033[0m | \033[0;32me\033[0m | \033[0;32mf\033[0m | \033[0;32mg\033[0m | \033[0;32mh\033[0m |");

    for (int i = 0; i <= last_row; i++)
    {
        printf("\n+---+---+---+---+---+---+---+---+---+---+\n| \033[0;32m%d\033[0m |", board_size - i);
    
        for (int j = 0; j <= last_row; j++)
        {
            if (chess_board[last_row - i][j] > 'A' && chess_board[last_row - i][j] < 'Z')
            {
                printf(" \033[0;31m%c\033[0m |", chess_board[last_row - i][j]); 
            }
            else
            {
                printf(" \033[0;34m%c\033[0m |", chess_board[last_row - i][j]);
            }
        }

        printf(" \033[0;32m%d\033[0m |", board_size - i);
    }

    printf("\n+---+---+---+---+---+---+---+---+---+---+\n    | \033[0;32ma\033[0m | \033[0;32mb\033[0m | \033[0;32mc\033[0m | \033[0;32md\033[0m | \033[0;32me\033[0m | \033[0;32mf\033[0m | \033[0;32mg\033[0m | \033[0;32mh\033[0m |\n    +---+---+---+---+---+---+---+---+\n");
}

void print_current_player (int current_player)
{
    if (current_player % 2)
    {
        printf("\nRED'S TURN\n");
    }
    else
    {
        printf("\nBLUE'S TURN\n");
    }
}

struct coords get_coordinate ()
{
    char column_letter;
    int row;
    scanf(" %1c%1d", &column_letter, &row);
    
    int offset = 1;


    struct coords result = {chess_board[row - offset][column_letter - 'a'], column_letter - 'a', row - offset};
    return result;
}

void choose_piece (int current_player)
{
    int is_piece_valid = 0;
    while (!is_piece_valid)
    {
        printf("\nEnter the spot of the piece you want to move:\n");

        struct coords start = get_coordinate ();

        if (((start.piece == 'p' || start.piece == 'r' || start.piece == 'n' || start.piece == 'b' || start.piece == 'q' || start.piece == 'k') && current_player % 2 == 0) || ((start.piece == 'P' || start.piece == 'R' || start.piece == 'N' || start.piece == 'B' || start.piece == 'Q' || start.piece == 'K') && current_player % 2 == 1))
        {
            is_piece_valid++;

            choose_move (current_player, start);
        }
        else
        {
            print_board ();

            printf("\nINVALID PIECE\n");

            print_current_player (current_player);
        }
    }
}

void choose_move (int current_player, struct coords start)
{
    int is_move_valid = 0;
    
    while (!is_move_valid)
    {
        printf("\nEnter the spot where you want to move your piece:\n");

        struct coords end = get_coordinate();

        char spot_chosen = chess_board[end.row][end.column];

        if (start.piece == 'p' || start.piece == 'P')
        {
            is_move_valid = validate_pawn_move (start, end);
        }
        else if (start.piece == 'r' || start.piece == 'R')
        {
            is_move_valid = validate_rook_move (start, end);
        }
        else if (start.piece == 'n' || start.piece == 'N')
        {
            is_move_valid = validate_nite_move (start, end);
        }
        else if (start.piece == 'b' || start.piece == 'B')
        {
            is_move_valid = validate_bishop_move (start, end);
        } 
        else if (start.piece == 'q' || start.piece == 'Q')
        { 
            is_move_valid = validate_queen_move (start, end);
        }
        else
        {
            is_move_valid = validate_king_move (start, end);
        }

        if (!is_move_valid)
        {
            printf("\nINVALID MOVE\n");

            printf("\nWould you like to pick a different piece to move? (y/n)\n");
            char response;
            scanf(" %c", &response);

            if (response == 'y')
            {
                is_move_valid = 1;

                print_board();

                print_current_player(current_player);

                choose_piece(current_player);
            }
            else
            {
                print_board();
            }
        }
    }
}

void fill_move (struct coords start, struct coords end)
{
    chess_board[end.row][end.column] = start.piece;
    chess_board[start.row][start.column] = ' ';
}

int validate_pawn_move (struct coords start, struct coords end)
{
    int offset = 1;
    if (start.piece == 'p')
    {
        if ((end.piece == ' ' && start.column == end.column && start.row - end.row == offset)
        || (end.piece != ' ' && abs(end.column - start.column) == offset && start.row - end.row == offset && chess_board[end.row][end.column] > 'A' && chess_board[end.row][end.column] < 'Z'))
        {
            if (end.row == 0)
            {
                chess_board[end.row][end.column] = 'q';
            }
            else
            {
                chess_board[end.row][end.column] = start.piece;
            }
        }
        else if (end.piece == ' ' && chess_board[end.row + 1][end.column] == ' ' && start.column == end.column && start.row - end.row == offset * 2 && start.row == board_size - (offset * 2))
        {
            chess_board[end.row][end.column] = start.piece;
        }
        else
        {
            return 0;
        }
    }
    else if (start.piece == 'P')
    {
        if ((end.piece == ' ' && end.column == start.column && end.row - start.row == offset) 
        || (end.piece != ' ' && abs(end.column - start.column) == offset && end.row - start.row == offset && end.piece > 'a' && end.piece < 'z'))
        {
            if (end.row == board_size - offset)
            {
                chess_board[end.row][end.column] = 'Q';
            }
            else
            {
                chess_board[end.row][end.column] = start.piece;
            }
        }
        else if (end.piece == ' ' && chess_board[end.row - 1][end.column] == ' ' && start.column == end.column && end.row - start.row == offset * 2 && start.row == offset)
        {
            chess_board[end.row][end.column] = start.piece;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        return 0;
    }

    chess_board[start.row][start.column] = ' ';
    return 1;
}

int validate_rook_move (struct coords start, struct coords end)
{
    if ((start.piece == 'R' && end.piece > 'A' && end.piece < 'Z') 
    || (start.piece == 'r' && end.piece > 'a' && end.piece < 'z'))
    {
        return 0;
    }

    int start_index, end_index;
    if (start.row == end.row)
    {
        if (start.column < end.column)
        {
            start_index = start.column;
            end_index = end.column;
        }
        else
        {
            start_index = end.column;
            end_index = start.column;
        }
        
        for (int i = start_index + 1; i < end_index; i++)
        {
            if (chess_board[end.row][i] != ' ')
            {
                return 0;
            }
        }
    }
    else if (start.column == end.column)
    {
        if (start.row < end.row) 
        {
            start_index = start.row;
            end_index = end.row;
        } 
        else 
        {
            start_index = end.row;
            end_index = start.row;
        }

        for (int i = start_index + 1; i < end_index; i++)
        {
            if (chess_board[i][end.column] != ' ')
            {
                return 0;
            }
        }
    }
    else
    {
        return 0;
    }

    fill_move (start, end);
    return 1;
}

int validate_nite_move (struct coords start, struct coords end)
{
    if ((start.piece == 'N' && end.piece > 'A' && end.piece < 'Z') 
    || (start.piece == 'n' && end.piece > 'a' && end.piece < 'z'))
    {
        return 0;
    }

    int column_distance = abs(end.column - start.column), row_distance = abs(end.row - start.row);

    if ((column_distance == 2 && row_distance == 1) || (column_distance == 1 && row_distance == 2)) 
    {
        fill_move (start, end);
        return 1;
    } 

    return 0;
}

int validate_bishop_move (struct coords start, struct coords end) 
{
    if ((start.piece == 'B' && end.piece > 'A' && end.piece < 'Z') 
    || (start.piece == 'b' && end.piece > 'a' && end.piece < 'z'))
    {
        return 0;
    }

    int row_distance = abs (end.row - start.row), column_distance = abs (end.column - start.column);
    if (row_distance != column_distance)
    {
        return 0;
    }

    int row_step, column_step;
    if (end.row > start.row) 
    {
        row_step = 1;
    } 
    else 
    {
        row_step = -1;
    }

    if (end.column > start.column) 
    {
        column_step = 1;
    }
    else 
    {
        column_step = -1;
    }

    for (int i = start.row + row_step, j = start.column + column_step; i != end.row; i += row_step, j += column_step) 
    {
        if (chess_board[i][j] != ' ')
        {
            return 0;
        }
    }

    fill_move (start, end);
    return 1;
}

int validate_queen_move (struct coords start, struct coords end)
{
    if ((start.piece == 'Q' && end.piece > 'A' && end.piece < 'Z') 
    || (start.piece == 'q' && end.piece > 'a' && end.piece < 'z'))
    {
        return 0;
    }

    int row_distance = abs(end.row - start.row), column_distance = abs(end.column - start.column);
    if (row_distance != 0 && column_distance != 0 && row_distance != column_distance) 
    {
        return 0;
    }

    int row_step = 0, column_step = 0;
    if (end.row > start.row) 
    {
        row_step = 1;
    } 
    else if (end.row < start.row) 
    {
        row_step = -1;
    }
    if (end.column > start.column) 
    {
        column_step = 1;
    } 
    else if (end.column < start.column) 
    {
        column_step = -1;
    }
    
    for (int i = start.row + row_step; i != end.row; i += row_step) 
    {
        for (int j = start.column + column_step; j != end.column; j += column_step) 
        {
            if (chess_board[i][j] != ' ') 
            {
                return 0;
            }
        }
    }

    fill_move (start, end);
    return 1;
}

int validate_king_move (struct coords start, struct coords end)
{
    if ((start.piece == 'K' && end.piece > 'A' && end.piece < 'Z') 
    || (start.piece == 'k' && end.piece > 'a' && end.piece < 'z'))
    {
        return 0;
    }

    int row_distance = abs (end.row - start.row), column_distance = abs (end.column - start.column);
    if (row_distance > 1 || column_distance > 1)
    {
        return 0;
    }

    fill_move (start, end);
    return 1;
}
