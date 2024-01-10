/******************************************************************************
 *	Author:    Yuval
 *	Reviewer :
 *	Date:
 ******************************************************************************/

#include <assert.h> /* assert */
#include <stdlib.h> /* malloc */


#include "../include/hash.h"
#include "../include/dll.h"
#include "../include/utiles.h"




/******************************************************************************
 *							 DECLRATION								  *
 ******************************************************************************/
struct hash
{
	dll_t **table;
	hash_func_t hash_func;
	is_match_t is_match;
	size_t table_size;
}; 


/******************************************************************************
 *							 FUNCTIONS 										  *
 ******************************************************************************/


hash_t *HashTableCreate(hash_func_t hash_func, size_t table_size,
						is_match_t is_match)
{
    hash_t * new_hash = NULL;

    assert(hash_func != NULL);
    assert(table_size != 0);
    assert(is_match != 0);

    new_hash = (hash_t *)malloc(sizeof(hash_t));
    if(NULL == new_hash)
    {
        return NULL;
    }
    new_hash->hash_func = hash_func;
    new_hash->table_size = table_size;
    new_hash->is_match = is_match;

    new_hash->table = (dll_t **)calloc(table_size, sizeof(dll_t *));

    if (NULL == new_hash->table)
    {
        free(new_hash);
        return NULL;
    }
    return new_hash;
}


void HashDestroy(hash_t *hash)
{
    size_t i = 0; 

    for(i = 0; i < hash->table_size; i++)
    {
        if (hash->table[i] != NULL)
        {
            DLLDestroy(hash->table[i]);
        }
    }
    free(hash->table);
    free(hash);
}

status_t HashInsert(hash_t *hash, const void *data)
{
    size_t key = 0;
    dll_t ** table = NULL;
    dll_iter_t dll_iter = NULL;
    assert(NULL != hash);
    table = hash->table;
    key = hash->hash_func((void *)data);

    if(table[key] == NULL)
    {
        table[key] = DLLCreate();
        if (NULL == table[key])
        {
            return FAIL;
        }
    }
   
    dll_iter =  DLLPushback(table[key], (void *)data);
    if (NULL == dll_iter)
    {
        return FAIL;
    } 
    return SUCCESS;
}


void HashRemove(hash_t *hash, const void *data)
{
    size_t key = 0;
    dll_iter_t from = NULL;
    dll_iter_t to = NULL;

    assert(NULL != hash);
    key = hash->hash_func((void *)data);
    from = DLLBegin(hash->table[key]);
    to = DLLEnd(hash->table[key]);

    DLLRemove(DLLFind(from, to, hash->is_match, (void *)data));

    if(DLLIsEmpty(hash->table[key]) == TRUE)
    {
        DLLDestroy(hash->table[key]);
        hash->table[key] = NULL;
    }

}

void *HashFind(const hash_t *hash, const void *data)
{
    size_t key = 0;
    dll_iter_t from = NULL;
    dll_iter_t to = NULL;
    void * found_data = NULL;
    assert(NULL != hash);

    key = hash->hash_func((void *)data);
    if (hash->table[key] != NULL)
    {
        from = DLLBegin(hash->table[key]);
        to = DLLEnd(hash->table[key]);
        found_data = (DLLGet(DLLFind(from, to, hash->is_match, (void *)data)));
    }
    return found_data;
}

size_t HashSize(const hash_t *hash)
{
    size_t counter = 0; 
    size_t i = 0;
    assert(NULL != hash);

    for(i = 0 ; i < hash->table_size; ++i)
    {
        if (hash->table[i] != NULL)
        {
            counter += DLLSize(hash->table[i]);
        }    
    }
    return counter; 
}

int HashIsEmpty(const hash_t *hash)
{
    size_t counter = 0; 
    size_t i = 0;
    assert(NULL != hash);

    for(i = 0 ; i < hash->table_size; ++i)
    {
        if (hash->table[i] != NULL)
        {
            counter += DLLSize(hash->table[i]);
        }
    }
    return counter; 
}

status_t HashForEach(hash_t *hash, action_t act_func, void *params)
{
    size_t i = 0;
    dll_t * list = NULL;
    int status = 0; 
    assert(NULL != hash);

   

    for(i = 0 ; i < hash->table_size; ++i)
    {
        list = hash->table[i];
        if (list != NULL)
        {
        status = DLLForEach(DLLBegin(list),DLLEnd(list), act_func, params);
        if(status != SUCCESS)
        {
            return FAIL;
        }
        }
    }
}



/******************************************************************************
 *							STATIC FUNCTIONS								  *
 ******************************************************************************/
