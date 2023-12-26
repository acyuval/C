
#include <stdio.h> 		    /* printf */
#include <stdlib.h> 		/* malloc, free */
#include <assert.h>		    /* assert */

#include "vsa.h"

typedef enum code
{
	FAILURE=-1,
	SUCCESS=0
} code_t;


void TestFuncs(void);
code_t TestAlloc(vsa_t *vsa, int **res, size_t size);
code_t TestFreeSize(vsa_t *vsa, size_t expected);


int main(void)
{
	TestFuncs();
	return (0);
}

void TestFuncs(void)
{
	int res = SUCCESS;

	void *pool = malloc(256);
	vsa_t *vsa = VSAInit(pool, 256);
	int *alloc1 = NULL, *alloc2 = NULL;
	int *alloc_not_aligned = NULL;
	int *alloc_end = NULL;
	/* size = 256 - 32 = 224 */
	res |= TestAlloc(vsa, &alloc1, 64);
	/* size = 224 - (64 + 16) = 144 */
	res |= TestFreeSize(vsa, 144);

	res |= TestAlloc(vsa, &alloc2, 32);
	/* size = 144 - (32 + 16) = 96 */
	res |= TestFreeSize(vsa, 96);

	res |= TestAlloc(vsa, &alloc_not_aligned, 41);
	/* size = 96 - (48 + 16) = 32 */
	res |= TestFreeSize(vsa, 32);

	res |= TestAlloc(vsa, &alloc_end, 24);
	/* size = 32 - 32 = 0 */
	res |= TestFreeSize(vsa, 0);

	VSAFree(alloc2);
	/* size = 0 + 32 = 32 */
	res |= TestFreeSize(vsa, 32);

	res |= TestAlloc(vsa, &alloc2, 32);
	/* size = 32 - 32 = 0 */
	res |= TestFreeSize(vsa, 0);

	VSAFree(alloc_end);
	/* size = 0 + 32 = 32 */
	res |= TestFreeSize(vsa, 32);

	VSAFree(alloc1);
	/* size = 0 + 64 = 64 */
	res |= TestFreeSize(vsa, 64);

	VSAFree(alloc2);
	/* size = 64 + (32 + 16) = 112 */
	res |= TestFreeSize(vsa, 112);

	VSAFree(alloc_not_aligned);
	/* size = 112 + (48 + 16) + (32 + 16) = 224 */
	res |= TestFreeSize(vsa, 224);

	printf("\n");
	if (SUCCESS == res)
	{
		printf("All Functions Succeded!\n");
	}
	else
	{
		printf("Some Functions Failed!\n");
	}

	free(pool);
	pool = NULL;
}

code_t TestAlloc(vsa_t *vsa, int **res, size_t size)
{
	*res = VSAAlloc(vsa, size);

	return (SUCCESS);
}

code_t TestFreeSize(vsa_t *vsa, size_t expected)
{
	size_t res = VSALargestFreeSize(vsa);
	if (res != expected)
	{
		printf("VSALargestFreeSize failed, expected: %lu, got: %lu\n", expected, res);
		return (FAILURE);
	}

	return (SUCCESS);
}
