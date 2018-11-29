#include <stdio.h>
#include <string.h>



const char * encryption(char *input_string)
{
  char ch;
  int string_length = strlen(input_string);
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
  char input_string[255] = "bruteforce";

  const char* encrypted_string = encryption(input_string);

  printf("%s\n", encrypted_string);

  return 0;
}
