#ifndef __KNIGHT_TOUR_H__
#define __KNIGHT_TOUR_H__

#include <stddef.h> /*  size_t  */



typedef enum
{
	SUCCESS = 0,
    TIME_OUT,
    DEAD_END
} status_t;


/******************************************************************************
 * Description: Finds a Path of a knight that traverses all squares in the 
 *              chessboard each exactly once.
 * Arguments:   path - an 8x8 matrix to which the solution steps will be written
 *              start_posiotion - random point from which the solution will start
 * Return Value: status code:  
 *                  SUCCESS - Valid solution was found in 5 minutes
 *                  TIME_OUT - No solution was found in 5 minutes
 * Time Complexity: O(8^(n^2))
 * Space Complexity: O(n)
 * Notes:   path and start_position should not be NULL and must have
 *          suffitient allocation, undefined behavior otherewise.
 ******************************************************************************/
status_t KnightTour(int *path, int start_position);
 


/******************************************************************************
 * Description: Finds a Path of a knight that traverses all squares in the 
 *              chessboard each exactly once.
 * Arguments:   path - an 8x8 matrix to which the solution steps will be written
 *              start_posiotion - random point from which the solution will start
 * Return Value: status code:  
 *                  SUCCESS - Valid solution was found in 5 minutes
 *                  TIME_OUT - No solution was found in 5 minutes
 * Time Complexity: O(8^(n^2))
 * Space Complexity: O(n)
 * Notes:   path and start_position should not be NULL and must have
 *          suffitient allocation, undefined behavior otherewise.
 ******************************************************************************/
status_t KnightTourWarnsdorff(int *path, int *start_position);
 

#endif /* __KNIGHT_TOUR_H__ */