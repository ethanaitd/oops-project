#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <conio.h>
#include <string.h>
#include <iomanip>
using namespace std;

//this is a base name class where all other classes are derived from
class Name
{
    string name;
public:
    void setName(string name){this->name=name;}
    string getName(){return name;}
};


//this is a company object used to  store the companies obtained from the database
class cmp:public Name
{
  string location,package;
  int id;
  int avail_pos;
  int max_pos;
  int number_of_placed;
  float eligibility;
  string placed_students[30];

public:
    //counter used to keep track of the number of companies in the database and assign the corresponding IDs
  static int counter;

  void setAvailPos()
  {//sets the number of available positions in the company
    avail_pos=max_pos-number_of_placed;
  }




    //setter to set the placed student in the database
  void setPlacedStudents(string placed_students)
  {
      int pos=-1,curr=-1,i=0;
      //if there are no placed_students or the length of placed students is 0
      if(placed_students=="null")
      {
          this->number_of_placed=0;
      }

      //if there is only one student
      else if(placed_students.find(",")==-1)
      {
          this->placed_students[0]=placed_students;
          this->number_of_placed=1;
      }

      //if there are more than one
      else
      {
      while(placed_students.find(",",pos+1)!=-1)
      {
          curr=pos+1;
          pos=placed_students.find(",",curr);
          this->placed_students[i++]=placed_students.substr(curr,pos-curr);
      }
      this->placed_students[i++]=placed_students.substr(pos+1,placed_students.length()-pos+1);
      this->number_of_placed=i;
      }
  }


  void setCmp(string name,string location,string package,float eligibility,int max_pos,string placed_students)
  {//sets the company details
    setName(name);
    this->location=location;
    this->package=package;
    this->eligibility=eligibility;
    this->max_pos=max_pos;
    setPlacedStudents(placed_students);
    setAvailPos();
    this->id=++counter;
  }




  bool addStudent(string name)
  {
      //to add a new student in the
      int i=0;
      if(number_of_placed==max_pos)
      {
          cout<<"Already full"<<endl;
          return false;
      }
      else{
      try
      {
        for(i=0;i<number_of_placed;i++)
        {
            if(placed_students[i]==name)
                throw name;
        }
        placed_students[number_of_placed]=name;
        number_of_placed++;
        setAvailPos();
        return true;
      }
      catch(string name)
      {
          cout<<"Student already placed in this company"<<endl;
          return false;
      }
      }
  }



/*
  void rmStudent(string name)
  {
    //to remove the student from the placed student
     int i=0;
     if(number_of_placed==1&&name==placed_students[0])
     {
         placed_students[0]="null";
         number_of_placed--;
     }
     else if(name==placed_students[number_of_placed-1])
     {
         number_of_placed--;
     }
      try
      {
        for(i=0;i<number_of_placed;i++)
        {
            if(placed_students[i]==name)
            {
                for(int j=i;j<number_of_placed-1;j++)
                {
                    placed_students[j]=placed_students[j+1];
                }
                number_of_placed--;
                setAvailPos();
                return;
            }
        }
        throw name;
      }
      catch(string name)
      {
          cout<<"Not in the company"<<endl;
      }
  }
  */

  void displayCmp()
  {
      cout<<"\n\nName : "<<getName()<<endl;
      cout<<"Location: "<<this->location<<endl;
      cout<<"Eligibility :"<<eligibility<<"CGPA or greater"<<endl;
      cout<<"Package :"<<package<<endl;
      cout<<"Number of students placed :"<<number_of_placed<<endl;
      cout<<"Number of available positions :"<<avail_pos<<endl;
      cout<<"ID:"<<id<<endl;
  }

    //getters
    int getAvailPos(){return avail_pos;}
    string getLocation(){return location;}
    string getPackage(){return package;}
    int getMax_pos(){return max_pos;}
    float getEligibility(){return eligibility;}
    string* getPlaced_students(){return placed_students;}
    int getNumberOfPlaced(){return number_of_placed;}
    string getPlaced_students_string()
    {
        if(number_of_placed==0)
        {
            return "null";
        }
        else{
            string students;
            int i=0;
            for(i=0;i<number_of_placed-1;i++)
            {
                students=students+placed_students[i]+",";
            }
            students=students+placed_students[i];
            return students;
        }
    }

