#include <stdio.h>//For standard I/O Operation
#include <stdlib.h>//To use functions like system(); system("dos command"); - this performs the dos command given. Eg. system("del abc.txt"); - This command deletes the file abc.txt from current location of project
#include <windows.h>//Used in making gotoxy(int, int) function
#include <conio.h>//For getch(); getche() type of functions
#include <time.h>//To get system date and time
#include <math.h>//To calculate mathematical problems, used esp. in interest calculation
#include <dos.h>
#include <iostream>
#include <bits/stdc++.h>
#include <cstdlib>
using namespace std;

class controller{

    public:
    int roll;
    string name;
    int tunits;
    controller()
    {
        roll=0;
        name="";
        tunits=0;
    }
    controller(const controller &d)
    {
        roll=d.roll;
        name=d.name;
        tunits=d.tunits;
    }
    int operator <(controller const &obj)
    {
        if(tunits<obj.tunits)
            return 1;
        else
            return 0;
    }



}tree[100],c[100];

class air
{
	char nair[20]={' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '};
	int time,take;
	public:
   void input()
   {
       cout<<"Enter Airline Name :";cin>>nair;
       cout<<"Enter Arrival Time :";cin>>time;
       cout<<"Enter Takeoff Time :";cin>>take;
   }
   void output()
   {
       cout<<nair<<endl<<time<<endl<<take<<endl;
   }
   air()
   {

   }
   air(string _x, int _y,int _z)
   {
      _x.copy(nair,11,0);
      time = _y;
      take = _z;
   }
   string getX() const { return nair; }
   int getY() const { return time; }
   int getZ() const { return take; }
};

// To compare two points
class myComparator
{
public:
    int operator() (const air& p1, const air& p2)
    {
        return p1.getY() > p2.getY();
    }
};

//funtion prototypes
void intro1();
void intro();
void welcome1();
void welcome();
void admin();
void gotoxy (int , int );
void rectangle(int ,int ,int ,int );
void display(priority_queue<air,vector<air>, myComparator> );
void buildtree(int ,int ,int ,controller [],controller []);
void update(int ,int ,int ,int ,int ,controller [],controller []);
controller func();
controller query(int ,int ,int ,int ,int ,controller []);
void person();
void graph();
void add_airline();



COORD coord = {0, 0};
void gotoxy (int x, int y)
        {
        coord.X = x;
        coord.Y = y; // X and Y coordinates
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
        }

 void rectangle(int x,int y,int l,int b)
{
    int i,m;
    gotoxy(x,y); printf("%c",201);
    for(i=x+1;i<l-1;i++)
    {
        gotoxy(i,y);
        printf("%c",205);
    }
    gotoxy(i,y); printf("%c",187);

    for (m=y+1;m<b;m++)
    {
        gotoxy(x,m);
        for(i=x;i<l;i++)
        {
            if(i==x||i==l-1)
            {
                gotoxy(i,m); printf("%c",186);
            }

        }

    }

    gotoxy(x,m); printf("%c",200);
    for(i=x+1;i<l-1;i++)
    {
        gotoxy(i,m);
        printf("%c",205);
    }
    gotoxy(i,m); printf("%c",188);
}

void display(priority_queue<air,vector<air>, myComparator> pq)
{
    int c=0;
    while(pq.empty()==false)
    {
        pq.pop();
        c++;
    }
    cout<<"No. of planes left to land: "<<c;

}

void buildtree(int node,int start,int end,controller tree[],controller a[])
{

if(start==end)
{
    tree[node]=a[start];

}
else
{
          int mid=(start+end)/2;
          buildtree(2*node,start,mid,tree,a);
          buildtree(2*node+1,mid+1,end,tree,a);
      if(tree[2*node]<tree[2*node+1])
          {
              tree[node]=tree[2*node];

          }
      else
          {

              tree[node]=tree[2*node+1];
          }
}
}
void update(int node,int start,int end,int idx,int val,controller tree[],controller a[])
{
      if(start==end)
            {
                 a[idx].tunits=val;
                 tree[node].tunits=val;
            }
      else
            {
                int mid=(start+end)/2;
                if(idx>=start&&idx<=mid)
                update(2*node,start,mid,idx,val,tree,a);
                else
                update(2*node+1,mid+1,end,idx,val,tree,a);
                if(tree[2*node]<tree[2*node+1])
                tree[node]=tree[2*node];
                else
                tree[node]=tree[2*node+1];
            }
}
controller func()
{
    controller h;
    h.name="";
    h.roll=0;
    h.tunits=100005;
    return h;
}
controller query(int node,int start,int end,int l,int r,controller tree[])
{
          if(l>end||start>r)
          return func();
          if(l<=start&&r>=end)
            return tree[node];
          controller p1,p2;
          int mid=(start+end)/2;
           p1=query(2*node,start,mid,l,r,tree);
           p2=query(2*node+1,mid+1,end,l,r,tree);
          if(p1<p2)
            return p1;
           else
            return p2;
}

