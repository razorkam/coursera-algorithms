#include <iostream>
#include <stdio.h>
#include <algorithm>

using namespace std;

long long* memory = new long long[1000000];
size_t n = 0;
const int left_limit = -10000,
        right_limit = 10000;


inline long long binsearch(long long element, size_t left)
{
    size_t right = n - 1;
    while(right - left > 1)
    {
        size_t mid = (left + right) >> 1;
        long long sum = element + memory[mid];
        if ( sum >= left_limit && sum <= right_limit )
        {
            return mid;
        }

        if( sum < left_limit )
        {
            left = mid;
        }
        else
        {
            right = mid;
        }
    }
    if ( element + memory[left] >= left_limit && element + memory[left] <= right_limit )
    {
        return left;
    }
    else
    {
        if ( element + memory[right] >= left_limit && element + memory[right] <= right_limit )
        {
            return right;
        }
        else
        {
            return -1;
        }
    }

}

int main (int argc, const char** argv)
{
    FILE * input;
    double size;
    char * buffer;

    input = fopen ( "data.txt" , "rb" );

    fseek (input , 0 , SEEK_END);
    size = ftell (input);
    rewind (input);

    buffer = (char*) malloc (sizeof(char)*size);
    fread (buffer, 1, size, input);

    long long number = 0;
    bool sing = false;
    bool smtd = false;

    bool* found = new bool[20001];

    for (size_t i = 0 ; i < 20001; i++)
    {
        found[i] = true;
    }


    for (size_t i = 0; i <= size; i++ )
    {
        if ( buffer[i] >= 48 && buffer[i] <= 57)
        {
            number = number*10 + buffer[i] - '0';
            smtd = true;
        }
        else
        {
            if (buffer[i] == 45)
            {
                sing = true;
            }
            else
            {
                if (smtd)
                {
                    if (sing)
                    {
                        memory[n++] = -number;
                    }
                    else
                    {
                        memory[n++] = number;
                    }
                    sing = false;
                    smtd = false;
                    number = 0;
                }
            }
        }
    }
    fclose (input);
    free (buffer);

    stable_sort(memory, memory + n);

    size_t q = 0,
            j = 0;
    long long k,
            key,
            in;

    while (j < n - 1)
    {
        if (memory[j] == memory[j + 1])
        {
            j++;
        }
        else
        {
            k = binsearch(memory[j], j + 1);
            if ( k != -1 )
            {
                key = k - 1;
                while ( k < n )
                {
                    in = memory[j] + memory[k];
                    if ( in >= left_limit && in <= right_limit)
                    {
                        if ( found[in + right_limit] )
                        {
                            q++;
                            found[in + right_limit] = false;
                        }
                        k++;
                    }
                    else
                    {
                        break;
                    }
                }
                while ( key > j )
                {
                    in = memory[j] + memory[key];
                    if ( in >= left_limit && in <= right_limit )
                    {
                        if ( found[in + right_limit] )
                        {
                            q++;
                            found[in + right_limit] = false;
                        }
                        key--;
                    }
                    else
                    {
                        break;
                    }
                }
            }
            j++;
        }
    }

    free(memory);
    free(found);

    cout << q << endl;
}