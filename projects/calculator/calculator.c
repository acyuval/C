/******************************************************************************
*	Author:    Yuval 
*	Reviewer : 
*	Date:      
******************************************************************************/

#include <assert.h> /* assert */
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

#include "../calculator/stack.h"
#include "../calculator/calculator.h"
#include "../calculator/utiles.h"


/******************************************************************************
*							 DECLRATION								  * 
******************************************************************************/

typedef enum States
{
    S_WAITING4NUM = 0, 
    S_WAITING4OP, 
    S_INVALID, 
    NUM_OF_STATES
}state_t;

typedef enum Events
{
    E_DIGITS = 0,
    E_OPEN_BRACKER,
    E_PLUS,
    E_MINUS, 
    E_MULTI,
    E_DIV, 
    E_POWER,
    E_CLOSE_BRACKET,
    E_TERMINATE,
    E_ANY_OTHER,
    NUM_OF_EVENTS
}events_t;

struct params;
typedef state_t (*handlers)(struct params *);
typedef int (*computation_funcs)(struct params *);

typedef struct params 
{
    stack_t * ops_stack;
    stack_t * nums_stack;
    char * expression;
    events_t * char2ENUM;
    computation_funcs * op2func;
    double * result;
    status_t status; 
}params;

static void InitChangeToEnums(events_t * CHANGE2ENUM);
static void InitStructParmms(params * params, stack_t * ops_stack, stack_t * nums_stack , char * this_char, events_t char2ENUM[256], computation_funcs op2func[NUM_OF_EVENTS], double * result);
static void InitOP2Func(computation_funcs * OP2Func);
static void InitOperationVSEvent2Func(handlers operation_vs_event[][NUM_OF_EVENTS]);
static state_t NumHandler(params * params_struct);
static state_t OPHandler(params * params_struct);
static state_t OpenBracketHandler(params * params_struct);
static state_t CloseBracketHandler(params * params_struct);

static state_t END(params * params_struct);
static state_t Exit(params * params_struct);
static state_t Invalid(params * params_struct);
static state_t Show(params * params_struct);
static state_t Exit(params * params_struct);

static int Power(params * params_struct);
static int Substract(params * params_struct);
static int Add(params * params_struct);
static int Divide(params * params_struct);
static int Multi(params * params_struct);
static int OpenBracketDummy(params * params_struct);

static void ComputeTwoNums(params * params_struct);
static void PopTwoNums(params * params_struct, double nums[]);

/******************************************************************************
*							 FUNCTIONS 										  * 
******************************************************************************/
status_t Calculate(const char * expression , double * result)
{
    state_t state = S_WAITING4NUM;
    
    size_t expre_len = strlen(expression); 
    
    char * string = (char *)expression;

    stack_t * ops_stack = StackCreate(expre_len, sizeof(events_t));
    stack_t * nums_stack = StackCreate(expre_len, sizeof(double));
    
    events_t change2ENUM[256] = {E_ANY_OTHER};
    computation_funcs op2func[256] = {NULL};
    handlers operation_vs_event[NUM_OF_STATES][NUM_OF_EVENTS]= {{Invalid}};

    params params = {0};
    
    InitChangeToEnums(change2ENUM);
    InitOP2Func(op2func);
    InitOperationVSEvent2Func(operation_vs_event);
    InitStructParmms(&params,ops_stack,nums_stack ,string,change2ENUM,op2func,result);

    while(state != S_INVALID) 
    {   
        handlers this_operation = operation_vs_event[state][change2ENUM[*params.expression]];
        state = this_operation(&params);
    }
    return SUCCESS; 
}
    



/******************************************************************************
*							STATIC FUNCTIONS								  * 
******************************************************************************/
static void InitChangeToEnums(events_t * CHANGE2ENUM)
{
    int i = 0; 
    events_t LUT[256] = {E_ANY_OTHER};

    for(i = 30; i< 40 ; i ++)
    {
         LUT[i] = E_DIGITS;
    }
    
    LUT['+'] =  E_PLUS;
    LUT['-'] =  E_MINUS;
    LUT['*'] =  E_MULTI;
    LUT['/'] =  E_DIV;
    LUT['('] =  E_OPEN_BRACKER;
    LUT[')'] =  E_CLOSE_BRACKET;
    LUT['^'] =  E_POWER;
    LUT['\0'] =  E_TERMINATE;
    
    memcpy(CHANGE2ENUM, &LUT, sizeof(LUT));
    return;
}

static void InitStructParmms(params * params, stack_t * ops_stack, stack_t * nums_stack ,char * expression, events_t char2ENUM[256], computation_funcs op2func[NUM_OF_EVENTS], double * result)
{
    params->ops_stack = ops_stack;
    params->nums_stack = nums_stack;
    params->expression = expression;
    params->char2ENUM = char2ENUM;
    params->op2func = op2func;
    params->result = result;
    params->status = SUCCESS;
}

static void InitOP2Func(computation_funcs * op2func)
{
   computation_funcs LUT[NUM_OF_EVENTS] = {NULL,OpenBracketDummy,Add, Substract, Multi, Divide,Power,NULL,NULL,NULL};
   
    memcpy(op2func,&LUT, sizeof(LUT));
    return;
}

