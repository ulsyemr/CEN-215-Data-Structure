#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define one_hundred 100000
#define ten_k 10000
#define HASH_SIZE 1009
#define one_k 1000

typedef struct text
{
	char string[30];
	int worth;
	struct text *next;
} SinglyList;

SinglyList *first = NULL;
SinglyList *last = NULL;


char ten_thousand[ten_k][30];
char one_hundred_k[one_hundred][30];

typedef struct HashTable {
  char array[30];
}HASH;
HASH Before_Hash[one_k];
HASH Hash_Table[one_k];
int hash_value[HASH_SIZE];



void _ascending(char ten_thousand[ten_k][30], int n) 
{ 
 int i, j;  
 for (i = 0; i < n - 1; i++) 
  for (j = 0; j < n - i - 1; j++) 
   if (strcmp(ten_thousand[j], ten_thousand[j + 1]) > 0) 
   { 
    char temp[30];
    strcpy(temp, ten_thousand[j]); 
    strcpy(ten_thousand[j], ten_thousand[j + 1]); 
    strcpy(ten_thousand[j + 1], temp); 
   } 
}
void _descending(char ten_thousand[ten_k][30], int n) 
{ 
 int i, j;  
 for (i = 0; i < n - 1; i++) 
  for (j = 0; j < n - i - 1; j++) 
   if (strcmp(ten_thousand[j + 1],ten_thousand[j] ) > 0) 
   { 
    char temp[30]; 
    strcpy(temp, ten_thousand[j]); 
    strcpy(ten_thousand[j], ten_thousand[j + 1]); 
    strcpy(ten_thousand[j + 1], temp); 
   } 
}
void Get_10k_Text() {
  char line[20];
  int i = 0;
  FILE *file = fopen("10-million-password-list-top/10000.txt", "r");
  while(!feof(file)) {
    fgets (line,20,file);
    strcpy(ten_thousand[i],line);
    i++;
  }
  fclose(file);  
}
void display_array_after_sorting(char ten_thousand[ten_k][30]) {
  for (int i = 0; i <= 9; i++) 
  printf("%s", ten_thousand[i]);
}

void Get_100k_Text()
{
    char array[20];
    int i = 0;
    FILE *file = fopen("10-million-password-list-top/100000.txt", "r");
    while (!feof(file))
    {
        fgets(array, 20, file);
        strcpy(one_hundred_k[i], array);
        i++;
    }
    fclose(file);
}
int Search_one_hundred_k(char password[])
{
 int i = 0;
 while ( i < one_hundred)
 {
  if (strncmp(one_hundred_k[i], password, strlen(password)) == 0) {
   printf("Password is found [%d]'th line of text file.",i+1);
   return 1;
  }
 i++;
 }
 printf("Password is not found.");
 return -1;
}


void initialize_before_hash() {
	int i = 0;
  while ( i < one_k)
	{
		strcpy(Before_Hash[i].array, "");
  i++;
  }
}
void initialize_hash() {
	int i = 0;
  while ( i < one_k)
	{
		strcpy(Hash_Table[i].array, "");
  i++;
  }
}


void Get_1k_Text() {
  initialize_before_hash();
	initialize_hash();
  char line[20];
  int i = 0;
  FILE *file = fopen("10-million-password-list-top/1000.txt", "r");
  while(!feof(file)) {
    fgets (line,20,file);
		line[strlen(line) - 1] = '\0';
    strcpy(Before_Hash[i].array,line);
    // printf("%s",Before_Hash[i].array);
    i++;
  }
  fclose(file);
}


int Hash(char d[]) {
  int unique =0 ;
  for(int i = 0; i < strlen(d);i++) {
  unique = unique + (d[i] - 48);
  }
  unique *= unique;
  int temp = unique%HASH_SIZE;
  temp >1000 ? temp /=2 : temp;
  return temp;
}
int insert_Hash(HASH a[], int size)
{ 
  
  int hash_key;
  for (int j = 0; j < size; j++)
  {
  int temporary;
  temporary = Hash(a[j].array);
  hash_value[j] = temporary;
  hash_key = hash_value[j];
  if (strcmp(Hash_Table[hash_key].array, "") == 0)
  {
     strcpy(Hash_Table[hash_key].array, a[j].array);
  }
  else
  {
    for (int k = hash_key; k <= size; k++)
    {
     if (strcmp(Hash_Table[k].array, "") == 0)
     {
       strcpy(Hash_Table[k].array, a[j].array);
       break;
     }
    }
  }
 }
}
void display_hash() {
  for (int i=0;i<one_k; i++) {
    printf("%d)%s\n",i,Hash_Table[i].array);
  }
}
int search_Hash(HASH a[], char s[20])
{
 int collusion = 0;
 int temporary = Hash(s);
 if (strcmp(Hash_Table[temporary].array, s) == 0) {
  printf("Your password is found no collusion detected.");
  return 1;
 }
 else
 {
  int i = temporary;
  while ( i < HASH_SIZE)
  {
   collusion +=1;
   if (strcmp(Hash_Table[i].array, s) == 0) {
    printf("Your password is found ---> number of collusion has occured %d",collusion);
    return 1;
    break;
   }
  i++;
  }
  printf("Your password is not found");
 }
}


