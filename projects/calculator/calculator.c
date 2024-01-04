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
    S_WAITING2NUM = 0, 
    S_WAITING2OP, 
    S_INVALID, 
    NUM_OF_STATES
}State;

typedef enum EVENTS
{
    E_DIGITS = 0,
    E_PLUS,
    E_MINUS, 
    E_MULTI,
    E_DIV, 
    E_OPEN_PARAN,
    E_CLOSE_PARAN,
    E_TERMINATE,
    E_ANY_OTHER,
    NUM_OF_EVENTS
}EVENTS;

typedef struct params 
{
    stack_t * ops_stack;
    stack_t * nums_stack;
    char * expression;
    EVENTS char2ENUM[256];
    operations op2func[NUM_OF_EVENTS];
    double * result;
}params;

typedef State (*operations)(params *);


static int Exit(params * params_struct);
/******************************************************************************
*							 FUNCTIONS 										  * 
******************************************************************************/
int Calculate(const char * expression , double * result)
{
    State state = S_WAITING2NUM;
    size_t expre_len = strlen(expression); 
    int status = 0; 
    char * this_char = expression;
    stack_t * ops_stack = StackCreate(expre_len, sizeof(double));
    stack_t * nums_stack = StackCreate(expre_len, sizeof(double));
    EVENTS change2ENUM[256] = {E_ANY_OTHER};
    operations op2func[256] = {NULL};
    operations OperationVSEvent[NUM_OF_STATES][NUM_OF_EVENTS] = {Exit};
    params params = {ops_stack, nums_stack , this_char, change2ENUM, op2func ,result};
    
    status = InitChangeToEnums(change2ENUM);
    status = InitOP2Func(op2func);
    status = InitOperationVSEvent2Func(OperationVSEvent);

    while(state != S_INVALID) 
    {   
        operations this_operation = OperationVSEvent[state][Change2ENUM[*this_char]];
        state = this_operation(&params);
    }   

}
    



/******************************************************************************
*							STATIC FUNCTIONS								  * 
******************************************************************************/
static int InitChangeToEnums(EVENTS * CHANGE2ENUM)
{
    int status = 0; 
    int i = 0; 
    EVENTS LUT[256] = {E_ANY_OTHER};
    
    for(i = 30; i< 40 ; i ++)
    {
         LUT[i] = E_DIGITS;
    }
    
    LUT['*'] =  E_MULTI;
    LUT['/'] =  E_DIV;
    LUT['+'] =  E_PLUS;
    LUT['-'] =  E_MINUS;
    LUT['('] =  E_OPEN_PARAN;
    LUT[')'] =  E_CLOSE_PARAN;
    
    status = memcpy(CHANGE2ENUM, &LUT, sizeof(LUT));
    return status;
}



static int InitOP2Func(operations * OP2Func)
{
   int status = 0; 
   operations LUT[NUM_OF_EVENTS] = {NULL,Add, Substract, Multi, Divide , NULL , NULL , NULL,NULL};
   
    status = memcpy(OP2Func,&LUT, sizeof(LUT));
    return status;
}

static int InitOperationVSEvent2Func(operations ** OperationVSEvent)
{
   int status = 0; 
   operations LUT[NUM_OF_STATES][NUM_OF_EVENTS] = {{PushDigit, Invalid,Invalid,Invalid,Invalid,PushOBracket, Invalid,Invalid,Invalid},
                                                    {Invalid, NumHandler,OPHandler,OPHandler,OPHandler,Invalid, Invalid,CloseBracket,Invalid},
                                                    {Exit, Exit,Exit,Exit,Exit,Exit, Exit,Exit,Exit}};
                                                    
   
    status = memcpy(OperationVSEvent,&LUT, sizeof(LUT));
    return status;
}

static int PushDigit(params * params_struct)
{
    double num = 0;
    num = strtod(params_struct->expression, params_struct->expression);
    StackPush(params_struct->nums_stack, (const void *)&num);
}


static int NumHandler(params * params_struct)
{
    double num = 0;
    num = strtod(params_struct->expression, params_struct->expression);
    StackPush(params_struct->nums_stack, &num);
}


static int OPHandler(params * params_struct)
{
    EVENTS operator  = params_struct->char2ENUM[*(params_struct->expression)];
    StackPush(params_struct->ops_stack, &operator);
    
}

static int Add(params * params_struct)
{
     
}


static int END(params * params_struct)
{
     
}

static int Substract(params * params_struct)
{
     
}

static int Divide(params * params_struct)
{
     
}

static int Multi(params * params_struct)
{
     
}
static int Exit(params * params_struct)
{
     
}

static int PushOBracket(params * params_struct)
{
     
}

static int CloseBracket(params * params_struct)
{
     
}

static int PushCBracket(params * params_struct)
{
     
}
static int IN(params * params_struct)
{
     
}

static int Invalid(params * params_struct)
{
    (void)params_struct;
    printf("INVALID!!!"); 
}

static int Show(params_struct)
{
    (void)params_struct;

    printf("result!!!"); 
}
