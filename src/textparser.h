#ifndef _TEXTPARSER_H
#define _TEXTPARSER_H

typedef struct VariableMapping VariableMapping;

struct VariableMapping{
  char *name;
  int *storage;
};

int stringCompare(char *str1, char *str2);
int getStringLength(char *str);
char *convertToLowerCase(char *str);
int getStringLengthTilSpace(char *str);
int verifyNumStringOnly(char **linePtr);

/**
* Parse and compare the string. It ignored all the spaces.  ('^')/
* If the strings are equal, it returns non-zero,
* otherwise zero value.
**/
int parseAndCompare(char **linePtr, char *cmpStr); // macam string compare

/**
* Parse and convert the first string number to value.
* It ignored all the spaces.  ('^')/
* The value is returned if the number is succesfully
* converted. If there is no number, ERR_NOT_A_NUMBER          (cannot return 0 cuz '0' also is number)
* is thrown.
**/
int parseAndConvertToNum(char **linePtr);
int parseTextAndAssignValues();


char *removeFrontSpaces(char *str1);
char *extractStringFromSpace(char *str);
//char *findSpaceAndRemoveSpace(char *line);

#endif // _TEXTPARSER_H
