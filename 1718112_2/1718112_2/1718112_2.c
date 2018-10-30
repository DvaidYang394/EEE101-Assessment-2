#include <stdio.h>
#include <string.h>
#include <Windows.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>

typedef enum
{
	rock = 0,
	scissors,
	paper
} General_Select;

typedef enum
{
	result_OK = 0,
	result_Error
} General_Result;

void welcome_UI(char *option_choice);
void info_input(char **user_name_addr, int *game_times, int *name_length);
General_Select computer_select_get(void);
General_Select user_select_get(void);

int main()
{
	char *option_choice, c_pbase, **name_addr, *na_pbase;
	int *game_times, t_pbase, *name_len, nl_pbase, i = 2;
	option_choice = &c_pbase;
	game_times = &t_pbase;
	name_len = &nl_pbase;
	name_addr = &na_pbase;

	welcome_UI(option_choice);
	if (*option_choice == 'a')
	{
		//info_input(name_addr, game_times, name_len);
		//computer_select_get();
		user_select_get();
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
		rewind(stdin);

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

	Sleep(1000);
	*option_choice = user_choice[0];
}

void info_input(char **user_name_addr, int *game_times, int *name_length)
{
	static char user_name[256] = { 0 }, user_times[256] = { 0 };
	int i = 0;
	General_Result name_result = result_Error, times_result = result_Error;
	*user_name_addr = user_name;

	system("cls");
	while (name_result == result_Error)
	{
		printf("Enter your name first, press \"ENTER\" to confirm:");
		gets(user_name);
		rewind(stdin);

		*name_length = strlen(user_name);
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

	system("cls");
	while (times_result == result_Error)
	{
		times_result = result_OK;
		printf("Enter the times you want to play(MUST BE A POSITIVE INTEGER!):");
		gets(user_times);
		rewind(stdin);

		if (strlen(user_times) != 0)
		{
			for (i = 0; i < strlen(user_times); i++)
			{
				if (!isdigit(user_times[i]))
				{
					times_result = result_Error;
					break;
				}
			}
		}
		if (times_result == result_Error)
		{
			printf("The times you input is illegal, please try again!\n");
			Sleep(1500);
			system("cls");
		}
	}
	*game_times = atoi(user_times);
}

General_Select computer_select_get(void)
{
	int randnum = 0;
	General_Select computer_select;

	srand((unsigned int)time(NULL));
	randnum = rand() % 3;
	switch (randnum)
	{
	case 0:
		computer_select = rock;
		break;
	case 1:
		computer_select = scissors;
		break;
	default:
		computer_select = paper;
	}

	return computer_select;
}

General_Select user_select_get(void)
{
	char select_input[256] = { 0 };
	General_Result select_result = result_Error;
	General_Select user_select;

	system("cls");
	printf("Please use a letter to choose what you want, the meanings are as follows:\n");
	printf("r: Rock \t\t s: Scissors \t\t p: Paper\n");

	while (select_result == result_Error)
	{
		printf("Your choice is(r/s/p): ");
		gets(select_input);
		rewind(stdin);

		if (strlen(select_input) == 1)
		{
			switch (select_input[0])
			{
			case 'r':
			case 's':
			case 'p':
				select_result = result_OK;
				break;
			default:
				select_result = result_Error;
			}
		}
		if (select_result == result_Error)
		{
			printf("Your input is illegal, please try again!\n");
			Sleep(1000);
		}
	}

	switch(select_input[0])
	{
	case 'r':
		printf("Picture R!\n");
		user_select = rock;
		break;
	case 's':
		printf("Picture S!\n");
		user_select = scissors;
		break;
	default:
		printf("Picture P!\n");
		user_select = paper;
	}

	return user_select;
}