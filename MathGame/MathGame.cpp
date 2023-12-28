#include <iostream>
using namespace std;

enum enQuestionsLevel {Easy=1, Med=2, Hard=3 ,MixLevel=4 };
enum enOperationType { Add = 1, Sub = 2, Mul = 3, Div=4 , MixOpType };

struct stQuestion
{
	short QuestionNumber = 0;
	enQuestionsLevel QuestionLevel; 
	enOperationType OperationType; 
	short Number1=0;
	short Number2=0;
	short PlayerAnswer=0;
	short CorrectAnswer=0;
	bool AnswerResult = false; 
};
struct stQuizz
{
	stQuestion Questions[100]; 
	enQuestionsLevel QuestionsLevel; 
	enOperationType OperationType;
	short NumberOfQuestions = 0; 
	short NumberOfWrongQuestions = 0; 
	short NumberOfRightQuestions = 0;
	bool isPass = false; 

};

short RandomNumber(short From , short To)
{
	return rand() % (To - From + 1) + From; 
}

short ReadHowManyQuestions()
{
	short Questions = 0 ; 

	do
	{
		cout << "How Many Questions do you want to answer ? ";
		cin >> Questions;

	} while (Questions < 1 || Questions > 10); 
	

	return Questions; 
}

enQuestionsLevel ReadQuestionsLevel()
{
	short Level = 0;
	do
	{
		cout << "Enter Questions Level  : [1] Easy , [2] Med , [3] Hard , [4] Mix ? ";
		cin >> Level;

	} while (Level < 1 || Level > 4);
	
	return (enQuestionsLevel)Level; 
}

enOperationType ReadOperationType()
{
	short OpType = 0;
	do
	{
		cout << "Enter Operation Type : [1] Add , [2] Sub , [3] Mul , [4] Div , [5] Mix ? ";
		cin >> OpType; 

	} while (OpType < 1 || OpType > 5);

	return (enOperationType)OpType; 

}

void ResetScreen()
{
	system("cls");
	system("color 0F");

}

void SetScreenColor(bool Pass)
{
	if(Pass)
		system("color 2F");
	else
	{
		cout << "\a";
		system("color 4F");
	}
	
}

string GetOperationTypeSymbol(enOperationType OperationType)
{
	string arr[] = { "+" , "-" , "*" , "/" }; 

	return arr[OperationType - 1];
}

string GetQuestionsLevelText(enQuestionsLevel QuestionsLevel)
{
	
	string arr[] = { "Easy" , "Med" , "Hard" , "Mix" };
	return arr[QuestionsLevel - 1]; 
}

string GetOperationTypeText(enOperationType OperationType)
{
	string arr[] = { "Add" , "Sub" , "Mul" , "Div" , "Mix" };
	return arr[OperationType - 1];
}

enQuestionsLevel GetRandomQuestionsLevel()
{
	return (enQuestionsLevel)RandomNumber(1, 3);
}

enOperationType GetRandomOperationType()
{
	return (enOperationType)RandomNumber(1, 4);
}

short SimpleCalculator(short Num1,short Num2 , enOperationType OpType)
{
	switch (OpType)
	{
	case enOperationType::Add : 
		return Num1 + Num2;

	case enOperationType::Sub:
		return Num1 - Num2;

	case enOperationType::Mul:
		return Num1 * Num2;

	case enOperationType::Div:
		return Num1 / Num2;

	}
	return 0; 
}

void GenerateQuestion(stQuestion &Question , enQuestionsLevel QuestionsLevel , enOperationType OperationType)
{
	if (QuestionsLevel == enQuestionsLevel::MixLevel)
	{
		QuestionsLevel = GetRandomQuestionsLevel();
	}

	if (OperationType == enOperationType::MixOpType)
	{
		OperationType = GetRandomOperationType(); 
	}

	Question.QuestionLevel = QuestionsLevel;
	Question.OperationType = OperationType;

	switch (QuestionsLevel)
	{
	case enQuestionsLevel::Easy:
		Question.Number1 = RandomNumber(1, 10);
		Question.Number2 = RandomNumber(1, 10);
		Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);
		break; 

	case enQuestionsLevel::Med:
		Question.Number1 = RandomNumber(10, 50);
		Question.Number2 = RandomNumber(10, 50);
		Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);
		break;

	case enQuestionsLevel::Hard:
		Question.Number1 = RandomNumber(50, 100);
		Question.Number2 = RandomNumber(50, 100);
		Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);
		break; 

	}
}