void Get_1k_Text_Linked_List()
{
	char line[30];
	int i = 0;

	FILE *file = fopen("./10-million-password-list-top/1000.txt", "r");
	while (!feof(file))
	{
		fgets(line, 30, file);
		line[strlen(line) - 1] = '\0';
	
 SinglyList *pointer;
	pointer = (SinglyList *)malloc(sizeof(SinglyList));

	strncpy(pointer->string, line, 30);

	if (first == NULL)
	{
		first = pointer;
		last = pointer;
		pointer->next = NULL;
	}
	else
	{
		last->next = pointer;
		pointer->next = NULL;
		last = pointer;
	}
		i++;
	}
	fclose(file);
}
int isPalindrome(char line [30]) 
{
 int l = 0;
 int h = strlen(line);
 while (l < h) {
  if (line[l++] != line[h--]) {
   return 1;
  }
  else return strlen(line);
 }
}
int Number_Degree(char line[30])
{
 int count = 0,i = 0;
	while ( i<strlen(line))
	{
		if (line[i] >= '1' && line[i] <= '5')
			count++;
  i++;
	}
	return count;
}
int Letter_Degree(char line[30])
{
	int count = 0,i = 0;
	while ( i < strlen(line))
	{
		if (line[i] >= 'g' && line[i] <= 'w')
			count++; 
  i++;
	}
	return count;
}
int Degree()
{
	SinglyList *pointer;
	pointer = first;

	do
	{
		char line[30];
		strncpy(line, pointer->string, 30);
		int string_length = strlen(line);
    int palindrome = isPalindrome(line);
		int number_degree = Number_Degree(line);
		int letter_degree = Letter_Degree(line);
		pointer->worth = (string_length * 7) + (number_degree *1) + (letter_degree * 3) + palindrome;
		pointer = pointer->next;
	} while ((pointer != NULL));
	return 0;
}
int Order_List()
{
	SinglyList *pointer;
	pointer = first;
	int i = 0;
	while (i < 10)
	{
		printf("[%d]  Password -> %s || Degree -> %d\n",i + 1, pointer->string, pointer->worth);
		pointer = pointer->next;
		i++;
	}
	return 0;
}
void Least_Degree()
{
	SinglyList *real = first;
	SinglyList *sign = NULL;
	int flag;
	char str_temporary[30];
	while (real != NULL)
	{
		sign = real->next;

		while (sign != NULL)
		{
			if (real->worth > sign->worth)
			{
				flag = real->worth;
				real->worth = sign->worth;
				sign->worth = flag;

				strcpy(str_temporary, real->string);
				strcpy(real->string, sign->string);
				strcpy(sign->string, str_temporary);
			}
			sign = sign->next;
		}
		real = real->next;
	}
}
void Most_Degree()
{
	SinglyList *real = first;
	SinglyList *sign = NULL;
	int flag;
	char str_temporary[30];
	while (real != NULL)
	{
		sign = real->next;

		while (sign != NULL)
		{
			if (sign->worth > real->worth)
			{
				flag = real->worth;
				real->worth = sign->worth;
				sign->worth = flag;

				strcpy(str_temporary, real->string);
				strcpy(real->string, sign->string);
				strcpy(sign->string, str_temporary);
			}
			sign = sign->next;
		}
		real = real->next;
	}
}



int main() {
int option;
	do
	{
		printf("\n  	1: Sort 10k text ascending order.");
		printf("\n  	2: Sort 10k text desending order.");
		printf("\n  	3: Search password in 100k text.");
    printf("\n  	4: Hash");
		printf("\n  	5: Least Passwords.");
		printf("\n  	6: Most Passwords.");
		printf("\n  	0: EXIT");
		printf("\n 	  Enter your option : ");
		scanf("%d", &option);
		switch (option)
		{
			case 1: Get_10k_Text();
              _ascending(ten_thousand,ten_k);
              display_array_after_sorting(ten_thousand);	  
              break;

			case 2: Get_10k_Text();
              _descending(ten_thousand,ten_k);
              display_array_after_sorting(ten_thousand); 
              break;

			case 3: Get_100k_Text();
              char wanted[30];
              printf("Insert password--->");
              scanf("%s",wanted);
              Search_one_hundred_k(wanted); 
              break;

			case 4: Get_1k_Text();
  						insert_Hash(Before_Hash,one_k);
  						char called[20];
							printf("Insert password---->");
							scanf("%s",called);
							search_Hash(Hash_Table,called);
              break;
			case 5: Get_1k_Text_Linked_List();
	            Degree();
	            printf("Least Passwords: \n");
	            Least_Degree();
	            Order_List(); 
              break;
			case 6: Get_1k_Text_Linked_List();
              Degree();
              printf("Most Passwords: \n");
	            Most_Degree();
	            Order_List(); 
              break;

		}
	} while (option != 0);

	return 0;
}
















