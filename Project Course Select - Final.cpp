// entekhabvahed.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <conio.h>
#include <stdio.h>
#include <fstream>
//#include <iomanip>
#include <windows.h> 

void SetWindow(int Width, int Height) 
    { 
    _COORD coord; 
    coord.X = Width; 
    coord.Y = Height; 

    _SMALL_RECT Rect; 
    Rect.Top = 0; 
    Rect.Left = 0; 
    Rect.Bottom = Height - 1; 
    Rect.Right = Width - 1; 

    HANDLE Handle = GetStdHandle(STD_OUTPUT_HANDLE);      // Get Handle 
    SetConsoleScreenBufferSize(Handle, coord);            // Set Buffer Size 
    SetConsoleWindowInfo(Handle, TRUE, &Rect);            // Set Window Size 
    } 
void gotoXY(int x, int y) 
{ 
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;
CursorPosition.X = x; // Locates column
CursorPosition.Y = y; // Locates Row
SetConsoleCursorPosition(console,CursorPosition); // Sets position for next thing to be printed 
}


using namespace std;
void G_C();
void menu(int);
int Login();
void splash();
void ReadFromFile();
static int i1=0,i2=0,i3=0,i4=0,lll;
static string s_name="Admin",s_family;
static int G=0,s_id=0;
int idtea;
bool t;


class student
{
	int id;
	string name;
	string field;
	string LastName;
public:
	void report ();
	void delfromfile ();
	void Save2File();
	void read(int rid,string rname,string rlast,string rfield);
	void report (int d);
	void report (string s);
	bool  input(int d);
	bool  Del(int d);
	bool  Del(string s);
	bool check(int d);
	bool check(string s);
	friend class get_course;
}stu[100];

class teacher
{
	int id;
	string name;
	string family;
	string field;
public:
	void Save2File();
	void delfromfile ();
	void read(int rid,string rname,string rfamily,string rfield);
	void report ();
	void report (int d);
	void report (string s);
	bool  input(int d);
	friend class lesson;
	friend class get_course;
	friend class courses;
	bool  Del(int d);
	bool  Del(string s);
	bool check(int d);
	bool check(string s);
	string r_name();
}tea[100];

class lesson
{
	string name_les;
	int id;
	int unit;
	//int pre_on;
	int pre_of;
public:
	friend class get_course;
	friend class courses;
	string r_name();
	void report ();
	void Save2File();
	int check2(int lessson);
	void read(int idl,string namel, int unitt, int preee );
	bool input(int d);
	//bool check_tea ();
	bool check(int d);
	void report (int d);
	void report (string s);
	bool Del(int d);
	bool Del(string s);
} les[100];

class get_course
{
	int id_stu;
	int id_tch;
	int id_dars;
	float score;
public:
	get_course();
	friend class student;
	void delfromfile ();
	bool check1(int idstudent,int idcourse);
	int check3(int idstudent,int pre);
	bool check4(int idstudent);
	void get_course::report(int _id);
	void Save2File();
	void get_course::Save2File2();
	void read(int rid_stu,int rid_tch,int rid_dars,float score);
	void input(int ds,int dt,int dl);
	bool en_s(int _ids, int _idc);
}g_c[100];

class courses
{
	int id,idt,idclass,capa,time_start_h,time_start_m,time_end_h,time_end_m,idl;
	string dates;
public:
	friend class student;
    void report (int i);
	void read(int id,int idt,int idclass,int capa,string dates,int time_start_h,int time_start_m,int time_end_h,int time_end_m,int idl);
	bool  input(int d);
	bool check_tea(int _idt);
	bool check_less(int _idl);
	bool check5(int idstudent);
	bool check_time(int idcourse);
	bool check_capa(int idcourse);
	int pre(int idcourse );
    void Save2File();
}cour[100];


//-------------------------------------------methods------------------------------

void student::Save2File()
{
	ofstream studfile("students.txt",ios::app);
	studfile<<id<<' '<<name<<' '<<LastName<<' '<<field<<endl;
	cout<<"record added to file successfully!"<<endl;
	studfile.close();

}

bool student::input(int d)
{ 
	
	cout<<"\nE.Exit or C.Continue \n";
	switch (_getch())
	{
	
	case 'e':
	case 'E':
		return false;
		break;
	case 'c':
	case 'C':
		cout <<"\nPlease enter an id for student number  (NUMBERS ONLY- NO SPACES !!) "<<d<<" :";
		char *dud;
		 dud=new char [20];
		//int temp2;
		 cin>>dud;
		 if(strtol(dud,NULL,10)!=0)
			 id=strtol(dud,NULL,20);
		
		else
		{
			cout<<"\a\ninvalid data entered!"<<endl;
			id=NULL;
			this->input(d);
			delete dud;
			break;
		}

	

		
		cout <<"\nPlease enter a name for student number (NO SPACES !!) "<<d<<" :";
		//cin.getline(name,80,'\n');
		cin>>name;
		cout <<"\nPlease enter a  last name for student number (NO SPACES !!)"<<d<<" :";
		cin>>LastName;

		cout <<"\nPlease enter a field for student number (NO SPACES !!)"<<d<<" :";
		cin>>field;
		
		cout<<"\n\nnew student "<<name<<" "<<LastName<< " with the id "<<id << " added in "<<field<<" field\n\n";
		
		Save2File();
		return true;
		
		break;
	}
}

void student::delfromfile ()
{
	ofstream delfile ("students.txt" , ios::app);
	if(name==""&& id==NULL)
		return;
	else
	{
		delfile<<id<<' '<<name<<' '<<field<<endl;
	}
	delfile.close();
}

bool student::Del(int d)
{
	if (id==d)
	{
		cout<<"The student you want delete is "<<name<<" . Are you sure ? Y.Yes  N.No : ";
		switch (_getch())
		{
		case '*':
			menu(lll);
			break;
		case'Y':
		case'y':
			id=NULL;
			name="";
			field="";
			delfromfile();
			

			return true;
			break;
		case'n':
		case'N':
			return false;
			break;
		}
	}
	else
	{
		return false;
	}
}

bool student:: Del(string s)
{
	if (name==s)
	{
		cout<<"The student's id you want delete is "<<id<<" . Are you sure ? Y.Yes  N.No : ";
		switch (_getch())
		{
		case '*':
			menu(lll);
			break;
		case'Y':
		case'y':
			id=NULL;
			name="";
			field="";
			delfromfile();
			return true;
			break;
		case'n':
		case'N':
			return false;
			break;
		}
	}
	else
	{
		return false;
	}
}

void student::report()
{
	if (id==0&&name=="")
	{
		return ;
	}
	cout<<"____________________________________________________\n";
	cout<<id<<"\t"<<name<<"\t"<<LastName<<"\t"<<field<<"\n";
}

void student::report(string s)
{
	if (s==name)
	{
		cout<<"____________________________________________________\n";
	   cout<<id<<"\t"<<name<<"\t"<<LastName<<"\t"<<field<<"\n";
	}
}

