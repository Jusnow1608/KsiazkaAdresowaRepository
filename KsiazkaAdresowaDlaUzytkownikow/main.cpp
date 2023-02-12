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
    int id = 0;
    string nazwa, haslo;
};

struct Recipient
{
    int id = 0;
    int idZalogowanegoUzytkownika = 0;
    string name = "", surname = "", phoneNumber = "", address = "", email = "";
};

vector <Uzytkownik> uzytkownicy;
vector <Recipient> recipients;

//-------------OPCJE DLA NIEZALOGOWANEGO UZYTKOWNIKA----------------------
void startMenu(vector <Uzytkownik> & uzytkownicy);
int rejestracja (vector <Uzytkownik> & uzytkownicy);
void addUserToFile (Uzytkownik & newUser);
int readDataFromUsersBook (vector <Uzytkownik> & uzytkownicy);
int logowanie(vector <Uzytkownik> & uzytkownicy);

//-------------OPCJE DLA ZALOGOWANEGO UZYTKOWNIKA----------------------
void mainMenu (vector <Recipient> & recipients, int idZalogowanegoUzytkownika);
int readDataFromAddressBook (vector <Recipient> & recipients);
int addNewRecipientToAddressBook (vector <Recipient> & recipients, int idZalogowanegoUzytkownika);
void addRecipientToFile (Recipient & newContact);
void searchByName (vector <Recipient> & recipients, int idZalogowanegoUzytkownika);
void searchBySurname (vector <Recipient> & recipients, int idZalogowanegoUzytkownika);
void displayFullAddressBook (vector <Recipient> & recipients, int idZalogowanegoUzytkownika);
int removeRecipientFromAddressBook (vector <Recipient> & recipients, int idZalogowanegoUzytkownika);
void editRecipientName (vector <Recipient> & recipients, int recipientId, int idZalogowanegoUzytkownika);
void editRecipientSurname (vector <Recipient> & recipients, int recipientId, int idZalogowanegoUzytkownika);
void editRecipientPhoneNumber (vector <Recipient> & recipients, int recipientId, int idZalogowanegoUzytkownika);
void editRecipientAddress (vector <Recipient> & recipients, int recipientId, int idZalogowanegoUzytkownika);
void editRecipientEmail (vector <Recipient> & recipients, int recipientId, int idZalogowanegoUzytkownika);
void displayRecipient (vector <Recipient> & recipients, int i, int idZalogowanegoUzytkownika);
void refreshDataInFile (vector <Recipient> & recipients);
void editMenu(vector <Recipient> & recipients, int idZalogowanegoUzytkownika);
void zmianaHasla (vector <Uzytkownik> & uzytkownicy, int idZalogowanegoUzytkownika);
void refreshDataInUsersFile (vector <Uzytkownik> & uzytkownicy);

//-------------OPCJE DLA NIEZALOGOWANEGO UZYTKOWNIKA----------------------

//PRZETESTOWANE

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

//PRZETESTOWANE

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

//DO PRZETESTOWANIA, CZY DANE SA ZAPISANE PO ZAMKNIECIU PROGRAMU

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
            for (int i = 0; i < 3; i++)
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
                                                                cout <<"Ilosc uzytkownikow = "<<lastUserInFile<<endl;
                                                                system ("pause");
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
//PRZETESTOWANE
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
    getch();
    return 0;
}
//DO PRZETESTOWANIA

void zmianaHasla (vector <Uzytkownik> & uzytkownicy, int idZalogowanegoUzytkownika)
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

//-------------OPCJE DLA NIEZALOGOWANEGO UZYTKOWNIKA----------------------

