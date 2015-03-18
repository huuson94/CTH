/* Scanner
 * @copyright (c) 2008, Hedspi, Hanoi University of Technology
 * @author Huu-Duc Nguyen
 * @version 1.0
 *
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "reader.h"
#include "charcode.h"
#include "token.h"
#include "error.h"


extern int lineNo;
extern int colNo;
extern int currentChar;

extern CharCode charCodes[];

/***************************************************************/

void skipBlank() {
  // TODO
  while(charCodes[currentChar] == CHAR_SPACE){
    readChar();
    if(currentChar == EOF) break;
  }

}

void skipComment() {
  // TODO
  while(currentChar != EOF){
    readChar();
    if(charCodes[currentChar] == CHAR_TIMES){
      readChar();
      if(charCodes[currentChar] == CHAR_RPAR)
        readChar();
        return;
    }
  }
  error(ERR_ENDOFCOMMENT, lineNo, colNo);
}

Token* readIdentKeyword(void) {
  // TODO
  Token * temp;
  char str[MAX_IDENT_LEN +1];
  int i = 0;
  int ln = lineNo;
  int cn = colNo;
  while((charCodes[currentChar]) ==  CHAR_LETTER || (charCodes[currentChar] == CHAR_DIGIT) ){
    str[i++] = currentChar;
    readChar();
  }
  str[i] = '\0';
  if(checkKeyword(str) == TK_NONE){
    temp = makeToken(TK_IDENT, ln, cn);
    strcpy(temp->string, str);
    return temp;
  }
  else{
    return makeToken(checkKeyword(str), ln, cn);
  }
}

Token* readNumber(void) {
  // TODO
  int periodCount = 0;
  Token *temp = (Token*)malloc(sizeof(Token) *1);
  temp = makeToken(TK_NUMBER, lineNo, colNo);
  char str[MAX_IDENT_LEN +1];
  int i =0;
  while(charCodes[currentChar] == CHAR_DIGIT || charCodes[currentChar] == CHAR_PERIOD){
    if(periodCount == 1 && charCodes[currentChar] == CHAR_PERIOD) break;
    if(periodCount == 0 && charCodes[currentChar] == CHAR_PERIOD) periodCount++;;
    // if(periodCount == 1 && charCodes[currentChar] == CHAR_DIGIT) break;
    str[i++] = currentChar;
    readChar();
  }
  str[i] = '\0';
  strcpy(temp->string,str);
  temp->value = atof(str);
  return temp;
}

Token* readConstChar(void) {
  // TODO
  Token *temp = makeToken(TK_CHAR, lineNo, colNo);
  int ln = lineNo;
  int cn = colNo;
  readChar();  
  int i= 0;
  char str[MAX_IDENT_LEN +1];
  while((charCodes[currentChar] == CHAR_LETTER) || (charCodes[currentChar] == CHAR_SPACE)){
    str[i++] = currentChar;
    readChar();
  }
  if(i > 1) error(ERR_INVALIDCHARCONSTANT, ln, cn);
  str[i] ='\0';
  strcpy(temp->string,str);
  readChar();
  return temp;
}

Token* getToken(void) {
  Token *token;
  int ln, cn;

  if (currentChar == EOF) 
    return makeToken(TK_EOF, lineNo, colNo);

  switch (charCodes[currentChar]) {
  case CHAR_SPACE: skipBlank(); return getToken();
  case CHAR_LETTER: return readIdentKeyword();
  case CHAR_DIGIT: return readNumber();
  case CHAR_PLUS: 
    token = makeToken(SB_PLUS, lineNo, colNo);
    readChar(); 
    return token;
  // ....
  case CHAR_SEMICOLON:
    token = makeToken(SB_SEMICOLON, lineNo, colNo);
    readChar();
    return token;
  case CHAR_LPAR:
    ln = lineNo;
    cn = colNo;
    readChar();
    if(charCodes[currentChar] == CHAR_TIMES){
      skipComment();
      return getToken();
    }
    if(charCodes[currentChar] == CHAR_PERIOD){
      // =>>> (. .)
      readChar();
      return makeToken(SB_LSEL,ln, cn);
    }
    return makeToken(SB_LPAR, ln, cn);
  case CHAR_RPAR:
    token = makeToken(SB_RPAR, lineNo, colNo);
    readChar();
    return token;
  case CHAR_PERIOD:
    ln = lineNo;
    cn = colNo;
    char temp[MAX_IDENT_LEN +1];
    int i =0;
    temp[i++] = '.';
    readChar();
    if(charCodes[currentChar] == CHAR_RPAR){
      readChar();
      return makeToken(SB_RSEL, ln, cn);
    }
    if(charCodes[currentChar] == CHAR_DIGIT){
      while(charCodes[currentChar] == CHAR_DIGIT){
        temp[i++] = currentChar;
        readChar();
      }
      token = makeToken(TK_NUMBER, ln, cn);
      strcpy(token->string,temp);
      token->value = atof(temp);
      return token;
    }
    token = makeToken(SB_PERIOD, ln, cn);
    readChar();
    return token;
  case CHAR_COLON:
    ln = lineNo;
    cn = colNo;
    readChar();
    if(charCodes[currentChar] == CHAR_EQ){
      readChar();
      return makeToken(SB_ASSIGN, ln, cn);
      
    }
    token = makeToken(SB_COLON, ln, cn);
    
    return token;
  case CHAR_EQ:
    token = makeToken(SB_EQ, lineNo, colNo);
    readChar();
    return token;
  case CHAR_TIMES:
    token = makeToken(SB_TIMES, lineNo, colNo);
    readChar();
    return token;
  case CHAR_MINUS:
    token = makeToken(SB_MINUS, lineNo, colNo);
    readChar();
    return token;
  case CHAR_EXCLAIMATION:
    ln = lineNo;
    cn = colNo;
    readChar();
    if(charCodes[currentChar] == CHAR_EQ){
      readChar();
      return makeToken(SB_NEQ, ln, cn);
    }
    error(ERR_INVALIDSYMBOL,ln,cn);
    return makeToken(TK_NONE, lineNo ,colNo);
  case CHAR_COMMA:
    token = makeToken(SB_COMMA, lineNo, colNo);
    readChar();
    return token;
  case CHAR_SINGLEQUOTE:
    return readConstChar();
  case CHAR_LT:
    ln = lineNo;
    cn = colNo;
    readChar();
    if(charCodes[currentChar] == CHAR_EQ){
      readChar();
      return makeToken(SB_LE, ln, cn);
    }
    return makeToken(SB_LT, ln, cn);
  case CHAR_GT:
    ln = lineNo;
    cn = colNo;
    readChar();
    if(charCodes[currentChar] == CHAR_EQ){
      readChar();
      return makeToken(SB_GE, ln, cn);
    }
    return makeToken(SB_GE, ln, cn);  
  // ....
  default:
    token = makeToken(TK_NONE, lineNo, colNo);
    error(ERR_INVALIDSYMBOL, lineNo, colNo);
    readChar(); 
    return token;
  }
}


