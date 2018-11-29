#include <stdio.h>


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
  char input_string[255] = "bruceforce";

  const char* encrypted_string = encryption(input_string);

  printEnryptedMessage(encrypted_string);

  return 0;
}