void student::report(int d)
{
	if (d==id)
	{
		cout<<"____________________________________________________\n";
	    cout<<id<<"\t"<<name<<"\t"<<LastName<<"\t"<<field<<"\n";
		for (int k = 0; k < 100; k++)
		{
			if (g_c[k].id_stu ==d)
			{
				   cout<<"[1]"<<g_c[k].id_dars<<"\t[2]"<<g_c[k].score;
				   if (g_c[k].score>=10)
					   cout<<"    passed!"<<endl;
				   else if (g_c[k].score==0)
					   cout<<"     don't have any score!"<<endl;
				   else
					   cout<<"     failed!"<<endl;
			}
		}
	}
}

bool student::check(int d)
{
	if (d==id)
		return true;
	else
		return false;
}

bool student::check(string s)
{
	if(s==name)
	{
		s_id=id;
		s_name=name;
		s_family=LastName;
		return true;
	}
	else
	{
		return false;
	}
}

void student::read(int rid,string rname,string rlast,string rfield)
{
	id=rid;
	name=rname;
	field=rfield;
	LastName=rlast;

	
}



void teacher::Save2File()
{
	ofstream studfile("teachers.txt",ios::app);
	studfile<<id<<' '<<name<<' '<<family<<' '<<field<<endl;
	cout<<"record added to file successfully!"<<endl;
	studfile.close();

}

bool teacher::input(int d)
{
	cout<<"\nE.Exit or C.Continue \n";
	switch (_getch())
	{
	case '*':
			menu(lll);
			break;
	case 'e':
	case 'E':
		return false;
		break;
	case 'c':
	case 'C':
		//cout <<"Please enter an id for teacher number (NUMBERS ONLY !!) "<<d<<" :";
		cout <<"\nPlease enter an id for teacher number  (NUMBERS ONLY- NO SPACES !!) "<<d<<" :";
		char *dud;
		 dud=new char [20];
		 cin>>dud;
		 if(strtol(dud,NULL,10)!=0)
			 id=strtol(dud,NULL,20);
		
		else
		{
			cout<<"\a\ninvalid data entered!"<<endl;
			id=NULL;
			this->input(d);
			delete dud;
			break;
		}
		cout <<"Please enter a name for teacher number (NO SPACES !!) "<<d<<" :";
		cin>>name;
		cout <<"Please enter a family for teacher number (NO SPACES !!) "<<d<<" :";
		cin>>family;
		cout <<"Please enter a field for teacher number (NO SPACES !!) "<<d<<" :";
		cin>>field;

		cout<<"\n\nnew teacher "<<name<<" with the id "<<id << " added in "<<field<<" field\n\n";

		Save2File();
		return true;
		break;
	}
}

bool teacher::check(int d)
{
	if (d==id)
		return true;
	else
		return false;
}

bool teacher::check(string s)
{
	if(s==name)
	{  
		s_id=id;
		s_name=name;
		s_family=family;
		return true;
	}
	else
		return false;
}

void teacher::delfromfile ()
{
	ofstream delfile ("teachers.txt" , ios::app);
	if(name==""&& id==NULL)
		return;
	else
	{
		delfile<<id<<' '<<name<<' '<<field<<endl;
	}
	delfile.close();
}

bool teacher::Del(int d)
{
	if (id==d)
	{
		cout<<"The teacher you want delete is "<<name<<" . Are you sure ? Y.Yes  N.No : ";
		switch (_getch())
		{
		case '*':
			menu(lll);
			break;
		case'Y':
		case'y':
			id=NULL;
			name="";
			field="";
			delfromfile();
			return true;
			break;
		case'n':
		case'N':
			return false;
			break;
		}
	}
	else
	{
		return false;
	}
}
bool teacher::Del(string s)
{
	if (name==s)
	{
		cout<<"The teacher's id you want delete is "<<id<<" . Are you sure ? Y.Yes  N.No : ";
		switch (_getch())
		{
		case '*':
			menu(lll);
			break;
		case'Y':
		case'y':
			id=NULL;
			name="";
			field="";
			delfromfile();
			return true;
			break;
		case'n':
		case'N':
			return false;
			break;
		}
	}
	else
	{
		return false;
	}
}
void teacher::report()
{
	if (id==0&&name=="")
	{
		return ;
	}
	cout<<"____________________________________________________\n";
	cout<<id<<"\t"<<name<<"\t"<<family<<"\t"<<field<<"\n";
}
void teacher::report(string s)
{
	if (s==name)
	{
		cout<<"____________________________________________________\n";
	    cout<<id<<"\t"<<name<<"\t"<<family<<"\t"<<field<<"\n";
	}
}
void teacher::report(int d)
{ 
	if (d==id)
	{
		cout<<"____________________________________________________\n";
	    cout<<id<<"\t"<<name<<"\t"<<family<<"\t"<<field<<"\n";
	}
}
void teacher::read(int rid,string rname,string rfamily,string rfield)
{
	id=rid;
	name=rname;
	family=rfamily;
	field=rfield;
	
}
string teacher::r_name()
{
	return (name+" "+family);
}



void lesson::report()
{
	if (id==0&&name_les=="")
	{
		return ;
	}
	cout<<"____________________________________________________\n";
	cout<<id<<"\t"<<name_les<<"\t\t"<<unit<<"\t\t"<<pre_of<<endl;
}

void lesson::report(string s)
{
	if (s==name_les)
	{
		cout<<"____________________________________________________\n";
	    cout<<id<<"\t"<<name_les<<"\t\t"<<unit<<"\t\t"<<pre_of<<endl;
	}
}

void lesson::report(int d)
{ 
	if (d==id)
	{
		cout<<"____________________________________________________\n";
	    cout<<id<<"\t"<<name_les<<"\t\t"<<unit<<"\t\t"<<pre_of<<endl;
	}
}

void lesson::Save2File()
{
	ofstream studfile("lessons.txt",ios::app);
	studfile<<id<<' '<<unit<<' '<<name_les<<' '<<pre_of<<endl;
	cout<<"record added to file successfully!"<<endl;
	studfile.close();

}

bool lesson::input(int d)
{
	cout<<"\nE.Exit or C.Continue \n";
	char *dud2=new char [20];
	char *dud;
		 dud=new char [20];
		 char *dud1=new char [20];
	switch (getch())
	{
	case '*':
			menu(lll);
			break;
	case 'e':
	case 'E':
		return false;
		break;
	case 'c':
	case 'C':
		cout <<"\nPlease enter an id for lesson number  (NUMBERS ONLY- NO SPACES !!) "<<d<<" :";
		
		//int temp2;
		 cin>>dud;
		 if(strtol(dud,NULL,10)!=0)
		 {
			 id=strtol(dud,NULL,10);
			 delete dud;
		 }
		 
		else
		{
			cout<<"\a\ninvalid data entered!"<<endl;
			id=NULL;
			this->input(d);
			delete dud;
			break;
		}
		cout <<"Please enter unit for lesson number  (NUMBERS ONLY !!) "<<d<<" :";
		//cin>>unit;
//		char *dud;
		
		//int temp2;
		 cin>>dud1;
		 if(strtol(dud1,NULL,10)!=0)
		 {
			 unit=strtol(dud1,NULL,10);
			 delete dud1;
		 }
		
		else
		{
			cout<<"\a\ninvalid data entered!"<<endl;
			unit=NULL;
			id=NULL;
			this->input(d);
			delete dud1;
			break;
		}
		cout <<"Please enter a name for lesson number (NO SPACES !!) "<<d<<" : ";
		cin>>name_les;

		
		cout<<"is it a dependant lesson? if yes enter the id of prerequestie lesson, if no enter 0: ";
		dud=new char [20];
		///int temp2;
		cin>>dud;
		if(strtol(dud,NULL,10)!=0)
		{
		   pre_of=strtol(dud,NULL,10);
		   delete dud;
		}
		else
		{
			cout<<"\a\ninvalid data entered!"<<endl;
			pre_of=NULL;
			this->input(d);
			delete dud;
			break;
		}
		cout<<pre_of;
		les[i3].Save2File();
		i3++;
		les[i3].input(i3+1);
		return true;
		break;
	}
}

