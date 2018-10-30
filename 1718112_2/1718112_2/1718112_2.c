#include <stdio.h>

typedef enum
{
	result_OK = 0,
	result_Error
} General_Result;

void welcome_UI(char *option_choice);
General_Result welcome_choice(char *choice);

int main()
{
	char *option_choice, a = 2;
	option_choice = &a;
	welcome_UI(option_choice);
	if (*option_choice == 'a')
	{
		printf("The game will start!\n");
	}
	else
		printf("The game will exit...\n");

	system("pause");
	return 0;
}

void welcome_UI(char *option_choice)
{
	General_Result option_result = result_Error;

	printf("Welcome to the EXCITING GAME!\n");
	printf("Please choose the option with serial number before it.\n\n");
	printf("\t\t\ta. START!\n\n");
	printf("\t\t\tb. Exit\n\n");

	while (option_result == result_Error)
	{
		printf("Your choice is(a/b): ");
		option_result = welcome_choice(option_choice);
		if (option_result == result_Error)
			printf("Your input is illegal, please try again!\n");
	}
}

General_Result welcome_choice(char *choice)
{
	General_Result result;

	scanf("%c", choice);
	getchar();
	fflush(stdin);
	switch (*choice)
	{
	case 'a':
	case 'b':
		result = result_OK;
		break;
	default:
		result = result_Error;
	}

	return result;
}