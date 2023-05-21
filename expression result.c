#include<stdio.h>
main(){
int s=0,i,t;
char a;
for(t=1;;){
scanf("%d %c",&i,&a);
t=t*i;
if(a=='-')
{
s=s+t;
break;
}
if(a=='+')
{
s=s+t;
t=1;
}}
printf("%d",s);
}
