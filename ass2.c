#include <stdio.h>

#define TRUE 1
#define RETURNEOF 2
// #define FALSE 0
#define MAX 255


int readInput(char input[]);
int checkInput(char input_array[], int counter);

//Return values of the program
typedef enum _ReturnValue_
{
  EVERYTHING_OK = 0,
  INVALID_NUM_OF_CHARS = -1,
  INVALID_CHAR = -2,
} ReturnValue;

ReturnValue printError(ReturnValue return_value)
{
  switch(return_value)
  {
    case INVALID_NUM_OF_CHARS:
      printf("[ERR] too many characters\n");
      break;
    case INVALID_CHAR:
      printf("[ERR] invalid characters\n");
      break;
  }
  return return_value;
}

void printEnryptedMessage(const char * encrypted_string)
{
  printf("encrypted text: %s\n", encrypted_string);
}

int stringLenght(char *string)
{
  int it = 0;
  while(string[it] != '\0')
  {
    ++it;
  }
  return it;
}

const char * encryption(char *input_string)
{
  char ch;
  int string_length = stringLenght(input_string);
  //TODO return reverse string if key is 0
  int enryption_key = 256 % string_length;
  ////encrypitng chars
  for(int it = 0; input_string[it] != '\0'; ++it)
  {
    ch = input_string[it] + enryption_key;
    //ch > 'z'
    if(ch > 122)
    {
      //ch = ch - z + a -1
      ch = ch - 122 + 97 -1;
    }
    input_string[it] = ch;
  }
  return input_string;
}

int main (void)
{
  char input[MAX];

  ReturnValue return_value = readInput(&input);

  if(return_value != EVERYTHING_OK){
    printError(return_value);
  }
  else
  {
    const char* encrypted_string = encryption(input);
    printEnryptedMessage(encrypted_string);
    return 0;
  }
}


int readInput(char *input)
{
  // int retrieve;
  int counter = 0;
  int checked_value;
  char ch;

  printf("plain text: ");
  while(TRUE)
  {
    ch = getchar();
    input[counter] = ch;
    if(ch == EOF)
    {
        return RETURNEOF;
    }

    if(ch == '\n' && counter == 0)
    {
        return RETURNEOF;
    }
    //TODO you can stop reading with EOF too...
    // if there are only low letters
    if(ch == '\n' && counter > 0)
    {
        // if more than 255 chars
        if(counter > 255)
        {
            return -1;
        }
        checked_value = checkInput(input, counter);
        return checked_value;
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
      //TODO space returns invalid_char
      // check for letters
      if(read_array[loop_counter] < 97 || read_array[loop_counter] > 122)
      {
          return -2;
      }
  }
  return 0;
}
