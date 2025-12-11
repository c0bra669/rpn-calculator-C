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
float calculate(char * rpn,int size);
int precedence(char c);