#include "textparser.h"
#include "string.h"

int getStringLength(char *str){
  int i = 0;

  if( str == NULL){
	  return 0;
  }
  else{
  while( *(str + i) != '\0'){
    i++;
  }
  return i;
  }
}

char *removeFrontSpaces(char *str1)
{
    char *str2;
    str2=str1;
    while (*str2==' ') str2++;
    return str2;
}

char *findSpaceAndRemoveSpace(char *str){
  // To keep track of non-space character count
  int count = 0;
  char *str2 ;
  int len = getStringLength(str);
  str2 = str;
  // Traverse the given string. If current character
  // is not space, then place it at index 'count++'
  for (int i = 0; str2[i]; i++){
      if (str2[i] != ' ')
          str2[count++] = str2[i]; // here count is incremented
     }
  //str2[count] = '\0';
  return str2;
}

/*char *findSpaceAndRemoveSpace(char *str){
  // To keep track of non-space character count
  int count = 0;
  char *str2 ;
  int len = getStringLength(str);
  str2 = str;

  str2.erase(remove(str2.begin(), str2.end(), ' '), str2.end());
  //str2[count] = '\0';
  return str2;
}*/

/**
* Parse and compare the string. It ignored all the spaces.  ('^')/
* If the strings are equal, it returns non-zero,
* otherwise zero value.
**/
int parseAndCompare(char **linePtr, char *cmpStr)
{
  //char *newline;
  //newline = removeFrontSpaces(linePtr);
  return 0; //(for temp use only)
}

/**
* Parse and convert the first string number to value.
* It ignored all the spaces.  ('^')/
* The value is returned if the number is succesfully
* converted. If there is no number, ERR_NOT_A_NUMBER          (cannot return 0 cuz '0' also is number)
* is thrown.
**/
int parseAndConvertToNum(char **linePtr)
{
  return 0; //(for temp use only)
}

int parseTextAndAssignValues()
{

}
