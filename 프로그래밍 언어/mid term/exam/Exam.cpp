/* 
* File Name: "exam.cpp"
* Description:
* - This program is Exam
* Programmed by Jung-Ha Cho,
* Last updated: Version 1.0, Aprill 26, 2012 (by Jung-Ha Cho).
* ========================================================
* Version Control (Explain updates in detail)
* ========================================================
* Updated By Date (2012/04/26) Version Remarks
* J.H Cho 2012/04/26 1.0 Project & Main function is created
* ========================================================
*/
#include <iostream>
#include <fstream>
#include <time.h>
#include <iomanip>
#include "MyStructures.h"
#include "ListNode.h"
#include "ListOfStudents.h"
#define NUM_STUDENTS 2000
#define IDS_TO_SEARCH 5

using namespace std;

void initStudents(Student pSA[], int size);
void genBigRandArray(Student pSA[], int num , int RANGE);
void printArrayOfStudents(Student pSA[], int num);
void insertStudentInList(ListOfStudents *pLS, ListNode *pStt);
void sortStudentArrayByID(Student pSA[], int n );
void printListOfStudents(ListNode *pStt);
void seachStudentFromList(ListOfStudents *pLS, int idToSearch[]);
void insertStudentInTree();
void printTreeOrderOfStudents();

ofstream fout("output.txt", ios::app);

int main()
{

	int *idToSearch;

	/*fout.open("output.txt");
	if(fout.fail()){
	cout<<"output file(output.txt) open failed !! \n";
	return 0;
	}*/

	/*Initialize Students*/

	Student *pSA;
	pSA = new Student[NUM_STUDENTS];
	initStudents(pSA, NUM_STUDENTS);

	cout<<"Initalization of "<<NUM_STUDENTS<<" is completed.\n";

	idToSearch = new int[NUM_STUDENTS];
	int RANGE = IDS_TO_SEARCH;
	int num = NUM_STUDENTS;

	genBigRandArray(pSA, IDS_TO_SEARCH, NUM_STUDENTS);


	/* Management of array of students */
	printArrayOfStudents(pSA, num);

	fout<<"Sort students array by ID \n";
	sortStudentArrayByID(pSA, NUM_STUDENTS);
	printArrayOfStudents(pSA, num);


	/*Linked List*/

	ListOfStudents *pLS;
	ListNode *pStt;
	pLS = new ListOfStudents;
	pLS->num_st = 0;
	pLS->pFirst = pLS->pLast = NULL;

	for(int st=0; st<NUM_STUDENTS; st++)
	{
		pStt = new ListNode;
		pStt->pSt = &pSA[st];
		insertStudentInList(pLS, pStt);
	}
	fout<<"\nList of"<<pLS->num_st;
	fout<<"\nStudents in sorted order by ID(decreasing order): \n";
	//printListOfStudents(pStt);
	fout<<"\n Seached results from linked list of students";
	for(int i = 0; i<IDS_TO_SEARCH; i++)
	{
		//pS = seachStudentFromList(pLS, idToSearch[i]);
		//printStudent(pS, &fout);
	}

	/* Binary */
}

void initStudents(Student pSA[], int size)
{
	int name_len;                  
	name_len = rand()%12+3;  
	for(int i = 0 ; i < size; i++)
	{

		(pSA+i)->first_name[0] = rand()%14 + 'A'; 
		for (int j=1; j<name_len; j++)  
		{
			(pSA+i)->first_name[j] = rand()%14 + 'a'; 
			(pSA+i)->first_name[name_len] = NULL;
		}

		(pSA+i)->last_name[0] = rand()%14 + 'A'; 
		for (int j=1; j<name_len; j++)  
		{
			(pSA+i)->last_name[j] = rand()%14 + 'a'; 
			(pSA+i)->last_name[name_len] = NULL;
		}

		for (int j=0; j<name_len; j++)  
		{
			(pSA+i)->department[j] = rand()%14 + 'a'; 
			(pSA+i)->department[name_len] = NULL;
		}

		for (int j=0; j<name_len; j++)  
		{
			(pSA+i)->description[j] = rand()%255 + 10 + 'a'; 
			(pSA+i)->description[name_len] = NULL;
		}

		(pSA+i)->grade = (int)(rand()%7+1);
		(pSA+i)->GPA = (double)(rand()%100);
	}
}