  ~cmp()
  {
    counter--;
  }
};
//this is a new student class for creating a Newstud object
class NewStud:public Name
{
    string email,cmp_placed,password;
    float cgpa;
public:
    void setNewStud(string name,string email,string password,string cmp_placed,float cgpa)
    {
        setName(name);
        this->email=email;
        this->password=password;
        this->cmp_placed=cmp_placed;
        this->cgpa=cgpa;
    }
    string getEmail(){return email;}
    string getPassword(){return password;}
    string getCmp_Placed(){return cmp_placed;}
    float getCgpa(){return cgpa;}

};

//student class
class student:public Name
{
    string email,password,cmp_placed;
    float cgpa;
    bool placed;
public:
    void setStudent(string name,string email,string password,string cmp_placed,float cgpa)
    {
        setName(name);
        this->email=email;
        this->password=password;
        this->cmp_placed=cmp_placed;
        this->cgpa=cgpa;
        setPlaced();
    }
    void setPlaced()
    {       //sets the placed boolean to true or false
        if(cmp_placed=="null")
        {
            placed=false;
        }
        else
            placed=true;
    }

    void operator=(NewStud newStud)
    {
        setName(newStud.getName());
        this->email=newStud.getEmail();
        this->password=newStud.getPassword();
        this->cmp_placed=newStud.getCmp_Placed();
        this->cgpa=newStud.getCgpa();
        setPlaced();
    }

    void operator=(student stud)
    {
        setName(stud.getName());
        this->email=stud.getEmail();
        this->password=stud.getPassword();
        this->cmp_placed=stud.getCmp_Placed();
        this->cgpa=stud.getCgpa();
        setPlaced();
    }


    void displayStudent()
    {
        cout<<"Name :"<<getName()<<endl;
        cout<<"Email :"<<email<<endl;
        cout<<"Password :"<<password<<endl;
        cout<<"Company placed in:"<<cmp_placed<<endl;
        cout<<"Cgpa :"<<cgpa<<endl;
    }

    void setCmpPlaced(string cmp_placed)
    {
        this->cmp_placed=cmp_placed;
        setPlaced();
    }

    string getEmail(){return email;}
    string getPassword(){return password;}
    string getCmp_Placed(){return cmp_placed;}
    float getCgpa(){return cgpa;}
    bool getPlaced(){return placed;}


};

//Global variables
cmp company[10];
bool signedIn=false;
student students[30];
student currStudent;
int number_of_companies=0;
int number_of_students=0;

//static variables
int cmp::counter=0;

//functions
void getCmpDatabase()
{
    ifstream cmp_getdatabase;
    string name,location,package,placed_students;
    float eligibility;
    int max_pos;

    cmp_getdatabase.open("./database/company_database.txt");

    int i=0;
    while(cmp_getdatabase.eof()!=1)
    {
    int flag=0;
    if(cmp_getdatabase.eof())
    {
        flag=1;
    }
    cmp_getdatabase>>name;
    cmp_getdatabase>>location;
    cmp_getdatabase>>package;
    cmp_getdatabase>>eligibility;
    cmp_getdatabase>>max_pos;
    cmp_getdatabase>>placed_students;

    if(flag==0&&!cmp_getdatabase.eof())
    {
        company[i].setCmp(name,location,package,eligibility,max_pos,placed_students);
        number_of_companies++;
        i++;
    }
    }
    cmp_getdatabase.close();
}

