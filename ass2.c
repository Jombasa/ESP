//------------------------------------------------------------------------------
// ass2.c
//
// This little program do take some input, which are only small letters from 
// [a-z] and encrypte it with a help of caesar encryption
// 
//
// Group: Group 6, study assistant Michael Hancianu
//
// Authors: Blaž Mesarec 01414280
//          Tomaž Mesarec 0654321
//------------------------------------------------------------------------------
//

#include <stdio.h>

#define TRUE 1
#define MAX 256
#define RETURN_OK 0
#define RETURN_INVALID_NUMBER -1
#define RETURN_INVALID_CHAR -2

typedef enum _ReturnValue_
{
  EVERYTHING_OK = 0,
  INVALID_NUM_OF_CHARS = -1,
  INVALID_CHAR = -2,
} ReturnValue;

// forward declarations
void printError(ReturnValue return_value);
int stringLength(char* input, int* whole_length);
void printEncryptedMessage(char* encrypted_string);
char* reverseString(char* input_string, int string_length);
char* encryption(char* input_string);
char* readInput(ReturnValue* return_value);
int checkInput(char read_array[], int counter);

//------------------------------------------------------------------------------
///
/// The main program.
/// It is the controller of the programm. It handels input and send it into 
/// encryption funcition and after encrypted message is made it sends it into 
/// print funciton. It handels also with error messages
/// 
///
/// @return if input is ok than 0, else -2 or -1
//
int main (void)
{
  char* input;
  int whole_lenght = 0;
  ReturnValue return_value;
  input = readInput(&return_value);
  // checks the return value
  if(return_value != EVERYTHING_OK){
    printError(return_value);
  }
  else if(stringLength(input, &whole_lenght) > 0)
  {
    char* encrypted_string = encryption(input);
    printEncryptedMessage(encrypted_string);
    return RETURN_OK;
  }
  // if there is no input
  else
  {
    printEncryptedMessage(input);
    return RETURN_OK;
  }
}

//------------------------------------------------------------------------------
///
/// Print of error messages.
/// It checks wich return value has been passed. it everything is ok, there is no
/// need of an error message
///
/// @param return_value passes the value of error
///
//
void printError(ReturnValue return_value)
{
  switch(return_value)
  {
    case EVERYTHING_OK:
      break;
    case INVALID_NUM_OF_CHARS:
      printf("[ERR] too many characters\n");
      break;
    case INVALID_CHAR:
      printf("[ERR] invalid characters\n");
      break;
  }
}

//------------------------------------------------------------------------------
///
/// Checks the length.
/// This function checks what is the legth of array
/// 
///
/// @param *input it is an input value
/// @param *whole_length returns value of array with spaces
///
/// @return value of char counter
//
int stringLength(char* input, int* whole_length)
{
  int it = 0;
  int inserted_space = 0;
  while(input[it] != '\0')
  {
    if(input[it] == 32)
    {
      inserted_space++;
    }
    ++it;
  }
  *whole_length = it;
  it = it - inserted_space;
  return it;
}

//------------------------------------------------------------------------------
///
/// Prints enrcypted message.
/// This function prints the output of enrcypted message
/// 
///
/// @param *encrypted_string it is an input value
///
//
void printEncryptedMessage(char* encrypted_string)
{
  printf("encrypted text: %s\n", encrypted_string);
}

//------------------------------------------------------------------------------
///
/// Reverse of encrypted output.
/// This function do reverse the input string
/// 
///
/// @param *input_string user's input
/// @param string_length checks the value of string
///
/// @return reversed input
//
char* reverseString(char* input_string, int string_length)
{
  char ch;
  for(int it = 0; it < string_length / 2; ++it)
  {
    ch = input_string[it];
    input_string[it] = input_string[string_length - it -1];
    input_string[string_length - it -1] = ch;
  }
  return input_string;
}

//------------------------------------------------------------------------------
///
/// Enrcyption of input.
/// This function do take input throug parameter and do encrypted it
/// 
///
/// @param *input_string user's input
///
/// @return encrypted input
//
char* encryption(char* input_string)
{
  unsigned char ch;
  int whole_lenght;
  int string_length = stringLength(input_string, &whole_lenght);
  int encryption_key = 256 % string_length;
  if(encryption_key == 0){
    input_string = reverseString(input_string, whole_lenght);
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

//------------------------------------------------------------------------------
///
/// Reads the input value.
/// This function reads the input value with help of getchar and while loop
/// and returned it as an array
/// 
///
/// @param *return_value is member of ReturnValue
///
/// @return input as array
//
char* readInput(ReturnValue* return_value)
{
  // static because of heap
  static char input[MAX];
  int counter = 0;
  char ch;

  printf("plain text: ");
  while(TRUE)
  {
    ch = getchar();
    if(ch == EOF || ch == '\n')
    {
      if(ch == EOF)
      {
        printf("\n");
      }
      input[counter] = '\0';
      break;
    }
    else
    {
      input[counter] = ch;
    }
    counter++;
  }
  *return_value = checkInput(input, counter);
  return input;
}

//------------------------------------------------------------------------------
///
/// Checks the input.
/// This function checks the input, if there are errors in writting it.
/// (only low letters)
///
/// @param read_array[] user's input
/// @param counter length of input
///
/// @return 0 if input ok, other if input false
//
int checkInput(char read_array[], int counter)
{
  int loop_counter;
  // if counter bigger than 255
  if(counter > 255)
  {
    return RETURN_INVALID_NUMBER;
  }
  else
  {
    for(loop_counter = 0; loop_counter < counter; loop_counter++)
    {
        // checks for letters
        if(read_array[loop_counter] < 97 || read_array[loop_counter] > 122)
        {
            if(read_array[loop_counter] != 32)
            {
              return RETURN_INVALID_CHAR;
            }
        }
    }
  }
  return RETURN_OK;
}

