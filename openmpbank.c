#include <stdio.h>
#include <omp.h>

int main()
{
    int num_counters = 4;
    int num_customers = 100;
    int customers_per_counter = num_customers / num_counters;

    #pragma omp parallel for
    for (int i = 0; i < num_counters; i++)
    {
        int counter_id = omp_get_thread_num();
        switch (counter_id)
        {
            case 0:
                printf("Counter 1 is serving %d customers for cash withdrawals\n", customers_per_counter);
                break;
            case 1:
                printf("Counter 2 is serving %d customers for deposits\n", customers_per_counter);
                break;
            case 2:
                printf("Counter 3 is serving %d customers for submitting challans\n", customers_per_counter);
                break;
            case 3:
                printf("Counter 4 is serving %d customers for bank inquiries\n", customers_per_counter);
                break;
        }
    }

    return 0;
}