//WSZYSTKIE DO PRZETESTOWANIA
int addNewRecipientToAddressBook (vector <Recipient> & recipients, int idZalogowanegoUzytkownika)
{
    Recipient newContact;
    int numberOfRecipients = recipients.size();
    cout << "Podaj imie: "<<endl;
    cin >> newContact.name ;
    cout << "Podaj nazwisko: " << endl;
    cin >> newContact.surname;
    cout << "Podaj telefon: " << endl;
    cin.sync();
    getline(cin, newContact.phoneNumber);
    cout << "Podaj adres: " << endl;
    cin.sync();
    getline(cin, newContact.address);
    cout << "Podaj email: " << endl;
    cin >> newContact.email;
    if (numberOfRecipients > 0)
    {
        newContact.id = recipients[numberOfRecipients - 1].id + 1;
    }
    else
    {
        newContact.id = 1;
    }
    newContact.idZalogowanegoUzytkownika = idZalogowanegoUzytkownika;
    recipients.push_back( newContact );
    numberOfRecipients = recipients.size();
    addRecipientToFile (newContact);
    cout << endl << "Nowa osoba zostala dodana do ksiazki adresowej. Jej dane to: " << endl;
    cout << newContact.id << "|" << newContact.idZalogowanegoUzytkownika << "|" << newContact.name << "|" << newContact.surname << "|" << newContact.phoneNumber << "|" << newContact.address << "|" << newContact.email << "|" << endl;
    getch();
    return numberOfRecipients;
}

void addRecipientToFile (Recipient & newContact)
{
    fstream file;
    file.open ("KsiazkaAdresowa.txt", ios::out| ios::app);
    file << newContact.id << "|" << newContact.idZalogowanegoUzytkownika << "|" << newContact.name << "|"<<newContact.surname << "|" << newContact.phoneNumber << "|" << newContact.address << "|" << newContact.email << "|" << endl;
    file.close();
}

void refreshDataInFile (vector <Recipient> & recipients)
{
    int numberOfContacts = recipients.size();
    fstream file;
    file.open ("KsiazkaAdresowa.txt", ios::out);
    if( file.good() )
    {
        for( int i = 0; i < numberOfContacts; i++ )
        {
            file << recipients[i].id << "|" << recipients[i].idZalogowanegoUzytkownika << "|" << recipients[i].name << "|" << recipients[i].surname << "|" << recipients[i].phoneNumber << "|" << recipients[i].address << "|" << recipients[i].email << "|" << endl;
        }
        file.close();
    }
}

int readDataFromAddressBook (vector <Recipient> & recipients)
{
    Recipient recipient;
    char character = '|';
    int numberOfRecipients = 0;
    string row = "";
    int rowNumber = 1;
    int lastRecipientInFile = 0;
    fstream file;
    file.open ("KsiazkaAdresowa.txt", ios::in);
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
            for (int i = 0; i < 7; i++)
            {
                switch (i)
                {
                case 0:
                    recipient.id = atoi(element[i].c_str());
                    break;
                case 1:
                    recipient.idZalogowanegoUzytkownika = atoi(element[i].c_str());
                    break;
                 case 2:
                    recipient.name = element[i];
                    break;
                case 3:
                    recipient.surname = element[i];
                    break;
                case 4:
                    recipient.phoneNumber = element[i];
                    break;
                case 5:
                    recipient.address = element[i];
                    break;
                case 6:
                    recipient.email = element[i];
                    break;
                }
            }
            if (rowNumber > 0)
            {
                numberOfRecipients++;
                recipients.push_back(recipient);
                rowNumber++;
            }
        }
        getline(file,row);
        file.close();
    }
    else
    {
        file.open ("KsiazkaAdresowa.txt", ios::out);
        file.close();
        cout << "Nie udalo sie otworzyc pliku!" << endl;
    }
    lastRecipientInFile = recipients.size();

    if (numberOfRecipients == 0)
    {
        return numberOfRecipients;
    }
    else if (numberOfRecipients == recipients[lastRecipientInFile - 1].id)
    {
        return numberOfRecipients;
    }
    else if (numberOfRecipients != recipients[lastRecipientInFile - 1].id)
    {
        return recipients[lastRecipientInFile - 1].id;
    }
    else
    {
        return 0;
    }
}
void displayRecipient (vector <Recipient> & recipients, int i, int idZalogowanegoUzytkownika)
{
    cout << recipients[i].id << "|" << recipients[i].idZalogowanegoUzytkownika << "|" << recipients[i].name << "|" << recipients[i].surname << "|" << recipients[i].phoneNumber << "|" << recipients[i].address << "|" << recipients[i].email << "|" << endl;
}

