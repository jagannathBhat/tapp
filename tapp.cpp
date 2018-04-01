/*
Teacher's App (TAPP)

A program that enables users to create and maintain records of students.

This project is licensed under the terms of the GNU GPLv3 license.
A copy of the lisence will be found in the root directory of the project as "LICENSE.txt"
*/
#include<fstream.h>
#include<conio.h>
#include<string.h>
#include<stdio.h>
#include<process.h>
#include<dos.h>

char filenam[60];

struct user{
	char id[50],pass[50];
};

struct subject{
	char sname[50];
	float mark;
};

struct student{
	char name[50];
	float clas;
	int roll,no;
	subject subs[10];
	void getdata();
	void dispdata();
};

void student::getdata(){
	char ch='y';
	clrscr();
	cout<<"\nEnter Name:   ";
	gets(name);
	clrscr();
	cout<<"Instructions-\nEnter in digits only. Enter -2 for LKG and -1 for UKG.\n";
	cout<<"Put division in decimal place.\nFor example enter 12.1 for Class 12, A division.\nEnter Class: ";
	cin>>clas;
	clrscr();
	cout<<"Enter Roll no.: ";
	cin>>roll;
	cout<<"Do you want to enter marks?(Y/N) ";
	cin>>ch;
	for(int i=0;i<10&&ch=='y';i++){
		cout<<"\tSubject: ";
		gets(subs[i].sname);
		cout<<"\tMark:    ";
		cin>>subs[i].mark;
		if(i<9){
			cout<<"Do you want to enter more marks?(Y/N) ";
			cin>>ch;
		}
		else if(i==9){
			cout<<"Subject Limit Reached. ";
			system("pause");
		}
	}
	no=i;
	cout<<endl;
}

void student::dispdata(){
	cout<<"Name:     "<<name;
	cout<<"\nRoll no.: "<<roll;
	cout<<"\nClass:    "<<clas;
	cout<<"\nSubjects and Marks:\n";
	for(int i=0;i<no;i++){
		cout<<subs[i].sname<<"  "<<subs[i].mark<<endl;
	}
	cout<<endl<<endl;
}

void stopp(char a[50]="try"){
	if(!strcmpi(a,"back")){
		cout<<"Enter any key to go back.";
		getch();
	}
	else if(!strcmpi(a,"try")){
		cout<<"Enter any key to try again.";
		getch();
	}
	else if(!strcmpi(a,"next")){
		cout<<"Enter any key to display next.";
		getch();
	}
}

void getp(char pass[50]){
	int i=0;
	pass[i]=getch();
	while(pass[i]!=13){
		if(pass[i]==8){
			cout<<"\b"<<" "<<"\b";
			pass[--i]=getch();
		}
		else{
			cout<<"*";
			pass[++i]=getch();
		}
	}
	pass[i]='\0';
	cout<<endl;
}

int logout(){
	char ch;
	cout<<"Are you sure?(Y/N) ";
	cin>>ch;
	if(ch=='Y'||ch=='y') return 0;
	else return 1;
}

void login(int);
void signin();
void delac(char*);
void home(user);

void main(){
	clrscr();
	gotoxy(1,7); cout<<"T A P P\n\nLoading 34%"; delay(700); clrscr();
	gotoxy(1,7); cout<<"Teacher's A P P\n\nLoading 61%"; delay(700); clrscr();
	gotoxy(1,7); cout<<"Teacher's Application\n\nLoading 92%"; delay(700); clrscr();
	gotoxy(1,7); cout<<"Teacher's Application\n\nLoading 100%"; delay(700); clrscr();
	int ch,key=108;
	while(key){
		clrscr();
		cout<<"Menu\n1.Log into Account\n2.Make Account\n3.Delete Account\n4.Exit\nEnter your choice: ";
		cin>>ch;
		cout<<endl;
		switch(ch){
			case 1: login(ch); break;
			case 2: signin(); break;
			case 3: login(ch); break;
			case 4: key=0; break;
			default: cout<<"Invalid Choice. "; stopp();
		}
	}
	clrscr();
	gotoxy(1,10);
	cout<<"Program by Jagannath, Vishwas, Ashwin, Athul, Juan and Yogesh.";
	delay(300);
	cout<<"\nEnter any key to Exit.";
	getch();
}

