#include "parser.h"


//<N> => class <id> { <class_body> } <class_def>
int LLclass(){
    
    int error =1;
    Token * token;
    
    token=getToken();
    if(token->type != t_class){
        return error;
    }
    
    token=getToken();
    if(token->type != t_simple_id){
        return error;
    }
    
    token=getToken();
    if(token->type != t_LSlozena){
        return error;
    }
    
    error=LLClassBody();
    if( error == 1){
        return error;
    }
    
    token=getToken();
    if (token->type != t_PSlozena){
        return error;
    }
    
    error=LLclassDef();
    if( error == 1){
        return error;
    }
    
    return 0;
    
}

int parseStart(){
    int error = 1;
    
    error=LLclass();
    if (error == 0){
        //spustit interpret s paskou na vstuput
    }
    
    return error;
    
    
    
    
}