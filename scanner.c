/******************************************************************************/
/*													Projekt do IFJ a IAL														 	*/
/*						Implementace interpretu imperativního jazyka IFJ16							*/
/*													Lexikalni analyzator															*/
/* 																2016/2017																		*/
/*																xcisar07																		*/
/******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "scanner.h"
#include "garbage.h"

Token token;
FILE *file;


/*                           Zadam klicova slova                              */
char *keyWords[17] = {"boolean", "break", "class", "continue", "do", "double",
                      "else", "false", "for", "if", "int", "return", "String",
                      "static", "true", "void", "while"};

/******************************************************************************/
/*                                  Funkce                                    */
/******************************************************************************/
/******************************************************************************/
/*                          Funkce pro zmeny tokenu                           */
/******************************************************************************/
/*                           Inicializovani tokenu                            */
int initToken(Token *token){
  /*if((token->string = (char*) malloc(8)) == NULL){
    return 99;
  }*/
  token->string = (char*) myMalloc(8);
  token->type = t_start;
  token->lenght = 0;
  token->alocated = 8;
  token->string = '\0';
  return 0;
}

/*                             Uvolneni tokenu              pa                  */
void freeToken(Token *token){
  free(token->string);
}
/*                      Pridani posledniho znaku do tokenu                    */
int addCharToToken(Token *token, char c){
  if(token->alocated <= (token->lenght+1)){
    if((token->string = (char*) realloc(token->string, token->lenght+8))==NULL){
      return 99;
    }
    token->alocated = token->lenght + 8;
  }
  token->string[token->lenght] = c;
  token->lenght++;
  token->string[token->lenght] = '\0';
  return 0;
}
/*                              Zmena typu tokenu                             */
int changeTypeOfToken(Token *token, tType type){
  token->type = type;
  return 0;
}
/*                                Smazani tokenu                              */
void cleanToken(Token *token){
  token->string[0] = '\0';
  token->lenght = 0;
}
/******************************************************************************/
/*                            Funkce k vyhodnoceni                            */
/******************************************************************************/
/*                    Funkce kontroluje jestli je klicove slovo               */
/*                       Pokud je klicove slovo navraci 1                     */
int checkKeyWord(char *word){
  for(int i = 0; i < 17; i++){
    if(strcmp(word, keyWords[i]) == 0){
      return 1;
    }
  }
  return 0;
}

