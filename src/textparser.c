#include "textparser.h"
#include "Exception.h"
#include "CException.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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

int getStringLengthTilSpace(char *str){
  int i = 0;

  if( str == NULL){
	  return 0;
  }
  else{
  while( *(str + i) != '\0' && *(str + i) != ' ' ){
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

char *extractStringFromSpace(char *str){
  char *temp;
  char *result;
  int i = 0;
  temp = removeFrontSpaces(str);
  while( temp[i] != ' '){
    result = temp;
    ++i;
  }
  printf("result :%s",result );
  return result;
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
  char *tempCmpStr;

  tempCmpStr = removeFrontSpaces(cmpStr);
  newline = removeFrontSpaces(*linePtr);
  //printf("test :%s",newline);

  if( (*tempCmpStr) == '=' && (**linePtr) == '='){
    return 1;
  }

  int lenOfCmpStr = getStringLengthTilSpace(tempCmpStr);
  for(int i = 0 ; i < lenOfCmpStr ; i++){
    if(newline[i] != tempCmpStr[i]){
      return 0;
    }
    else{
    }
  }

  /*while( (*newline) != '/0' )
  {
  }*/

  return 1;
}

int verifyNumStringOnly (char **linePtr){

  int step = 0;
  char *temp;
  //char *errvarname;

  temp = removeFrontSpaces((*linePtr));

  while ((*temp) != ' ' && (*temp) != '\0') {   //Checks linePtr until ' ' or '\0'
      if (isdigit((*temp)) == 0) {
        //(*linePtr) -= step;
        //errvarname = extractVariable(linePtr);
        throwError(1,"ERROR %d:  is not a number!",1); //Throw not a number error when element is not a digit
      }
      else {
        temp++;
        //step ++;
      }
  }
  (*linePtr) -= step;   //Revert back and return 1 when it is done
  return 1;
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
  int result = 0;

  char *temp;
  temp = removeFrontSpaces(*linePtr);

  if(verifyNumStringOnly (&temp)) {   //Check string only contains number
    while((*temp) != ' ' && (*temp) != '\0') {    //Convert string into int
      result += ((*temp) - 48);
      result *= 10;
      (temp)++;
    }

    while((*temp) == ' ') {   //Remove trailing spaces
      temp++;
    }

    result /= 10;
    return result;
    }

  else
    return 0;
}

int parseTextAndAssignValues()
{

}
