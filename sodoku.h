#ifndef SODOKU_H
#define SODOKU_H

typedef struct
{
    /* Value of the box */
    int value;
    /* Describes which row the box is in (1-9) */
    int row;
    /* Describes which column the box is in (1-9) */
    int col;
    /* Is the box a pre-set number */
    int locked;
    /* Describes which square the box is in (1-9) */
    int square;
} aBox;

typedef aBox** Box;

int ** Create_Puzzle(void);

void Print_Puzzel(int ** puzzel);

void Print_Puzzel_Boxes(Box puzzel_boxes);

Box Generate_Puzzel_Boxes(int** puzzel);

void Solve_Puzzel(Box puzzel_boxes);

int Legal_Value(Box puzzel_boxes, int myRow, int myCol, int mySquare);

#endif
