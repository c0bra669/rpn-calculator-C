#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<stack.h>
#include"calc.h"
//cstack librery  
#define _GNU_SOURCE
// gnu extension 
int operators(char o){
   switch (o)
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
    switch (operators(c))
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
    stack_t *num_stack =create_stack(size,float_t);
    if(num_stack==NULL){
        return 0.0;
    }
    //creates stack and checks if it was created
    for(int i=0; i<size;i++){
        if(operators(rpn[i])==not_operator){
            float value = (float)(rpn[i]-'0');
            // if current char is a number, converts it to float, pushes it to the stack
            push(num_stack,value);
            continue;
        }
        float a,b=0;
        pop(num_stack,&b);
        pop(num_stack,&a);
        //pops two digiets
        switch (operators(rpn[i]))
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
              push(num_stack,(float)(a/b));
            break;
            default:
                return 0;
            break;
        }
    }
    // checks which operator is used performs operations
    float result;
    
    pop(num_stack,&result);
    // last item on a stack is result
    destroy_stack(num_stack);
    return result;
}
void insert_char(char *str, int pos, char ch)
{
    size_t len = strlen(str);
    memmove(str + pos + 1, str + pos, len - pos + 1);  // shift right
    str[pos] = ch;
}
char *postfix_to_infix(char *rpn, int size) {

    stack_t *stack = create_stack(size, char_t);
    if (stack == NULL){
        return NULL;
    }
    // allocate memory 
    char *infix = malloc(size * 4);  
    if (!infix){
        return NULL;
    }
    infix[0] = '\0'; 
    for (int i = 0; i < size; i++) {
        char c = rpn[i];
        if (operators(c) == not_operator) {
            // push operand
            push(stack, c);
        } else {
            // pop 2 chars
            char b, a;
            int len = strlen(infix);
            if(pop(stack, &b)){
                if(pop(stack, &a)){
                    infix[len]='(';
                    infix[len+1] = a;
                    infix[len+2] = c;
                    infix[len+3] = b;
                    infix[len+4] = ')';
                    infix[len+5] = '\0';
                }
                else{
                    infix[len]=c;
                    infix[len+1]=b;
                    infix[len+2]='\0';
                }
            }
            else{
                for(int i=0;i<len;i++){
                    char a=infix[i];
                    char b=infix[i+1];
                    if(a==')'&& b=='('){
                        insert_char(infix,i+1,c);
                        break;
                    }
                }
            }
        }
    }
    destroy_stack(stack);
    return infix;
}

int main(int argc, char **argv){
    if(argc==1){
        char *user_input=NULL;
        scanf("%m[^\n]",&user_input);
        char rpn[strlen(user_input)+1];
        // user input
        stack_t *char_stack = create_stack(sizeof(char)*strlen(user_input),char_t);
        // stack creation
        for(int i =0;i<strlen(user_input);i++){
            char cToStr[2];
            cToStr[1] = '\0';
            cToStr[0]=user_input[i];
            //char to sting for strcat
            if(operators(user_input[i])==not_operator){
                strcat(rpn,cToStr);
                continue;
                //if is not operator add to rpn;
            }
            else if(operators(user_input[i])==left_p){
                push(char_stack,user_input[i]);
                continue;
                // if is ( push to stack
            }
            else if (operators(user_input[i])==right_p){
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
    else if (argc==2)
    {
        // work in progres 

        if(strcmp(argv[1],"-R")==0)
        {
            char *user_input=NULL;
            scanf("%m[^\n]",&user_input);
            printf("%s\n",postfix_to_infix(user_input,strlen(user_input)));
            printf("%f",calculate(user_input,strlen(user_input)));
            
            return 0;
        }
        printf("Enter 0 args or -R\n");
        return 0;
    }
    printf("Enter 0 args or -R\n");
    return 0;
}