void searchByName (vector <Recipient> & recipients, int idZalogowanegoUzytkownika)
{
    int numberOfRecipients = recipients.size();
    string name;
    int numberOfRecipientOccurance = 0;
    cout << "Podaj imie, ktore chcesz wyszukac: ";
    cin.sync();
    cin >> name;
    cin.sync();
    for (int i = 0; i < numberOfRecipients; i++)
    {
        if(recipients[i].name == name)
        {
            numberOfRecipientOccurance++;
        }
    }
    if (numberOfRecipientOccurance >0)
    {
        cout << endl << "Wyniki wyszukiwania: " << endl;
        for (int i = 0; i < numberOfRecipients; i++)
        {
            if(recipients[i].name == name)
            {
                displayRecipient (recipients, i, idZalogowanegoUzytkownika);
            }
        }
    }
    else
    {
        cout << endl << "Brak adresata o podanym imieniu w ksiazce adresowej" << endl;
    }
    getch();
}

void searchBySurname (vector <Recipient> & recipients, int idZalogowanegoUzytkownika)
{
    int numberOfRecipients = recipients.size();
    string surname;
    int numberOfRecipientOccurance = 0;
    cout << "Podaj nazwisko, ktore chcesz wyszukac: ";
    cin.sync();
    cin >> surname;
    cin.sync();
    for (int i = 0; i < numberOfRecipients; i++)
    {
        if(recipients[i].surname == surname)
        {
            numberOfRecipientOccurance++;
        }
    }
    if (numberOfRecipientOccurance > 0)
    {
        cout << endl << "Wyniki wyszukiwania: " << endl;
        for (int i = 0; i < numberOfRecipients; i++)
        {
            if(recipients[i].surname == surname)
            {
                displayRecipient (recipients, i, idZalogowanegoUzytkownika);
            }
        }
    }
    else
    {
        cout << endl << "Brak adresata o podanym nazwisku w ksiazce adresowej" << endl;
    }
    getch();
}

void displayFullAddressBook(vector <Recipient> & recipients, int idZalogowanegoUzytkownika)
{
    int numberOfRecipients = recipients.size();
    cout << "Ksiazka adresowa: " << endl<<endl;
    for (int i = 0; i < numberOfRecipients; i++)
    {
        displayRecipient (recipients, i, idZalogowanegoUzytkownika);
    }
    getch();
}

int removeRecipientFromAddressBook (vector <Recipient> & recipients, int idZalogowanegoUzytkownika)
{
    int numberOfContacts = recipients.size();
    int id;
    int numberOfRecipientOccurance = 0;
    cout << "Podaj id adresata, ktorego chcesz usunac: " << endl;
    cin >> id;
    char letter;

    for (int i = 0; i < numberOfContacts; i++)
    {
        if (recipients[i].id == id)
        {
            numberOfRecipientOccurance++;
            cout << "Potwierdz usuniecie adresata:  " << endl << endl;
            displayRecipient (recipients, i, idZalogowanegoUzytkownika);
            cout << "ze swojej listy znajomych poprzez nacisniecie 't' " << endl;
            cin >> letter;
            if (letter == 't')
            {
                recipients.erase( recipients.begin() + i);
                numberOfContacts = recipients.size();
            }
        }
    }
    if(numberOfRecipientOccurance<=0)
    {
        cout << endl << "Nie ma adresata o podanym id." << endl;
        getch();
    }
    else if (numberOfContacts >= 1)
    {
        cout << endl << "Aktualna lista adresatow wyglada nastepujaco: " << endl;
        for (int i = 0; i < numberOfContacts; i++)
        {
            displayRecipient (recipients, i, idZalogowanegoUzytkownika);
        }
        refreshDataInFile (recipients);
        getch();
    }
    else
    {
        cout << endl << "Aktualnie lista adresatow jest pusta" << endl;
        getch();
    }
    return numberOfContacts;
}