static void InitOperationVSEvent2Func(handlers operation_vs_event[][NUM_OF_EVENTS])
{
    handlers LUT[NUM_OF_STATES][NUM_OF_EVENTS] = {{NumHandler,OpenBracketHandler,Invalid,Invalid,Invalid,Invalid,Invalid,Invalid,Invalid,Invalid},
                                                  {Invalid,Invalid,OPHandler,OPHandler,OPHandler,OPHandler,OPHandler,CloseBracketHandler,Show,Invalid},
                                                    {Exit, Exit,Exit,Exit,Exit,Exit,Exit,Exit,Exit,Exit}};
                                                    
   
    memcpy(operation_vs_event,LUT, sizeof(LUT));
    
    return;
}


static state_t NumHandler(params * params_struct)
{
    double num = 0;
    char * to_double = params_struct->expression;
    num = strtod(to_double, &params_struct->expression);
    StackPush(params_struct->nums_stack, &num);
    return S_WAITING4OP;
}


static void ComputeTwoNums(params * params_struct)
{
    events_t poped_op = 0;
    computation_funcs this_function = NULL;

    poped_op = *(events_t *)StackPeek(params_struct->ops_stack);
    
    this_function = params_struct->op2func[poped_op];
    
    this_function(params_struct);
}

static state_t OPHandler(params * params_struct)
{
    events_t operator  = params_struct->char2ENUM[*params_struct->expression];
    events_t prev_opreator = *(events_t *)StackPeek(params_struct->ops_stack);

    while ((FALSE == StackIsEmpty(params_struct->ops_stack)) && operator <= prev_opreator)
    {
        ComputeTwoNums(params_struct);
        prev_opreator = *(events_t *)StackPeek(params_struct->ops_stack);
    }
    StackPush(params_struct->ops_stack, &operator);
    ++(params_struct->expression);
    return S_WAITING4NUM;
}


static state_t OpenBracketHandler(params * params_struct)
{
    events_t operator  = params_struct->char2ENUM[*params_struct->expression];
    StackPush(params_struct->ops_stack, &operator);
    ++(params_struct->expression);
    return S_WAITING4NUM;
}

static state_t CloseBracketHandler(params * params_struct)
{
    events_t operator  = params_struct->char2ENUM[*params_struct->expression];
    events_t prev_opreator = *(events_t *)StackPeek(params_struct->ops_stack);
    while ((FALSE == StackIsEmpty(params_struct->ops_stack)) && prev_opreator != E_OPEN_BRACKER)
    {
        ComputeTwoNums(params_struct);
        prev_opreator = *(events_t *)StackPeek(params_struct->ops_stack);
    }
    StackPop(params_struct->ops_stack);
    ++(params_struct->expression);
    return S_WAITING4OP;
}

static state_t END(params * params_struct)
{
    (void)params_struct;
    return S_INVALID;
}


static int OpenBracketDummy(params * params_struct)
{
    (void)params_struct;
    return 0;
}


static void PopTwoNums(params * params_struct, double nums[])
{
    nums[1] = *(double *)StackPeek(params_struct->nums_stack);
    StackPop(params_struct->nums_stack); 
    nums[2] = *(double *)StackPeek(params_struct->nums_stack);
    StackPop(params_struct->nums_stack); 
}

static int Add(params * params_struct)
{
    double nums[2] = {0};
    double res = 0 ; 

    PopTwoNums(params_struct, nums);
    res = nums[2] + nums[1];
    StackPush(params_struct->nums_stack, &res);
    StackPop(params_struct->ops_stack);
    return 0;
}

static int Power(params * params_struct)
{
    double nums[2] = {0};
    double res = 0 ; 

    PopTwoNums(params_struct, nums);
    res = pow(nums[2],nums[1]);
    StackPush(params_struct->nums_stack, &res);
    StackPop(params_struct->ops_stack);
    return 0;
}

static int Substract(params * params_struct)
{
    double nums[2] = {0};
    double res = 0 ;
    PopTwoNums(params_struct, nums);

    res = nums[2] - nums[1];
    StackPush(params_struct->nums_stack, &res);
    StackPop(params_struct->ops_stack);
    return 0;
}

static int Divide(params * params_struct)
{
    double nums[2] = {0};
    double res = 0 ; 

    PopTwoNums(params_struct, nums);
    res = nums[2] / nums[1];
    StackPush(params_struct->nums_stack, &res);
    StackPop(params_struct->ops_stack);
    return 0;
}

static int Multi(params * params_struct)
{
    double nums[2] = {0};
    double res = 0 ; 

    PopTwoNums(params_struct, nums);
    res = nums[2] * nums[1];
    StackPush(params_struct->nums_stack, &res);
    StackPop(params_struct->ops_stack);
    return res;
}


static state_t Exit(params * params_struct)
{
    (void)params_struct;
    return S_INVALID;
}



static state_t Invalid(params * params_struct)
{
    (void)params_struct;
    printf("INVALID!!!");
    return S_INVALID; 
}

static state_t Show(params * params_struct)
{
    while (FALSE  == StackIsEmpty(params_struct->ops_stack))
    {
        ComputeTwoNums(params_struct);
    }

    params_struct->result = (double *)StackPeek(params_struct->nums_stack);

    printf("result: %f", *params_struct->result); 
    return S_INVALID;
}
