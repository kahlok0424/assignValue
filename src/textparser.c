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

char *convertToLowerCase(char *str)
{

  int i = 0;
  char *buffer;
  buffer = (char*)malloc(strlen(str)+1);
  strcpy(buffer,str);
  //convert the word to lowercase 1 by 1
  while(buffer[i] != '\0')
  {
   buffer[i] = tolower(buffer[i]);
    ++i;
  }
    return buffer;
}

int stringCompare(char *str1, char *str2){
  int lengthOfStr1 = 0;
  int lengthOfStr2 = 0;
  int i = 0;

  lengthOfStr1 = getStringLength(str1);
  lengthOfStr2 = getStringLength(str2);

  str1 = convertToLowerCase(str1);
  str2 = convertToLowerCase(str2);

  if(lengthOfStr1 != lengthOfStr2){
    return 0;
  }
  else{
    while(str1[i] != ' ')
    {
      if(str1[i] != str2[i]){
        return 0;
      }
      else{ i++; }
    }
  }
  return 1;
}

char *removeFrontSpaces(char *str1)
{
    char *str2;
    str2=str1;
    while (*str2==' ') str2++;
    return str2;
}

/*char *findSpaceAndRemoveSpace(char *str){
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
}*/

/**
* Parse and compare the string. It ignored all the spaces.  ('^')/
* If the strings are equal, it returns non-zero,
* otherwise zero value.
**/
int parseAndCompare(char **linePtr, char *cmpStr)
{
  char *newline;
  newline = removeFrontSpaces(*linePtr);
  printf("test : %s",newline);

  /*for(int i = 0; i < lengthOfStr1; i++ )
  {
    if(str1[i] != str2[i]){
      return 0;
    }
    else{
    }
  }
}
return 1;*/
return 0;
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
