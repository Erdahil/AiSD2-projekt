#include <iostream>
using namespace std;

bool wspolliniowe(int xc, int yc, int xa, int ya, int xb, int yb)
{
    if(((xb-xa)*(yc-ya))==((yb-ya)*(xc-xa)))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool przecina_krawedz(int xc, int yc, int xa, int ya, int xb, int yb)
{
    if(((xa<=xc && xc<xb) || (xa>=xc)) && yc>((ya-yb)/(xa-xb))*(xc-xa)+ya)
    {
        return true;
    }
    return false;
}

int main()
{
    int n;
    cout<<"podaj ile katow ma to cos:\n";
    cin>>n;
    int t[n][2]; // to powinno być raczej dynamicznie zadeklarowane ale jebac
    cout<<"podaj te wierzcholki pls:\n";
    for(int i=0; i<n; i++)
    {
        cin>>t[i][0]>>t[i][1];
    }
    int x, y;
    cout<<"podaj punkt ktory chcesz sprawdzic:\n";
    cin>>x>>y;
    for(int i=0; i<n; i++)
    {
        int xa,ya,xb,yb;
        xa=t[i][0];
        ya=t[i][1];
        
        if(i==n)
        {
            xb=t[0][0];
            yb=t[0][1];
        }
        
        
        /*if(x==t[i][0] && y==t[i][1];
        {
            cout<<"punkt nalezy do wielokata:\n";
            return 0;
        }*/
    }
    int xmax=t[0][0]; xmin=t[0][0];
    for(int i=0; i<n; i++)
    {
        if(t[i][0]>xmax)
        {
            xmax=t[i][0];
        }
        if(t[i][0]<xmin)
        {
            xmin=t[i][0];
        }
    }
    if(x>xmax || x<xmin)
    {
        cout<<"punkt nie nalezy do wielokata\n";
        return 0;
    }
    
    
    
    return 0;
}
