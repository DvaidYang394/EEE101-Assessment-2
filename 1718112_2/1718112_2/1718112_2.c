#include <stdio.h>
#include <string.h>
#include <Windows.h>

typedef enum
{
	result_OK = 0,
	result_Error
} General_Result;

void welcome_UI(char *option_choice);
void info_input(void);

int main()
{
	char *option_choice, a;
	option_choice = &a;

	welcome_UI(option_choice);
	if (*option_choice == 'a')
	{
		name_input();
	}

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
	printf("\t\t\tb. EXIT.\n\n");

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
	if (user_choice[0] == 'a')
	{
		printf("The game will start!\n");
	}
	else
		printf("The game will exit...\n");
	*option_choice = user_choice[0];
}

void info_input(void)
{
	char user_name[256] = { 0 };
	int i = 0;
	General_Result name_result = result_Error, times_result = result_Error;

	system("cls");
	while (name_result == result_Error)
	{
		printf("Enter your name first, press \"ENTER\" to confirm:");
		gets(user_name);
		fflush(stdin);

		if (strlen(user_name) != 0)
		{
			for (i = 0; i < strlen(user_name); i++)
			{
				if (user_name[i] != 32)
				{
					name_result = result_OK;
					break;
				}
			}
		}
		if (name_result == result_Error)
		{
			printf("The name cannot be space, please try again!\n");
			Sleep(1500);
			system("cls");
		}
	}

	while (times_result == result_Error)
	{
		printf("Enter your name first, press \"ENTER\" to confirm:");
		gets(user_name);
		fflush(stdin);

		if (strlen(user_name) != 0)
		{
			for (i = 0; i < strlen(user_name); i++)
			{
				if (user_name[i] != 32)
				{
					name_result = result_OK;
					break;
				}
			}
		}
		if (name_result == result_Error)
		{
			printf("The name cannot be space, please try again!\n");
			Sleep(1500);
			system("cls");
		}
	}
}