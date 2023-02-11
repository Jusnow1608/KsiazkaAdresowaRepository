#include <iostream>
#include <windows.h>
#include<fstream>
#include<cstdlib>
#include<vector>
#include<string>
#include<windows.h>
#include <sstream>
#include <conio.h>
using namespace std;

struct Uzytkownik
{
    int id;
    string nazwa, haslo;
};
vector <Uzytkownik> uzytkownicy;
void addUserToFile (Uzytkownik & newUser);

int rejestracja (vector <Uzytkownik> & uzytkownicy)
{
    Uzytkownik newUser;
    int usersCount = uzytkownicy.size();
    cout<<"Podaj nazwe uzytkownika: ";
    cin>>newUser.nazwa;
    cout<<"Podaj haslo: ";
    cin>>newUser.haslo;
    if (usersCount > 0)
    {
        newUser.id = uzytkownicy[usersCount - 1].id + 1;
    }
    else
    {
        newUser.id = 1;
    }
    uzytkownicy.push_back( newUser );
    usersCount = uzytkownicy.size();
    addUserToFile (newUser);
    cout << endl << "Uzytkownik zostal zapisany. Konto zalozone." << endl;
    cout << newUser.id << "|" << newUser.nazwa << "|" << newUser.haslo<< "|" << endl;
    getch();
    return usersCount;
      }

void addUserToFile (Uzytkownik & newUser)
{
    fstream file;
    file.open ("Uzytkownicy.txt", ios::out| ios::app);
    file << newUser.id << "|" << newUser.nazwa << "|"<<newUser.haslo << "|" << endl;
    file.close();
}
void refreshDataInUsersFile (vector <Uzytkownik> & uzytkownicy)
{
    int numberOfContacts = uzytkownicy.size();
    fstream file;
    file.open ("Uzytkownicy.txt", ios::out);
    if( file.good() )
    {
        for( int i = 0; i < numberOfContacts; i++ )
        {
            file << uzytkownicy[i].id << "|" << uzytkownicy[i].nazwa << "|" << uzytkownicy[i].haslo << "|" << endl;
        }
        file.close();
    }
}

int readDataFromUsersBook (vector <Uzytkownik> & uzytkownicy)
{
    Uzytkownik uzytkownik;
    char character = '|';
    int usersCount = 0;
    string row = "";
    int rowNumber = 1;
    int lastUserInFile = 0;
    fstream file;
    file.open ("Uzytkownicy.txt", ios::in);
    if(file.good() == true)
    {
        while(getline(file,row))
        {
            string l = row;
            vector <string> element;
            stringstream ss(l);
            string rowToRead;

            while (getline(ss, rowToRead, character))
            {
                element.push_back(rowToRead);
            }
            for (int i = 0; i < 6; i++)
            {
                switch (i)
                {
                case 0:
                    uzytkownik.id = atoi(element[i].c_str());
                    break;
                case 1:
                    uzytkownik.nazwa = element[i];
                    break;
                case 2:
                    uzytkownik.haslo = element[i];
                    break;
                }
            }
            if (rowNumber > 0)
            {
                usersCount++;
                uzytkownicy.push_back(uzytkownik);
                rowNumber++;
            }
        }
        getline(file,row);
        file.close();
    }
    else
    {
        file.open ("Uzytkownicy.txt", ios::out);
        file.close();
        cout << "Nie udalo sie otworzyc pliku!" << endl;
    }
    lastUserInFile = uzytkownicy.size();

    if (usersCount == 0)
    {
        return usersCount;
    }
    else if (usersCount == uzytkownicy[lastUserInFile - 1].id)
    {
        return usersCount;
    }
    else if (usersCount != uzytkownicy[lastUserInFile - 1].id)
    {
        return uzytkownicy[lastUserInFile - 1].id;
    }
    else
    {
        return 0;
    }
}

int logowanie(vector <Uzytkownik> & uzytkownicy)
{
    string nazwa, haslo;
    int usersCount = uzytkownicy.size();
    cout<<"Podaj login: ";
    cin>>nazwa;
    int i = 0;
    while (i<usersCount)
    {
        if (uzytkownicy[i].nazwa == nazwa)
        {
            for (int proby=0; proby<3; proby++)
            {
                cout<<"Podaj haslo. Pozostalo prob "<<3-proby<<": ";
                cin>>haslo;
                if(uzytkownicy[i].haslo==haslo)
                {
                    cout<<"Zalogowales sie."<<endl;
                    Sleep(1000);
                    return uzytkownicy[i].id;
                }
            }
            cout<<"Podales 3 razy bledne haslo. Poczekaj 3 sekundy przed kolejna proba."<<endl;
            Sleep(3000);
            return 0;
        }
        i++;
    }
    cout<<"Nie ma uzytkownika z takim loginem. "<<endl;
    Sleep(1500);
    return 0;
}
void zmianaHasla (vector <Uzytkownik> uzytkownicy, int idZalogowanegoUzytkownika)
{
    int usersCount = uzytkownicy.size();
    string haslo;
    cout<<"Podaj nowe haslo: ";
    cin>>haslo;
    for (int i=0; i<usersCount; i++)
    {
        if (uzytkownicy[i].id==idZalogowanegoUzytkownika)
        {
            uzytkownicy[i].haslo=haslo;
            cout<<"Haslo zostalo zmienione."<<endl;
            Sleep(1500);
        }
    }
    refreshDataInUsersFile (uzytkownicy);
    getch();
}
void startMenu(vector <Uzytkownik> & uzytkownicy)
{
int idZalogowanegoUzytkownika = 0;
int usersCount = uzytkownicy.size();
 char wybor;
    while (1)
    {
        if (idZalogowanegoUzytkownika==0)
        {
            system ("cls");
            cout<<"1. Rejestracja"<<endl;
            cout<<"2. Logowanie"<<endl;
            cout<<"9. Zakoncz program"<<endl;
            cin>>wybor;
            if (wybor == '1')
            {
               usersCount = rejestracja (uzytkownicy);
            }
            else if (wybor == '2')
            {
                idZalogowanegoUzytkownika = logowanie(uzytkownicy);
            }
            else if (wybor =='9')
            {
                exit(0);
            }
        }
        else
        {
            system ("cls");
            cout<<"1. Zmiana hasla"<<endl;
            cout<<"2. Wylogowanie"<<endl;
            cin>>wybor;
            if (wybor == '1')
            {
                zmianaHasla (uzytkownicy, idZalogowanegoUzytkownika);
            }
            else if (wybor == '2')
            {
               idZalogowanegoUzytkownika = 0;
            }
        }
    }
}

int main()
{
    vector <Uzytkownik> uzytkownicy;
    Uzytkownik uzytkownik;

    int idZalogowanegoUzytkownika = 0;//identyfikator zalogowanego uzytkownika.
//Jesli rowna zero, to znaczy, ¿ ¿aden u¿ytkownik nie jest zalogowany
//i program ma wyswietlac manu zwiazane z rejestrowaniem uzytkownika oraz logowaniem.
//W przeciwnym razie gdy wartosc wieksza od zera, bedzie wiadomo, ze jakis uzytkownik
//juz jest zalogowany i wtedy program ma mi wyswietlac manu zwiazane ze zmiana hasla
//oraz wylogowywaniem sie.
    int usersCount = 0;
    usersCount = readDataFromUsersBook (uzytkownicy);
    startMenu(uzytkownicy);
    return 0;
}
