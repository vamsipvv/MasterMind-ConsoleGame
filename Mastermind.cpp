#include<bits/stdc++.h>
using namespace std;
void clearScreen()
{
    system("CLS");
}
struct players
{
    string name;
    int moves;
    string code;
};
struct players getplayer(int i)
{
    struct players p;
    cout<<"Enter the name of the player"<<i<<":";
    cin>>p.name;
    p.moves=0;
    clearScreen();
    return p;
}
string getRandom()
{
    fflush(stdin);
    char a,b,c,d,choice;
    string ans="";
    srand(time(0));
    a=rand()%10+'0';
    if(a=='0')
    {
        while(a=='0')
            a=rand()%10+'0';
    }
    b=rand()%10+'0';
    if(b=='0'||b==a)
    {
        while(b=='0'||b==a)
            b=rand()%10+'0';
    }
    c=rand()%10+'0';
    if(c=='0'||(c==b||c==a))
    {
        while(c=='0'||(c==b||c==a))
            c=rand()%10+'0';
    }
    d=rand()%10+'0';
    if(d=='0'||(d!=c||d!=b||d!=a))
    {
        while(d=='0'||d==c||d==b||d==a)
            d=rand()%10+'0';
    }
    ans+=a;ans+=b;ans+=c;ans+=d;
    ans+=" ";
    cout<<"Random code:"<<ans;
    cout<<"\nIf Ok press 1, To generate again press 2\n";
    cin>>choice;
    switch(choice)
    {
        case '1':return ans;
        case '2': return getRandom();
        default:
                cout<<"Wrong choice!!!Enter again\n";
                system("pause");
                return getRandom();
    }
    return NULL;
}
bool check(string code)
{
    if(code.size()>4)
        return true;
    if(code[0]==code[1]||code[0]==code[2]||code[0]==code[3])
        return true;
    if(code[1]==code[0]||code[1]==code[2]||code[1]==code[3])
        return true;
    if(code[2]==code[0]||code[2]==code[1]||code[2]==code[3])
            return true;
    if(code[3]==code[0]||code[3]==code[1]||code[3]==code[2])
        return true;
    return false;
}
void setCodes(struct players *p,struct players *p1)
{
    fflush(stdin);
    clearScreen();
    char choice;
    string code="";
    p->moves=0;
    p1->code="";
    cout<<"Player "<<p->name<<":\n1.Set your own code  2.Generate random code\nEnter your choice:";
    cin>>choice;
   // cout<<"Choice ="<<choice<<"\n";
    switch(choice)
    {
        case '1': cout<<"Enter your code:";
                cin>>code;
                if(check(code))
                {
                    cout<<"Invalid Code\nNote:\n1)Duplicates should not be there!!!\n2)A 4 digit code without zeroes \n";
                    system("pause");
                    clearScreen();
                    setCodes(p,p1);
                }
                else
                    p1->code=code;
                break;
        case '2':p1->code=getRandom();
               break;
        default:

                    cout<<"Wrong choice!!\n";
                    getchar();
                    getchar();
                    system("pause");
                    setCodes(p,p1);
    }
    fflush(stdin);
}
int calculate(string code,struct players *p)
{
    int i,correct=0,wrong=0,hash[10]={0};
    for(int i=0;i<4;i++)
    {
        hash[p->code[i]-'0']++;
    }
    for(i=0;i<4;i++)
    {
        hash[code[i]-'0']++;
        if(hash[code[i]-'0']==2)
        {
            wrong++;
        }
        if(code[i]==p->code[i])
            correct++;
    }
    wrong=abs(wrong-correct);
    cout<<"["<<wrong<<" : "<<correct<<"]";
    return((correct==4)?1:0);
}
int validate(string code)
{
    for(int i=0;i<4;i++)
    {
        if(code[i]<='9'&&code[i]>='0');
        else
            return 0;
    }
    if(code[0]==code[1]||code[0]==code[2]||code[0]==code[3])
        return 0;
    if(code[1]==code[0]||code[1]==code[2]||code[1]==code[3])
        return 0;
    if(code[2]==code[0]||code[2]==code[1]||code[2]==code[3])
            return 0;
    if(code[3]==code[0]||code[3]==code[1]||code[3]==code[2])
        return 0;
    return 1;
}
int turnP(struct players *p)
{
    int status=0;
    string code;
    cout<<p->name<<":";
    cin>>code;
    if(validate(code))
    {
        status=calculate(code,p);
    }
    else
    {
        cout<<"Invalid code please enter valid digits:\n";
        system("pause");
        turnP(p);
    }
    fflush(stdin);
    return status;
}
void startGame(struct players *p1,struct players *p2)
{
    int move=0,status=0;
    while(status!=1)
    {
           if(move==0)
           {
                status=turnP(p1);
                if(status==1)
                {
                    cout<<"\nPlayer "<<p1->name<<" Wins!!!\n";
                    break;
                }
                move=1;
           }
           else
           {
                status=turnP(p2);
                if(status==1)
                {
                    cout<<"\nPlayer "<<p2->name<<" Wins!!!\n";
                    break;
                }
                move=0;
           }
           cout<<"\n";
    }
}
int main()
{
    struct players p1,p2;
    p1=getplayer(1);
    p2=getplayer(2);
    setCodes(&p1,&p2);
    clearScreen();
   //cout<<"Moves:"<<p1.moves;
    setCodes(&p2,&p1);
    cout<<p1.name<<" Code is "<<p1.code<<"\n"<<p2.name<<" Code is "<<p2.code;
    cout<<"\nPress Enter to start the game...\n";
    clearScreen();
    startGame(&p1,&p2);
    return 0;
}
