#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<stack.h>
//cstack librery  
#define _GNU_SOURCE
enum operator{
        add,
        sub,
        mul,
        dev,
        left_p,
        right_p,
        not_operator=-1,
};
enum precedence{
    low,
    high
};

int operator(char operator){
   switch (operator)
       {
        case '+':
            return add;
        break;
        case '-':
            return sub;
        break;
        case '*':
            return mul;
        break;
        case '/':
            return dev;
        break;
        case '(':
            return left_p;
        break;
        case ')':
            return right_p;
        break;
        default:
            return -1;
        break;
       } 
}
int precedence(char c){
    switch (operator(c))
    {
        case add:
        case sub:
            return low;
        break;
        case mul:
        case dev:
            return high;
        break;

    }
}
float calculate(char * rpn,int size){
    stack_t *num_stack =create_stack(size,"float");
    if(num_stack==NULL){
        return 0.0;
    }
    for(int i=0; i<size;i++){
        if(operator(rpn[i])==not_operator){
            float value = (float)(rpn[i]-'0');
            push(num_stack,value);
            continue;
        }
        float a,b=0;
        pop(num_stack,&b);
        pop(num_stack,&a);
        switch (operator(rpn[i]))
        {
            case add:
                push(num_stack,(float)(a+b));
            break;
            case sub:
                push(num_stack,(float)(a-b));
            break;
            case mul:
                push(num_stack,(float)(a*b));
            break;
            case dev:
              push(num_stack,(float)(a*b));
            break;
            default:
                return 0;
            break;
        }
    }
    float result;
    
    pop(num_stack,&result);
    destroy_stack(num_stack);
    return result;
}
int main(){
    char *user_input=NULL;
    scanf("%m[^\n]",&user_input);
    char rpn[strlen(user_input)+1];
    // user input
    stack_t *char_stack = create_stack(sizeof(char)*strlen(user_input),"char");
    // stack creation
    for(int i =0;i<strlen(user_input);i++){
        char cToStr[2];
        cToStr[1] = '\0';
        cToStr[0]=user_input[i];
        //char to sting for strcat
        if(operator(user_input[i])==not_operator){
            strcat(rpn,cToStr);
            continue;
            //if is not operator add to rpn;
        }
        else if(operator(user_input[i])==left_p){
            push(char_stack,user_input[i]);
            continue;
            // if is ( push to stack
        }
        else if (operator(user_input[i])==right_p){
            char temp;
            //temp variable reqired to peek
            while(!is_empty(char_stack)){
                pop(char_stack,&temp);
                if(temp=='('){
                    break;
                }
                for(int i=0;i<sizeof(rpn);i++){
                    if(rpn[i]=='\0'){
                        rpn[i]=temp;
                        rpn[i+1]='\0';
                        break;
                    }
                }
                //pops operators from stack until operator is = ( append them to rpn
            }
            

        }
        else{
            //if is operator
            char temp;
            peek(char_stack,&temp);
            if(precedence(temp)>=precedence(user_input[i])){
                //checks order of operations 
                while (!is_empty(char_stack)&&temp!='('&&temp!=')')
                {
                    // pops everything from stack 
                    pop(char_stack,&temp);
                    for(int i=0;i<sizeof(rpn);i++){
                        if(rpn[i]=='\0'){
                            rpn[i]=temp;
                            rpn[i+1]='\0';
                            break;
                        }
                    }
                    // if rpn string is to small makes it bigger

                }
            }
            push(char_stack,user_input[i]);
        }

    }
    while (!is_empty(char_stack))
    {
        //pops whats left from stack
        int temp;
        pop(char_stack,&temp);
        for(int i=0;i<sizeof(rpn);i++){
            if(rpn[i]=='\0'){
                rpn[i]=temp;
                rpn[i+1]='\0';
                break;
            }
        }
        // if rpn string is to small makes it bigger
   
    }
    destroy_stack(char_stack);
    printf("%s\n",rpn);
    printf("%f\n",calculate(rpn,strlen(rpn)));
    //printf("%d",calculate("22+",3));
    //calculate(rpn,strlen(rpn));
    return 0;
}