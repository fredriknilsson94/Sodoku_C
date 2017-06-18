#include <stdlib.h>
#include <stdio.h>

#include "sodoku.h"

int ** Create_Puzzle(void)
{
    int ** puzzel;
    int array [9][9] = {{0, 8, 0,   0, 4, 6,    2, 0, 0},
                        {3, 2, 4,   1, 0, 0,    0, 0, 5},
                        {1, 5, 0,   2, 0, 0,    0, 0, 0},

                        {2, 0, 9,   6, 0, 0,    4, 0, 0},
                        {0, 7, 0,   0, 0, 0,    0, 1, 0},
                        {0, 0, 8,   0, 0, 1,    5, 0, 3},

                        {0, 0, 0,   0, 0, 5,    0, 6, 4},
                        {7, 0, 0,   0, 0, 4,    8, 9, 2},
                        {0, 0, 2,   8, 6, 0,    0, 5, 0}};

    puzzel = (int**)malloc(sizeof(int*)*9);

    int row, col;

    for (row = 0; row < 9; row++)
    {
        puzzel[row] = (int*)malloc(sizeof(int)*9);

        for (col = 0; col < 9; col++)
        {
            puzzel[row][col] = array[row][col];
        }
    }

    return puzzel;
}

void Print_Puzzel(int ** puzzel)
{
    int row, col;

    for (row = 0; row < 9; row++)
    {
        if (row % 3 == 0 )
        {
            printf("-----------------------\n");
        }

        for (col = 0; col < 9; col++)
        {
            if (col % 3 == 0)
            {
                printf("|");
            }

            printf(" %d", puzzel[row][col]);
        }

        printf(" |\n");
    }

    printf("-----------------------\n\n");
}

void Print_Puzzel_Boxes(Box puzzel_boxes)
{
    int row, col;

    for (row = 0; row < 9; row++)
    {
        if (row % 3 == 0 )
        {
            printf("-----------------------\n");
        }

        for (col = 0; col < 9; col++)
        {
            if (col % 3 == 0)
            {
                printf("|");
            }

            printf(" %d", puzzel_boxes[row][col].value);
        }

        printf(" |\n");
    }

    printf("-----------------------\n\n");
}

Box Generate_Puzzel_Boxes(int** puzzel)
{
    Box boxes;

    boxes = (Box)malloc(sizeof(aBox*)*9);

    int row, col;

    for (row = 0; row < 9; row++)
    {
        boxes[row] = (aBox*)malloc(sizeof(aBox)*9);

        for (col = 0; col < 9; col++)
        {
            /* If the box is locked */
            if (puzzel[row][col] != 0)
            {
                boxes[row][col].locked = 1;
                boxes[row][col].value = puzzel[row][col];
            }
            else
            {
                boxes[row][col].locked = 0;
                boxes[row][col].value = 0;
            }

            boxes[row][col].row = row;
            boxes[row][col].col = col;

            /* Decide which square the box is associated with */
            if (row < 3 & col < 3)
            {
                boxes[row][col].square = 1;
            }
            else if (row < 3 & col > 2 & col < 6)
            {
                boxes[row][col].square = 2;
            }
            else if (row < 3 & col > 5)
            {
                boxes[row][col].square = 3;
            }
            else if (row > 2 & row < 6 & col < 3)
            {
                boxes[row][col].square = 4;
            }
            else if (row > 2 & row < 6 & col > 2 & col < 6)
            {
                boxes[row][col].square = 5;
            }
            else if (row > 2 & row < 6 & col > 5)
            {
                boxes[row][col].square = 6;
            }
            else if (row > 5 & col < 3)
            {
                boxes[row][col].square = 7;
            }
            else if (row > 5 & col > 2 & col < 6)
            {
                boxes[row][col].square = 8;
            }
            else if (row > 5 & col > 5)
            {
                boxes[row][col].square = 9;
            }
        }
    }

    return boxes;
}

