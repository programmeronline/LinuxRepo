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
char *get_ten_thousand(char *);
char* get_hundreds(char *);
char* get_tens(char *);
char* get_thousand(char *);
void print_num2text(char *);
char *i2str(int);
char num_words[][11]= {"zero",
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
char numbers[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
char *str = NULL;
int main()
{
	char *str, *usr_str;
	usr_str = (char *)malloc(sizeof(char) * 60);
	str = (char *)malloc(sizeof(char) * 6);
	int limit = 0;
	printf("Enter limit\n");
	scanf("%d",&limit);
	for(int i = 1; i < limit ; i++)
	{
		sprintf(str, "%d", i);
		print_num2text(str);
		fflush(stdout);
		memset(str, 0, 6);
	}
	/*printf("Enter number in string\n");
	scanf("%s",usr_str);
	printf("Entered number is %s\n",usr_str);
	*/
	free(str);
	return 0;
}

char *i2str(int num)
{
	int digit = 0, i = 0;
	if(num < '9')
		str[i] = numbers[num];
	while(num/10 != 0)
	{
		digit = num % 10;
		str[i++] = numbers[digit];
		num = num/10;
	}
	str[i] = '\0';
}
void print_num2text(char *usr_str)
{
	int len = strlen(usr_str),i;
	char *str = usr_str;
	if(usr_str[0] == '0')
		str = usr_str+1;
	int text_index = 0;
	int len_hundreds = 0;
	
	char *tens_text = NULL,*tens_text1, *hundreds_text = NULL;
	char *text = NULL;
	
	if(validate_num_in_text(str) == 0)
	{
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
				text = get_thousand(str);
				break;
			case 5:
				text = get_ten_thousand(str);
				break;
		}
		printf("%s : %s\n",usr_str,text);
	}
	else
		printf("Incorrect text: Enter only numbers !!!!!!!!!!\n");
	free(text);

}
char *get_ten_thousand(char *str)
{
	int len = strlen(str);
	char *tens_text=NULL, *hundreds_text=NULL, *tens_text1 = NULL;
	char *text = (char *)malloc(sizeof(char) * get_fixed_text_len(len));
	tens_text = (char *)malloc(sizeof(char) * 3);
	tens_text1 = tens_text;
	strncpy(tens_text, str, 2);
	tens_text[2]='\0';
	tens_text = get_tens(tens_text);	
	strcpy(text, tens_text);
	len = strlen(text);//copy number for first two digits
	text[len]=' ';
	strcpy(1+len+text, num_words_3[1]);//copy "thousand"
	len = strlen(text);
	hundreds_text = get_hundreds(str+2);
	if(hundreds_text != NULL)
	{
		text[len]=' ';
		strcpy(1+len+text, hundreds_text);
		free(hundreds_text);
	}
	free(tens_text);
	free(tens_text1);
	return text;
}
char* get_tens(char *str)
{
	char *text = NULL;
	int len = strlen(str);
	int text_index = 0;
	if(strncmp(str, "00",2) == 0)
		return NULL;
	if(str[0] == '0')
	{
		text = (char *)malloc(sizeof(char) * (1+strlen(num_words[str[1]-'0'])));
		strcpy(text, num_words[str[1] - '0']);
	}
	else if(strcmp(str, "10") == 0)

	{
		text = (char *)malloc(sizeof(char) * (1+strlen(num_words[10])));
		strcpy(text, num_words[10]);
	}
	else if(str[0] == 1+'0')//check for 11-19
	{	
		text_index = (str[1]-'0')+10;
		text = (char *)malloc(sizeof(char) * (1+strlen(num_words[text_index])));
		strcpy(text, num_words[text_index]);
	}
	else if(strcmp(str,"20")==0)//20
	{
		text = (char *)malloc(sizeof(char) * (1+strlen(num_words_2[0])));
		strcpy(text, num_words_2[0]);
	}
	else//21-99
	{
		text = (char *)malloc(sizeof(char) * get_fixed_text_len(len));
		char *cpyret = (char *)strcpy(text, num_words_2[(str[0]-'0')-2]);
		if(str[1] != '0')
		{
			text[(len = strlen(cpyret))]= ' '; 
			strcpy(len+1+text,num_words[str[1]-'0']);
		}
	}
	return text;
}
char* get_thousand(char *str)
{
	int len_hundreds = 0;
	int len = strlen(str);
	char *text = NULL, *tens_text = NULL;
	len_hundreds = get_fixed_text_len(len);
	text = (char *)malloc(sizeof(char) * len_hundreds);
	strcpy(text, num_words[str[0]-'0']);//copy the first digit, ex 1000, one is copied
	text[(len_hundreds = strlen(text))]= ' ';//space "one "
	strcpy(len_hundreds+1+text, num_words_3[1]);//copy thousand- "one thousand "
	if(strncmp(str+1,"000",3) == 0)
	{
		return text;
	}
	text[(len_hundreds = strlen(text))]= ' ';	
	tens_text = get_hundreds(str+1);
	if(tens_text != NULL)
	{
		strcpy(1+len_hundreds+text, tens_text);
		free(tens_text);
	}
	return text;
}

char *get_hundreds(char *str)
{
	int len = strlen(str), len_hundreds = -1;
	char *text = NULL, *tens_text = NULL;
	text = (char *)malloc(sizeof(char) * get_fixed_text_len(len));
	if(str[0] == '0')
	{
		if(str[1] != '0')
		{
			len_hundreds = -1;
			goto TENS;
		}
		else
		{
			if(str[2] != '0')
			{
				strcpy(text, num_words[str[2]-'0']);
				return text;
			}
			else 
			{
				free(text);	
				return NULL;
			}
		}
	}
	strcpy(text,num_words[str[0]-'0']);
	len_hundreds = strlen(text);
	text[len_hundreds] = ' ';
	strcpy(len_hundreds+1+text, num_words_3[0]);
	text[(len_hundreds = strlen(text))] = ' ';

TENS:   tens_text = get_tens(str+1);
	if(tens_text !=  NULL)
	{
		strcpy(1+len_hundreds+text, tens_text);
		free(tens_text);
	}
	else
		text[len_hundreds+1] = '\0';
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
			return 23+get_fixed_text_len(3);
			break;

	}
	return 0;
}


