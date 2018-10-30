#include <stdio.h>
#include <string.h>

typedef enum
{
	result_OK = 0,
	result_Error
} General_Result;

void welcome_UI(char *option_choice);

int main()
{
	char *option_choice, a;
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
	General_Result user_result = result_Error;
	char user_choice[256] = { 0 };

	printf("Welcome to the EXCITING GAME!\n");
	printf("Please choose the option with serial number before it.\n\n");
	printf("\t\t\ta. START!\n\n");
	printf("\t\t\tb. Exit\n\n");

	while (user_result == result_Error)
	{
		printf("Your choice is(a/b): ");
		gets(user_choice);
		fflush(stdin);

		if (strlen(user_choice) == 1)
		{
			switch (user_choice[0])
			{
			case 'a':
			case 'b':
				user_result = result_OK;
				break;
			default:
				user_result = result_Error;
			}
		}
		if (user_result == result_Error)
			printf("Your input is illegal, please try again!\n");
	}
	*option_choice = user_choice[0];
}