void editRecipientName(vector <Recipient> & recipients, int recipientId, int idZalogowanegoUzytkownika)
{
    int numberOfContacts = recipients.size();
    for( int i = 0; i < numberOfContacts; i++ )
    {
        if (recipients[i].id == recipientId)
        {
            cout << "Zmien imie adresata:  " << endl;
            cin >> recipients[ i ].name;
            cout << endl << "Dane adresata po edycji: " << endl;
            displayRecipient (recipients, i, idZalogowanegoUzytkownika);
        }
    }
    refreshDataInFile (recipients);
    getch();
}
void editRecipientSurname(vector <Recipient> & recipients, int recipientId, int idZalogowanegoUzytkownika)
{
    int numberOfContacts = recipients.size();
    for( int i = 0; i < numberOfContacts; i++ )
    {
        if(recipients[i].id == recipientId)
        {
            cout << "Zmien nazwisko adresata:  " << endl;
            cin >> recipients[ i ].surname;
            cout << endl << "Dane adresata po edycji: " << endl;
            displayRecipient (recipients, i, idZalogowanegoUzytkownika);
        }
    }
    refreshDataInFile (recipients);
    getch();
}

void editRecipientPhoneNumber(vector <Recipient> & recipients, int recipientId, int idZalogowanegoUzytkownika)
{
    int numberOfContacts = recipients.size();
    for( int i = 0; i < numberOfContacts; i++ )
    {
        if(recipients[i].id == recipientId)
        {
            cout << "Zmien numer telefonu adresata:  " << endl;
            cin.sync();
            getline(cin, recipients[ i ].phoneNumber);
            cout << endl << "Dane adresata po edycji: " << endl;
            displayRecipient (recipients, i, idZalogowanegoUzytkownika);
        }
    }
    refreshDataInFile (recipients);
    getch();
}

