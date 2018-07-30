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

char *removeFrontSpaces(char *str1)
{
    char *str2;
    str2=str1;
    while (*str2==' ') str2++;
    return str2;
}

void removeFrontSpacesWithdPtr(char **str1)
{
    //char *str2;
    //str2=str1;
    while ((**str1) ==' '){
      *str1++;
      //(*line)++;
    }
    //return str1;
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

  while ((**linePtr) == ' ') {
   (*linePtr)++;
  }

  if( (*tempCmpStr) == '=' && (**linePtr) == '='){
    return 1;
  }

  int lenOfCmpStr = getStringLengthTilSpace(tempCmpStr);
  for(int i = 0 ; i < lenOfCmpStr ; i++){
    if(newline[i] != tempCmpStr[i]){
      return 0;
    }
    else{
      (*linePtr)++;
    }
  }

  while( (**linePtr) == ' ' )
  {
    (*linePtr)++;
  }

  return 1;
}

int verifyNumStringOnly (char **linePtr){


    int step = 0;
    char *errvarname;

    while ((**linePtr) == ' ') {
      (*linePtr)++;
      step++;
    }

    while ((**linePtr) != ' ' && (**linePtr) != '\0') {
        if (isdigit((**linePtr)) == 0) {
          (*linePtr) -= step;
          errvarname = extractVariable(linePtr);
          throwError(1,"ERROR %d: '%s' is not a number!",1,(errvarname));
        }
        else {
          (*linePtr)++;
          step ++;
        }
    }
    (*linePtr) -= step;
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

  //char *temp;
  //removeFrontSpacesWithdPtr(*linePtr);

  while ((**linePtr) == ' ') {
   (*linePtr)++;
  }

  if(verifyNumStringOnly (linePtr)) {
    while((**linePtr) != ' ' && (**linePtr) != '\0') {
      result += ((**linePtr) - 48);
      result *= 10;
      //(temp)++;
      (*linePtr)++;
    }

    while((**linePtr) == ' ') {
      //temp++;
      (*linePtr)++;
    }

    result /= 10;
    return result;
    }

  else
    return 0;
}

char *extractVariable(char **linePtr) {

  int length = 0, i = 0;
  char *result;

  while ((**linePtr) == ' ') {
    (*linePtr)++;
  }

  length = getVariableLength(linePtr);
  result = malloc (length);

  while (i < length) {
    result[i] = (**linePtr);
    (*linePtr)++;
    i++;
  }

  result[i] = '\0';

  return result;
}

int getVariableLength (char **linePtr) {

  	int count = 0;

    if((**linePtr) == '=') {
      count =+ 1;
    }
    else {
	    while ((**linePtr) != ' ' && (**linePtr) != '=') {
        if((**linePtr) == '\0') {
          (*linePtr) -= count;
      		return count;
        }
        else
			    count++;
          (*linePtr)++;
			}
    (*linePtr) -= count;
    }

		return count;
	}

int parseTextAndAssignValues(char **linePtr, VariableMapping varTableMapping[])
{
  int i = 0;
char *error;

if(*linePtr == NULL) {
  return 1;
}

if(varTableMapping == NULL) {
  throwError(5,"ERROR %d: Table is NULL!",5);
}

if(varTableMapping[i].name == 0) {
  throwError(6,"ERROR %d: Table is empty!",6);
}

else {
  if(parseAndCompare(linePtr, "assign")) {
    while((**linePtr) != '\0') {
      if(varTableMapping[i].name == NULL) {
        error = extractVariable(linePtr);
        throwError(2,"ERROR %d: '%s' is not a valid variable.",2,(error));
      }
      else {
        if(parseAndCompare(linePtr, varTableMapping[i].name)) {
          if(parseAndCompare(linePtr,"=")) {
            *varTableMapping[i].storage = parseAndConvertToNum(linePtr);
            i = 0;
          }
          else {
            error = extractVariable(linePtr);
            throwError(4,"ERROR %d: Expected '=', but %s is encountered.",4,(error));
          }
        }
        else
          i++;
      }
    }
  }
  else{
    error = extractVariable(linePtr);
    throwError(3,"ERROR %d: Expected 'assign', but %s is encounted from the beginning.",3, (error));
  }
}

}
