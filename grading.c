#include<stdio.h> 
int main()
{
char grade;
printf("MUSINGU PRIMARY SCHOOL\n");
printf("Enter your grade:"); 
scanf("%c", &grade);
switch (grade) 
{
case 'A':
printf("Excellent!\n");
break; 
  
case 'B':
printf("Very Good!\n");
break;
  
case 'C':
printf("Good!\n");
break;
  
case 'D':
printf("Work harder!\n");
break; 

default:

printf("Fail!\n");
}
  return 0;
}