void setCmpDatabase()
{
    ofstream cmp_database;
    string name,location,package,placed_students;
    float eligibility;
    int max_pos;

    cmp_database.open("./database/company_database.txt");

    for(int i=0;i<number_of_companies;i++)
    {
        cmp_database<<setw(15)<<setiosflags(ios::left)<<company[i].getName();
        cmp_database<<setw(15)<<setiosflags(ios::left)<<company[i].getLocation();
        cmp_database<<setw(15)<<setiosflags(ios::left)<<company[i].getPackage();
        cmp_database<<setw(15)<<setiosflags(ios::left)<<company[i].getEligibility();
        cmp_database<<setw(15)<<setiosflags(ios::left)<<company[i].getMax_pos();
        cmp_database<<setiosflags(ios::left)<<company[i].getPlaced_students_string();
        cmp_database<<"\n";
    }
    cmp_database.close();
}
/********************Student database*********************/
void getStudentDatabase()
{
    string name,email,password,cmp_placed;
    float cgpa;
    ifstream student_getdatabase;

    student_getdatabase.open("./database/student_database.txt");

    int i=0;
    while(student_getdatabase.eof()!=1)
    {
        int flag=0;
        if(student_getdatabase.eof())
        {
            flag=1;
        }
        student_getdatabase>>name;
        student_getdatabase>>email;
        student_getdatabase>>password;
        student_getdatabase>>cmp_placed;
        student_getdatabase>>cgpa;

        if(!student_getdatabase.eof()&&flag==0)
        {
            students[i].setStudent(name,email,password,cmp_placed,cgpa);
            number_of_students++;
            i++;
        }
        }
        student_getdatabase.close();
}

void setStudentDatabase()
{
    ofstream student_database;
    string name,email,password,cmp_placed;
    float cgpa;

    student_database.open("./database/student_database.txt");

    for(int i=0;i<number_of_students;i++)
    {
        student_database<<setw(15)<<setiosflags(ios::left)<<students[i].getName();
        student_database<<setw(30)<<setiosflags(ios::left)<<students[i].getEmail();
        student_database<<setw(15)<<setiosflags(ios::left)<<students[i].getPassword();
        student_database<<setw(15)<<setiosflags(ios::left)<<students[i].getCmp_Placed();
        student_database<<setw(15)<<setiosflags(ios::left)<<students[i].getCgpa();
        student_database<<"\n";
    }
    student_database.close();
}

void setCurrStudent(string email,string password)
{
    //sets the current user based on email and password
    string name,cmp_placed;
    float cgpa;
    for(int i=0;i<number_of_students;i++)
    {
        if(students[i].getEmail()==email)
        {
            name=students[i].getName();
            cmp_placed=students[i].getCmp_Placed();
            cgpa=students[i].getCgpa();

            currStudent.setStudent(name,email,password,cmp_placed,cgpa);

            signedIn=true;
            return;
        }
    }

}

void addStudentInDatabase(string name,string email,string password,string cmp_placed,float cgpa)
{
    //creates a new student object and adds it to the students obj array
    NewStud student;
    student.setNewStud(name,email,password,cmp_placed,cgpa);
    students[number_of_students++]=student;
}
//checks if student present in database
bool checkStudentInDatabase(string email,string password)
{
    for(int i=0;i<number_of_students;i++)
    {
        if(email==students[i].getEmail())
        {
            return true;
        }
    }
    return false;
}

void createNewStudent()
{
    string name,email,password,cmp_placed;
    float cgpa;
    int choice;
    cout<<"Please enter the following details in the form :"<<endl;
    cout<<"Enter Name: ";
    cin.ignore();
    cin>>name;

    cout<<"Enter Email: ";
    cin.ignore();
    cin>>email;

    cout<<"Enter Password: ";
    cin.ignore();
    cin>>password;

    system("cls");

    cout<<"Enter your cgpa: ";
    cin.ignore();
    cin>>cgpa;
    if(checkStudentInDatabase(email,password))
    {
        setCurrStudent(email,password);
        cout<<"Signed In!"<<endl;
        return;
    }
    system("cls");

    cmp_placed="null";

    cout<<"Adding you into the database please wait......"<<endl;
    addStudentInDatabase(name,email,password,cmp_placed,cgpa);
    cout<<"Student signed-up !"<<endl;
    setCurrStudent(email,password);
}




bool checkEmailAndPassword(string email,string password)
{   //checks the password
    for(int i=0;i<number_of_students;i++)
    {
        if(email==students[i].getEmail())
        {
            if(password==students[i].getPassword())
            {
                return true;
            }
            return false;
        }
    }
}

