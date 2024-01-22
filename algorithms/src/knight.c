/******************************************************************************
 *	Author:    Yuval
 *	Reviewer :
 *	Date:
 ******************************************************************************/

#include <assert.h> /* assert */
#include <stdlib.h> /* malloc */
#include <stdio.h>
#include <time.h>
#include "knight.h"
#include "bitarray.h"
#include "utiles.h"

#define FALSE (0)
#define TRUE (1)
#define BOARD_SIZE (8)
#define NUM_OF_MOVES (8)
#define TOPOS(i,j) ((i*BOARD_SIZE + j))
#define GETI(pos) (pos / BOARD_SIZE)
#define GETJ(pos) (pos % BOARD_SIZE)
#define I (0)
#define J (1)
/******************************************************************************
 *							 DECLRATION								  *
 ******************************************************************************/
static status_t StaticKnightTour(int *path, bitarray_t map, int pos_i, int pos_j, time_t time, int lut[][2]);



/******************************************************************************
 *							 FUNCTIONS 										  *
 ******************************************************************************/

status_t KnightTour(int *path, int start_position)
{
    bitarray_t b_arr = 0;
    time_t start_time = time(NULL);

    struct moves
    {
        i;
        j;
        counter;
    }m0 = {-2,1,0},m1 = {-2,-1,0},m2 = {-1,2,0},m3 = {-1,-2,0},
     m4 = {1,2,0},m5 = {1,-2,0},m6 = {2,-1,0},m7 = {2,1,0};

    struct moves table[8] = {m0,m1,m2,m3,m4,m5,m6,m7};

    return StaticKnightTour(path ,b_arr, GETI(start_position), GETJ(start_position), start_time, table);


}
 


/******************************************************************************
 *							Static FUNCTIONS 								  *
 ******************************************************************************/


int isVaildPosition(int pos_i, int pos_j, bitarray_t b_arr)
{

    if (pos_i > (BOARD_SIZE -1)|| pos_i < 0 || pos_j < 0 || pos_j > (BOARD_SIZE-1))
    {
        return FALSE;
    }

    if (BitArrayGetVal(b_arr, TOPOS(pos_i,pos_j)) == 1)
    {
        return FALSE;
    }
    
    return TRUE;
}




static status_t StaticKnightTour(int *path, bitarray_t map, int pos_i, int pos_j, time_t time, struct move table[8])
{
    int runner = 0;
    status_t status = 1; 
    bitarray_t full_map = ~0;
    

    map = BitArraySetBit(map, TOPOS(pos_i,pos_j) ,1);

    if (map != full_map)
    {
        while(runner < NUM_OF_MOVES && status != SUCCESS)
        {
            if(isVaildPosition(pos_i + lut[0][runner][0],pos_j + lut[0][runner][1], map) == TRUE)
            { 
                status  = StaticKnightTour(path + 1, map ,pos_i + lut[0][runner][0], 
                                            pos_j + lut[0][runner][1], time , lut);
            }
            ++runner;
        }
        if (status != SUCCESS)
        {
            return DEAD_END;
        }   
    }
    *path = TOPOS(pos_i, pos_j);
    return SUCCESS;
}

void UpdateLUT(int lut[][8][2], bitarray_t map, int pos_i, int pos_j,struct moves table[])
{
    int moves_runner = 0;
    int in_move_runner = 0;
    int this_move = 0;
    int new_pos_i = 0;
    int new_pos_j = 0;
    for (moves_runner = 0 ; moves_runner < NUM_OF_MOVES ; ++moves_runner)
    {
        new_pos_i = pos_i + (table[moves_runner])->x;
        new_pos_j = pos_j + (table[moves_runner])->y;

        for (in_move_runner = 0 ; in_move_runner < NUM_OF_MOVES ; ++in_move_runner)
        {
            if (isVaildPosition(pos_i + lut[0][in_move_runner][I],pos_j + lut[0][in_move_runner][J], map) == TRUE)
            {
                ++lut[1][in_move_runner][I];
                ++lut[1][in_move_runner][J];     
            }
        }  
    }


    return TRUE;
}
