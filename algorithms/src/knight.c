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

/******************************************************************************
 *							 DECLRATION								  *
 ******************************************************************************/

typedef struct moves
{
    int i;
    int j;
    int counter;
}moves;

static status_t StaticKnightTour(int *path, bitarray_t map, int pos_i, int pos_j, time_t time, moves *table[]);
static void UpdateLUT(moves **table, bitarray_t map, int pos_i, int pos_j);
static int CompareByCounter(const void * arg1,const void * arg2);

/******************************************************************************
 *							 FUNCTIONS 										  *
 ******************************************************************************/

status_t KnightTour(int *path, int start_position)
{
    bitarray_t b_arr = 0;
    time_t start_time = time(NULL);

    moves m0 = {-2,1,0};
    moves m1 = {-2,-1,0};
    moves m2 = {-1,2,0};
    moves m3 = {-1,-2,0};
    moves m4 = {1,2,0};
    moves m5 = {1,-2,0};
    moves m6 = {2,-1,0};
    moves m7 = {2,1,0};

    moves *table[8] = {NULL};

    table[0] = &m0;
    table[1] = &m1;
    table[2] = &m2;
    table[3] = &m3;
    table[4] = &m4;
    table[5] = &m5;
    table[6] = &m6;
    table[7] = &m7;


    return StaticKnightTour(path ,b_arr, GETI(start_position),
                                     GETJ(start_position), start_time, table);


}
 

/******************************************************************************
 *							Static FUNCTIONS 								  *
 ******************************************************************************/


static int isVaildPosition(int pos_i, int pos_j, bitarray_t b_arr)
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




static status_t StaticKnightTour(int *path, bitarray_t map, int pos_i, 
                                    int pos_j, time_t cur_time, moves **table)
{
    int runner = 0;
    status_t status = 1; 
    bitarray_t full_map = ~0;
    if (time(NULL) > cur_time+300)
    {
        return TIME_OUT;
    }

    map = BitArraySetBit(map, TOPOS(pos_i,pos_j) ,1);


    if (map == full_map)
    {
        *path = TOPOS(pos_i, pos_j);
        return SUCCESS;
    }

    while(runner < NUM_OF_MOVES && status != SUCCESS)
    {
        UpdateLUT(table, map, pos_i, pos_j);

        if(table[runner]->counter != -1)
        { 
            status  = StaticKnightTour(path + 1, map ,pos_i+table[runner]->i, 
                                    pos_j+table[runner]->j, cur_time , table);
        }
        ++runner;
    }
    if (status != SUCCESS)
    {
        return DEAD_END;
    }   
    
    *path = TOPOS(pos_i, pos_j);
    return SUCCESS;
}

static void UpdateLUT(moves **table, bitarray_t map, int pos_i, int pos_j)
{
    int moves_runner = 0;
    int in_move_runner = 0;
    int new_pos_i = 0;
    int new_pos_j = 0;
    
    for (moves_runner = 0 ; moves_runner < NUM_OF_MOVES ; ++moves_runner)
    {
        table[moves_runner]->counter = 0;
    }

    for (moves_runner = 0 ; moves_runner < NUM_OF_MOVES ; ++moves_runner)
    {
        new_pos_i = pos_i + table[moves_runner]->i;
        new_pos_j = pos_j + table[moves_runner]->j;
        
        if (isVaildPosition(new_pos_i, new_pos_j, map) != TRUE)
        {
            table[moves_runner]->counter = -1;
            continue;
        }

        map = BitArraySetBit(map, TOPOS(new_pos_i,new_pos_j) ,1);
        for (in_move_runner = 0 ; in_move_runner < NUM_OF_MOVES ; ++in_move_runner)
        {
            if (isVaildPosition(new_pos_i + table[in_move_runner]->i,
                        new_pos_j +table[in_move_runner]->j, map) == TRUE)
            {
                table[moves_runner]->counter += 1;
            }
        }
        map = BitArraySetBit(map, TOPOS(new_pos_i,new_pos_j) ,0);
    }

    qsort(*table, NUM_OF_MOVES , sizeof(moves), CompareByCounter); 
}


static int CompareByCounter(const void * arg1,const void * arg2)
{
    moves * m1 = (moves *)arg1;
    moves * m2 = (moves *)arg2;

    return (((m1)->counter) - ((m2)->counter)); 
}