/*                       Funkce preskakuje komentare                          */
/*int ignoreComment(){

}*/
/*                         Funkce na ziskami tokenu                           */
Token getToken(){
  char c;
  int type = t_start;
  cleanToken(&token);
  c=fgetc(file);
  if(c == EOF){
    type = t_eof;
    changeTypeOfToken(&token, type);
  }

  while(1) {
    switch (type) {
      case  t_start: {
        if(isspace(c)){                 // ignoruji pocatecni mezery
          type = t_start;
          break;
        }
        else if(isdigit(c)){           // je to cislo 0-9?
          if(c == '0'){
            type = t_zero;       // ignoruji pocatecni nuly
            break;
          }
          else{                       // vyhodnotim jako cele cislo
             type = t_int;
          }
        }
        else if(c == '"'){           // vyhodnotim jako retezcovy literal
          type = t_string_m;
        }
        else if(c == '+'){
          type = t_plus;
        }
        else if(c == '-'){
          type = t_minus;
        }
        else if(c == '*'){
          type = t_multiply;
        }
        else if(c == '/'){          // tady to muze byt i komentar
          type = t_divide;
        }
        else if(c == '('){
          type = t_left_bracket;
        }
        else if(c == ')'){
          type = t_right_bracket;
        }
        else if(c == '<'){
          type = t_smaller;
        }
        else if(c == '>'){
          type = t_bigger;
        }
        else if(c == '='){
          type = t_m_equals;
        }
        else if(c == '!'){
          type = t_exclamation;
        }
        else if(c == '.'){
          type = t_dot;
        }
        else if(c == ','){
          type = t_comma;
        }
        else if(c == ':'){
          type = t_colon;
        }
        else if(c == ';'){
          type = t_semicolon;
        }
        else if((isalpha(c)) || c == '_' || c == '$'){ // identifikator
          type = t_simple_id;
        }
        else{
          type = t_lex_error;
        }
        addCharToToken(&token , c);
        break;
      }

      case t_zero: {
        if(c == '0'){
          type = t_zero;
        }
        else if(c != '0' && isdigit(c)){
          type = t_int;
          addCharToToken(&token, c);
          changeTypeOfToken(&token, type);
        }
        else if(c == '.'){
          type = t_double_m;
          addCharToToken(&token, '0');
          addCharToToken(&token, c);
        }
        else{
          ungetc(c, file);
          type = t_int;
          addCharToToken(&token, '0');
          changeTypeOfToken(&token, type);
          return token;
        }
        break;
      }

      case t_int: {
        if(isdigit(c)){
          type = t_int;
          addCharToToken(&token, c);
          changeTypeOfToken(&token, type);
        }
        else if(c == '.'){
          type = t_double_m;
          addCharToToken(&token, c);
          changeTypeOfToken(&token, type);
        }
        else {
          ungetc(c, file);
          type = t_int;
          changeTypeOfToken(&token, type);
          type = t_finish;
        }
        break;
      }

      case t_double_m: {
        if(isdigit(c)){
          type = t_double;
          addCharToToken(&token, c);
          changeTypeOfToken(&token, type);
        }
        else{
          type = t_lex_error;
        }
        break;
      }

      case t_double: {
        if(isdigit(c)){
          type = t_double;
          addCharToToken(&token, c);
          changeTypeOfToken(&token, type);
        }
        else{
          ungetc(c, file);
          type = t_finish;
        }
        break;

      }

      case t_simple_id: {
        if((isalnum(c) || c == '_' || c == '$')){
          type = t_simple_id;
          addCharToToken(&token, c);
          changeTypeOfToken(&token, type);
        }
        else if(c == '.'){
          type = t_qualified_id;
          addCharToToken(&token, c);
          changeTypeOfToken(&token, type);
        }
        else{
          ungetc(c, file);
          type = checkKeyWord(token.string);
          changeTypeOfToken(&token, type);
          type = t_finish;
        }
        break;
      }

      case t_qualified_id: {
        if((isalnum(c) || c == '_' || c == '$')){
          type = t_qualified_id;
          addCharToToken(&token, c);
          changeTypeOfToken(&token, type);
        }
        else{
          ungetc(c, file);
          type = t_finish;
        }
        break;
      }

      case t_string_m: {
        if(c > 31 && c != 34){
          type = t_string_m;
          addCharToToken(&token, c);
          changeTypeOfToken(&token, type);
        }
        else{
          type = t_lex_error;
        }
      }

      case t_string: {
        if(c == 34){
          type = t_string;
          addCharToToken(&token, c);
          changeTypeOfToken(&token, type);
        }
        else{
          type = t_lex_error;
        }
      }

      case t_smaller: {
        if(c == '='){
          type = t_eq_smaller;
          addCharToToken(&token, c);
          changeTypeOfToken(&token, type);
        }
        else{
          ungetc(c, file);
          type = t_smaller;
          changeTypeOfToken(&token, type);
          type = t_finish;
        }
      }

      case t_eq_smaller: {
        type = t_finish;
        break;
      }

      case t_bigger: {
        if(c == '='){
          type = t_eq_bigger;
          addCharToToken(&token, c);
          changeTypeOfToken(&token, type);
        }
        else{
          ungetc(c, file);
          type = t_bigger;
          changeTypeOfToken(&token, type);
          type = t_finish;
        }
      }

      case t_eq_bigger: {
        type = t_finish;
        break;
      }

      case t_exclamation: {
        if(c == '='){
          type = t_not_equals;
          addCharToToken(&token, c);
          changeTypeOfToken(&token, type);
        }
        else{
          type = t_lex_error;
        }
      }

      case t_not_equals: {
        type = t_finish;
        break;
      }
    
    }
  }
}
