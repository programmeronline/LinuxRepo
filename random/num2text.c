#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <errno.h>
#include <unistd.h>
#include <stdbool.h>


/*
 *one
 two
 three
 four
 five
 six
 seven
 eight
 nine
 ten
 twenty
 thirty
 forty
 fifty
 sixty
 seventy
 eighty
 ninety
 hundred
 thousand

 1- one
 23-twenty three
 ten eleven twelve thirteen fourteen fifteen sixteen
 seventeen eighteen nineteen twenty thirty forty fifty sixty seventy eighty ninety hundred thousand

 234-two hundred thirty four
 4567- four thousand five hundred sixty seven
 23456- twenty three thousand four hundred fifty six
 99999- ninety nine thousand nine hundred ninety nine
 77777- seventy seven thousand seven hundred seventy seven
 7777- seven thousand seven hundred seventy one
 777 seven hundred seventy seven
 77- seventy seven
 7 seven
//till twenty we have to print actual string, i.e till the text is of only one word, only when there are
//more than two words we need to construct the string
 *
 * */
int validate_num_in_text(const char *);
int get_fixed_text_len(int len);
int main()
{
	char *str;
	char num_words[][9]= {"zero",
		"one","two","three","four","five",
		"six","seven","eight","nine","ten",
		"eleven","twelve", "thirteen","fourteen","fifteen",
		"sixteen","seventeen","eighteen","nineteen"
	};
	char num_words_2[][9]={
		"twenty","thirty","forty","fifty",
		"sixty","seventy","eighty","ninety"
	};
	char num_words_3[][8]={"hundred","thousand"};
	int len = 0,i;
	str = (char *)malloc(sizeof(char) * 60);
	int *num = NULL;
	char *text = NULL;
	printf("Enter number in string\n");
	scanf("%s",str);
	printf("Entered number is %s\n",str);
	printf("First number is %d\n",str[0]-'0');
	num = (int *)malloc((len = strlen(str)));
	bool free_text = false;
	int text_index = 0;
	
	if(validate_num_in_text(str) == 0)
	{
		text = (char *)malloc(sizeof(char) * get_fixed_text_len(len));
		printf("Entered number is correct\n");
		i = 0;
		while(str[i] != '\0')
		{
			switch(len)
			{
				case 1:
					text = (char *)malloc(sizeof(char) * strlen(num_words[str[i]-'0']));
					strcpy(text, num_words[str[i]- '0']);
					break;
				case 2:
					if(strcmp(str, "10") == 0)
					{
						text = (char *)malloc(sizeof(char) * strlen(num_words[10]));
						strcpy(text, num_words[10]);
					}
					else if(str[0] == 1+'0')//check for 11-19
					{	
						text_index = (str[1]-'0')+10;
						text = (char *)malloc(sizeof(char) * strlen(num_words[text_index]));
						strcpy(text, num_words[text_index]);
						printf("Text no match\n");
					}
					else if(strcmp(str,"20")==0)
					{
						text = (char *)malloc(sizeof(char) * strlen(num_words_2[0]));
						strcpy(text, num_words[20]);
					}
					else
					{
						text = (char *)malloc(sizeof(char) * strlen(num_words[20]));
					}
					break;
				case 3:
					break;
				case 4:
					break;
				case 5:
					break;
			}
			i++;
		}
		printf("Entered number is %s\n",text);
	}
	else
		printf("Incorrect text: Enter only numbers !!!!!!!!!!\n");

	if(str != NULL)
		free(str);
	if(num != NULL)
		free(num);
	if(free_text)
		free(text);
	return 0;
}



int validate_num_in_text(const char* str)
{
	int i = 0;
	while(str[i] != '\0')
	{
		if(str[i] > '9' || str[i] < '0')
			return -1;
		i++;
	}
	if(i == strlen(str))
		return 0;
	else
		return -1;
}


int get_fixed_text_len(int len)
{
	switch(len)
	{
		case 1:
			return 5;
			break;
		case 2:
			return 13;//includes space
			break;
		case 3:
			return 18;
			break;
		case 4:
			break;
		case 5:
			break;

	}
	return 0;
}
