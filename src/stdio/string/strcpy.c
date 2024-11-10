void strcpy(char *dest, char *src) {
  char* s = dest;
  char* t = src;
  while (*s !='\0')
    {
       *(t) = *(s);
       s++;
       t++;
    }
    *t = '\0';
}