void lesson::read(int idl,string namel,int unitt, int preee )
{
	name_les=namel;
	id=idl;
	unit=unitt;
	pre_of=preee;


}

bool lesson::check(int d)
{
	if (d==id )
	{
		if (/*capa>0*/true)
		{
			cout<<"3\t";
			cout<<"Your choosen lesson is "<<name_les<<" is it right ? Y.yes  N.No   :";
			switch(_getch())
			{
			case'Y':
			case'y':
				/*cout<<capa<<endl;
				--capa;
				cout<<capa<<endl;*/
				remove("lessons.txt");
				return true;
				break;
			case'N':
			case'n':
				return false;
				break;
			default:
				return false;
				break;
			}
		}
		else 
		{
			cout<<"the is no capacity for this lesson \n\n";
			G_C();
			return false ;
		}
	}

}

int lesson::check2(int lessson)
{
	if (id==lessson)
	{
		return pre_of;
	}
	else
	{
		return -1;
	}
}

string lesson::r_name()
{
	return name_les;
}


int times,timee;string datee;
void courses::report (int i)
{
	
	if (id==0&& idtea==0)
	{
		return ;
	}
	cout<<id<<"  [2]"<<les[i].r_name()<<"  [3]"<<tea[i].r_name()<<"  [4]"<<idclass<<"  [5]"<<capa<<"  [6]"<<dates<<"  [7]"<<time_start_h<<":"<<time_start_m<<"  [8]"<<time_end_h<<":"<<time_end_m<<endl<<endl;
}
//void courses::
void courses::read(int _id,int _idt,int _idclass,int _capa,string _dates,int _time_start_h,int _time_start_m,int _time_end_h,int _time_end_m,int _idl)
{
	id=_id;
	idt=_idt;
	idclass=_idclass;
	capa=_capa;
	dates=_dates;
	time_start_h=_time_start_h;
	time_start_m=_time_start_m;
	time_end_h=_time_end_h;
	time_end_m=_time_start_m;
	idl=_idl;
}
bool courses::input(int d)
{
	cout<<"\nE.Exit or C.Continue \n";
	/*char *dud2=new char [20];*/
	char *dud;
		 dud=new char [20];
		 /*char *dud1=new char [20];*/
		 switch (getch())
	{
	case '*':
			menu(lll);
			break;
	case 'e':
	case 'E':
		return false;
		break;
	case 'c':
	case 'C':
		cout <<"\nPlease enter an id for course number  (NUMBERS ONLY- NO SPACES !!) "<<d<<" :";
		
		//int temp2;
		 cin>>dud;
		 if(strtol(dud,NULL,10)!=0)
		 {
				id=strtol(dud,NULL,10);
				delete dud;
		 }
		else
		{
			cout<<"\a\ninvalid data entered!"<<endl;
			id=NULL;
			this->input(d);
			delete dud;
			break;
		}
		dud=new char [20];
		cout <<"Please enter an teaches's id for course number  (NUMBERS ONLY !!) "<<d<<" :";
		//cin>>unit;
//		char *dud;
		
		//int temp2;
		 cin>>dud;
		 if(strtol(dud,NULL,10)!=0)
		 {
			 int _idt=strtol(dud,NULL,10);
			 if (check_tea(_idt))
			 {
				idt=strtol(dud,NULL,10);
				delete dud;
			 }
		 }
		
		else
		{
			cout<<"\a\ninvalid data entered!"<<endl;
			idt=NULL;
			this->input(d);
			delete dud;
			break;
		}
		 dud=new char [20];
		 cout <<"Please enter an class number for course number "<<d<<"  (NUMBERS ONLY- NO SPACES !!) :";
		
		//int temp2;
		 cin>>dud;
		 if(strtol(dud,NULL,10)!=0)
		 {
			 idclass=strtol(dud,NULL,10);
			 delete dud;
		 }
		 
		else
		{
			cout<<"\a\ninvalid data entered!"<<endl;
			idclass=NULL;
			this->input(d);
			delete dud;
			break;
		}
		 dud=new char [20];
		cout <<"Please enter an capacity id for course number  (NUMBERS ONLY !!) "<<d<<" :";
		
		//int temp2;
		 cin>>dud;
		 if(strtol(dud,NULL,10)!=0)
		 {
			 capa=strtol(dud,NULL,10);
			 delete dud;
		 }
		 
		else
		{
			cout<<"\a\ninvalid data entered!"<<endl;
			capa=NULL;
			this->input(d);
			delete dud;
			break;
		}
		 dud=new char [20];
		 cout <<"Please enter date of exam for course number  (NUMBERS ONLY !!) "<<d<<" :";
		 cin>>dates;
		 
		 dud=new char [20];
		 cout <<"Please enter start time <HOUR> of course number (NUMBERS ONLY!)<HOUR> "<<d<<" :";
		
		//int temp2;
		 cin>>dud;
		 if(strtol(dud,NULL,10)!=0)
		 {
			 time_start_h=strtol(dud,NULL,10);
			 delete dud;
		 }
		 
		else
		{
			cout<<"\a\ninvalid data entered!"<<endl;
			time_start_h=NULL;
			this->input(d);
			delete dud;
			break;
		}
		 
		 cout <<"Please enter start time <MINUTE> of course number (NUMBERS ONLY!)<MINUTE> "<<d<<" :";
		 cin>>time_start_m;


		 dud=new char [20];
		 cout <<"Please enter end time <Hour> of course number (NUMBERS ONLY!)<Hour> "<<d<<" :";
		
		//int temp2;
		 cin>>dud;
		 if(strtol(dud,NULL,10)!=0)
		 {

			 time_end_h=strtol(dud,NULL,10);
			 delete dud;
		 }
		 
		else
		{
			cout<<"\a\ninvalid data entered!"<<endl;
			time_end_h=NULL;
			this->input(d);
			delete dud;
			break;
		}
		 cout <<"Please enter end time <MINUTE> of course number (NUMBERS ONLY!)<MINUTE> "<<d<<" :";
		 cin>>time_end_m;


		 dud=new char [20];
		 cout <<"Please enter an id for lesson that course number "<<d<<" inharits from that(NUMBERS ONLY!)";
		
		//int temp2;
		 cin>>dud;
		 if(strtol(dud,NULL,10)!=0)
		 {
			 int _idl=strtol(dud,NULL,10);
			 if (check_less(_idl))
			 {
				idl=strtol(dud,NULL,10);
				delete dud;
			 }
			 else
			 {
				 cout<<"there is no lesson with this id!!!!!\n\n";
				 this->input(d);
				 return false;
			 }
		 }
		else
		{
			cout<<"\a\ninvalid data entered!"<<endl;
			idl=NULL;
			this->input(d);
			delete dud;
			break;
		}
		/*default:
			return false;
	    break;*/

		cour[i4].Save2File();
		i4++;
		cour[i4].input(i4+1);
		return true;
		    break;
	}

}
bool courses::check_tea(int _idt)
{
	for (int o=0;o<100;o++)
	{
		if (_idt==tea[o].id)
		{
			return true;
		}
	}
	return false;
}
bool courses::check_less(int _idl)
{
	for (int o=0;o<100;o++)
	{
		if (_idl==les[o].id)
		{
			return true;
		}
	}
	return false;
}
void courses::Save2File()
{
	ofstream studfile("teachers_courses.txt",ios::app);
	studfile<<id<<' '<<idt<<' '<<idclass<<' '<<capa<<' '<<dates<<' '<<time_start_h<<' '<<time_start_m<<' '<<time_end_h<<' '<<time_end_m<<' '<<idl<<endl;
	cout<<"record added to file successfully!"<<endl;
	studfile.close();

}
int  courses::pre(int idcourse )
{
	if (idcourse==id)
	{
		times=time_start_h*60+time_start_m;
		timee=time_end_h*60+time_end_m;
		datee=dates;
		return idl;
	}
	else
	{
		return -1;
	}
}
bool courses::check_capa(int idcourse)
{
	if (idcourse==id && capa<0 )
	{
		cout<<"there is no capacity for this class!!!!!\n\n";
		return false;
	}
	else if (id=idcourse==id && capa>0)
	{
		capa--;
		idtea=idt;
		return true;
	}
	return true;
}
bool courses::check_time(int idcourse)
{
	if (id==idcourse &&datee==dates && ( (times<(time_end_h*60+time_end_m) && times>=(time_start_h*60+time_start_m))||(timee<(time_end_h*60+time_end_m) && timee>=(time_start_h*60+time_start_m))  ) )
	{
		cout<<"tadakhole zamani ba darse "<<id<<"\n\n";
		return false;
	}
	else 
	{
		return true;
	}
}
bool courses::check5(int idstudent)
{
	return true;
}


