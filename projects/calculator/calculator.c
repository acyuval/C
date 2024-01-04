/******************************************************************************
*	Author:    Yuval 
*	Reviewer : 
*	Date:      
******************************************************************************/

#include <assert.h> /* assert */
#include <stdlib.h>
#include <string.h>

#include "stack.h"
#include "utiles.h"
#include "calculator.h"


/******************************************************************************
*							 DECLRATION								  * 
******************************************************************************/

typedef enum State
{
    WAITING_FOR_NUM = 0, 
    WAITING_FOR_OP, 
    INVALID, 
    STATE_END
}State;


typedef enum Input
{
    ANY_OTHER = 0,
    DIGITS, 
    OPERATORS, 
    OPEN_PARAN,
    CLOSE_PARAN,
    TERMINATE,
    NUM_OF_INPUTS
}Input;

typedef struct statechange 
{
    const Input in;
    const State out;
}statechange;

typedef struct FSM 
{
    const State state;
    void (*Action)(void *, void *, void *);
    const statechange table[NUM_OF_INPUTS];
}FSM;

/******************************************************************************
*							 FUNCTIONS 										  * 
******************************************************************************/
int Calculate(const char * expression , double * result)
{
    State cur_state = WAITING_FOR_NUM;
    size_t expre_len = strlen(expression); 
    stack_t * stack_ops = StackCreate(expre_len, sizeof(double));
    stack_t * nums_stack = StackCreate(expre_len, sizeof(double));
    enum Input in = ANY_OTHER;

    const FSM fsm[] =
    {
    { WAITING_FOR_NUM,  &number_func,       {{DIGITS,WAITING_FOR_OP}, {OPEN_PARAN,WAITING_FOR_NUM}, {CLOSE_PARAN,INVALID},          {OPERATORS,INVALID},        {ANY_OTHER,INVALID }, {TERMINATE,INVALID}}},
    { WAITING_FOR_OP,   &operation_func,    {{DIGITS,INVALID},        {OPEN_PARAN,INVALID},         {CLOSE_PARAN,WAITING_FOR_OP},   {OPERATORS,WAITING_FOR_NUM},{ANY_OTHER,INVALID }, {TERMINATE,STATE_END}}},
    { INVALID,          &invalid_func,      {{DIGITS,INVALID},        {OPEN_PARAN,INVALID},         {CLOSE_PARAN,INVALID},          {OPERATORS,INVALID},        {ANY_OTHER,INVALID }, {TERMINATE,INVALID}}},
    { STATE_END,        &Show,              {{DIGITS,STATE_END},      {OPEN_PARAN,STATE_END},       {CLOSE_PARAN,STATE_END},        {OPERATORS,STATE_END},      {ANY_OTHER,STATE_END },{TERMINATE,STATE_END}}},
    };


    while(cur_state != INVALID) 
    {   
        double token = strtod(expression, &expression);
        fsm[cur_state].Action(expression);
        cur_state = fsm[cur_state].table[in].out;
    }   

}
    



/******************************************************************************
*							STATIC FUNCTIONS								  * 
******************************************************************************/
static void BuildStatesLUT()
{

}

static int NumberFunc(void *ptr, void *nums_stack)
{
     
}
static int OperatorFunc(void *ptr, void *operator_stack)
{
     
}

static int InvalidFunc(void *ptr, void *nums_stack, void *nums_stack)
{
    (void)ptr;
    printf("INVALID!!!"); 
}
