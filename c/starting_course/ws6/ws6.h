/******************************************************************************
*	Author:    Yuval 
*	Reviewer : Igal
*	Date:      
******************************************************************************/

#ifndef __WS6_H__
#define __WS6_H__


/* this function return x*2^y   */
long Pow2(unsigned int x, unsigned int y);

/* this function return 1 if n is a power of 2 using loop  */
unsigned int CheckPower2Loop(unsigned int n);

/* this function return 1 if n is a power of 2 using bitwise  */
unsigned int CheckPower2BitWise(unsigned int n);

/* this function return n +1 using bitwise  */
unsigned int AddOne(int n);

/* this function print the numbers in arr that has 3 bits on  */
int CheckArrayFor3Bits(unsigned int arr[],int size);

/* this function preform a bit miror to num */
unsigned int ByteMirorBitWise(unsigned int num);

/* this function preform a bit miror to num */
unsigned int ByteMirorLoop(unsigned int n);

/* this function return 1 if ch has 2nd and 6th bits on  */
int Check2and6BitsAnd(unsigned char ch);

/* this function return 1 if ch has 2nd or 6th bits on  */
unsigned char Check2and6BitsOr(unsigned char ch);

/* this function preform swap of 3rd and 5th bits in ch  */
unsigned char Swap3and5Bits(unsigned char ch);

/* this function return the closest lower number that is devided by 16 with no reminder   */
unsigned int CheckDevisionBy16(unsigned int num);

/* this function preform swap of two var with no exptra var   */
unsigned int SwapTwoVarNoTemp(unsigned int A ,unsigned int B);

/* this function counts the number of set bits in number   */
int CountNumberOfSetBitsLoop(int number);

/* this function counts the number of set bits in number   */
int CountNumberOfSetBitsBitWise(int number);

/* this function prints a binary represintion of float number    */
void PrintFloatToBinary(float number);


#endif /*	WS6_H        	*/
