#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<stack.h>
//cstack librery  
enum operand{
        add,
        mul 
    };
int operator(char operator){
   switch (operator)
       {
        case '+':
        case '-':
        return add;
        break;
        case '*':
        case '/':
        return mul;
        break;
    
       default:
       return -1;
        break;
       } 
}
int main(){
    char user_input[10];
    char* rpn;
    scanf("%s",&user_input);
    stack_t *char_stack = create_stack(sizeof(user_input),"char");
    for(int i =0;i<strlen(user_input);i++){
        char cToStr[2];
        cToStr[1] = '\0';
        cToStr[0]=user_input[i];
        if(operator(user_input[i])==-1){
            strcat(rpn,cToStr);
            continue;
        }
        else if(user_input[i]=='('){
            push(char_stack,user_input[i]);
            continue;
        }
        else if (user_input[i]==")"){
            char temp;
            
            while(!is_empty(char_stack) && temp!='('){
                peek(char_stack,&temp);
                if(temp=='('){
                    break;
                }
                pop(char_stack,&temp);
                for(int i=0;i<sizeof(rpn);i++){
                    if(rpn[i]=='\0'){
                    rpn[i]=temp;
                    rpn[i+1]='\0';
                    }
                }
            }
            pop(char_stack,&temp);

        }
        else{
            char temp;
            peek(char_stack,&temp);
            while (!is_empty(char_stack)&&temp!='('&&(operator(temp)>=operator(user_input[i])))
            {
                pop(char_stack,&temp);
                for(int i=0;i<sizeof(rpn);i++){
                    if(rpn[i]=='\0'){
                    rpn[i]=temp;
                    rpn[i+1]='\0';
                    }
                }

            }

            push(char_stack,user_input[i]);
        }

    }
    while (!is_empty(char_stack))
    {
        int temp;
        pop(char_stack,&temp);
        for(int i=0;i<sizeof(rpn);i++){
            if(rpn[i]=='\0'){
                rpn[i]=temp;
                rpn[i+1]='\0';
            }
        }
    }
    destroy_stack(char_stack);
    printf("%s",rpn);
    return 0;
}