void Solve_Puzzel(Box puzzel_boxes)
{
    int row, col, legal, backing;

    row = 0;
    col = 0;
    backing = 0;

    while (row < 9)
    {
        while (col < 9)
        {
            /* Check if we the box "is empty" */
            if (puzzel_boxes[row][col].locked)
            {
                if (backing)
                {
                    if (col == 0)
                    {
                        printf("Backing up a row\n");
                        col = 8;
                        row--;
                    }
                    else
                    {
                        col--;
                    }

                    continue;
                }
            }
            else
            {
                /* Inits the legality variable */
                legal = 0;

                backing = 0;

                Print_Puzzel_Boxes(puzzel_boxes);

                printf("Entering [%d][%d]\n", row, col);

                while (legal == 0)
                {
                    /* If it is the first time visiting the box, set it to 1 */
                    if (puzzel_boxes[row][col].value == 0)
                    {
                        puzzel_boxes[row][col].value = 1;
                    }
                    /* Otherwise increase it by 1 */
                    else if (puzzel_boxes[row][col].value < 9)
                    {
                        //printf("Incrementing the value by 1\n");
                        puzzel_boxes[row][col].value++;
                    }
                    /* Back up ones box and start again */
                    else
                    {
                        printf("Backing one box\n");

                        puzzel_boxes[row][col].value = 0;

                        if (col == 0)
                        {
                            printf("Back up a row\n");
                            col = 8;
                            row--;
                        }
                        else
                        {
                            col--;
                        }

                        legal = 0;
                        backing = 1;

                        break;
                    }

                    /* Now check if the value is legit */
                    legal = Legal_Value(puzzel_boxes, row, col,
                                            puzzel_boxes[row][col].square);
                    printf("Box[%d][%d]\n", row, col);
                    printf("Legal value: %d\n", legal);
                    Print_Puzzel_Boxes(puzzel_boxes);
                } /* End while legal */
            }

            printf("backing: %d\n", backing);

            if (!backing)
            {
                printf("Incremeting col\n");
                col++;
            }

        } /* End while col */

        if (!backing)
        {
            printf("Incremeting row\n");
            row++;
            col = 0;
        }

    } /* End while row */
}

int Legal_Value(Box puzzel_boxes, int myRow, int myCol, int mySquare)
{
    /* Assume legal number in the box */
    int res = 1;

    //printf("Entered Legal_Value[%d][%d]\n", myRow, myCol);

    int value = puzzel_boxes[myRow][myCol].value;
    //printf("Check value: %d\n", value);

    /* Start by checking the row */
    int col;

    for (col = 0; col < 9; col++)
    {
        /* Dont check ourselves or unsigned boxes */
        if (col == myCol || puzzel_boxes[myRow][col].value == 0)
        {
            continue;
        }
        /* If we find the same value in the row its a unlegal value */
        if (puzzel_boxes[myRow][col].value == value)
        {
            //printf("[%d][%d] stops it (ROW)\n", myRow, col);
            res = 0;
        }
    }

    /* Checking the column */
    int row;

    for (row = 0; row < 9; row++)
    {
        /* Dont check ourselves or unsigned boxes */
        if (row == myRow || puzzel_boxes[row][myCol].value == 0)
        {
            continue;
        }
        /* If we find the same value in the column its a unlegal value */
        if (puzzel_boxes[row][myCol].value == value)
        {
            //printf("[%d][%d] stops it (COL)\n", row, myCol);
            res = 0;
        }
    }

    /* Check the square */
    for (row = 0; row < 9; row++)
    {
        for (col = 0; col < 9; col++)
        {
            /* Dont check ourselves or unsigned boxes */
            if ((row == myRow && col == myCol) ||
                puzzel_boxes[row][col].value == 0)
            {
                continue;
            }

            if (puzzel_boxes[row][col].square == mySquare)
            {
                if (puzzel_boxes[row][col].value == value)
                {
                    //printf("[%d][%d] stops it (SQU)\n", row, col);
                    res = 0;
                }
            }
        }
    }

    return res;
}

int main(void)
{
    /* Initilize the original puzzel */
    int ** puzzel_orig;
    puzzel_orig = Create_Puzzle();

    /* Print the puzzel in the terminal */
    Print_Puzzel(puzzel_orig);

    /* Creates a pointer to the puzzel, now as a structres of boxes */
    Box box_pointer;
    box_pointer = Generate_Puzzel_Boxes(puzzel_orig);

    Solve_Puzzel(box_pointer);

    printf("\n--- Final solution ---\n");
    Print_Puzzel_Boxes(box_pointer);

    return 0;
}