bool get_course::check1(int idstudent,int idcourse)
{
	if (idcourse==id_dars && idstudent==id_stu)
	{
		cout<<"you have picked this course before !!!!!!!\n\n";
		return false;
	}
	/*else if (idstudent==id_stu  &&  cour[0].check_less()== true)
	{
		return false;
	}*/
	else
	{
		return true;
	}
}
void get_course::Save2File()
{
	ofstream studfile("GetCourses.txt",ios::app);
	studfile<<id_stu<<' '<<id_tch<<' '<<id_dars<<' '<<score<<endl;
	cout<<"record added to file successfully!"<<endl;
	studfile.close();
}
void get_course::Save2File2()
{
	if (id_stu!=0 && id_tch!=0)
	{
	ofstream studfile("GetCourses.txt",ios::app);
	studfile<<id_stu<<' '<<id_tch<<' '<<id_dars<<' '<<score<<endl;
	studfile.close();
	}
}
void get_course::input(int ds,int dt,int dl)
{
	id_stu=ds;
	id_tch=dt;
	id_dars=dl;
	cout<<"For Student number "<<ds<<" the lesson number "<<dl<<" with teacher by name "<<dt<<" Accepted ! \n\n";
	Save2File();
	G_C();
}
void get_course::delfromfile ()
{
	ofstream delfile ("GetCourses.txt" , ios::app);
	if(id_stu==NULL&& id_tch==2)
		return;
	else
	{
		delfile<<id_stu<<' '<<id_tch<<' '<<id_dars<<endl;
	}
	delfile.close();
}
void get_course::read(int rid_stu,int rid_tch,int rid_dars,float _score)
{
	id_stu=rid_stu;
	id_tch=rid_tch;
	id_dars=rid_dars;
	score=_score;
}
get_course::get_course()
{
	score=0;
}
int get_course::check3(int idstudent,int pre)
{
	if (idstudent==id_stu && pre==id_dars)
	{
		if (score>=10)
		{
			return 1;
			t=true;
		}
		else
		{
			cout<<"adame raiate doroose pishniaz !!!!!!\n\n";
			return 3;
		}
	}
	return 2;
}
void get_course::report(int _id)
{
	if (id_tch==_id)
	{
		cout<<id_stu<<"      "<<id_dars<<"      "<<score<<endl;
	}
}
bool get_course::check4(int idstudent)
{
	if (id_stu==idstudent)
	{
		for (int c3=0;c3<100;c3++)
		{
			if (!cour[c3].check_time(id_dars))
			{
				return false;
				break;
			}
		}
	}
	return true;
}
bool get_course::en_s(int _ids, int _idc)
{
	if (_ids==id_stu && _idc==id_dars)
	{
		cout<<"please enter a score for student number "<<_ids<<" : ";
		cin>>score;
		remove ("GetCourses.txt");
		for (int p=0;p<100 ;p++)
		{
			g_c[p].Save2File2();
		}
		cout<<"record added to file successfully!"<<endl;
		return true;
	}
	return false;;
}
//-

//---------------------------------------------- functions---------------------------

void DataEntry();
void DataRemoval();
void Report();
void About();
void check (char ch);
void Ent_stu();
void Ent_tea();
void Ent_les();
void Ent_cour();
void Del_stu();
void Del_tea();
void Del_les();
void Rep_Stu();
void Rep_Tea();
void Rep_Les();
void Rep_Cour();
void Ent_Score();

//----------------------------------------------global data--------------------------

//----------------------------------------------main---------------------------------
int main()
{
	SetWindow(80,40);
	system ("Color 1E");
	splash();
	ReadFromFile();
	menu(Login());
	return 0;
}

