#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h> 
#include <ctype.h>
#include <math.h>
#include <iso646.h>

#define YELLOW  "\e[1;33m"
#define PURPLE  "\e[1;35m"
#define BLUE    "\e[1;34m"
#define RED     "\e[1;31m"
#define DEFAULT "\e[0m"

#define log(v) printf(PURPLE "\n[%s:%d] " #v " == " BLUE "%s \n" DEFAULT, __FILE__, __LINE__, v)

#include "stack.c"
#include "code.c"


bool seq(char s1[], char s2[]) {  // string equal
    if(strcmp(s1, s2) == 0) return true; 
    else return false;
}

bool is_definition(char w[]) {
    int l = strlen(w);     
    if((l>1) and (w[l-1]=='{' or w[l-1]==':')) return true;
    else return false;
}

char *next_cmd(char f[], char s[]) {
    int i = 0, j = 0;
    while(s[i] != '\0') {
        if(not isspace(s[i])) f[j++] = s[i];
        else if(j > 0) break;
        i++;
    }
    f[j] = '\0';           
    return &s[i];
}

bool eval_word(char w[], char source[]) {
    char w2[80];
    //strcpy(w, word);
    se_t number;
    se_t n2;
    //char *str[80];
    char *p;                      
    unsigned index;                                           
    if(sscanf(w, "%lf", &number) == 1) 
        {stack_push(number);}
    else 
        if(sscanf(w, "[%u]", &index) == 1) stack_push(stack_read(index));
    //else if(sscanf(w, "'%[ -~^']'", str) == 1) printf(str);
    //else if(seq(w, "")) printf("oh, hai");
    else 
        if(seq(w, "q")) exit(0);
    else if(seq(w, "return")) return false;
    else if(seq(w, ".")) return false;
   // else if(seq(w, "then")) { return false;}
    else if(seq(w, "log")) stack_print();
    else if(seq(w, "c")) stack_clear();
    else if(seq(w, "swp")) stack_swap();
    else if(seq(w, "x")) stack_pop();
    else if(seq(w, "+")) stack_infix(+);
    else if(seq(w, "^")) stack_prefix(pow);
    else if(seq(w, "*")) stack_infix(*);
    else if(seq(w, "/")) stack_infix(/);
    else if(seq(w, ">")) stack_infix(>);
    //else if(seq(w, "!")) stack_prefix_1(!);
    else if(seq(w, "==")) stack_infix(==);
    else if(p = find_def(w, source), p != NULL) eval(p, source);
    else printf(RED "%s? \n" DEFAULT, w);    
    return true;
}

void eval(char sentence[], char source[]) {
    char next[80]; //, rest[80];
    char *rest;
    rest = next_cmd(next, sentence);
                        //printf("[%s|%s]",next,rest);
    if(*next == '\0') return;
    
    if(is_definition(next)) {
        printf("Unimplemented \n");
    } else {
        if(seq(next, "then")) {
            rest = next_cmd(next, rest);
            if(stack_peek()==0) rest = next_cmd(next, rest);
            stack_pop();
        }
        if(seq(next, ":")) {
            rest = next_cmd(next, rest);
            if(stack_peek()==0) { 
                rest = strstr(rest, ".");
                rest = next_cmd(next, rest);
                rest = next_cmd(next, rest);
            }
            stack_pop();
        }                   
        if(eval_word(next, source)) eval(rest, source);
    }
}
     
int main() {
    char *src = add_src(std, NULL); 
    char buffer[80];

    while(1) {
        stack_print();
        printf(YELLOW "> " DEFAULT);  // ➤
        fgets(buffer, 80, stdin); 
        eval(buffer, src);
    }
}
    
    















