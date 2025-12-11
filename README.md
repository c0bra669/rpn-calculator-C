# rpn-calculator-C  
hanges input from infix to postfix and caclulates or from postfix to infix
# Usage
**ENTER ONLY INTAGERS WITHOUT SPACES!**
## use with no arguments 
```bash
calculate
Enter infix expresion:
<infix>
```
## OR -R
```bash
calculate -R
Enter postfix expresion:
<postfix>
```
![a](screenshots/image.png)
# Instalation
## Linux only:
Install libcstack and link it
```bash
git clone https://github.com/c0bra669/libcstack.git
cd libcstack
./install.sh
gcc -o calculate src/calc.c -lcstack
```
## OR
compile and link libstack staticly

# Dependencies
- libcstack
- GNU C