int Login ()
{
	int lid;
	string lname;
	gotoXY(24,7);
	cout<<"Intelligent Course Select App\n\n"<<endl;
	gotoXY(25,9);
	cout<<"Login using your ID and pass\n\n"<<endl;
	gotoXY(15,12);
	cout<<" --------------------------------------------"<<endl;
	gotoXY(15,13);
	cout<<"|ID:                                         |"<<endl;
	gotoXY(15,14);
	cout<<" --------------------------------------------"<<endl;
	gotoXY(15,15);
	cout<<"|Passphrase:                                 |"<<endl;
	gotoXY(15,16);
	cout<<" --------------------------------------------"<<endl;
	gotoXY(19,13);
		cin>>lid;
		gotoXY(28,15);	 
		char key;
		key=getch();
		while (key!='\r')
		{
			if(key=='\b')
			{
				if(lname.length()!=0)
				{
				lname.pop_back();
				cout<<"\b"<<" "<<"\b" ;
				}
				else
					cout<<"\a";
			}
			else
			{
			lname+=key;
			cout<<"*";
			}
			key=getch();
		}
		

		 //asterisk passwords!
		 if(lid==8888)
		{
		 if(lname=="admin")
		lll=0;	 
		 {
		system("cls");
		gotoXY(25,9);
		cout<<"Welcome ADMIN, Login successful"<<endl;
		

		Sleep(900);
			 return 0;
		 }
		}
		else if (lid!=8888)
		{
		//check if it is a student
			for (int i = 0; i < 100; i++)
				{
					if (stu[i].check(lid)==true)
					{
					 if(stu[i].check(lname))
						{
		system("cls");
		gotoXY(25,9);
		cout<<"Welcome "<<lname<<", Login successful"<<endl;
		Sleep(900);
				 lll=1;
							return 1;
						 break;
						}
					}
				}

	//check if it is a teacher
		for (int i = 0; i < 100; i++)
			{
				if (tea[i].check(lid)==true)
					{
						if(tea[i].check(lname))
						{
						 system("cls");
		gotoXY(25,9);
		cout<<"Welcome "<<lname<<", Login successful"<<endl;
		Sleep(900);
		lll=2;
			return 2;
						 break;
						}
					}
			}
	
		}
	else
		return 50;
		
    
}
		
void ReadFromFile()
{
	ifstream read_stud("students.txt");
	int ids=0,i=0;
	string names,fields,LastNames;	
	while (read_stud>>ids>>names>>LastNames>>fields)
	{
		stu[i].read(ids,names,LastNames,fields);
		i++;
		i1++;
	}
	read_stud.close();
	ifstream read_teac("teachers.txt");
	int idt=0,j=0;
	string namet,fieldt,familyt;	
	while (read_teac>>idt>>namet>>familyt>>fieldt)
	{
		tea[j].read(idt,namet,familyt,fieldt);
		j++;
		i2++;
	}
	read_teac.close();
    ifstream read_less("lessons.txt");
	int idl=0,f=0,unitt,pree;
	string namel;	
	while (read_less>>idl>>unitt>>namel>>pree)
	{
		les[f].read(idl,namel,unitt,pree);
		f++;
		i3++;
	}
	read_less.close();
	ifstream read_g_c("GetCourses.txt");
	int id_stu=0,id_dars=0,j2=0;
	float score=0;
	int name_tch;	
	while (read_g_c>>id_stu>>name_tch>>id_dars>>score)
	{
		g_c[j2].read(id_stu,name_tch,id_dars,score);
		j2++;
		G++;
	}
	read_g_c.close();

	ifstream read_course("teachers_courses.txt");
	int id,idtea,idclass,capa,time_start_h,time_start_m,time_end_h,time_end_m,idles,j4=0;
	string dates;
	while (read_course>>id>>idtea>>idclass>>capa>>dates>>time_start_h>>time_start_m>>time_end_h>>time_end_m>>idles)
	{
		cour[j4].read(id,idtea,idclass,capa,dates,time_start_h,time_start_m,time_end_h,time_end_m,idles);
		j4++;
		i4++;
	}
}

void check (char ch )
{

	switch (ch)
	{
	case '*':
		
		menu(lll);
		break;
	case 'A':
	case 'a':
		
		DataEntry();
		break;
	case 'B':
	case 'b':
		
		DataRemoval();
		break;
	case 'C':
	case 'c':
		
		Report();
		break;
	
	case 'E':
	case 'e':
		
		G_C();
		break;
	case 'F':
	case 'f':
		
		About();	
	break;
	case 'X':
	case 'x':
		exit;
		break;
	case 'L':
	case 'l':
		system("CLS");
		menu(Login());
		break;
	case 'S':
	case's':
		Ent_Score();
		break;


	default:
		menu(lll);		
		break;
	system("CLS");
	}
}
//------------------------------------score functions---------------------------------
void Ent_Score()
{
	if (lll==0 || lll==2)
	{
		int idstudent=0,idcourse=0;
		cout<<"____________________________________Score___________________________________\n\n";
		char *dud;
        dud=new char [20];
	cout<<"C.Continue      E.Exit   : \n";
	switch(_getch())
	{
	case 'e':
	case 'E':
	case '*':
		menu(lll);
		break;
	case 'C':
	case 'c':
		cout<<"Please Enter an Id for student <ONLY NUMBER!!!!!> : ";
		dud=new char [20];
		cin>>dud;
		if(strtol(dud,NULL,10)!=0)
		{
			idstudent=strtol(dud,NULL,10);
			delete dud;
		}
		else
		{
			cout<<"\a\ninvalid data entered!"<<endl;
			idstudent=NULL;
			delete dud;
			G_C();
			return;
			break;
		}
		cout<<"Please Enter a course id  <ONLY NUMBER!!!!!>\n ";
		dud=new char [20];
		cin>>dud;
		if(strtol(dud,NULL,10)!=0)
		{
			idcourse=strtol(dud,NULL,10);
			delete dud;
		}
		else
		{
			cout<<"\a\ninvalid data entered!"<<endl;
			idcourse=NULL;
			delete dud;
			G_C();
			return;
			break;
		}
		for (int p=0;p<100 ;p++)
		{
			if (g_c[p].en_s(idstudent,idcourse))
			{
				Ent_Score();
				return;
				break;
			}
		}
		cout<<"find a mistake!!!!!!";
		Ent_Score();
		return;
		menu(lll);
		break;
	}
	}
}
//------------------------------------DataEntry functions---------------------------------

void DataEntry()
{
	if (lll==0)
	{
		system("cls");
	    cout<<"____________________________________DataEntry___________________________________\n\n";
		cout<<"S.Student\t\tT.Teacher\t\tL.Lesson\t\tC.Course\n\n";
		switch (_getch())
		{
		case 's':
		case 'S':
			Ent_stu();
			break;
		case 't':
		case 'T':
			Ent_tea();
			break;
		case 'l':
		case 'L':
			Ent_les();
			break;
	    case 'C':
		case 'c':
			Ent_cour();
			break;
		default:
			DataEntry();
			break;
		system("CLS");
		}
	}
}

void Ent_stu()
{
	bool b;
	for (i1 ; i1<100;i1++)
	{
		b=stu[i1].input(i1+1);
		if ( b ==false)
		{
			//i1-=1;
			break;
		}
	}
	
	
	menu(lll);
}

void Ent_tea()
{
	bool b;
	for (i2; i2<100;i2++)
	{
		b=tea[i2].input(i2+1);
		if ( b ==false)
		{
			break;
		}
	}
	menu(lll);
}

void Ent_les()
{
	bool b;
	int ii=i3 ;
		b=les[ii].input(ii+1);
	menu(lll);
}

void Ent_cour()
{
    bool b;
	int ii=i4 ;
		b=cour[ii].input(ii+1);
	menu(lll);
}

//---------------------------------------Delete data functions----------------------------
void DataRemoval()
{
	system("cls");
	cout<<"______________________Data Removal_____________________\n\n";
		cout<<"S.Student\t\tT.Teacher\t\tL.Lesson\n\n";
		switch (_getch())
		{
		case 's':
		case 'S':
			Del_stu();
			break;
		case 't':
		case 'T':
			Del_tea();
			break;
		case 'l':
		case 'L':
			Del_les();
			break;
		}
}

