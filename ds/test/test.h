#ifndef __TEST_H__
#define __TEST_H__

#include <stdio.h> /* printf, fprintf */

#define RESET ("\033[0m")
#define BLACK ("\033[30m")              /* Black */
#define RED ("\033[31m")                /* Red */
#define GREEN ("\033[32m")              /* Green */
#define YELLOW ("\033[33m")             /* Yellow */
#define BLUE ("\033[34m")               /* Blue */
#define MAGENTA ("\033[35m")            /* Magenta */
#define CYAN ("\033[36m")               /* Cyan */
#define WHITE ("\033[37m")              /* White */
#define BOLDBLACK ("\033[1m\033[30m")   /* Bold Black */
#define BOLDRED ("\033[1m\033[31m")     /* Bold Red */
#define BOLDGREEN ("\033[1m\033[32m")   /* Bold Green */
#define BOLDYELLOW ("\033[1m\033[33m")  /* Bold Yellow */
#define BOLDBLUE ("\033[1m\033[34m")    /* Bold Blue */
#define BOLDMAGENTA ("\033[1m\033[35m") /* Bold Magenta */
#define BOLDCYAN ("\033[1m\033[36m")    /* Bold Cyan */
#define BOLDWHITE ("\033[1m\033[37m")   /* Bold White */

#define TEST_START(func_name)                                                  \
	do                                                                         \
	{                                                                          \
		_failed_tests_count = 0;                                               \
		printf("----------------------------------------\n");                  \
		printf("%sTESTING: %s%s\n", CYAN, func_name, RESET);                   \
	} while (0)

#define TEST_ASSERT(expr)                                                      \
	do                                                                         \
	{                                                                          \
		if (!(expr))                                                           \
		{                                                                      \
			++_failed_tests_count;                                             \
			fprintf(stderr, "%sTEST FAILED: (LINE %d) \"%s\", FILE %s%s\n",    \
					RED, __LINE__, #expr, __FILE__, RESET);                    \
		}                                                                      \
		++_total_tests;                                                        \
	} while (0)

#define TEST_END                                                               \
	do                                                                         \
	{                                                                          \
		if (0 == _failed_tests_count)                                          \
		{                                                                      \
			printf("%sTESTS PASSED (%ld/%ld) %s\n", GREEN, _total_tests,       \
				   _total_tests, RESET);                                       \
		}                                                                      \
		else if (_failed_tests_count < _total_tests)                           \
		{                                                                      \
			printf("%sSOME TESTS FAILED (%ld/%ld) %s\n", YELLOW,               \
				   (_total_tests - _failed_tests_count), _total_tests, RESET); \
		}                                                                      \
		else                                                                   \
		{                                                                      \
			printf("%sALL TESTS FAILED (%ld/%ld) %s\n", RED,                   \
				   (_total_tests - _failed_tests_count), _total_tests, RESET); \
		}                                                                      \
		_failed_tests_count = 0;                                               \
		_total_tests = 0;                                                      \
	} while (0)

#define TRUE (1)
#define FALSE (0)

#define FAIL (-1)
#define SUCCESS (0)

size_t _total_tests = 0;
size_t _failed_tests_count = 0;

#endif /* __TEST_H__ */