void editRecipientAddress(vector <Recipient> & recipients, int recipientId, int idZalogowanegoUzytkownika)
{
    int numberOfContacts = recipients.size();
    for( int i = 0; i < numberOfContacts; i++ )
    {
        if(recipients[i].id == recipientId)
        {
            cout << "Zmien adres adresata:  " << endl;
            cin.sync();
            getline(cin, recipients[ i ].address);
            cout << endl << "Dane adresata po edycji: " << endl;
            displayRecipient (recipients, i, idZalogowanegoUzytkownika);
        }
    }
    refreshDataInFile (recipients);
    getch();
}
void editRecipientEmail(vector <Recipient> & recipients, int recipientId, int idZalogowanegoUzytkownika)
{
    int numberOfContacts = recipients.size();
    for( int i = 0; i < numberOfContacts; i++ )
    {
        if(recipients[i].id == recipientId)
        {
            cout << "Zmien email adresata:  " << endl;
            cin >> recipients[ i ].email;
            cout << endl << "Dane adresata po edycji: " << endl;
            displayRecipient (recipients, i, idZalogowanegoUzytkownika);
        }
    }
    refreshDataInFile (recipients);
    getch();
}
void editMenu(vector <Recipient> & recipients, int idZalogowanegoUzytkownika)
{
    char editingType;
    int recipientId;
    int numberOfRecipientOccurance = 0;
    int numberOfRecipients = recipients.size();
    if (numberOfRecipients > 0)
    {
        cout << "Podaj id adresata: ";
        cin >> recipientId;
        do
        {
            for(int i = 0; i < numberOfRecipients; i++ )
            {
                if(recipientId == recipients[i].id)
                {
                    numberOfRecipientOccurance++;
                    system ("cls");
                    cout << "=====================" << endl;
                    cout << "Wybierz dane do edycji:" << endl;
                    cout << "=====================" << endl;
                    cout << "1 - imie" << endl;
                    cout << "2 - nazwisko" << endl;
                    cout << "3 - numer telefonu" << endl;
                    cout << "4 - adres" << endl;
                    cout << "5 - email" << endl;
                    cout << "6 - powrot do menu" << endl;
                    cout << "Twoj wybor: ";
                    cin >> editingType;
                    system ("cls");
                    switch (editingType)
                    {
                    case '1':
                        editRecipientName(recipients, recipientId, idZalogowanegoUzytkownika);
                        break;
                    case '2':
                        editRecipientSurname(recipients, recipientId, idZalogowanegoUzytkownika);
                        break;
                    case '3':
                        editRecipientPhoneNumber(recipients, recipientId, idZalogowanegoUzytkownika);
                        break;
                    case '4':
                        editRecipientAddress(recipients, recipientId, idZalogowanegoUzytkownika);
                        break;
                    case '5':
                        editRecipientEmail(recipients, recipientId, idZalogowanegoUzytkownika);
                        break;
                    case '6':
                        mainMenu (recipients, idZalogowanegoUzytkownika);
                        break;
                    default:
                        cout << "Nie ma takiej opcji w menu!" << endl;
                        getch();
                        break;
                    }
                }
            }
            if (numberOfRecipientOccurance <= 0)
            {
                cout << "Nie ma adresata o podanym id.";
                getch();
                break;
            }
        }
        while (1);
    }
    else
    {
        cout<<"Ksiazka adresowa jest pusta. Dodaj adresatow, by moc ich edytowac" << endl;
        getch();
    }
}
void startMenu(vector <Uzytkownik> & uzytkownicy)
{
    int idZalogowanegoUzytkownika;
    int usersCount = uzytkownicy.size();
    char wybor;
    vector <Recipient> recipients;
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
            mainMenu (recipients, idZalogowanegoUzytkownika);
        }
    }
}
void mainMenu (vector <Recipient> & recipients, int idZalogowanegoUzytkownika)
{
    Recipient recipient;
    int numberOfRecipients = 0;
   numberOfRecipients = readDataFromAddressBook(recipients);
   //int numberOfRecipients = recipients.size();
    char menuSelection;
    while (1)
    {
        system ("cls");
        cout << "=================" << endl;
        cout << "KSIAZKA ADRESOWA" << endl;
        cout << "=================" << endl;
        cout << "1. Dodaj adresata" << endl;
        cout << "2. Wyszukaj po imieniu" << endl;
        cout << "3. Wyszukaj po nazwisku" << endl;
        cout << "4. Wyswietl wszystkich adresatow" << endl;
        cout << "5. Usun adresata" << endl;
        cout << "6. Edytuj adresata" << endl;
        cout << "7. Zmien haslo" << endl;
        cout << "9. Wyloguj sie" << endl;
        cout << "Twoj wybor: ";
        cin >> menuSelection;
        system ("cls");
        switch (menuSelection)
        {
       case '1':
            numberOfRecipients =  addNewRecipientToAddressBook (recipients, idZalogowanegoUzytkownika);
            break;
        case '2':
            if (numberOfRecipients>0)
               searchByName (recipients, idZalogowanegoUzytkownika);
            else
            {
                cout << "Ksiazka adresowa jest pusta. Dodaj adresatow, by moc ich wyszukiwac" << endl;
                getch();
            }
            break;
        case '3':
            if (numberOfRecipients>0)
              searchBySurname(recipients, idZalogowanegoUzytkownika);
            else
            {
                cout << "Ksiazka adresowa jest pusta. Dodaj adresatow, by moc ich wyszukiwac" << endl;
                getch();
            }
            break;
        case '4':
            if (numberOfRecipients>0)
                displayFullAddressBook(recipients, idZalogowanegoUzytkownika);
            else
            {
                cout << "Ksiazka adresowa jest pusta. Dodaj adresatow, by moc ich wyswietlac" << endl;
                getch();
            }
            break;
        case '5':
            if (numberOfRecipients > 0)
                numberOfRecipients = removeRecipientFromAddressBook(recipients, idZalogowanegoUzytkownika);
            else
            {
                cout << "Ksiazka adresowa jest pusta. Dodaj adresatow" << endl;
                getch();
            }
            break;
        case '6':
            editMenu(recipients, idZalogowanegoUzytkownika);
            break;
        case '7':
            zmianaHasla (uzytkownicy, idZalogowanegoUzytkownika);
            break;
        case '9':
            system ( "cls" );
              idZalogowanegoUzytkownika = 0;
            cout << "Zostales wylogowany"<< endl;
            exit(0);
        default:
            cout << "Nie ma takiej opcji w menu!"<< endl;
            getch();
            break;
        }
    }
}

int main()
{
    vector <Uzytkownik> uzytkownicy;
    vector <Recipient> recipients;
    Uzytkownik uzytkownik;
    int idZalogowanegoUzytkownika = 0;
    int usersCount = 0;
    usersCount = readDataFromUsersBook (uzytkownicy);
    startMenu(uzytkownicy);
    return 0;
}
