#include<stdio.h>
#include<windows.h>

main()
{
int c1=1, c2=1;
char p1, p2, g1, g2;

printf("Player 1 please enter your secret character: ");
while(!(scanf("%c",&p1)==1 && p1>=33 && p1<=126))							/*read in character for player 1 and test it is a printable character ASCII value between 33 and 126*/
	{																		/*if the character is invalid, request a new input character unti a valid value is entered*/
	system("cls");															/*clear the screen*/
	printf("Please enter your character again it was out of range: ");
	fflush(stdin);															/*clear the input buffer ready for the next character*/
	}
fflush(stdin);
system("cls");

printf("Player 2 please enter your secret character: ");					/*repeat the above process for player 2*/

while(!(scanf("%c",&p2)==1 && p2>=33 && p2<=126))
	{
	system("cls");
	printf("Please enter your character again it was out of range: ");
	fflush(stdin);
	}
fflush(stdin);	
system("cls");

for(;;)																		/*start the game loopt*/
	{
	printf("Player 1 please enter your guess: ");							/*get player 1's first guess*/
	while((scanf("%c",&g1)!=1))													/*ensure the guess is a valid character and repeat until a valid character is entered*/
		{
		printf("Please enter your character again it was out of range: ");
		fflush(stdin);
		}
	if(g1==p2)																	/*Test, was the guess correct*/
		{
		printf("Congratulaions player 1, you have guessed correctly it took you %d attempts", c1);
		break;																							/*user break to finish the game*/
		}
	else if(g1<p2)
		printf("Player 1 your guess is too low");										/*Otherwise tell player 1 if ASCII value of there character guess was too high*/ 
	else
		printf("Player 1 your guess is too high");
	
	Sleep(5000);															/*make the system wait for 5 seconds*/
	c1++;	 																/*add 1 to the count of player 1 guesses*/
	system("cls");
	fflush(stdin);
	
	printf("Player 2 please enter your guess: ");							/*repeat the process for player 2*/
	while((scanf("%c",&g2)!=1))
		{
		printf("Please enter your character again it was out of range: ");
		fflush(stdin);
		}
	if(g2==p1)
		{
		printf("Congratulaions player 2, you have guessed correctly it took you %d attempts", c2);
		break;
		}
	else if(g2<p1)
		printf("Player 2 your guess is too low");
	
	else
		printf("Player 2 your guess is too high");	   	  	   
	Sleep(5000);
	c2++;
	system("cls");
	fflush(stdin);
	}
printf("\n\nThank you for playing the guessing game, please press a key to close the program\n\n");		/*End the program by pressing a key*/
getch();
}