void person()
{
      cout<<endl;
      int choice;
      char ch;
      system("cls");
      do
     {
      system("cls");
      cout<<"The Segment Tree of Controllers\n";
      cout<<"1. Display Tree\n";
      cout<<"2. Update\n";
      cout<<"3. Range Minimum\n";
      cout<<"4. Exit\n";
      cout<<"Enter Your Choice:";
      cin>>choice;
      switch(choice)
      {
          case 1: {
                       for(int i=1;i<16;i++)
                        {
                            cout<<tree[i].roll<<" "<<tree[i].name<<" "<<tree[i].tunits<<endl;
                        }
                        break;
                  }
          case 2:{

                     int o,p;
                     cout<<"\nEnter index of the person(1-6):";
                     cin>>o;
                     cout<<"\nEnter value of tunits to be changed:";
                     cin>>p;
                     update(1,1,6,o,p,tree,c);
                     break;

                 }
         case 3:{
                      int o,p;
                      cout<<"\nEnter the range from which you want to find the minimum [1,6] inclusive:";
                      cin>>o>>p;
                      controller m=query(1,1,6,o,p,tree);
                      cout<<"Controller "<<m.name<<" working for "<<m.tunits<<" units";
                      break;
                 }

      }
      cout<<"\nContinue?(Y/N)";
      cin >>ch;
      }while(ch=='y' || ch=='Y');



}

int size=0;

class BoardingPass
{
    public:
	char aname[20];
	char pname[20];
   void input()
   {
       cout<<"Enter Airline Name :";cin>>aname;
       cout<<"Enter Passenger Name :";cin>>pname;
   }
   void output()
   {
       cout<<aname<<endl<<pname<<endl;
   }
   BoardingPass(){};
   BoardingPass(char a[20],char p[20])
   {
    strcpy(aname,a);
    strcpy(pname,p);
   }
}BP[20];

void add_passenger()
{
    fstream fil;
    struct BoardingPass P;
    fil.open("P.dat",ios::binary|ios::out);
    int ch=1;
    while(ch==1)
    {
        P.input();


        fil.write((char*)&P,sizeof(P));
        cout<<"More (1/0) ?";
        cin>>ch;
    }
    fil.close();
}

void catch_flight(string fname)
{
    fstream file;
    struct BoardingPass P;
    int i=0;
    char s1[20];
    char s2[20];
    file.open("P.dat",ios::binary|ios::in);
    while(file.read((char*)&P,sizeof(P)))
    {
        strcpy(BP[i].aname,P.aname);
        strcpy(BP[i].pname,P.pname);
        i++;
        size++;

    }
    string temp;
    file.close();
    for(int i=0;i<size;i++)
    {
     temp=BP[i].aname;
     if(temp==fname)
        BP[i].pname;
    }
}

void graph()
{
     priority_queue<air,vector<air>,myComparator> pq;
    fstream file;
    string s;
    int t,l;
    class air B;
    file.open("A.dat",ios::binary|ios::in);
    while(file.read((char*)&B,sizeof(B)))
    {
        s=B.getX();
        t=B.getY();
        l=B.getZ();
        pq.push(air(s,t,l));
    }
    file.close();
    cout<<"Flights In The Landing Queue(prior to thier arrival time\n";
    cout<<"Flight Name        Arrival Time   Takeofflimit\n";
    priority_queue<air,vector<air>,myComparator> jj=pq;
    while (jj.empty() == false)
    {
        air p = jj.top();
        cout << p.getX() << "           " << p.getY() <<"              "<<p.getZ();
        cout << endl;
        jj.pop();
    }
    cout<<"\nChecking if flights have same arrival times:";
    for(int i=0;i<10;i++)
    {
        cout<<".";
        for(int j=0;j<4000;j++)
            for(int k=0;k<4000;k++)
            {
            }
            }
            cout<<endl;
     priority_queue<air,vector<air>,myComparator> rr,ll;
     jj=pq;
    while(jj.empty()==false)
     {
         air n=jj.top();
         jj.pop();
         air m=jj.top();
         jj.pop();
         int count=m.getY();
         if(n.getY()==m.getY())
         {
             rr.push(air(n.getX(),n.getY(),n.getZ()));
             count++;
             jj.push(air(m.getX(),count,m.getZ()));

         }
         else
         {
             rr.push(air(n.getX(),n.getY(),n.getZ()));
             rr.push(air(m.getX(),m.getY(),m.getZ()));
         }

     }
     pq=rr;
    while (pq.empty() == false)
    {
        air p = pq.top();
        cout << p.getX() << "           " << p.getY() <<"              "<<p.getZ();
        cout << endl;
        pq.pop();
    }
    pq=rr;



    cout<<"This Program is set for One runway (One flight can land at a a time)\n\n";
    int total;
    cout<<"Enter No. Of Time Cycles:";
    cin>>total;
    cout<<"\n\nThe Complete Landing Simulation Is as follows:-\n\n";
    while(pq.empty()==false)
    {

          if(total>0)
        {
         cout<<"Air traffic Personal In the control room(who has the least shift period):";
         controller m=query(1,1,6,1,6,tree);
         cout<<"Controller "<<m.name<<" working for "<<m.tunits<<" units\n\n";
         int thresh=m.tunits;

         air q=pq.top();
        cout<<"Flight Asking To Land::"<<q.getX()<<" Airlines\n\n";
        char g;
        cout<<"Grant Permission?(Y/N)";
        cin>>g;
        if(g=='y' || g=='Y')
        {
            cout<<q.getX()<<" Landed with Arrival time of "<<q.getY()<<" units and will stay "<<q.getZ()<<" units on the runway\n\n";
            total=total-q.getZ();
            thresh=thresh-q.getZ();
            if(thresh<=0)
            {
                for(int i=1;i<7;i++)
                if(c[i].name==m.name)
                update(1,1,6,i,100,tree,c);
            }

            catch_flight(q.getX());
                cout<<q.getX()<<" Took off after staying for "<<q.getZ()<<" units\n";
                cout<<"Total Time cycles Left: "<<total<<endl;
                pq.pop();
        }
         else
            {
                cout<<"Access Denied\n\n";
                pq.pop();
            }



    }
    else
            {

                cout<<"Time cycles are ended\n";
                break;
            }



    }
    display(pq);







}

