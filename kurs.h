using namespace std;

 struct students{
	 	string studentsFullName;
	 	unsigned int numberOfRB;
	 	float GPA;
	 	students *l,*r;
	 };

ofstream out("database.txt");

	void show(students *&MyTree) //Функция прямого вывода
	{
		if (MyTree!=NULL) 
		{
		   show(MyTree->l);
		   cout<<"|||"<<"Full name: "<<MyTree->studentsFullName<<endl<<"|||"<<"Number of record-book: "<<MyTree->numberOfRB<<endl<<"|||"<<"Grade point average: "<<MyTree->GPA<<endl<<endl; //Отображаем корень дерева
		   show(MyTree->r);
		}
	}
	void show2(students *&MyTree) //Функция обратного вывода
	{
		if (MyTree!=NULL) 
		{
		   show2(MyTree->r);
		   cout<<"|||"<<"Full name: "<<MyTree->studentsFullName<<endl<<"|||"<<"Number of record-book: "<<MyTree->numberOfRB<<endl<<"|||"<<"Grade point average: "<<MyTree->GPA<<endl<<endl; //Отображаем корень дерева
		   show2(MyTree->l);
		}
	}	

	void add(string Name, unsigned int Rb, float GP, students *&MyTree){
	if (MyTree==NULL){
		MyTree=new students; 
		MyTree->studentsFullName=Name; 
    	MyTree->numberOfRB=Rb;
    	MyTree->GPA=GP;
		MyTree->l=MyTree->r=NULL;
	} else {
             if (Name < MyTree->studentsFullName){
                          if (MyTree->l!=NULL) add(Name, Rb, GP, MyTree->l);
                          else
                          {
                              MyTree->l=new students;  
                              MyTree->l->l=MyTree->l->r=NULL; 
                              MyTree->l->studentsFullName=Name; 
                              MyTree->l->numberOfRB=Rb;
                              MyTree->l->GPA=GP;
                          }
                      }
                    if ((Name>MyTree->studentsFullName)||(Name==MyTree->studentsFullName)){
                          if (MyTree->r!=NULL) add(Name, Rb, GP,MyTree->r); 
                          else 
                          {
                              MyTree->r=new students; 
                              MyTree->r->l=MyTree->r->r=NULL; 
                              MyTree->r->studentsFullName=Name;              
                              MyTree->r->numberOfRB=Rb;
                              MyTree->r->GPA=GP; 
                          }
                      }

                  }
	}
	int search(students *t,string key) {

		if(t==NULL) {
		cout <<":::::This student not found "<<endl; 
		return -1;
		}// ветка пуста
		if (key==t->studentsFullName) {
			cout<<":::::Information about this student:\n";
			cout<<"Full Name: "<<t->studentsFullName<<"\nNumber of student's record-book: "<<t->numberOfRB<<"\nGrade point average: "<<t->GPA<<endl; 
			 if (t->r!=NULL) search(t->r,key); else cout <<":::::More information not found "<<endl;}
			if (key>t->studentsFullName){ if (t->r!=NULL)search(t->r,key); else cout <<":::::More information not found "<<endl;}
			if (key<t->studentsFullName){ if (t->l!=NULL)search(t->l,key); else cout <<":::::More information not found "<<endl;}
	}
	void del1 (students *&p, students *&q){
	students *s;
  	if  (p->r==NULL)
  	{
    	q->studentsFullName = p->studentsFullName; 
    	q->numberOfRB = p->numberOfRB;
    	q->GPA = p->GPA;
    	q = p;
    	s = p; p = p->l; delete s; cout<<"The information was deleted.\n";
  		}
  			else  del1(p->r, q);
	}
	int del (students *&t, string key) {
		if (t==NULL) {cout<<":::::This student not found :("; return-1;}
	else 
		if  (key<t->studentsFullName) del(t->l,key);
	 else
		if  (key>t->studentsFullName) del(t->r,key);
		else
		  {
                    students *q = t;
                    if  (q->r==NULL) {t = q->l; cout<<"The information was deleted.\n"; delete q;}
                    else
                     if  (q->l==NULL) {t = q->r; cout<<"The information was deleted.\n"; delete q;}
                     else  del1 (q->l,q);
		  }	
	}
	void saveInFile(students *&MyTree) {
		if (MyTree!=NULL) 
		{	
		   saveInFile(MyTree->l);
		   out<<"\n\n|||"<<"Full name: "<<MyTree->studentsFullName<<
		   "\n|||"<<"Number of record-book: "<<MyTree->numberOfRB<<"\n|||"<<
		   "Grade point average: "<<MyTree->GPA;		   
		   saveInFile(MyTree->r);

		}

	}

	int com (students* &student){		
		int command;
		 cout <<"\nPress 0: exit" <<
		 		"\nPress 1: add info from keyboard" <<
		 		"\nPress 2: add info from file" <<
		 		"\nPress 3: search" <<
		 		"\nPress 4: delete" <<
		 		"\nPress 5: show database" <<
		 		"\nPress 6: print database in file" <<		 		
		 		"\n";
		 cin>>command;
		 if (cin.fail()) {
                    cout << "You entered incorrect value, program will be closed." << endl;
                    return -1;
                	}
		 cout << "\n";		 
		 switch(command) {
		 	case 0: {
		 			while (student)
						{  
    						del(student, student->studentsFullName); 
    						cout << "\n";
						}
						
					break;

					}
			case 1: {
				cout << "How many records do you want to add?"<<endl;
				int number;
				cin >> number;
				if (cin.fail()) {
                    cout << "You entered incorrect value, program will be closed." << endl;
                    return -1;
                }
				cout << "\n";				
				for (int i = 0; i < number; ++i){				
					string Name;
					unsigned int Rb;
					float GP;
					cout <<"Enter student's full name."<<endl;
					cin.ignore();								
					getline (cin, Name);					
					cout << "\n";
					cout <<"Enter number of student's record-book (six-digit positive number) "<<endl;
					cin>>Rb;
					if (cin.fail()) {
                    cout << "You entered incorrect value, program will be closed." << endl;
                    return -1;
                	}
                	while (Rb>999999) {
						cout << "Incorrect value, enter  number of student's record-book again, please."<<endl;
						cin>>Rb;
					}
					
					cout << "\n";
					cout <<"Enter student's GPA (from 0 to 5)"<<endl;					
					cin>>GP;
					if (cin.fail()) {
                    cout << "You entered incorrect value, program will be closed." << endl;
                    return -1;
                	}
					while (GP<0||GP>5) {
						cout << "Incorrect value, enter  student's GPA again, please."<<endl;
						cin>>GP;
					}
					cout << "\n";
					add(Name,Rb,GP,student);					
				}
				com(student);
				break;
				}
			case 2: {
				FILE *file;
				int amount;
				string Name;
				char Name1[100];
				char Name2[100];
				char Name3[100];
				unsigned int Rb;
				float GP;
				char nameOfFile [100];
				cout << "Enter name of file"<<endl;
				cin.ignore();
				cin.getline(nameOfFile,100);
				file = fopen(nameOfFile, "rb");
            	cout << "Enter amount of elements which you want read out file." << endl;
            	cin >> amount;
            	if (cin.fail()) {
                    cout << "You entered incorrect value, program will be closed." << endl;
                    return -1;
                }
            	for (int i=0; i<amount; i++){
                fscanf (file, "%s %s %s", Name1, Name2, Name3);
                Name = string(Name1)  + ' ' +string(Name2) +' '+ string(Name3);
                fscanf(file,"%u %f", &Rb, &GP);
                if (GP<0||GP>5||Rb>999999) {
						cout << "There are incorrect values in file"<<endl;
				}
                else add(Name,Rb,GP,student);
            	}
            	com(student);
            	break;
			}
			case 3: {
				cout<< "Enter student's full name to search."<<endl;
				string ss;
				cin.ignore();			
				getline (cin, ss);
				cout << "\n";
				search(student,ss);
				com(student);
				break;
				}				
			case 4: {
				cout << "Enter the student's full name you want to remove from the database." <<endl;
				string key;
				cin.ignore();							
				getline (cin, key);
				cout << "\n";
				del (student,key);
				com (student);
				break;
			 }
			case 5: {
				cout<< "Select the order of the database output"<<endl;
				cout<< "1- pre-order" <<endl;
				cout<< "2- post-order"<<endl;
				int order;
				cin>>order;
				if (cin.fail()) {
                    cout << "You entered incorrect value, program will be closed." << endl;
                    return -1;
                }
				cout << "\n";
				switch(order) {
					case 1:{
					show (student);
					com (student);
					break;
					}
					case 2: {
					show2 (student);
					com (student);
					break;	
					}
					default: 
					cout<< "Incorrect order"<<endl;
					com(student);
					break;
				}
				break;
			}
			case 6: {										
				saveInFile (student);
				out.close();			
				cout << "Your database in database.txt\n";
				com (student);
				break;
			}
			default: {
			com(student);
			break;
			}
		}
	}

