#include <unistd.h>
#include <time.h>
#include <stdio.h>

int main()
{
    time_t timer = 0;
    int num_of_sec = 5;
    while (timer < num_of_sec)
    {
        printf("time is %ld\n", time(NULL));
        sleep(1);
        timer++;
    }

    return 0;
}