void SignInStudent()
{

    while(true){
    string email,password;
    cout<<"Sign-In Student :"<<endl;
    cin.ignore();

    cout<<"\nEnter the email : ";
    cin>>email;

    cout<<"Enter the password : ";
    cin>>password;

    if(!checkStudentInDatabase(email,password))//checks if the student is in the database returns a boolean
    {
        cout<<"Student does not exist in the database please sign-up"<<endl;
        break;
    }
    else
    {
        if(!checkEmailAndPassword(email,password))//checks if the password is correct
        {
            cout<<"Password incorrect enter again"<<endl;
        }
        else
        {
            setCurrStudent(email,password);//sets the current user based on the email
            cout<<"Signed in !"<<endl;
            break;
        }

    }
    }

}



string joinCmp(int id)
{
    system("cls");
    int choice;
    if(!currStudent.getPlaced())
    {
    company[id-1].displayCmp();
    cout<<"Do you wish to join this company ?"<<endl<<endl;
    cout<<"1.Yes        2.No"<<endl;
    cin.ignore();
    cin>>choice;
    if(choice==1)
    {
        if(currStudent.getCgpa()<company[id-1].getEligibility())
        {
            return "You are not eligible to join this company based on the company's hiring criteria";
        }
        cout<<"adding you to the company ... please wait"<<endl;
        if(company[id-1].addStudent(currStudent.getName()))
        {
        for(int i=0;i<number_of_students;i++)
        {
            if(currStudent.getEmail()==students[i].getEmail())
            {
                currStudent.setCmpPlaced(company[id-1].getName());
                students[i]=currStudent;
                return "Done! you've joined the company";
            }
        }
        }
        else
        {
            return "Please try again";
        }

    }
    else if(choice==2)
    {
        return "";
    }
    }
    else
        return "Already placed !";
}

void app()
{
    int op;
    string message="";
    while(signedIn)
    {
        system("cls");
        cout<<message<<"\n\n"<<endl;
        cout<<"->"<<"WELCOME TO THE PLACEMENT MANAGEMENT SYSTEM!<-"<<endl;
        cout<<"Student :"<<currStudent.getName()<<setw(60-currStudent.getName().length())<<setiosflags(ios::right)<<"email:"<<currStudent.getEmail()<<endl;
        cout<<"Status :";


        if(currStudent.getPlaced())
            cout<<"Placed at "<<currStudent.getCmp_Placed()<<endl;
        else
            cout<<"Not placed"<<endl;


        cout<<"Available companies for placement :\n";
        cout<<"Total: "<<number_of_companies<<endl;
        cout<<"0. Sign-Out"<<endl;
        if(number_of_companies==0)
        {
            cout<<"No companies available for placement\n";
        }
        else
        {

        for(int i=0;i<number_of_companies;i++)
        {
            if(company[i].getAvailPos()!=0)
                company[i].displayCmp();
            cout<<"\n\n";
        }
        cout<<"Enter the ID of the company you wish to apply for or 0 for exit:\n";
        cin.ignore();
        cin>>op;
        if(op==0)
            signedIn=false;
        else
            message=joinCmp(op);
        }
    }
}
int main()
{
    getStudentDatabase();
    getCmpDatabase();
    int op=0;
    while(op!=3)
    {
        if(!signedIn)  //sign-in/sign-up page
        {
        system("cls");
        cout<<"->"<<"WELCOME TO THE PLACEMENT MANAGEMENT SYSTEM!<-\n\n"<<endl;
        cout<<"->"<<"1)Sign-Up        2)Sign-In       3)Exit<-\n";
        cin>>op;
        switch(op)
        {
            case 1:
            {
            createNewStudent();
            }break;
            case 2:
            {
            SignInStudent();
            }break;
            case 3:
            {
            cout<<"Thank you for using our service"<<endl;
            }break;
        }
        }
        else//the app page
        {
            cout<<"Please wait....\n";
            app();
        }

    }
    setCmpDatabase();
    setStudentDatabase();
    return 0;
}