/******************************************************************/

void printToken(Token *token) {

  printf("%d-%d:", token->lineNo, token->colNo);

  switch (token->tokenType) 
{  case TK_NONE: printf("TK_NONE\n"); break;
  case TK_IDENT: printf("TK_IDENT(%s)\n", token->string); break;
  case TK_NUMBER: printf("TK_NUMBER(%s)\n", token->string); break;
  case TK_CHAR: printf("TK_CHAR(\'%s\')\n", token->string); break;
  case TK_EOF: printf("TK_EOF\n"); break;

  case KW_PROGRAM: printf("KW_PROGRAM\n"); break;
  case KW_CONST: printf("KW_CONST\n"); break;
  case KW_TYPE: printf("KW_TYPE\n"); break;
  case KW_VAR: printf("KW_VAR\n"); break;
  case KW_INTEGER: printf("KW_INTEGER\n"); break;
  case KW_CHAR: printf("KW_CHAR\n"); break;
  case KW_ARRAY: printf("KW_ARRAY\n"); break;
  case KW_OF: printf("KW_OF\n"); break;
  case KW_FUNCTION: printf("KW_FUNCTION\n"); break;
  case KW_PROCEDURE: printf("KW_PROCEDURE\n"); break;
  case KW_BEGIN: printf("KW_BEGIN\n"); break;
  case KW_END: printf("KW_END\n"); break;
  case KW_CALL: printf("KW_CALL\n"); break;
  case KW_IF: printf("KW_IF\n"); break;
  case KW_THEN: printf("KW_THEN\n"); break;
  case KW_ELSE: printf("KW_ELSE\n"); break;
  case KW_WHILE: printf("KW_WHILE\n"); break;
  case KW_DO: printf("KW_DO\n"); break;
  case KW_FOR: printf("KW_FOR\n"); break;
  case KW_TO: printf("KW_TO\n"); break;
  case KW_FLOAT: printf("KW_FLOAT\n"); break;

  case SB_SEMICOLON: printf("SB_SEMICOLON\n"); break;
  case SB_COLON: printf("SB_COLON\n"); break;
  case SB_PERIOD: printf("SB_PERIOD\n"); break;
  case SB_COMMA: printf("SB_COMMA\n"); break;
  case SB_ASSIGN: printf("SB_ASSIGN\n"); break;
  case SB_EQ: printf("SB_EQ\n"); break;
  case SB_NEQ: printf("SB_NEQ\n"); break;
  case SB_LT: printf("SB_LT\n"); break;
  case SB_LE: printf("SB_LE\n"); break;
  case SB_GT: printf("SB_GT\n"); break;
  case SB_GE: printf("SB_GE\n"); break;
  case SB_PLUS: printf("SB_PLUS\n"); break;
  case SB_MINUS: printf("SB_MINUS\n"); break;
  case SB_TIMES: printf("SB_TIMES\n"); break;
  case SB_SLASH: printf("SB_SLASH\n"); break;
  case SB_LPAR: printf("SB_LPAR\n"); break;
  case SB_RPAR: printf("SB_RPAR\n"); break;
  case SB_LSEL: printf("SB_LSEL\n"); break;
  case SB_RSEL: printf("SB_RSEL\n"); break;
  }
}


/******************************************************************/

Token* getValidToken(void){
Token *token = getToken();
  while (token->tokenType == TK_NONE) {
    free(token);
    token = getToken();
  }
  return token;
}


