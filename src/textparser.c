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
  char *errorName;

  temp = removeFrontSpaces((*linePtr));

  while ((*temp) != ' ' && (*temp) != '\0') {   //Checks linePtr until ' ' or '\0'
      if (isdigit((*temp)) == 0) {
        (*linePtr) -= step;
        errorName = extractVariable(linePtr);
        throwError(1,"ERROR %d: %s is not a number!",1, errorName); //Throw not a number error when element is not a digit
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

  result[i] = '\0'; //End string

  return result;
}

int getVariableLength (char **linePtr) {

  	int counter = 0;

    if((**linePtr) == '=') {
      counter =+ 1;
    }
    else {
	    while ((**linePtr) != ' ' && (**linePtr) != '=') {
        if((**linePtr) == '\0') {
          (*linePtr) -= counter;
      		return counter;
        }
        else
			    counter++;
          (*linePtr)++;
			}
    (*linePtr) -= counter;  //Return original linePtr address
    }

		return counter;
	}

int parseTextAndAssignValues(char **linePtr, VariableMapping varTableMapping[])
{
  int i = 0;
char *errvarname;

if(*linePtr == NULL) {   //Return 1 if the command is NULL
  return 1;
}

if(varTableMapping == NULL) {   //Throw table error when there is no table given
  throwError(5,"ERROR %d: Table is NULL!",5);
}

if(varTableMapping[i].name == 0) {   //Throw table error when there is no table given
  throwError(6,"ERROR %d: Table is empty!",6);
}

else {
  if(parseAndCompare(linePtr, "assign")) {    //Check if linePtr contains "assign"
    while((**linePtr) != '\0') {
      if(varTableMapping[i].name == NULL) {          //Throw unknown variable error if
        errvarname = extractVariable(linePtr);      //found unmatched var
        throwError(2,"ERROR %d: '%s' is not a valid variable.",2,(errvarname));
      }
      else {
        if(parseAndCompare(linePtr, varTableMapping[i].name)) {   //Checks for every var name in table
          if(parseAndCompare(linePtr,"=")) {    //Checks for the presence of '=' sign
            *varTableMapping[i].storage = parseAndConvertToNum(linePtr);    //Convert string num and return back
            i = 0;    //Reset back when found its corresponding var         //int and store to its storage
          }
          else {
            errvarname = extractVariable(linePtr);   //If no "=" is found, throw malform error
            throwError(4,"ERROR %d: Expected '=', but %s is encountered.",4,(errvarname));
          }
        }
        else
          i++;  //Increase index when the var is not matched from table
      }
    }
  }
  else{
    errvarname = extractVariable(linePtr);  //If no "assign" word is found, throw unknown command
    throwError(3,"ERROR %d: Expected 'assign', but %s is encounted from the beginning.",3, (errvarname));
  }
}

}
