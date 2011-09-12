

char code[] = "\n"
"max: [2] [2] > [3] [3] swp > [3] * swp [4] * + swp x swp x return \n"
"e: 2.71822 return \n"
"pi: 3.14159 return \n"
"not: 0 == then 1 [1] 1 == then . 0 . \n"
"!: not . \n"
"if: . \n"
"bool: ! ! . \n"
"and: * bool . \n"
"!=: == ! return \n"
"<: swp > return \n"
"-: -1 * + return \n"
"goto: log 1 +  goto\n"
"or: ! swp ! and ! return\n"
"==: [2] [2] > [3] [3] < or ! swp x swp x return \n"
"fact: if [1] 0 == : x 1 .                  \n"
"                    [1] 1 - fact * .       \n"
//"fact: [1] 0 == then fact(0) [1] 1 == then return fact(n) return    \n"
//"fact(0): x 1 return  \n"
//"fact(n): [1] 1 - fact * return \n"      
"do: 1 + [1] 10 > then . x do . \n"
;


char *find_def(char *word, char *code) {
    char def[sizeof(word) + 2];
    sprintf(def, "\n%s:", word);
       // printf();
    char *r = strstr(code, def);
    if(r == NULL) return NULL;
    else return r + strlen(def);
}       


//char code[] = "e: 2.71822 ";
//char code[] = "!=: == !":