void login(int argument){
	clrscr();
	user log,temp;
	int flag=0;
	gotoxy(1,10);
	cout<<"Enter User Name: ";
	gets(log.id);
	ifstream ifs("USERS.DAT",ios::binary|ios::in);
	while(ifs.read((char*)&temp,sizeof(temp))){
		if(!strcmpi(log.id,temp.id)){
			flag=1;
			break;
		}
	}
	switch(flag){
		case 0:
			cout<<"User ID is wrong. If you don't have account make one first.\n";
			stopp();
			break;
		case 1:
			ifs.seekg(0);
			flag=0;
			cout<<"Enter Password: ";
			getp(log.pass);
			ifstream ifs("USERS.DAT",ios::binary|ios::in);
			while(ifs.read((char*)&temp,sizeof(temp))){
				if(!strcmpi(log.id,temp.id))
					if(!strcmpi(log.pass,temp.pass)){
						flag=1;
						break;
					}
			}
			ifs.close();
			switch(flag){
				case 0:
					cout<<"Password is wrong. ";
					stopp();
					break;
				case 1:
					if(argument==1)
						home(log);
					else
						delac(log.id);
					break;
			}
	}
}

void signin(){
	clrscr();
	user log,temp;
	int flag=0;
	char check[50];
	cout<<"Enter User ID: ";
	gets(log.id);
	ifstream ifs("USERS.DAT",ios::binary|ios::in);
	while(ifs.read((char*)&temp,sizeof(temp))){
		if(!strcmpi(log.id,temp.id)){
			flag=1;
			break;
		}
	}
	ifs.close();
	if(!strcmpi(log.id,"users")) flag=1;
	else if(!strcmpi(log.id,"temp")) flag=1;
	else if(!strcmpi(log.id,"tempo")) flag=1;
	switch(flag){
		case 0:
			lab:
			cout<<"Enter Password: ";
			getp(log.pass);
			cout<<"Re-enter Password: ";
			getp(check);
			if(strcmp(log.pass,check)){
				cout<<"Password Re-enetered is wrong. Enter 1 to go back or enter any other number to try again.";
				cin>>flag;
				cout<<"\n\n";
				if(flag != 1)
					goto lab;
			}
			if(flag != 1){
				ofstream ofs("USERS.DAT",ios::binary|ios::app);
				ofs.write((char*)&log,sizeof(log));
				ofs.close();
				home(log);
			}
			break;
		case 1:
			cout<<"User ID exisits. Please Give another ID. ";
			stopp();
			break;
	}
}

void delac(char id[50]){
	ifstream ifs("USERS.DAT",ios::binary|ios::in);
	ofstream ofs("TEMP.DAT",ios::binary|ios::app);
	user temp;
	while(ifs.read((char*)&temp,sizeof(temp))){
		if(strcmpi(id,temp.id)){
			ofs.write((char*)&temp,sizeof(temp));
		}
	}
	ofs.close();
	ifs.close();
	remove("USERS.DAT");
	rename("TEMP.DAT","USERS.DAT");
	char filenam[60];
	strcpy(filenam,id);
	strcat(filenam,".DAT");
	remove(filenam);
	cout<<"Account Deleted. ";
	stopp("back");
}

void dispa();
void srch();
void add();
void modi();
void sort();
void dels();
void txtcol();

void home(user current){
	int key=1998,ch;
	strcpy(filenam,current.id);
	strcat(filenam,".DAT");
	while(key){
		clrscr();
		cout<<"Menu\n1.Display Records\n2.Add one Record\n3.Modify Records\n4.Sort Records\n5.Search and Display\n6.Delete Records\n7.Change Screen Text Color\n8.Log Out\nEnter your choice:\t";
		cin>>ch;
		cout<<endl;
		switch(ch){
			case 1: dispa(); break;
			case 2: add(); break;
			case 3: modi(); break;
			case 4: sort(); break;
			case 5: srch(); break;
			case 6: dels(); break;
			case 7: txtcol(); break;
			case 8: key=logout(); break;
			default: cout<<"Invalid Choice. "; stopp();
		}
	}
}