void add_airline()
{
    fstream fil;
    air A;
    fil.open("A.dat",ios::binary|ios::app);
    int ch=1;
    while(ch==1)
    {
        A.input();


        fil.write((char*)&A,sizeof(A));
        cout<<"More (1/0) ?";
        cin>>ch;
    }
    fil.close();
}




void intro()
{
     system("cls");
      char jk;
      do{
            system("cls");
      int choice;
      char ch;
      cout<<"Welcome To Air Traffic Control\n";
      cout<<"1. List Of The Air Traffic Controllers\n";
      cout<<"2. AirPort Landing Queues And Mechanism\n";
      cout<<"3. Add Airlines\n";
      cout<<"4. Add Passengers\n";
      cout<<"5. Exit\n";
      cout<<"Enter Your Choice:";
      cin>>choice;
      switch(choice)
      {
          case 1: {
              person();
              break;
                  }
          case 2: {
                  graph();
                  break;
                  }
          case 3: {
                  add_airline();
                  break;
                  }
          case 4: {
                  add_passenger();
                  break;
                  }

      }
      cout<<"\nContinue?(Y/N)";
      cin >>jk;
      }while(jk=='y' || jk=='Y');


}

void welcome1()
{
    system("cls");

system("color 4f");
rectangle(10,6,80,30);
gotoxy(29,10);cout<<"AIR TRAFFIC CONTROLLER";

gotoxy(34,8);cout<<"_____________";
gotoxy(34,11);cout<<"_____________";

gotoxy(20,15);cout<<"               SUBMITTED BY";
gotoxy(15,16);cout<<"                 **SHORYA KAUSHIK**";


gotoxy(15,17);cout<<"                 **SAKSHI MISHRA **";
gotoxy(15,18);cout<<"                 **URVASHI GUPTA **";
gotoxy(15,19);cout<<"                 **RAKSHIT SINGH **";

gotoxy(18,23);cout<<"       A PROJECT IN C++ (BY BATCH - B1)";
gotoxy(19,25);cout<<"JAYPEE INSTITUTE OF INFORMATION TECHNOLOGY";
gotoxy(19,26);cout<<"******************************************";


gotoxy(30,28);cout<<"A DEEMED UNIVERSITY";
char ch;
ch=getche();
if(ch==13)
{
    intro1();
}
}

void intro1()
{
    char c;
    do
    {
        system("cls"); //Clears the screen
        rectangle(8,9,70,13);
        gotoxy(31,11); cout<<"Press <-'Enter to login \n\n\n\t\t\t\t\t";
        c=getche(); //Variable c stores the key pressed by user
        if (c==13)
        admin();
        if (c==27)
        exit(0); //27 is ASCII code of escape key

    }while(1); //infinite loo
}

void admin()

{/*char d[6],p[6];

    system("cls");
cout<<"Login Id:";cin>>d;
cout<<"Password(5 characters):";
int i=0;
char c;
for(i=0;i<5;i++)
{
c=getch();
p[i]=c;
printf("*");
}
p[i]='\0';

if((strcmp(d,"admin")==0)&&(strcmp(p,"admin")==0))
{

}
else{
    printf("No match!!");*/

intro();
}




int main()
{
    fstream file;

    file.open ("example4.txt", ios::out | ios::in );
    string x;int y,w;
    int i=1;
    while(file>>w>>x>>y)
    {
      c[i].roll=w;
      c[i].name=x;
      c[i].tunits=y;
      i++;
    } //got the data
    /* storing the data in the segment tree*/
    buildtree(1,1,6,tree,c);
    file.close();
    welcome1();



    return 0;
}
