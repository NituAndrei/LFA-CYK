#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

struct Productie
{
    char Stanga;
    int NrDreapta;
    struct
    {
        char x,y;
    }Dreapta[20];
};

int main()
{
    ifstream f("date.in");
    int NrProductii,i,j,l;
    char Cuvant[100];
    f>>NrProductii;
    struct Productie Productii[NrProductii];

    for(i=0;i<NrProductii;i++)
    {
        f>>Productii[i].Stanga;
        f>>Productii[i].NrDreapta;
        for(j=0;j<Productii[i].NrDreapta;j++)
        {
            f>>Productii[i].Dreapta[j].x;
            if(Productii[i].Dreapta[j].x>='a' && Productii[i].Dreapta[j].x<='z')
            {
                Productii[i].Dreapta[j].y='\0';
                continue;
            }
            f>>Productii[i].Dreapta[j].y;
        }
    }
    f>>Cuvant;

    char Solutie[strlen(Cuvant)][strlen(Cuvant)][100];
    int n=strlen(Cuvant),Adancime[strlen(Cuvant)][strlen(Cuvant)],naux;

    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            Adancime[i][j]=0;
    for(i=0;i<n;i++)
    {
        for(j=0;j<NrProductii;j++)
        {
            int bol=0;
            for(l=0;l<Productii[j].NrDreapta;l++)
            {
                if(Productii[j].Dreapta[l].x==Cuvant[i])
                {
                    Solutie[0][i][Adancime[0][i]++]=Productii[j].Stanga;
                    bol=1;
                }
            }
            if(bol)
                continue;
        }
    }
    naux=n;
    n--;
    for(i=1;i<naux;i++)//linia
    {
        for(j=0;j<n;j++)//coloana
        {
            for(int k=0;k<i;k++)//index pt CYK
            {
                int adancime1=Adancime[k][j],adancime2=Adancime[i-k-1][j+k+1];
                for(int o=0;o<adancime1;o++)//adancime1
                {
                    for(int p=0;p<adancime2;p++)//adancime2
                    {
                        for(int m=0;m<NrProductii;m++)//productiile
                        {
                            for(l=0;l<Productii[m].NrDreapta;l++)//fiecare pereche de neterminali
                            {
                                if(Productii[m].Dreapta[l].x==Solutie[k][j][o] && Productii[m].Dreapta[l].y==Solutie[i-k-1][j+k+1][p])
                                {
                                    int bol=1;
                                    for(int h=0;h<Adancime[i][j];h++)
                                        if(Solutie[i][j][h]==Productii[m].Stanga)
                                            bol=0;
                                    if(bol)
                                        Solutie[i][j][Adancime[i][j]++]=Productii[m].Stanga;
                                }
                            }
                        }
                    }
                }
            }
        }
        n--;
    }
    n=naux;
    for(i=0;i<naux;i++)
    {
        for(j=0;j<n;j++)
        {
            if(Adancime[i][j])
            {
                for(l=0;l<Adancime[i][j];l++)
                    cout<<Solutie[i][j][l];
                cout<<" ";
            }
            else
                cout<<char(237)<<" ";
        }
        n--;
        cout<<'\n';
    }
    n=naux;
    try
    {
        for(i=0;i<Adancime[n-1][0];i++)
            if(Solutie[n-1][0][i]=='S')
                throw 1;
        cout<<"Cuvantul nu e acceptat";
    }
    catch(...)
    {
        cout<<"Cuvantul e acceptat";
    }
    f.close();
}
