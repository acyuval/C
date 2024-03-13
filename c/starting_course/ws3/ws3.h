/******************************************************************************
*	Author:    Yuval 
*	Reviewer : 
*	Date:      
******************************************************************************/

/* to accsess any element of 2d arr can use arr[i][j] */
void Get2DArr(int arr[][10]);

/* to accsess any element of 2d arr can use *(arr+i)[j] */

void Sum2DArr(int (*arr)[3], int *result, size_t row_no, size_t col_no);

/* to accsess any element of 2d arr can use *(*arr+i)+j) */
int GetPtrOfPtrs(int **arr);

/* this function will list all c datatype and thier sizes*/
void ListOfDataTypes(void);

/* this function will recive envirment variables and print them in lower case */
void PrintAllEnvp(const char ** env);


int Jusephus();
/* this function will return 1 if a number is a power of 2*/
int isPowerOf2(int number);