void GenerateQuestionsList(stQuizz& Quizz)
{
	for (short Question = 0; Question < Quizz.NumberOfQuestions; Question++)
	{
		GenerateQuestion(Quizz.Questions[Question], Quizz.QuestionsLevel, Quizz.OperationType);
	}
}

void PrintQuestion(stQuizz Quizz, short QuestionNumber)
{
	cout << "\n\nQuestion [" << QuestionNumber+1 << "/" << Quizz.NumberOfQuestions << "] \n\n";
	cout << Quizz.Questions[QuestionNumber].Number1 << "\n";
	cout << Quizz.Questions[QuestionNumber].Number2 << "  " << GetOperationTypeSymbol(Quizz.Questions[QuestionNumber].OperationType) << "\n";
	cout << "_____________ \n";

}

short ReadPlayerAnswer()
{
	short Answer = 0;
	cin >> Answer; 

	return Answer; 
}

void CorrectQuestionAnswer(stQuizz &Quizz , short QuestionNumber)
{   
	
	if (Quizz.Questions[QuestionNumber].PlayerAnswer != Quizz.Questions[QuestionNumber].CorrectAnswer)
	{
	
		cout << "\nWrong Answer :-( ";
		cout << "\nThe Right Answer Is : "<< Quizz.Questions[QuestionNumber].CorrectAnswer << endl ;
		Quizz.Questions[QuestionNumber].AnswerResult = false;

		Quizz.NumberOfWrongQuestions++;
	}

	else
	{
		
		cout << "\nRight Answer  :-) ";
		Quizz.Questions[QuestionNumber].AnswerResult = true;
		
		Quizz.NumberOfRightQuestions++;
	}

	Quizz.isPass = (Quizz.NumberOfRightQuestions >= Quizz.NumberOfWrongQuestions);

	SetScreenColor(Quizz.Questions[QuestionNumber].AnswerResult);

}

void AskAndCorrectQuestionsListAnswers(stQuizz &Quizz )
{
	for (short Question = 0; Question < Quizz.NumberOfQuestions; Question++)
	{
		PrintQuestion(Quizz , Question);
	
		Quizz.Questions[Question].PlayerAnswer = ReadPlayerAnswer();

		CorrectQuestionAnswer(Quizz, Question);
	
	}

}

string GetFinalResultsText(bool FinalResult)
{
	return FinalResult ? "PASS :-)" : "FAIL :-(";
}

void PrintFinalQuizzResults(stQuizz Quizz)
{
	cout << "\n\n"; 
	cout << "____________________________________\n";
	cout << "\n   Final Results is  " << GetFinalResultsText(Quizz.isPass) <<"\n";
	cout << "____________________________________\n\n";

	cout << "Number Of Questions      : "  << Quizz.NumberOfQuestions << "\n";
	cout << "Questions Level          : " << GetQuestionsLevelText(Quizz.QuestionsLevel) << "\n";
	cout << "Operation Type           : " << GetOperationTypeText(Quizz.OperationType) << "\n";
	cout << "Number Of Right Answers : " << Quizz.NumberOfRightQuestions << "\n";
	cout << "Number Of Wrong Answers  : "  << Quizz.NumberOfWrongQuestions << "\n";
	cout << "____________________________________\n\n";

}

void PlayGame()
{
	stQuizz Quizz; 

	Quizz.NumberOfQuestions = ReadHowManyQuestions();
	Quizz.OperationType = ReadOperationType(); 
	Quizz.QuestionsLevel = ReadQuestionsLevel(); 

	GenerateQuestionsList(Quizz); 
	AskAndCorrectQuestionsListAnswers(Quizz);
	PrintFinalQuizzResults(Quizz);
}

void StartGame()
{
	char PlayAgain = 'Y'; 
	do
	{
		ResetScreen(); 
		PlayGame(); 

		cout << "Do You Want To Play Again ? Y/N ?";
		cin >> PlayAgain;

	} while (toupper(PlayAgain) == 'Y');

}

int main()
{
	srand((unsigned)time(NULL));
	StartGame(); 

}