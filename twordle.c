//Author: Eli Bjur
//Date: 4/21/26
//Purpose: Project 10

#include <stdio.h>
#include <stdbool.h>

#define INFILE "word.txt"
#define maxGuesses 6
#define strLength 5
#define rows 7
#define columns 6

void wordInput(char wordFileInput[rows][columns]);
void playTheGame(char wordToCheck[rows][columns]);
void getGuesses(char wordToCheck[rows][columns], int guessNum);
bool isAcceptableWord(char lettersInWord[]);
void convertToLowercase(char lettersInWord[]);
void displayGame(char wordToCheck[rows][columns], int currentGuessNum);
bool checkForWin(char wordToCheck[rows][columns], int guessNum);

int main(){
	
	char word[rows][columns];
	
	wordInput(word);
	playTheGame(word);
	
	return 0;
}

void wordInput(char wordFileInput[rows][columns]){
	FILE* inPTR = fopen(INFILE, "r");
	
	if (inPTR != NULL){
		fgets(wordFileInput[0], columns, inPTR);
	}
	
	fclose(inPTR);
}

void getGuesses(char wordToCheck[rows][columns], int guessNum){
	bool acceptableWord = false;
	printf("Enter your guess: ");
	
	while (!acceptableWord){
		scanf("%s", wordToCheck[guessNum]);
		convertToLowercase(wordToCheck[guessNum]);
		
		if (isAcceptableWord(wordToCheck[guessNum])){
			acceptableWord = true;
		}
		else{
			printf("Your guess must be 5 letters long.\n");
			printf("Please try again: ");
		}
	}
}

bool isAcceptableWord(char lettersInWord[]){
	int length = 0;
	while (lettersInWord[length] != '\0'){
		bool isLetter = (lettersInWord[length] >= 'a' && lettersInWord[length] <= 'z') ||
				(lettersInWord[length] >= 'A' && lettersInWord[length] <= 'Z');
		if (!isLetter){
			return false;
		}
		length++;
	}
	
	if (length == strLength){
		return true;
	}
	else{
		return false;
	}

}

void convertToLowercase(char lettersInWord[]){
	for (int i = 0; i < strLength; i++){
		if (lettersInWord[i] >= 'A' && lettersInWord[i] <= 'Z'){
			lettersInWord[i] = lettersInWord[i] + 32;
		}
	}
}

void displayGame(char wordToCheck[rows][columns], int currentGuessNum){

	printf("================================\n");

	for (int i = 1; i <= currentGuessNum; i++){
		char carrotHolder[columns] = "     ";
		
		for (int j = 0; j < strLength; j++){
			if (wordToCheck[i][j] == wordToCheck[0][j]){
				printf("%c", wordToCheck[i][j] - 32);
			}
			else {
				printf("%c", wordToCheck[i][j]);
				for (int k = 0; k < strLength; k++){
					if (wordToCheck[i][j] == wordToCheck[0][k]){
						carrotHolder[j] = '^';
					}
				}
			}
		}
	printf("\n%s\n", carrotHolder);
	}
}

bool checkForWin(char wordToCheck[rows][columns], int guessNum){
	for (int i = 0; i < strLength; i++){
		if (wordToCheck[guessNum][i] != wordToCheck[0][i]){
			return false;
		}
	}
	return true;
}

void playTheGame(char wordToCheck[rows][columns]){
	int guessCount = 0;
	bool won = false;
	
	do {
		if (guessCount == 5) {
			printf("FINAL GUESS : ");
		}
		else {
			printf("GUESS %d! ", guessCount + 1);
		}
	
		getGuesses(wordToCheck, guessCount + 1);
		displayGame(wordToCheck, guessCount + 1);
	
		if (checkForWin(wordToCheck, guessCount + 1)){
			won = true;
			int totalGuesses = guessCount + 1;
			
			printf("================================\n");
			printf("            ");
			for (int i = 0; i < strLength; i++){
				printf("%c", wordToCheck[0][i] - 32);
			}
			printf("\n");
			
			if (totalGuesses == 1){
				printf("        You won in 1 guess!\n");
				printf("            GOATED!\n");
			}
			else {
				printf("        You won in %d guesses!\n", totalGuesses);
				if (totalGuesses <= 3){
					printf("            Amazing!\n");
				}
				else {
					printf("            Nice!\n");	
				}
			}
		}
		guessCount++;
	
	} while (guessCount < maxGuesses && !won);

	if (!won){
		printf("You lost, better luck next time!\n");
	}
}






