void dispa(){
	student temp;
	ifstream ifs(filenam,ios::binary|ios::in);
	if(!ifs.read((char*)&temp,sizeof(temp))){
		cout<<"No Records Exists. ";
		stopp("back");
	}
	else{
		clrscr();
		temp.dispdata();
		stopp("next");
		cout<<endl;
		while(ifs.read((char*)&temp,sizeof(temp))){
			clrscr();
			temp.dispdata();
			stopp("next");
			cout<<endl;
		}
		cout<<"\nNo MORE records exist. ";
		stopp("back");
	}
	ifs.close();
}

void srch(){
	clrscr();
	student temp;
	int flag=0,key=9,ch;
	ifstream ifs;
	while(key){
		clrscr();
		cout<<"Menu\n1.Search by Name\n2.Search by Class\n3.Search by Roll no.\n4.Go Back\nEnter your choice:\t";
		cin>>ch;
		cout<<endl;
		switch(ch){
			case 1:
				ifs.open(filenam,ios::binary|ios::in);
				flag=0;
				char item1[50];
				cout<<"Enter Name of Student: ";
				gets(item1);
				while(ifs.read((char*)&temp,sizeof(temp))){
					if(!strcmpi(temp.name,item1)){
						clrscr();
						temp.dispdata();
						stopp("next");
						cout<<endl;
						flag=1;
					}
				}
				if(!flag){
					cout<<"\nNo Records Found. ";
					stopp("try");
				}
				else{
					cout<<"\nNo MORE Records Found. ";
					stopp("back");
				}
				ifs.close();
				break;
			case 2:
				ifs.open(filenam,ios::binary|ios::in);
				flag=0;
				float item2;
				cout<<"Enter Class: ";
				cin>>item2;
				while(ifs.read((char*)&temp,sizeof(temp))){
					if(temp.clas==item2){
						clrscr();
						temp.dispdata();
						stopp("next");
						cout<<endl;
						flag=1;
					}
				}
				if(!flag){
					cout<<"\nNo Records Found. ";
					stopp("try");
				}
				else{
					cout<<"\nNo MORE Records Found. ";
					stopp("back");
				}
				ifs.close();
				break;
			case 3:
				ifs.open(filenam,ios::binary|ios::in);
				flag=0;
				int item3;
				cout<<"Enter Roll no.: ";
				cin>>item3;
				while(ifs.read((char*)&temp,sizeof(temp))){
					if(temp.roll==item3){
						clrscr();
						temp.dispdata();
						stopp("next");
						cout<<endl;
						flag=1;
					}
				}
				if(!flag){
					cout<<"\nNo Records Found. ";
					stopp("try");
				}
				else{
					cout<<"\nNo MORE Records Found. ";
					stopp("back");
				}
				ifs.close();
				break;
			case 4: key=0; break;
			default: cout<<"Invalid Choice. "; stopp();
		}
	}
}

void add(){
	clrscr();
	student news;
	ofstream ofs(filenam,ios::binary|ios::app);
	news.getdata();
	ofs.write((char*)&news,sizeof(news));
	ofs.close();
}

void modi(){
	clrscr();
	student temp;
	float item2;
	int flag=0,eflag=0;
	char ans,item1[50];
	ifstream ifs(filenam,ios::binary|ios::in);
	ofstream ofs("TEMP.DAT",ios::binary|ios::out);
	cout<<"Enter Name of Student: ";
	gets(item1);
	cout<<"Enter Class: ";
	cin>>item2;
	while(ifs.read((char*)&temp,sizeof(temp))){
		if(!strcmpi(temp.name,item1)){
			if(temp.clas==item2){
				clrscr();
				cout<<"Old Details Are:-\n";
				temp.dispdata();
				cout<<"Do you want to modify this record?(Y/N) ";
				cin>>ans;
				if(ans=='Y'||ans=='y'){
					temp.getdata();
					system("pause");
					eflag=1;
				}
				flag=1;
			}
		}
		ofs.write((char*)&temp,sizeof(temp));
	}
	ofs.close();
	ifs.close();
	if(flag){
		remove(filenam);
		rename("TEMP.DAT",filenam);
		if(eflag)
			cout<<"\nModification Done. ";
		else
			cout<<endl;
		stopp("back");
	}
	else{
		remove("TEMP.DAT");
		cout<<"\nNo record found. ";
		stopp("back");
	}
}

