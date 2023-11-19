/******************************************************************************
*	Author:    Yuval 
*	Reviewer : Igal
*	Date:      
******************************************************************************/

#ifndef __WS6_H__
#define __WS6_H__


/* this function return x*2^y   */
long pow2(unsigned int x, unsigned int y);

/* this function return 1 if n is a power of 2 using loop  */
unsigned int checkPower2Loop(unsigned int n);

/* this function return 1 if n is a power of 2 using bitwise  */
unsigned int checkPower2BitWise(unsigned int n);

/* this function return n +1 using bitwise  */
unsigned int addOne(int n);

/* this function print the numbers in arr that has 3 bits on  */
int checkArrayFor3Bits(unsigned int arr[],int size);

/* this function preform a bit miror to num */
unsigned int byteMirorBitWise(unsigned int num);

/* this function preform a bit miror to num */
unsigned int byteMirorLoop(unsigned int n);

/* this function return 1 if ch has 2nd and 6th bits on  */
int check2and6BitsAnd(unsigned char ch);

/* this function return 1 if ch has 2nd or 6th bits on  */
unsigned char check2and6BitsOr(unsigned char ch);

/* this function preform swap of 3rd and 5th bits in ch  */
unsigned char Swap3and5Bits(unsigned char ch);

/* this function return 1 if number is devided in 16 with no reminder   */
unsigned int checkDevisionBy16(unsigned int num);

/* this function preform swap of two var with no exptra var   */
unsigned int SwapTwoVarNoTemp(unsigned int A ,unsigned int B);

/* this function counts the number of set bits in number   */
int CountNumberOfSetBitsLoop(int number);

/* this function counts the number of set bits in number   */
int CountNumberOfSetBitsBitWise(int number);

/* this function prints a binary represintion of float number    */
void PrintFloatToBinary(float number);


#endif /*	WS6_H        	*/
