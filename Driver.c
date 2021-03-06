//==========================================================================
// cs12xcm                         Homework 7            Matt Roth 
//
// February 19 2019	
//--------------------------------------------------------------------------
// File: Driver.c
//
// Description:		The driver will implement and demonstrate the Tree 
//		program. The Driver has an inner class UCSDStudent to test the
//		Tree program. 
//==========================================================================

#include <cstdlib>
#include <iostream>
#include <string.h>
#include "Base.h"
#include "SymTab.h"
using namespace std;

#ifdef NULL
#undef NULL
#define NULL 0
#endif

//=========================================================================
// class UCSDStudent 
//
// Description:		This class will test the Tree program. The main
//				data fields are the name and the student number. 
//
//  
// Data Fields:
//
//     name - the name of the student    
//     studentnum - the number of the student 
//     
//
// Public functions:
//					UCSDStudent - constructor(s) for initialization
//					~UCSDStudent - destructor 
//					ostream & Write - the toString  
//					operator const char * - overrride the char *   
//					operator  - override the == 
//					operator > - override the >  
//==========================================================================
class UCSDStudent : public Base {

	//the name and the student number 
	char * name;
	long studentnum;

public:
	
/***************************************************************************
% Routine Name : UCSDStudent (public)
% File :         Driver.c
% 
% Description :  initialize the data fields
***************************************************************************/

    UCSDStudent(char * nam, long stunum = 0):
		name(strdup (nam)), studentnum(stunum){}

/***************************************************************************
% Routine Name : UCSDStudent (public)
% File :         Driver.c
% 
% Description :  initialize the data fields
***************************************************************************/
	UCSDStudent (const UCSDStudent & ucsdstudent){
		name = strdup (ucsdstudent.name);
		studentnum = ucsdstudent.studentnum;
	}

/***************************************************************************
% Routine Name : ~UCSDStudent (public)
% File :         Driver.c
% 
% Description :  Deallocated memory deletes the data 
***************************************************************************/
	~UCSDStudent (void){
		free(name);
	}

/***************************************************************************
% Routine Name : const char * (public)
% File :         Driver.c
% 
% Description :  overload the char * 
***************************************************************************/
	operator const char * (void) const{
		return name;
	}

/***************************************************************************
% Routine Name : operator == (public)
% File :         Driver.c
% 
% Description :  overload the == 
***************************************************************************/
	long operator == (const Base & bbb) const {
		return ! strcmp (name, bbb);
	}

/***************************************************************************
% Routine Name : operator > (public)
% File :         Driver.c
% 
% Description :  overload the > 
***************************************************************************/
	long operator > (const Base & bbb) const {
		return (strcmp (name, bbb) > 0) ? 1 : 0;
	}

/***************************************************************************
% Routine Name : ostream & Write (public)
% File :         Driver.c
% 
% Description :  toString 
***************************************************************************/
	ostream & Write (ostream & stream) const {
		return stream << "name:  " << name
			<< "  studentnum:  " << studentnum;
	}
};


//PROVIDED CODE BELOW
int main (int argc, char * const * argv) {
	char buffer[80];
	char command;
	long number;

	Tree::Set_Debug(0);

	if (argc != 1 && strcmp("-x", argv[1]) == 0) {
		Tree::Set_Debug(1);
	}
	
	SymTab * ST;
	ST = new SymTab ("UCSDStudentTree");
	ST->Write (cout << "Initial Symbol Table:\n");

	while (cin) {
		command = NULL;		// reset command each time in loop
		cout <<  "Please enter a command:  ((a)llocate, is(e)mpty," <<
			" (i)nsert, (l)ookup, (r)emove, (w)rite):  ";
		cin >> command;

		switch (command) {

		case 'a':
			cout << "Please enter name of new Tree to allocate:  ";
			cin >> buffer; 

			delete ST;
			ST = new SymTab (buffer);

			break;

		case 'e':
                        if (ST->IsEmpty ())
                                cout << "Tree is empty." << endl;
                        else
                                cout << "Tree is not empty." << endl;
                        break;
			
		case 'i':
			cout << "Please enter UCSD student name to insert:  ";
			cin >> buffer;	// formatted input

			cout << "Please enter UCSD student number:  ";
			cin >> number;

			// create student and place in symbol table
			ST->Insert (new UCSDStudent (buffer, number));
			break;

		case 'l': {
			const Base * found;	// whether found or not

			cout << "Please enter UCSD student name to lookup:  ";
			cin >> buffer;	// formatted input

			UCSDStudent stu (buffer, 0);
			found = ST->Lookup (&stu);
			
			if (found)
				found->Write (cout << "Student found!\n") << "\n";
			else
				cout << "student " << buffer << " not there!\n";
			}
			break;
		
		case 'r': {
			Base * removed;	// data to be removed

			cout << "Please enter UCSD student name to remove:  ";
			cin >> buffer;	// formatted input

			UCSDStudent stu (buffer, 0);
			removed = ST->Remove (&stu);

			if (removed)
				removed->Write (cout << "Student removed!\n") << "\n";
			else
				cout << "student " << buffer << " not there!\n";
			}
			break;


		case 'w':
			ST->Write (cout << "The Symbol Table contains:\n");
		}
	}

	ST->Write (cout << "\nFinal Symbol Table:\n");
	delete ST;
}
