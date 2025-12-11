enum operators{
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
int operators(char o);
char *postfix_to_infix(char *rpn,int size);
void insert_char(char *str, int pos, char ch);
float calculate(char * rpn,int size);
int precedence(char c);