void Del_stu()
{
	string s;
	int id;
	bool t=false;
	cout<<"________________________Delete a student________________________\n\n";
	cout<<"I.Delete by id \t\t N.Delete by name\n";
	switch (_getch())
	{
	case '*':
			menu(lll);
			break;
	case 'N':
	case 'n':
		cout<<"\n\n_____________________Delete by Name_____________________\n\n";
		cout<<"Please Enter youe student's name : ";
		cin>>s;
		for (int i = 0; i < 100; i++)
		{
			t=stu[i].Del(s);
			if (t)
			{
				cout<<"\n<<Your student Deleted>>\n\n";
				remove ("students.txt");
				for (int f =0 ;f<100;f++)
				{
					stu[f].delfromfile();
				}
				break;
			}
		}
		if (!t)
			cout<<"\n<<No Body Deleted !>>\n";
		break;
	case 'I':
	case 'i':
		cout<<"\n\n_____________________Delete by Id_____________________\n\n";
		cout<<"Please Enter youe student's id : ";
		cin>>id;
		for (int i = 0; i < 100; i++)
		{
			t=stu[i].Del(id);
			if (t)
			{
				cout<<"\n<<Your student Deleted>>\n\n";
				remove ("students.txt");
				for (int f =0 ;f<100;f++)
				{
					stu[f].delfromfile();
				}
				break;
			}
		}
		if (!t)
			cout<<"\n<<No Body Deleted !>>\n";
		break;
	}
	menu(lll);
}

void Del_tea()
{
	string s;
	bool t=false;
	int id;
	cout<<"________________________Delete a teacher________________________\n\n";
	cout<<"I.Delete by id \t\t N.Delete by name\n";
	switch (_getch())
	{
	case '*':
			break;
			menu(lll);
	case 'N':
	case 'n':
		cout<<"\n\n_____________________Delete by Name_____________________\n\n";
		cout<<"Please Enter youe teacher's name : ";
		cin>>s;
		for (int i = 0; i < 100; i++)
		{
			t=tea[i].Del(s);
			if (t)
			{
				cout<<"\n<<Your teacher Deleted>>\n\n";
				remove ("teachers.txt");
				for (int f =0 ;f<100;f++)
				{
					tea[f].delfromfile();
				}
				break;
			}
		}
		if (!t)
			cout<<"\n<<No Body Deleted !>>\n";
		break;
		break;
	case 'I':
	case 'i':
		cout<<"\n\n_____________________Delete by Id_____________________\n\n";
		cout<<"Please Enter youe teacher's id : ";
		cin>>id;
		for (int i = 0; i < 100; i++)
		{
			t=tea[i].Del(id);
			if (t)
			{
				cout<<"\n<<Your teacher Deleted>>\n\n";
				remove ("teachers.txt");
				for (int f =0 ;f<100;f++)
				{
					tea[f].delfromfile();
				}
				break;
			}
		}
		if (!t)
			cout<<"\n<<No Body Deleted !>>\n";
		break;
	}
	menu(lll);
}

void Del_les()
{
	bool b;
	for (i3 ; i3<100;i3++)
	{
		b=les[i3].input(i3+1);
		if ( b ==false)
		{
			break;
		}
	}
	menu(lll);
}
//----------------------------------------Report---------------------------
void Report()
{
	system("cls");
	if (lll==0)
	{
	cout<<"____________________________________Report_____________________________________\n\n";
		cout<<"S.Student\t\tT.Teacher\t\tL.Lesson\t\tC.course\n\n";
		switch (_getch())
		{
			case 's':
			case 'S':
				Rep_Stu();
				break;
			case 't':
			case 'T':
				Rep_Tea();
				break;
			case 'l':
			case 'L':
				Rep_Les();
				break;
			case 'C':
			case 'c':
				Rep_Cour();
				break;
			default:
				Report();
				return;
		}
	}
	else if (lll==1)
	{
		cout<<"____________________________________Report_____________________________________\n\n";
		Rep_Stu();
	}
	else if (lll==2);
	{
		cout<<"____________________________________Report_____________________________________\n\n";
		Rep_Stu();
	}
}
void Rep_Stu()
{
	if (lll==0)
	{
	cout<<"________________________Report Students________________________\n\n";
	cout<<"A.All Students \t\t I.Id \t\t N.Name\n";
	int id;
	string s;
	switch (_getch())
	{
	case '*':
		menu(lll);
		break;
	case 'A':
	case 'a':
		cout<<"\n\n_____________________Report All Students_____________________\n\n";
		cout<<"Id"<<"\t"<<"Name"<<"\t"<<"Last Name"<<"\t"<<"field"<<"\n";
		for (int i =0 ;i<100;i++)
		{
			stu[i].report();
			
		}
		_getch();
		menu(lll);
		break;
	case 'i':
	case 'I':
		cout<<"\n\n_____________________Report By Id_____________________\n\n";

		cout<<"Please Enter a Id :";
		cin>>id;
		cout<<"Id"<<"\t"<<"Name"<<"\t"<<"Last Name"<<"\t"<<"field"<<"\n[1]Course    [2]score\n";
		for (int i =0 ;i<100;i++)
		{
			stu[i].report(id);
			
		}
		_getch();
		menu(lll);
		break;
	case 'N':
	case 'n':
		cout<<"\n\n_____________________Report By Name_____________________\n\n";
		cout<<"Please Enter a Name :";
		cin>>s;
		cout<<"Id"<<"\t"<<"Name"<<"\t"<<"Last Name"<<"\t"<<"field"<<"\n";
		for (int i =0 ;i<100;i++)
		{
			stu[i].report(s);
		}
		_getch();
		menu(lll);
		break;
		
	}
	}
	else if (lll==1)
	{
		cout<<"Id"<<"\t"<<"Name"<<"\t"<<"Last Name"<<"\t"<<"field"<<"\n[1]Course    [2]score\n";
		for (int i =0 ;i<100;i++)
		{
			stu[i].report(s_id);
			
		}
		_getch();
		menu(lll);
	}
	else if (lll==2)
	{
		cout<<"Student-id"<<"\t"<<"courses-id"<<"\t"<<"score"<<endl;
		for (int i =0 ;i<100;i++)
		{
			g_c[i].report(s_id);
		}
		_getch();
		menu(lll);
	}

}
void Rep_Tea()
{
	cout<<"________________________Report Teachers________________________\n\n";
	cout<<"A.All Teachers \t\t I.Id \t\t N.Name\n";
	int id;
	string s;
	switch (_getch())
	{
	case '*':
		menu(lll);
		break;
	case 'A':
	case 'a':
		cout<<"\n\n_____________________Report All Teachers_______________\n\n";
		cout<<"Id"<<"\t"<<"Name"<<"\t\t"<<"field"<<"\n";
		for (int i =0 ;i<100;i++)
		{
			tea[i].report();
		}
				_getch();
		menu(lll);
		break;
	case 'i':
	case 'I':
		cout<<"\n\n_____________________Report By Id_____________________\n\n";

		cout<<"Please Enter a Id :";
		cin>>id;
		cout<<"Id"<<"\t"<<"Name"<<"\t\t"<<"field"<<"\n";
		for (int i =0 ;i<100;i++)
		{
			tea[i].report(id);
		}
		_getch();
		menu(lll);
		break;
	case 'N':
	case 'n':
		cout<<"\n\n_____________________Report By Name_____________________\n\n";
		cout<<"Please Enter a Name :";
		cin>>s;
		cout<<"Id"<<"\t"<<"Name"<<"\t\t"<<"field"<<"\n";
		for (int i =0 ;i<100;i++)
		{
			tea[i].report(s);
		}
		_getch();
		menu(lll);
		break;
	}
}
void Rep_Les()
{
	cout<<"________________________Report Lessons________________________\n\n";
	cout<<"A.All lessons \t\t I.Id \t\t N.Name\n";
	int id;
	string s;
	switch (_getch())
	{
	case '*':
		menu(lll);
		break;
	case 'A':
	case 'a':
		cout<<"\n\n_____________________Report All Lessons_____________________\n\n";
		cout<<"Id"<<"\t"<<"Name"<<"\t\t"<<"field"<<"\n"<<"prerequistitie"<<endl;
		for (int i =0 ;i<100;i++)
		{
			les[i].report();
			
		}
		_getch();
		menu(lll);
		break;
	case 'i':
	case 'I':
		cout<<"\n\n_____________________Report By Id_____________________\n\n";

		cout<<"Please Enter a Id :";
		cin>>id;
		cout<<"Id"<<"\t"<<"Name"<<"\t\t"<<"field"<<"\n"<<"prerequistitie"<<endl;
		for (int i =0 ;i<100;i++)
		{
			les[i].report(id);
		}
		_getch();
		menu(lll);
		break;
	case 'N':
	case 'n':
		cout<<"\n\n_____________________Report By Name_____________________\n\n";
		cout<<"Please Enter a Name :";
		cin>>s;
		cout<<"Id"<<"\t"<<"Name"<<"\t\t"<<"field"<<"\n"<<"prerequistitie"<<endl;
		for (int i =0 ;i<100;i++)
		{
			les[i].report(s);
		}
		_getch();
		menu(lll);
		break;
	}
}
void Rep_Cour()
{
		cout<<"\n\n_____________________Report All Courses_____________________\n\n";
		cout<<"Id"<<"  [2]Name"<<" "<<"[3]Name-teacher"<<" "<<"[4]class"<<" "<<"[5]capacity "<<"[6]date "<<"[7]s-time "<<" [8]e-time  "<<endl<<endl;
		for (int i =0 ;i<100;i++)
		{
			cour[i].report(i);
			
		}
		_getch();
		menu(lll);
}

