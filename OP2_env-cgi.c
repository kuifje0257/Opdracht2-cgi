#include <stdio.h>
#include <stdlib.h>
#define MAXLEN 80
#define EXTRA 5
/* 4 for field name "data", 1 for "=" */
#define MAXINPUT MAXLEN+EXTRA+2
/* 1 for added line break, 1 for trailing NUL */
#define DATAFILE "/var/www/html/data.json"

void unencode(char *src, char *last, char *dest)
{
 for(; src != last; src++, dest++)
   if(*src == '+')
     *dest = ' ';
   else if(*src == '%') {
     int code;
     if(sscanf(src+1, "%2x", &code) != 1) code = '?';
     *dest = code;
     src +=2; }     
   else
     *dest = *src;
 *dest = '\n';
 *++dest = '\0';
}

int main(void)
{
char *lenstr;
char input[MAXINPUT], data[MAXINPUT];
long len;
printf("%s%c%c\n",
"Content-Type:text/html;charset=iso-8859-1",13,10);
printf("<TITLE>Response</TITLE>\n");
lenstr = getenv("CONTENT_LENGTH");
if(lenstr == NULL || sscanf(lenstr,"%ld",&len)!=1 || len > MAXLEN)
  printf("<P>Error in invocation - wrong FORM probably.");
else {
  FILE *f;
  fgets(input, len+1, stdin);
  unencode(input+EXTRA, input+len, data);
  f = fopen(DATAFILE, "a+");
  if(f == NULL)
    printf("<P>Sorry, cannot store your data.");
  else
    fputs(data, f);
  fclose(f);
  printf("<P>Thank you! Your contribution has been stored.");

  printf("<br><a href=\"http://brankopi/index.html\" >return</a>");
  }
return 0;
}