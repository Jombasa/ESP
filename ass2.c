#include <stdio.h>

#define TRUE 1
#define RETURNEOF 2
// #define FALSE 0
#define MAX 255


int readInput(char *input);
int checkInput(char input_array[], int counter);

int main (void)
{
    char input[MAX];
    int check_loop = 0;
    while(check_loop != RETURNEOF)
    {
        // printf("%d \n", EOF);
        //   check loop if has a value or it is EOF
        check_loop = readInput(&input);
        printf("%c", input[254]);
        if(check_loop == -1)
        {
            return -1;
        }
        if(check_loop == -2)
        {
            return -2;
        }
    }
    return 0;
}


int readInput(char *input)
{
    // int retrieve;
    int counter = 0;
    int checked_value;
    char ch;
    char read_array[MAX];

    printf("plain text: ");
    while(TRUE)
    {
        ch = getchar();
        read_array[counter] = ch;
        if(ch == EOF)
        {
            return RETURNEOF;
        }

        if(ch == '\n' && counter == 0)
        {
            return RETURNEOF;
        }

        // if there are only low letters
        if(ch == '\n' && counter > 0)
        {
            checked_value = checkInput(read_array, counter);
            return checked_value;
            // printf("%c",read_array[0]);
        }

        // if more than 255 chars
        if(counter > 256)
        {
            return -1;
        }

        counter++;
    }
    return -1;
}

// check if there are all low letters
int checkInput(char read_array[], int counter)
{
    int loop_counter;
    for(loop_counter = 0; loop_counter < counter; loop_counter++)
    {
        // check for letters
        if(read_array[loop_counter] < 97 || read_array[loop_counter] > 122)
        {
            return -2;
        }
        printf("%c", read_array[loop_counter]);
    }
    return 0;
}