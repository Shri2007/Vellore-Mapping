#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>
#include<iostream>
using namespace std;

struct node
{
    node *parent;
    int x, y;
    float f, g, h;
};

node olist[100], clist[100];
int otop=-1, ctop=-1;

int main()
{
    int sx, sy, fx, fy, i, vmap[10][10]={0}, least, j, tx, ty, k, l, x[16]={8,7,8,5,6,4,5,6,3,4,1,2,3,0,1,2}, y[16]={1,2,2,3,3,4,4,4,5,5,6,6,6,7,8,7}, ch1, ch2;
    char names[16][30]={"VIT","Gandhinagar","Kangyanellore Road","Vivekanand Nagar","Samuel Nagar","Madina Nagar","CMC","Thendral Nagar","Balaji Nagar","Arcot Road","Mariadoss Nagar","Azad Road","RV Nagar","Kanaraj Nagar","Thorapadi-Bagayam Road","Mullai Road"};
    node succ[8], q, *bt;

    cout<<"-----------------------VELLORE MAPPING-----------------------"<<endl<<endl<<endl;
    sloc:
    cout<<"Choose your start location"<<endl;
    cout<<"1.VIT"<<"               "<<"2.Gandhinagar"<<"            "<<"3.Kangyanellore Road"<<endl<<"4.Vivekanand Nagar"<<"  "<<"5.Samuel Nagar"<<"           "<<"6.Madina Nagar"<<endl<<"7.CMC"<<"               "<<"8.Thendral Nagar"<<"         "<<"9.Balaji Nagar"<<endl<<"10.Arcot Road"<<"       "<<"11.Mariadoss Nagar"<<"       "<<"12.Azad Road"<<endl<<"13.RV Nagar"<<"         "<<"14.Kanaraj Nagar"<<"         "<<"15.Thorapadi-Bagayam Road"<<endl<<"16.Mullai Road ";
    cin>>ch1;
    cout<<endl;
    if(ch1>16 || ch1<=0)
    {
        cout<<"Wrong choice! Choose again."<<endl;
        goto sloc;
    }
    else
    {
        sx=x[ch1-1];
        sy=y[ch1-1];
    }
    floc:
    cout<<"Choose your destination"<<endl;
    cout<<"1.VIT"<<"               "<<"2.Gandhinagar"<<"            "<<"3.Kangyanellore Road"<<endl<<"4.Vivekanand Nagar"<<"  "<<"5.Samuel Nagar"<<"           "<<"6.Madina Nagar"<<endl<<"7.CMC"<<"               "<<"8.Thendral Nagar"<<"         "<<"9.Balaji Nagar"<<endl<<"10.Arcot Road"<<"       "<<"11.Mariadoss Nagar"<<"       "<<"12.Azad Road"<<endl<<"13.RV Nagar"<<"         "<<"14.Kanaraj Nagar"<<"         "<<"15.Thorapadi-Bagayam Road"<<endl<<"16.Mullai Road ";
    cin>>ch2;
    cout<<endl;
    if(ch2>16 || ch2<=0 || ch2==ch1)
    {
        cout<<"Wrong choice! Choose again."<<endl;
        goto floc;
    }
    else
    {
        fx=x[ch2-1];
        fy=y[ch2-1];
    }
    cout<<"Keep pressing any key to find traffic situation at other places within Vellore"<<endl;
    for(i=0;i<16;i++)
    {
        if(i!=ch1-1 && i!=ch2-1)
        {
            srand(time(NULL));
            getch();
            vmap[x[i]][y[i]]=rand()%2;
            if(vmap[x[i]][y[i]]==1)
            {
                cout<<"There is traffic at "<<names[i]<<endl;
            }
            else
            {
                cout<<"There is no/less traffic at "<<names[i]<<endl;
            }
        }
    }
    cout<<endl;

    //Getting starting and final, x and y values according to place name and allotting 1 to obstacles in path

    succ[0].parent=NULL;
    succ[0].x=sx;
    succ[0].y=sy;
    succ[0].f=0;
    succ[0].h=0;
    succ[0].g=0;
    otop++;
    olist[otop]=succ[0];

    while(otop!=-1)
    {
        least=0;
        cout<<"Open List:"<<endl;
        for(i=0;i<=otop;i++)
        {
            cout<<olist[i].x<<" "<<olist[i].y<<" "<<olist[i].f<<endl;
        }
        for(i=1;i<=otop;i++)
        {
            if(olist[i].f<olist[least].f)
            {
                least=i;
            }
        }
        q=olist[least];
        cout<<q.x<<" "<<q.y<<" "<<q.f<<endl<<endl;
        otop--;
        for(i=least;i<=otop;i++)
        {
            olist[i]=olist[i+1];
        }
        tx=q.x;
        ty=q.y;
        k=-1;
        ctop++;
        clist[ctop]=q;
        for(i=-1;i<=1;i++)
        {
            for(j=-1;j<=1;j++)
            {
               if(vmap[tx+i][ty+j]!=1 && tx+i>=0 && tx+i<10 && ty+j>=0 && ty+j<10)
               {
                   k++;
                   succ[k].parent=&clist[ctop];
                   succ[k].x=tx+i;
                   succ[k].y=ty+j;
                   if(abs(i)==abs(j))
                   {
                       succ[k].g=q.g+14.14;
                   }
                   else
                   {
                       succ[k].g=q.g+10;
                   }
                   succ[k].h=(abs(fx-succ[k].x)+abs(fy-succ[k].y))*10;
                   succ[k].f=succ[k].g+succ[k].h;
                   if(succ[k].x==fx && succ[k].y==fy)
                   {
                       ctop++;
                       clist[ctop]=succ[k];
                       goto last;
                   }
               }
            }
        }
        for(i=0;i<=k;i++)
        {
            for(j=0;j<=otop;j++)
            {
                if(succ[i].x==olist[j].x && succ[i].y==olist[j].y && olist[j].f<=succ[i].f)
                {
                    goto loopend;
                }
            }
            for(j=0;j<=ctop;j++)
            {
                if(succ[i].x==clist[j].x && succ[i].y==clist[j].y && clist[j].f<=succ[i].f)
                {
                    goto loopend;
                }
                else if(succ[i].x==clist[j].x && succ[i].y==clist[j].y && clist[j].f>succ[i].f)
                {
                    ctop--;
                    for(l=j;l<=ctop;l++)
                    {
                        clist[l]=clist[l+1];
                    }
                }
            }
            otop++;
            olist[otop]=succ[i];
            loopend:;
        }
    }
    last:
    if(clist[ctop].x!=fx || clist[ctop].y!=fy)
    {
        cout<<"Couldn't find a path!";
    }
    else
    {
        cout<<"Path Found!"<<endl;
        bt=&clist[ctop];
        while(bt!=NULL)
        {
             cout<<bt->x<<" , "<<bt->y<<endl;
             bt=bt->parent;
        }
    }
}