void genBigRandArray(Student pSA[], int num , int RANGE)
{

	char *flag = new char[RANGE];
	unsigned int uint_32;
	unsigned int bigRand;
	srand(time(0));
	for(int i = 0; i < RANGE; i++ )
	{
		flag[i] = 0;
	}
	int count = 0;
	while (count < RANGE) 
	{
		uint_32 = ( ( long ) rand() << 15) | rand(); 
		bigRand = uint_32 % RANGE;
		if (flag[bigRand] == 1)
		{ 
			continue;
		} else {
			flag[bigRand] = 1;
			(pSA+count++)->st_id = bigRand; 
		} 
	}
}
void printArrayOfStudents(Student pSA[], int num)
{
	fout<<endl;
	fout<<"First 100 total "<<NUM_STUDENTS<<endl;
	fout<<endl;
	for(int i = 0 ; i<10; i++)
	{
		fout<<setw(6)<<"st_id:"<<" "<<(pSA+i)->st_id<<" "<<(pSA+i)->last_name<<" "<<(pSA+i)->first_name<<" Dept: "<<(pSA+i)->department<<" grade: "<<(pSA+i)->grade<<" GPA: "<<(pSA+i)->GPA<<endl;
	}
	fout<<endl;
	fout<<"Last 100 total "<<NUM_STUDENTS<<endl;
	fout<<endl;
	for(int i = NUM_STUDENTS-10 ; i<NUM_STUDENTS; i++)
	{
		fout<<setw(6)<<"st_id:"<<" "<<(pSA+i)->st_id<<" "<<(pSA+i)->last_name<<" "<<(pSA+i)->first_name<<" Dept: "<<(pSA+i)->department<<" grade: "<<(pSA+i)->grade<<" GPA: "<<(pSA+i)->GPA<<endl;
	}

}

void sortStudentArrayByID(Student pSA[], int n )
{
	int iPos, jPos; 
	int iMin;  
	Student temp;

	for (iPos = 0; iPos < n; iPos++) 
	{

		iMin = iPos;                
		for (jPos = iPos+1; jPos < n; jPos ++) //
		{
			if (pSA[jPos].st_id < pSA[iMin].st_id) 
			{
				iMin = jPos;
			} 
		}
		if ( iMin != iPos ) 
		{
			temp = pSA[jPos];
			pSA[jPos] = pSA[iPos];
			pSA[iPos] = temp;
		}
	}
}

void insertStudentInList(ListOfStudents *pLS, ListNode *pStt)
{
	if(pLS->num_st==0)
	{
		pLS->pFirst = pLS->pLast = pStt;
		pStt->pNext = NULL;
		pStt->pPrev = NULL;
		pLS->num_st++;
	}else if(pLS->num_st < NUM_STUDENTS){
		for(ListNode *pS = pLS->pFirst; pS !=NULL;)
		{
			if(pStt->pSt->st_id < pS->pSt->st_id){
				pStt->pNext = pS;
				pStt->pPrev = pS->pPrev;
				if(pS != pLS->pFirst){
					if(pS->pPrev!=NULL)
						pS->pPrev->pNext= pStt;
					pS->pPrev = pStt;
				} else {
					pLS->pFirst = pStt;
					pStt->pPrev = NULL;
					pS->pPrev = pStt;
				}
				pLS->num_st++;
				break;
			}
			else if((pS==pLS->pLast)&&(pStt->pSt->st_id>pS->pSt->st_id))
			{
				pStt->pPrev = pS;
				pS->pNext = pStt;
				pLS->pLast=pStt;
				pStt->pNext = NULL;
				pLS->num_st++;
				break;
			}else{
				if(pS != pLS->pLast)
					pS=pS->pNext;
				else
					break;
			}
		}
	}
}
void printListOfStudents(ListNode *pStt)
{
	fout<<endl;
	fout<<"First 100 total "<<NUM_STUDENTS<<endl;
	fout<<endl;
	for(int i = 0 ; i<10; i++)
	{
		fout<<setw(6)<<"st_id:"<<" "<<(pStt+i)->pSt->first_name<<" "<<(pStt+i)->pSt->last_name<<" "<<(pStt+i)->pSt->first_name<<" Dept: "<<(pStt+i)->pSt->department<<" grade: "<<(pStt+i)->pSt->grade<<" GPA: "<<(pStt+i)->pSt->GPA<<endl;
	}
	fout<<endl;
	fout<<"Last 100 total "<<NUM_STUDENTS<<endl;
	fout<<endl;
	for(int i = NUM_STUDENTS-10 ; i<NUM_STUDENTS; i++)
	{
		fout<<setw(6)<<"st_id:"<<" "<<(pStt+i)->pSt->st_id<<" "<<(pStt+i)->pSt->last_name<<" "<<(pStt+i)->pSt->first_name<<" Dept: "<<(pStt+i)->pSt->department<<" grade: "<<(pStt+i)->pSt->grade<<" GPA: "<<(pStt+i)->pSt->GPA<<endl;
	}
}
void seachStudentFromList(ListOfStudents *pLS, int idToSearch[])
{
}
void insertStudentInTree()
{
}

void printTreeOrderOfStudents()
{
}
