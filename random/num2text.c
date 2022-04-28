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
char* get_hundreds(char *);
char* get_tens(char *);
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
char num_words_3[][9]={"hundred","thousand"};

int main()
{
	char *str, *usr_str;
	int len = 0,i;
	usr_str = (char *)malloc(sizeof(char) * 60);
	int *num = NULL;
	char *text = NULL;
	printf("Enter number in string\n");
	scanf("%s",usr_str);
	printf("Entered number is %s\n",usr_str);
	str = usr_str;
	if(usr_str[0] == '0')
		str = usr_str+1;
	num = (int *)malloc((len = strlen(str)));
	bool free_text = false;
	int text_index = 0;
	char *tens_text = NULL;
	int len_hundreds = 0;
	if(validate_num_in_text(str) == 0)
	{
		printf("Entered number is correct\n");
		i = 0;
		switch(len)
		{
			case 1:
				text = (char *)malloc(sizeof(char) * (strlen(num_words[str[i]-'0'])+1));
				strcpy(text, num_words[str[i]- '0']);
				break;
			case 2:
				text = get_tens(str);
				break;
			case 3:
				text = get_hundreds(str);
				break;
			case 4:
				len_hundreds = get_fixed_text_len(len);
				text = (char *)malloc(sizeof(char) * len_hundreds);
				strcpy(text, num_words[str[0]-'0']);
				text[(len_hundreds = strlen(text))]= ' ';
				strcpy(len_hundreds+1+text, num_words_3[1]);
				text[(len_hundreds = strlen(text))]= ' ';	
				strcpy(1+len_hundreds+text, (tens_text = get_hundreds(str+1)));
				free(tens_text);
				break;
			case 5:
				break;
		}
		printf("Entered number is %s\n",text);
	}
	else
		printf("Incorrect text: Enter only numbers !!!!!!!!!!\n");

	if(usr_str != NULL)
		free(usr_str);
	if(num != NULL)
		free(num);
	free(text);
	return 0;
}


char *get_hundreds(char *str)
{
	int len = strlen(str), len_hundreds;
	char *text = NULL, *tens_text = NULL;
	text = (char *)malloc(sizeof(char) * get_fixed_text_len(len));
	strcpy(text,num_words[str[0]-'0']);
	len_hundreds = strlen(text);
	text[len_hundreds] = ' ';
	strcpy(len_hundreds+1+text, num_words_3[0]);
	text[(len_hundreds = strlen(text))] = ' ';
	strcpy(1+len_hundreds+text, (tens_text = get_tens(str+1)));
	free(tens_text);

	return text;
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
			return 14;//includes space
			break;
		case 3:
			return 14+get_fixed_text_len(2);
			break;

		case 4:
			return 15+get_fixed_text_len(3);
			break;
		case 5:
			break;

	}
	return 0;
}


char* get_tens(char *str)
{
	char *text = NULL;
	int len = strlen(str);
	int text_index = 0;
	if(strcmp(str, "10") == 0)

	{
		text = (char *)malloc(sizeof(char) * (1+strlen(num_words[10])));
		strcpy(text, num_words[10]);
	}
	else if(str[0] == 1+'0')//check for 11-19
	{	
		text_index = (str[1]-'0')+10;
		text = (char *)malloc(sizeof(char) * (1+strlen(num_words[text_index])));
		strcpy(text, num_words[text_index]);
		printf("Text no match\n");
	}
	else if(strcmp(str,"20")==0)
	{
		text = (char *)malloc(sizeof(char) * (1+strlen(num_words_2[0])));
		strcpy(text, num_words_2[0]);
	}
	else
	{
		text = (char *)malloc(sizeof(char) * get_fixed_text_len(len));
		char *cpyret = (char *)strcpy(text, num_words_2[(str[0]-'0')-2]);
		text[(len = strlen(cpyret))]= ' '; 
		strcpy(len+1+text,num_words[str[1]-'0']);
	}
	return text;
}