//----------------------------------------main menu----------------------------
void menu(int m)
{
	
	system("CLS");
	switch (m)
	{
	case 0:
		cout <<"----Admin Menu ----"
			<<"_________________________________________________________\n\nWelcome to our intelligent course select app "<<s_name<<" "<<s_family<<". use one of the options to begin.\nRemember you can always return to this menu by pressing the asterisk ( * ).\nHave fun\n\n\n"
			 <<"A.Data Entry \t\tB.Data Removal \n\nC.Report \t\tE.Get Course\n\nL.Log out \t\tS.Score\n\nF.About us \t\tX.Exit \n";
		break;
	case 1:
		cout <<"----Student Menu ----"
			<<"_________________________________________________________\n\nWelcome to our intelligent course select app "<<s_name<<" "<<s_family<<". use one of the options to begin.\nRemember you can always return to this menu by pressing the asterisk ( * ).\nHave fun\n\n\n"
			 <<"C.Report\t\tE.Get Course  \n\nF.About us \t\tL.Log out\n\nX.Exit \n";
		
		break;
	case 2:
		cout <<"----Teacher Menu ----"
			<<"_________________________________________________________\n\nWelcome to our intelligent course select app "<<s_name<<" "<<s_family<<". use one of the options to begin.\nRemember you can always return to this menu by pressing the asterisk ( * ).\nHave fun\n\n\n"
			 <<"C.Report\t\tF.About us \t\tL.Log out\n\nS.score \t\tX.Exit \n";
		
		break;
	default:
		cout<<"bad id or passphrase"<<endl;
		getch();
		system("cls");
		menu(Login());
		break;
	}
	//ReadFromFile();
	//cin>>flush();
	check(_getch());
}
//----------------------------------------Get courses---------------------------

//----------------------------------------About---------------------------------

