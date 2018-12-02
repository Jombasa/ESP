#include <stdio.h>

#define TRUE 1
#define MAX 256
#define RETURN_OK 0
#define RETURN_FALSE_NUMBER -1
#define RETURN_FALSE_CHAR -2

int checkInput(char read_array[], int counter);

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
int stringLenght(char *string)
{
  int it = 0;
  while(string[it] != '\0')
  {
    ++it;
  }
  return it;
}

void printEnryptedMessage(char * encrypted_string)
{
  printf("encrypted text: %s\n", encrypted_string);
}


char * reverseString(char *input_string)
{
  char ch;
  int string_length = stringLenght(input_string);
  for(int it = 0; it < string_length/2; ++it)
  {
    ch = input_string[it];
    input_string[it] = input_string[string_length - it -1];
    input_string[string_length - it -1] = ch;
  }
  return input_string;
}

const char * encryption(char *input_string)
{
  unsigned char ch;
  int string_length = stringLenght(input_string);
  int encryption_key = 256 % string_length;
  //
  if(encryption_key == 0){
    input_string = reverseString(input_string);
  }
  else
  {
    for(int it = 0; input_string[it] != '\0'; ++it)
    {
      ch = input_string[it];// + encryption_key;
      if( ch >= 97 && ch <= 122)
      {
        ch += encryption_key;
        if(ch > 122)
        {
          ch = ch - 122 + 97 -1;
        }
        input_string[it] = ch;
      }
    }
  }
  return input_string;
}
/*

*/
int readInput(char *input)
{
  int counter = 0;
  int checked_value;
  char ch;

  printf("plain text: ");
  while(TRUE)
  {
    ch = getchar();
    if(ch == EOF || ch == '\n')
    {
      input[counter] = '\0';
      break;
    }
    else
    {
      input[counter] = ch;
    }
    counter++;
  }
  checked_value = checkInput(input, counter);
  return checked_value;
}
/*
  check if there are all low letters
*/
int checkInput(char read_array[], int counter)
{
  int loop_counter;
  // if counter bigger than 255
  if(counter > 255)
  {
    return RETURN_FALSE_NUMBER;
  }
  else
  {
    for(loop_counter = 0; loop_counter < counter; loop_counter++)
    {
        // check for letters
        if(read_array[loop_counter] < 97 || read_array[loop_counter] > 122)
        {
            if(read_array[loop_counter] != 32)
            {
              return RETURN_FALSE_CHAR;
            }
        }
    }
  }
  return RETURN_OK;
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
