/******************************************************************************/
/*													Projekt do IFJ a IAL														 	*/
/*						Implementace interpretu imperativního jazyka IFJ16							*/
/*													Lexikalni analyzator															*/
/*                                Knihovna                                    */
/*																2016/2017																		*/
/*																xcisar07																		*/
/******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*                          Stavy konecneho automatu                          */
typedef enum {
  t_start,         // pocatecni stav
  t_lex_error,     // lexikalni chyba nalezena
  t_zero,          // nuly na zacatku
  t_eof,           // konec souboru
  t_key_word,      // klicova slova
  t_int,           // celociselny literal
  t_double,        // desetinny literal
  t_double_m,      // mozna to bude double - mezistav (kontrola, co je za .)
  t_simple_id,     // jednoduchy identifikator
  t_qualified_id,  // plne kvalifikoany identifikator
  t_string,        // retezcovy literal
  t_comment,       // komentar // a /* */
  t_left_bracket,  // leva zavorka (
  t_right_bracket, // prava zavorka )
  t_plus,          // scitani +
  t_minus,         // odcitani -
  t_multiply,      // nasobeni *
  t_divide,        // deleni /
  t_smaller,       // mensi <
  t_bigger,        // vetsi >
  t_eq_smaller,    // mensi a rovno <=
  t_eq_bigger,     // vetsi a rovno >=
  t_equals,        // rovno ==
  t_m_equals,      // asi to bude rovno =
  t_not_equals,    // nerovno !=
  t_exclamation,   // vykricnik !
  t_dot,           // tecka .
  t_colon,         // dvojtecka :
  t_comma,         // carka ,
  t_semicolon,     // strednik ;
  t_finish         // konecny stav
} tType;

typedef struct {
  tType type;
  char *string;
  int alocated;
  int lenght;
} Token;