void G_C()
{
	if (lll==0)
	{
	system("cls");
	t=false;
	char *dud;
    dud=new char [20];
	int idstudent=0,idcourse=0,idlesson=0,idpre=0;
	idtea=0;
	cout<<"_______________________Get Course______________________\n\n";
	cout<<"C.Continue      E.Exit   : \n";
	switch(_getch())
	{
	case 'e':
	case 'E':
	case '*':
		menu(lll);
		break;
	case 'C':
	case 'c':
		cout<<"Please Enter an Id for student <ONLY NUMBER!!!!!> : ";
		dud=new char [20];
		cin>>dud;
		if(strtol(dud,NULL,10)!=0)
		{
			idstudent=strtol(dud,NULL,10);
			delete dud;
		}
		else
		{
			cout<<"\a\ninvalid data entered!"<<endl;
			idstudent=NULL;
			delete dud;
			G_C();
			return;
			break;
		}
		cout<<"Please Enter an Id for course that you want pick <ONLY NUMBER!!!!!>\n ";
		cout<<"(if you want see the courses list just Enter C ) :";
		dud=new char [20];
		cin>>dud;
		string s;
		s=dud;
		if (s=="c" || s=="C")
		{
			cout<<"\n\n_____________________Report All Courses_____________________\n\n";
		    cout<<"Id"<<"  [2]Name"<<" "<<"[3]Name-teacher"<<" "<<"[4]class"<<" "<<"[5]capacity "<<"[6]date "<<"[7]s-time "<<" [8]e-time  "<<endl<<endl;
			for (int iii3 =0 ;iii3<100;iii3++)
			{
				cour[iii3].report(iii3);
			}
			cout<<"Now please Enetr an Id for course that you want pick <ONLY NUMBER!!!!!> :";
			cin>>dud;
		}
		if(strtol(dud,NULL,10)!=0)
		{
			idcourse=strtol(dud,NULL,10);
			delete dud;
		}
		else
		{
			cout<<"\a\ninvalid data entered!"<<endl;
			idcourse=NULL;
			delete dud;
			G_C();
			return;
			break;
		}
		for (int c1=0;c1<100;c1++)
		{
			if (g_c[c1].check1(idstudent,idcourse))
			{
				continue;
			}
			else
			{
				G_C();
				return;
			}
		}

		for (int c1=0;c1<100;c1++)
		{
			if (cour[c1].pre(idcourse)==-1)
			{
				continue;
			}
			else
			{
				idlesson=cour[c1].pre(idcourse);
				break ;
			}
		}
        for (int c1=0;c1<100;c1++)
		{
			if (les[c1].check2(idlesson)==-1)
			{
				continue;
			}
			else
			{
				idpre=les[c1].check2(idlesson);
				break;
			}
		}

		for (int c1=0;c1<100;c1++)
		{
			if (g_c[c1].check3(idstudent,idpre)==2)
			{
				continue;
			}
		}
		t=true;
		   if (t)
			{
				for (int c2=0;c2<100;c2++)
				{
					if(g_c[c2].check4(idstudent))
					{
						 for (int c3=0;c3<100;c3++)
						 {
							 if (!cour[c3].check_capa(idcourse))
							 {
								 G_C();
								 return;
							 }
						 }

						 for (int c4=0;c4<100;c4++)
							 g_c[c4].input(idstudent,idtea,idcourse);
					}
					else
					{
						G_C();
						return;
					}
				}
				break;
			}
			else 
			{
				G_C();
				return;
			}
		G_C();
		return;
		break;
	}
	}
	else if (lll==1)
	{
		t=false;
	char *dud;
    dud=new char [20];
	int idstudent=0,idcourse=0,idlesson=0,idpre=0;
	idtea=0;
	cout<<"_______________________Get Course______________________\n\n";
	cout<<"C.Continue      E.Exit   : \n";
	switch(_getch())
	{
	case 'e':
	case 'E':
	case '*':
		menu(lll);
		break;
	case 'C':
	case 'c':
		idstudent=s_id;
		cout<<"Please Enter an Id for course that you want pick <ONLY NUMBER!!!!!>\n ";
		cout<<"(if you want see the courses list just Enter C ) :";
		dud=new char [20];
		cin>>dud;
		string s;
		s=dud;
		if (s=="c" || s=="C")
		{
			cout<<"\n\n_____________________Report All Courses_____________________\n\n";
		    cout<<"Id"<<"  [2]Name"<<" "<<"[3]Name-teacher"<<" "<<"[4]class"<<" "<<"[5]capacity "<<"[6]date "<<"[7]s-time "<<" [8]e-time  "<<endl<<endl;
			for (int iii3 =0 ;iii3<100;iii3++)
			{
				cour[iii3].report(iii3);
			}
			cout<<"Now please Enetr an Id for course that you want pick <ONLY NUMBER!!!!!> :";
			cin>>dud;
		}
		if(strtol(dud,NULL,10)!=0)
		{
			idcourse=strtol(dud,NULL,10);
			delete dud;
		}
		else
		{
			cout<<"\a\ninvalid data entered!"<<endl;
			idcourse=NULL;
			delete dud;
			G_C();
			return;
			break;
		}
		for (int c1=0;c1<100;c1++)
		{
			if (g_c[c1].check1(idstudent,idcourse))
			{
				continue;
			}
			else
			{
				G_C();
				return;
			}
		}

		for (int c1=0;c1<100;c1++)
		{
			if (cour[c1].pre(idcourse)==-1)
			{
				continue;
			}
			else
			{
				idlesson=cour[c1].pre(idcourse);
				break ;
			}
		}
        for (int c1=0;c1<100;c1++)
		{
			if (les[c1].check2(idlesson)==-1)
			{
				continue;
			}
			else
			{
				idpre=les[c1].check2(idlesson);
				break;
			}
		}

		for (int c1=0;c1<100;c1++)
		{
			if (g_c[c1].check3(idstudent,idpre)==2)
			{
				continue;
			}
		}
		t=true;
		   if (t)
			{
				for (int c2=0;c2<100;c2++)
				{
					if(g_c[c2].check4(idstudent))
					{
						 for (int c3=0;c3<100;c3++)
						 {
							 if (!cour[c3].check_capa(idcourse))
							 {
								 G_C();
								 return;
							 }
						 }

						 for (int c4=0;c4<100;c4++)
							 g_c[c4].input(idstudent,idtea,idcourse);
					}
					else
					{
						G_C();
						return;
					}
				}
				break;
			}
			else 
			{
				G_C();
				return;
			}
		G_C();
		return;
		break;
	}
	}
}

void About(){
cout<<"________________________About us_______________________\n\n";
		cout<<"<Intelligent Course Select Application>\nThis Application is made by:\n joint efforts of Reza Arani And Mohammad Hossein Nazemy \n(C)2013 All rights reserved \nContact us pis7aller@gmail.com --- reza.da.gr8@gmail.com \n\n\n";
		getch();
		menu(lll);

}
//----------------------------------------Splash Screen-------------------------

void splash()
{
cout<<"                   +                                    +\n";  
_sleep(100);
cout<<"                   +++                                +++\n";  
_sleep(100);
cout<<"                   +++++                            +++++\n";  
_sleep(100);
cout<<"                   +++++++                        +++++++\n";  
_sleep(100);
cout<<"                   +++++++++                    ++++++++\n";  
_sleep(100);
cout<<"                     ++++++++++               +++++++++ \n";   
_sleep(100);
cout<<"                      +++++++++++           ++++++++++ \n";    
_sleep(100);
cout<<"                    +   ++++++++++        ++++++++++    +\n";  
_sleep(100);
cout<<"                    +++   +++++++++++   ++++++++++    +++\n";  
_sleep(100);
cout<<"                    +++++   ++++++++++ +++++++++    +++++\n";  
_sleep(100);
cout<<"                     ++++++   +++++ :: :: ++++    ++++++\n";   
_sleep(100);
cout<<"                       ++++++ ++++ ::: ::: ++++ +++++++\n";    
_sleep(100);
cout<<"                    +   ++++++++ ::::: ::::: +++++++    +\n";  
_sleep(100);
cout<<"                    +++    ++++ :::::: :::::: ++++    +++\n"; 
_sleep(100);
cout<<"                    +++++ ++++ ::::::: ::::::: ++++ +++++\n"; 
_sleep(100);
cout<<"                     ++++++++ :::::::: :::::::: ++++++++\n";
_sleep(100);
cout<<"                       +++++ ::::::::: ::::::::: +++++\n";     
_sleep(100);
cout<<"                         +++ ::::::::   :::::::: +++\n";       
_sleep(100);
cout<<"                           +:::::::::   :::::::::+\n";         
_sleep(100);
cout<<"                             :::::::::::::::::::\n";           
_sleep(100);
cout<<"                            ++ ::::::::::::::: ++\n";          
_sleep(100);
cout<<"                            ++++ ::::::::::: ++++\n";          
_sleep(100);
cout<<"                            ++++++ ::::::: ++++++\n";          
_sleep(100);
cout<<"                            ++++++++ ::: ++++++++\n";          
_sleep(100);
cout<<"                            ++++++++++ ++++++++++\n";          
_sleep(100);
cout<<"                            ++++++++     ++++++++\n";          
_sleep(100);
cout<<"                            ++++++         ++++++\n";         
_sleep(100);
cout<<"                            +++++           +++++\n";          
_sleep(100);
cout<<"                            ++++             ++++\n";          
_sleep(100);
cout<<"                            +++               +++\n";          
_sleep(100);
cout<<"                            +++               +++\n";          
_sleep(100);
cout<<"                            ++                 ++\n";         
_sleep(100);
cout<<"                            ++                 ++\n";          
_sleep(100);
cout<<"                            +                   +\n";          
_sleep(100);
cout<<"                            +                   +\n";          
_sleep(1000);
                                                            

_sleep(1000);
                                                               
system("CLS");

}