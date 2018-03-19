#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <locale.h>
#include <string.h>

int Checker(char Words[][16]);

int Main; //индекс главного слова
int arrayOtherWords[3];//индексы остальных слов
int arrayMain_symbolIndex[3];// места пересечения на главном слове
int arrayOther_symbolIndex[3];//места пересечения на остальных словах

main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	
	char Words[4][16];
	
	//--------------------------------------Ввод
	puts("Кроссворд");
	
	protect:
	
	puts("-------------------");
	puts("Введите четыре слова длинной от пяти до пятнадцати букв");
	
	for(short int op = 0; op != 4; op++)
	{
		scanf("%s",Words[op]);
		if((strlen(Words[op]) > 15)||(strlen(Words[op]) < 5)) //Проверка слов (длина)
		{
	    	puts("Это слово не подходит под заданный интервал.\n");
	    	Sleep(500);
	    	puts("Попробуй ещё раз...");
	    	Sleep(500);
	    	goto protect;
		}
	}
					
	if(Checker(Words) == 0)	puts("Невозможно составить кроссоврд.");
	else
	{
		
		char Cross[30][15];
		
		//---Очистка
		for(int i = 0; i < 30; i++)
		{
			for(int j = 0; j < 15; j++)
			{
				Cross[i][j] = ' ';
			}
		}
		//------------
		
		int variable = arrayOther_symbolIndex[0];
		if(arrayOther_symbolIndex[1] > arrayOther_symbolIndex[0])		variable = arrayOther_symbolIndex[1];
		if(arrayOther_symbolIndex[2] > variable)	variable = arrayOther_symbolIndex[2];
		
		
		for(int i = 0;i < strlen(Words[Main]); i++)		Cross[variable][i] = Words[Main][i];  //написание главного слова
	
		for(int i = 0;i < strlen(Words[arrayOtherWords[0]]); i++)	Cross[variable - arrayOther_symbolIndex[0] + i][arrayMain_symbolIndex[0]] = Words[arrayOtherWords[0]][i];
		
		for(int i = 0;i < strlen(Words[arrayOtherWords[1]]); i++)	Cross[variable - arrayOther_symbolIndex[1] + i][arrayMain_symbolIndex[1]] = Words[arrayOtherWords[1]][i];
		
		for(int i = 0;i < strlen(Words[arrayOtherWords[2]]); i++)	Cross[variable - arrayOther_symbolIndex[2] + i][arrayMain_symbolIndex[2]] = Words[arrayOtherWords[2]][i];
		
		for(int i = 0;i < strlen(Words[Main]); i++)
		{
            if(Cross[variable][i] != Words[Main][i])
			{
				puts("Невозможно составить кроссоврд.");
				system("pause");
				return 0;
			}
        }
		
		//-----Вывод
		puts("---------------------\n      Результат\n---------------------");
		for(int i = 0; i < variable+15; i++)
		{
			for(int j = 0; j < 15; j++)
			{
				printf("%c ", Cross[i][j]);
			}
			puts("");
		}
	}
	
	system("pause");
	
return 0;
}



int Checker(char Words[][16])  
{
	
	for(int MainWordIndex = 0; MainWordIndex  < 4; MainWordIndex++)
	{
		int opportunity = 0;
		
		arrayOtherWords[0] = 345;
		arrayOtherWords[1] = 345;
		arrayOtherWords[2] = 345;
			
		for(int MainWord_symbolIndex = 0; MainWord_symbolIndex < strlen(Words[MainWordIndex]);MainWord_symbolIndex++)
		{
			
			back:
			
			for(int OtherWordIndex = 0; OtherWordIndex < 4;OtherWordIndex++)
			{
				if(OtherWordIndex == MainWordIndex)	continue;
				
				if(OtherWordIndex == arrayOtherWords[0])	continue;   
				if(OtherWordIndex == arrayOtherWords[1])	continue;
				if(OtherWordIndex == arrayOtherWords[2])	continue;
				
				for(int OtherWord_symbolIndex = 0; OtherWord_symbolIndex < strlen(Words[OtherWordIndex]); OtherWord_symbolIndex++)
				{
					if(Words[MainWordIndex][MainWord_symbolIndex] == Words[OtherWordIndex][OtherWord_symbolIndex])
					{
						arrayOtherWords[opportunity] = OtherWordIndex;
						arrayMain_symbolIndex[opportunity] = MainWord_symbolIndex;
						arrayOther_symbolIndex[opportunity] = OtherWord_symbolIndex;
						opportunity++;
						
						if(opportunity == 3)	return 1;
						
						MainWord_symbolIndex++;
						goto back;
					}
				}
			}
		}
	}
	
	return 0;
}