void sort(){
	int getno();
	void dels(student);
	student r, t;
	int rno=getno();
	ofstream ofs("TEMP.DAT",ios::binary|ios::app);
	for(int i=0;i<rno;i++){
		ifstream ifs(filenam,ios::binary|ios::in);
		ifs.read((char*)&t,sizeof(t));
		for(int j=i+1; j<rno; j++){
			ifs.read((char*)&r,sizeof(r));
			if(t.roll>r.roll) t=r;
		}
		ofs.write((char*)&t,sizeof(t));
		ifs.close(); dels(t);
	}
	ofs.close();
	remove(filenam);
	rename("TEMP.DAT",filenam);
	ofs.open("TEMP.DAT",ios::binary|ios::app);
	for(i=0;i<rno;i++){
		ifstream ifs(filenam,ios::binary|ios::in);
		ifs.read((char*)&t,sizeof(t));
		for(int j=i+1; j<rno; j++){
			ifs.read((char*)&r,sizeof(r));
			if(t.clas>r.clas)
				t=r;
		}
		ofs.write((char*)&t,sizeof(t));
		ifs.close();
		dels(t);
	}
	ofs.close();
	remove(filenam);
	rename("TEMP.DAT",filenam);
	cout<<"\nSorting is Done. "; stopp("back");
}

int getno(){
	student m; int i=0;
	ifstream ifs(filenam,ios::binary|ios::in);
	while(ifs.read((char*)&m,sizeof(m))) i++;
	ifs.close(); return i;
}

void dels(student a){
	student i;
	ifstream ifs(filenam,ios::binary|ios::in);
	ofstream ofs("TEMPO.DAT",ios::binary|ios::app);
	while(ifs.read((char*)&i,sizeof(i))){
		if(strcmpi(i.name,a.name)!=0){
			ofs.write((char*)&i,sizeof(i));
		}
	}
	ifs.close(); ofs.close();
	remove(filenam);
	rename("TEMPO.DAT",filenam);
}

void dels(){
	clrscr();
	student temp;
	float item2;
	int item3,flag=0;
	char item1[50];
	ifstream ifs(filenam,ios::binary|ios::in);
	ofstream ofs("TEMP.DAT",ios::binary|ios::out);
	cout<<"Enter Name of Student: ";
	gets(item1);
	cout<<"Enter Class: ";
	cin>>item2;
	cout<<"Enter Roll: ";
	cin>>item3;
	while(ifs.read((char*)&temp,sizeof(temp))){
		if(!strcmpi(temp.name,item1)){
			if(temp.clas==item2){
				if(temp.roll==item3){
					flag=1;
				}
				else{
					ofs.write((char*)&temp,sizeof(temp));
				}
			}
			else{
				ofs.write((char*)&temp,sizeof(temp));
			}
		}
		else{
			ofs.write((char*)&temp,sizeof(temp));
		}
	}
	ofs.close();
	ifs.close();
	remove(filenam);
	rename("TEMP.DAT",filenam);
	if(flag)
		cout<<"Deleted records. ";
	else
		cout<<"Record not found. ";
	stopp("back");
}

void txtcol(){
	clrscr();
	int n;
	cout<<"\n1.Deep Blue\t 9.Light Blue\n2.Deep Green\t10.Light Green\n3.Cyan\t\t11.Sky Blue\n4.Deep Red\t12.Light Red\n5.Pink\t\t13.Rose\n6.Orange\t14.Yellow\n7.Silver\t15.White\n8.Ash\nEnter Your Choice: ";
	cin>>n;
	textcolor(n);
}
