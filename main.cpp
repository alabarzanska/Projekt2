#include <iostream>
#include<vector>
#include<string>
#include<cstring>
#include<windows.h>
#include<time.h>
#include<cstdlib>
#include<stdio.h>

using namespace std;

class Czujnik
{
    public:
    virtual float mierz()=0;
    string nazwa;

};

class Wyswietlacz
{
    public:
    virtual void wyswietl_dane_biezace_cz(float pomiar_w,Czujnik *cz,Wyswietlacz *w)=0;
    string nazwa;
};

class Pary
{

    public:
    float pob_pomiar;
    Wyswietlacz *b;
    Czujnik *a;
    Pary (Wyswietlacz *w,Czujnik *cz)
    {
        b=w;
        a=cz;
    }
    ~Pary()
    {
        cout<<"destruktor"<<endl;
    }

    void pomiar()
    {
        pob_pomiar=a->mierz();
    }
    void wyslij_do_wyswietlacza()
    {
        b->wyswietl_dane_biezace_cz(pob_pomiar,a,b);
    }


};

class System
{

    vector <Czujnik *> czujniki;
    vector <Wyswietlacz *> wyswietlacze;
    vector <Pary *> para;
    float odebrany_pomiar;
    public:
/////////////////////////////////////////////////////////////////////////////////
        //WYSWIETLACZE
        void dodaj_wyswietlacz(Wyswietlacz * ob)
        {
            wyswietlacze.push_back(ob);
        }
       void usun_wyswietlacz();

///////////////////////////////////////////////////////////////////////////////
        //CZUJNIKI
   void dodaj_czujniki(Czujnik *ob)
    {
        czujniki.push_back(ob);
    }
   void usun_czujniki();

    void usun()
    {
        for(int i=0;i<para.size();i++)
            {

                delete para[i];
            }
    }


    void powiadom_cz_w()
    {
        for(int i=0;i<para.size();i++)
        {
            para[i]->pomiar();

            para[i]->wyslij_do_wyswietlacza();

        }
    }
    void odbierz_dane_czujnik(float pomiar)
    {

        odebrany_pomiar=pomiar;

    }


///////////////////////////////////////////////////////////////////////////////
//POLACZENIE CZUJNIKOW Z WYSWIETLACZEM

    void polacz_wys_czuj(string nazwa_cz, string nazwa_w)
    {
                for(int i=0;i<wyswietlacze.size();i++)
                {
                    if(nazwa_w==wyswietlacze[i]->nazwa)
                    {
                            for(int j=0; j<czujniki.size();j++)
                            {
                                    if(nazwa_cz==czujniki[j]->nazwa)
                                    {

                                       Pary *wsk=new Pary(wyswietlacze[i],czujniki[j]);
                                       para.push_back(wsk);


                                    }
                            }

                    }
                }


    }




};





class Czujnik_temp : public Czujnik
{
    float temp_biezaca;
    float temp_krytyczna;
    public:
        Czujnik_temp(string n="XXX",float temp=20)
        {
            temp_krytyczna=temp;
            nazwa=n;

        }

    float mierz()
    {
        srand(time(NULL));
        temp_biezaca=rand()%50+1;
        Sleep(1000);
        return temp_biezaca;

    }



};
class Czujnik_cisnienia : public Czujnik
{
    float cisnienie_biezace;
    float cisnienie_krytyczne;
    public:

        Czujnik_cisnienia(string n="XXX",float cisnienie=1024)
        {
            cisnienie_krytyczne=cisnienie;
            nazwa=n;
        }

    float mierz()
    {
        srand(time(NULL));
        cisnienie_biezace=rand()%2000+1;
        Sleep(1000);
        return cisnienie_biezace;

    }





};





class Wyswietlacz_kuchnia: public Wyswietlacz
{
    public:

        Wyswietlacz_kuchnia(string n="XXX")
        {
            nazwa=n;
        }

    void wyswietl_dane_biezace_cz(float pomiar_w,Czujnik *cz,Wyswietlacz *w)
    {

        cout<<"WYSWIETLACZ: "<<w->nazwa <<", CZUJNIK: "<<cz->nazwa <<", PMOIAR: "<<pomiar_w<<endl;
    }
};

class Wyswietlacz_hol: public Wyswietlacz
{
    public:

        Wyswietlacz_hol(string n="XXX")
        {
            nazwa=n;
        }

    void wyswietl_dane_biezace_cz(float pomiar_w,Czujnik *cz,Wyswietlacz *w)
    {
        cout<<"WYSWIETLACZ: "<<w->nazwa <<", CZUJNIK: "<<cz->nazwa <<", PMOIAR: "<<pomiar_w<<endl;
    }

};





int main()
{

    System s;
    s.dodaj_czujniki(new Czujnik_temp("Kuchnia",20));
    s.dodaj_czujniki(new Czujnik_temp("Salon",20));
    s.dodaj_czujniki(new Czujnik_temp("Dwor",20));
    s.dodaj_czujniki(new Czujnik_cisnienia("K",1024));

    ///////////////////////////////////////////////////////////
    s.dodaj_wyswietlacz(new Wyswietlacz_kuchnia("Wys_kuchnia"));
    s.dodaj_wyswietlacz(new Wyswietlacz_hol("Wys_salon"));
    s.dodaj_wyswietlacz(new Wyswietlacz_hol("Wys_salon2"));
    ////////////////////////////////////////////////////////////
    s.polacz_wys_czuj("Kuchnia","Wys_kuchnia");
    s.polacz_wys_czuj("Salon","Wys_salon");
    s.polacz_wys_czuj("Salon","Wys_salon2");

    s.powiadom_cz_w();
    s.usun();
    return 0;
}
