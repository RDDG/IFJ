#include "parser.h"


// <class_body> => static <type> <id> ; <class_body>
// <class_body> => static <type> <id> ( <arg> ) { <function_body> }
// <class_body> => Epsilon
int LLClassBody(){
    int error=1;
    
    
    
    return error;
}


// <class_def> => epsilon
// <class_def> => class <id> { <class_body> } <class_def>
int LLClassDef(){
    int error=1;
    
    return error;
}

// <N> => class <id> { <class_body> } <class_def>
int LLClass(){
    
    int error =1;
    Token token;
    
    token=getToken();
    if(token.type != t_class){
        return error;
    }
    
    token=getToken();
    if(token.type != t_simple_id){
        return error;
    }
    
    token=getToken();
    if(token.type != t_LSlozena){
        return error;
    }
    
    error=LLClassBody();
    if( error == 1){
        return error;
    }
    
    token=getToken();
    if (token.type != t_PSlozena){
        return error;
    }
    
    error=LLClassDef();
    if( error == 1){
        return error;
    }
    
    return 0;
    
}

int parseStart(){
    int error = 1;
    
    error=LLClass();
    if (error == 0){
        //spustit interpret s paskou na vstuput
    }
    
    return error;
    
}