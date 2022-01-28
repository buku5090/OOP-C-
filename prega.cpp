#include<cstring>
#include<string>
#include<iostream>
#include<sstream>
#include<algorithm>
#include<math.h>
#include<fstream>
#include <list>
#include <iterator>
#pragma warning (disable: 4996)
using namespace std;

ifstream f("ECUATII.txt");
ofstream g("REZULTATE.txt");

class Calculator {
protected:
    char* marca;
public:
    Calculator() {
        this->marca = NULL;
    }
    Calculator(char* m)
    {
        this->marca = new char[strlen(m) + 1];
        strcpy(this->marca, m);
    }

    virtual void afisare_mesaj_prim()
    {
        cout << "Mesaj prim - baza" << endl;
    }
    virtual void afisare_mesaj_secund()
    {
        cout << "Mesaj secund - baza" << endl;
    }

    Calculator(const Calculator& calc)
    {
        this->marca = new char[strlen(calc.marca) + 1];
        strcpy(this->marca, calc.marca);
    }

 

    char* getMarca()
    {
        return this->marca;
    }

    void setMarca(char* m)
    {
        this->marca = new char[strlen(m) + 1];
        strcpy(this->marca, m);
    }

    ~Calculator()
    {
        delete[] marca;
    }

    friend ostream& operator<<(ostream& os, const Calculator& calc);
    friend istream& operator>>(istream& is, const Calculator& calc);

    friend bool operator==(const Calculator& c1, const Calculator& c2);
    friend bool operator>=(const Calculator& c1, const Calculator& c2);
};

bool operator==(Calculator& c1, Calculator& c2)
{
    if (strcmp(c1.getMarca(), c2.getMarca()) == 0)
        return 1;
    return 0;
}

bool operator>=(Calculator& c1, Calculator& c2)
{
    if (strcmp(c1.getMarca(), c2.getMarca()) >= 0)
        return 1;
    return 0;
}

istream& operator>>(istream& is, Calculator& calc)
{
    cout << "Introduceti marca calculatorului: ";
    char* m = new char[100];
    cin >> m;
    calc.setMarca(m);

    return is;
}
ostream& operator<<(ostream& os, Calculator& calc)
{
    cout << "Calculatorul este de marca '" << calc.getMarca() << "'" << endl;
    return os;
}


class CalculatorStiintific :public Calculator {
private:
    double* rezultate_anterioare;
    int nr_rezultate;
    static string tip_calculator;
public:

    void afisare_mesaj_prim()
    {
        cout << "Mesaj prim - derivata" << endl;
    }
    void afisare_mesaj_secund()
    {
        cout << "Mesaj secund - derivata" << endl;
    }

    double* getRezultateAnterioare()
    {
        return this->rezultate_anterioare;
    }

    int getNrRezultate()
    {
        return this->nr_rezultate;
    }

    void setTip(string tip)
    {
        tip_calculator = tip;
    }

    string getTip()
    {
        return tip_calculator;
    }

    void setRezultateAnterioare(double* ra, int nr)
    {
        this->nr_rezultate = nr;
        this->rezultate_anterioare = new double[nr];
        for (int i = 0; i < nr; i++)
            this->rezultate_anterioare[i] = ra[i];
    }

    CalculatorStiintific()
    {
        this->rezultate_anterioare = NULL;
        this->nr_rezultate = 0;
    }
    CalculatorStiintific(double* rezultate_ant, int nr_rez)
    {
        this->nr_rezultate = nr_rez;
        if (nr_rez > 0)
        {
            this->nr_rezultate = nr_rez;
            this->rezultate_anterioare = new double[nr_rezultate];
            for (int i = 0; i < nr_rez; i++)
            {
                this->rezultate_anterioare[i] = rezultate_ant[i];
            }
        }
        else
            rezultate_anterioare = NULL;

    }

    CalculatorStiintific(const CalculatorStiintific& cs)
    {
        this->nr_rezultate = cs.nr_rezultate;
        if (cs.nr_rezultate > 0)
        {
            this->nr_rezultate = cs.nr_rezultate;
            this->rezultate_anterioare = new double[cs.nr_rezultate];
            for (int i = 0; i < cs.nr_rezultate; i++)
            {
                this->rezultate_anterioare[i] = cs.rezultate_anterioare[i];
            }
        }
        else
            this->rezultate_anterioare = NULL;
    }

    ~CalculatorStiintific()
    {
        delete[] rezultate_anterioare;
    }

    friend ostream& operator<<(ostream& os, const CalculatorStiintific& cs);
    friend istream& operator>>(istream& is, const CalculatorStiintific& cs);

    friend CalculatorStiintific operator++(
        const CalculatorStiintific& cs1, int nr);
    friend CalculatorStiintific operator--(
        const CalculatorStiintific& cs1, int nr);
};
CalculatorStiintific operator++(
    CalculatorStiintific& cs1, int nr)
{
    double* aux = new double;
    aux = cs1.getRezultateAnterioare();
    aux[cs1.getNrRezultate()] = 1;
    cs1.setRezultateAnterioare(aux, cs1.getNrRezultate() + 1);

    return cs1;
}

CalculatorStiintific operator--(
    CalculatorStiintific& cs1, int nr)
{
    double* aux = new double;
    aux = cs1.getRezultateAnterioare();
    cs1.setRezultateAnterioare(aux, cs1.getNrRezultate() - 1);

    return cs1;
}
ostream& operator<<(ostream& os, const CalculatorStiintific& cs)
{
    cout << "Tipul calcultorului este " << CalculatorStiintific::tip_calculator << " si are " << cs.nr_rezultate << " rezultate stocate" << endl;
    for (int i = 0; i < cs.nr_rezultate; i++)
    {
        cout << "Rezultat " << i + 1 << ": " << cs.rezultate_anterioare[i] << endl;
    }

    return os;
}
istream& operator>>(istream& is, CalculatorStiintific& cs)
{
    cout << "Introduceti numarul de rezultate: ";
    int aux;
    cin >> aux;
    double* v_aux = new double[aux];
    for (int i = 0; i < aux; i++)
    {
        cout << "Rezultatul " << i + 1 << ": ";
        cin >> v_aux[i];
    }

    cs.setRezultateAnterioare(v_aux, aux);
    return is;
}
string CalculatorStiintific::tip_calculator = "stiintific";

class Ecuatie {
private:
    const double pi;
    string ecuatie_s;
public:

    virtual void afisare_mesaj_ecuatie_1()
    {
        cout << "Baza - Ecuatia este " << ecuatie_s << endl;
    }

    virtual void afisare_mesaj_ecuatie_2()
    {
        cout << "Baza - apel functie mesaj"<< endl;
    }

    Ecuatie() :pi(3.14)
    {
        this->ecuatie_s = "";
    }
    Ecuatie(string e, string aux) :pi(3.14)
    {
        this->ecuatie_s = e;
    }
    double getpi()const {
        return pi;
    }
    string getEcuatie()
    {
        return this->ecuatie_s;
    }

    void setEcuatie(string s)
    {
        this->ecuatie_s = s;
    }
    void transforma_din_patrata_in_rotunda() {// (2-2)+4 -> 0 + 4 -> 4
        int aux_poz_patrat = 0;
        int i, ok = -1, poz_doi_patrat = 0;

        if (ecuatie_s.find("[") >= 0)
        {
            aux_poz_patrat = int(ecuatie_s.find("["));
            for (i = aux_poz_patrat; i < ecuatie_s.length(); i++)
            {
                if (ecuatie_s[i] == ']')
                {
                    ok = 0;
                    poz_doi_patrat = i;
                    break;
                }
                if (ecuatie_s[i] == '(')
                {
                    ok = 1;
                    break;
                }
            }
            if (ok == 0)
            {
                ecuatie_s[aux_poz_patrat] = '(';
                ecuatie_s[poz_doi_patrat] = ')';
            }
        }
    }

    string sterge_spatii()
    {
        ecuatie_s.erase(remove(ecuatie_s.begin(),
            ecuatie_s.end(), ' '), ecuatie_s.end());
        return ecuatie_s;
        //1 +              1 ->1+1
    }

    int cauta_paranteze()
    {
        int a = int(ecuatie_s.find(")"));//imi gaseste primul calcul de realizat in paranteze
        //daca am 4*((1+2)-(3+4)), vreau sa imi gaseasca 1+2
        // 4*(3-(3+4)) -> 4*(3-7) -> 4*-4 -> -16
        int i, poz1=0;
        double rez = 0;
        string aux = "", rez_str="";
        if (a > 0)
        {
            string aux_s = "";
            for (i = a-1; i > 0; i--)
            {
                if (ecuatie_s[i] != '(')
                {
                    aux = ecuatie_s[i] + aux;
                }
                else
                {
                    poz1 = i;
                    break;
                    
                }//nu mai are sens sa mergem, luam ce avem in paranteze
                //si prelucram, dupa care intoarcem rezultatul in ecuatia-mama
            }
            rez = rezolva_gr0(aux);
            rez_str = to_string(rez);
            ecuatie_s.replace(poz1, 2 + aux.length(), rez_str);


            return 1;
        }
        return 0;
    }
    
    double rezolva_gr0(string ecuatie_aux)//1+1
    {
        string aux = "";
        double numere[100];
        numere[0] = 0;
        char caractere[100];
        int i, j, x = 0, k = 0;
        double rezultat = 0, nr;

        for (i = 0; i < ecuatie_aux.length(); i++)
        {//11.1+1+2
            if (isdigit(ecuatie_aux[i]))
            {
                j = i;
                while (isdigit(ecuatie_aux[j]) || ecuatie_aux[j] == '.')
                {
                    aux = aux + ecuatie_aux[j];//11.1
                    j++;
                }
                i = j;
                stringstream stringToChar(aux);
                stringToChar >> nr;
                numere[x] = nr;//11.1
                x++;
                aux = "";
            }
            //1+2+3+4
            //nr = 1,2,3,4
            //carac = +, +, +
            if (ecuatie_aux[i] == '#')
            {
                caractere[k] = '#';
                k++;
            }

            if (ecuatie_aux[i] == '^')
            {
                caractere[k] = '^';
                k++;
            }

            if (ecuatie_aux[i] == '*' && ecuatie_aux[i+1]=='-')
            {
                caractere[k] = '*';
                numere[k] = -numere[k];
                k++;
                i++;
                
            }
            else if (ecuatie_aux[i] == '*')
            {
                caractere[k] = '*';
                k++;
            }
            if (ecuatie_aux[i] == '/' && ecuatie_aux[i + 1] == '-')
            {
                caractere[k] = '/';
                numere[k] = -numere[k];
                k++;
                i++;

            }
            else if (ecuatie_aux[i] == '/')
            {
                caractere[k] = '/';
                k++;
            }
            if (ecuatie_aux[i] == '+' && ecuatie_aux[i+1]=='-')
            {
                caractere[k] = '-';
                k++;
                i++;
            }
            else if (ecuatie_aux[i] == '+')
            {
                caractere[k] = '+';
                k++;
            }
            if (ecuatie_aux[i] == '-' && ecuatie_aux[i + 1] == '-')
            {
                caractere[k] = '+';
                k++;
                i++;
            }
            else if (ecuatie_aux[i] == '-' && i != 0 && ecuatie_aux[i-1] != '+' && ecuatie_aux[i - 1] != '*' && ecuatie_aux[i - 1] != '/' )
            {
                caractere[k] = '-';
                k++;
            }
        }

        double aux_nr_inm = 0;
        int z = 0;
        //mai intai realizam operatiile * si /, astfel ca mai intai le vom preluca pe ele
        //ca poate sa fie prelucrate operatiile + si -, o sa inlocuim valorile obtinute din * si / in 
        //vectorul nostru, astfel incat sa ramanem doar cu operatii simple de + si -.

        for (i = 0; i < k; i++)
        {
            if (caractere[i] == '#')
            {
                aux_nr_inm = pow(numere[i], 1.0/numere[i + 1]);

                for (j = i; j < x - 1; j++)
                {
                    numere[j] = numere[j + 1];
                }
                numere[i] = aux_nr_inm;//modificam vectorul de numere. inlocuim cele 2 valori cu produsul lor.

                for (j = i; j < k - 1; j++)
                {
                    caractere[j] = caractere[j + 1];//scoatem caracterul si din vectorul de caractere
                }
                k--;//scad nr de elemente din vec de caractere
                i--;//raman pe aceeasi pozitie, pt ca la for o sa imi adauge 1
                x--;//am scazut nr de elemente din numere, pt ca am scos un element.
            }
            //1+2#2+2^4 + 8*2
            //+ + +
            if (caractere[i] == '^')
            {
                aux_nr_inm = pow(numere[i], numere[i + 1]);

                for (j = i; j < x - 1; j++)
                {
                    numere[j] = numere[j + 1];
                }
                numere[i] = aux_nr_inm;//modificam vectorul de numere. inlocuim cele 2 valori cu produsul lor.

                for (j = i; j < k - 1; j++)
                {
                    caractere[j] = caractere[j + 1];//scoatem caracterul si din vectorul de caractere
                }
                k--;//scad nr de elemente din vec de caractere
                x--;//am scazut nr de elemente din numere, pt ca am scos un element.
                i--;//raman pe aceeasi pozitie, pt ca la for o sa imi adauge 1
            }

        }

        for (i = 0; i < k; i++)
        {
            if (caractere[i] == '*')
            {
                aux_nr_inm = numere[i] * numere[i + 1];

                for (j = i; j < x - 1; j++)
                {
                    numere[j] = numere[j + 1];
                }
                numere[i] = aux_nr_inm;//modificam vectorul de numere. inlocuim cele 2 valori cu produsul lor.

                for (j = i; j < k - 1; j++)
                {
                    caractere[j] = caractere[j + 1];//scoatem caracterul si din vectorul de caractere
                }
                k--;//scad nr de elemente din vec de caractere
                x--;//am scazut nr de elemente din numere, pt ca am scos un element.
                i--;//raman pe aceeasi pozitie, pt ca la for o sa imi adauge 1

            }
            if (caractere[i] == '/')//aceeasi chestie, se putea face si fara repetitie de cod totusi
            {
                aux_nr_inm = numere[i] / numere[i + 1];

                for (j = i; j < x - 1; j++)
                {
                    numere[j] = numere[j + 1];
                }
                numere[i] = aux_nr_inm;//modificam vectorul de numere. inlocuim cele 2 valori cu produsul lor.

                for (j = i; j < k - 1; j++)
                {
                    caractere[j] = caractere[j + 1];//scoatem caracterul si din vectorul de caractere
                }
                x--;//scad nr de elemente din vec de caractere
                k--;//am scazut nr de elemente din numere, pt ca am scos un element.
                i--;//raman pe aceeasi pozitie, pt ca la for o sa imi adauge 1
            }
        }

        rezultat = numere[0];
        if (ecuatie_aux[0] == '-')
        {
            rezultat = -numere[0];
        }
        for (i = 0; i < k; i++)
        {
            if (caractere[i] == '+')
            {
                rezultat = rezultat + numere[i + 1];
            }
            if (caractere[i] == '-')
            {
                rezultat = rezultat - numere[i + 1];
            }
        }
        //ecuatie_aux
        return rezultat;
    }

    double rezultat_final()
    {
        sterge_spatii();
        transforma_din_patrata_in_rotunda();
        double nr;

        while (cauta_paranteze() == 1)
        {
            transforma_din_patrata_in_rotunda();
            cauta_paranteze();
        }

        nr = rezolva_gr0(ecuatie_s);

        return nr;
        //1+(2*3) -> 1+6
    }

    friend ostream& operator<<(ostream& os, const Ecuatie& e);
    friend istream& operator>>(istream& is, const Ecuatie& e);

    friend bool operator>(const Ecuatie& e1, const Ecuatie& e2);
    friend bool operator<(const Ecuatie& e1, const Ecuatie& e2);
};

bool operator>(Ecuatie& e1, Ecuatie& e2)
{
    if (e1.rezultat_final() > e2.rezultat_final())
        return true;
    return false;
}
bool operator<(Ecuatie& e1, Ecuatie& e2)
{
    if (e1.rezultat_final() < e2.rezultat_final())
        return true;
    return false;
}

ostream& operator<<(ostream& os, Ecuatie& e)
{

    os << "rezultatul ecuatiei este: " << e.rezultat_final();

    return os;

}
istream& operator>>(istream& is, Ecuatie& e)
{
    string ec_de_la_tastatura;
    cout << "Introduceti o ecuatie: ";
    getline(cin, ec_de_la_tastatura);
    e.setEcuatie(ec_de_la_tastatura);

    return is;
}

class IstoricAbs {//clasa abstracta
protected:
    list <string> istoric_ecuatii;
public:
    virtual void afisare_ecuatii() = 0;
   
    void set_lista_istoric(list <string> g)
    {
        istoric_ecuatii = g;
    }

    void adauga_element_istoric(string g)
    {
        istoric_ecuatii.push_back(g);
    }
};

class Istoric : public IstoricAbs, public Ecuatie {//mostenire multipla
public:
    void afisare_ecuatii()
    {
        string ecuatie_ist;
        list <string> ::iterator it;
        Ecuatie e;
        for (it = istoric_ecuatii.begin(); it != istoric_ecuatii.end(); ++it)
        {
            ecuatie_ist = *it;
            e.setEcuatie(ecuatie_ist);
            cout << ecuatie_ist <<" = "<<e.rezultat_final()<< endl;
        }
        cout << '\n';
    }

    void afisare_mesaj_ecuatie_1()
    {
        cout << "Derivata - apel functie 1 clasa derivata ";
    }

    void afisare_mesaj_ecuatie_2()
    {
        cout << "Baza - apel functie mesaj 2" << endl;
    }
};

void meniu()
{
    unsigned varianta = 20;
    Ecuatie e;
    string ecuatie;
    Istoric i;
    char opt;

    while (varianta != 0)
    {
        
        cout << "1. Procesati ecuatiile din 'probleme.txt'" << endl;//unde le salveaza? in fisier sau afiseaza pe ecran//salvati?
        cout << "2. Introducere ecuatie." << endl;//salvati rez acesteia? -> stl
        cout << "3. Arhiva calculatorului." << endl;
        cout << "4. Calculati cosinus." << endl;//stl
        cout << "5. Calculati sinus." << endl;
        cout << "0. Iesire din meniu." << endl;
        cout << "Introduceti mai jos varianta dorita:" << endl;
        cin >> varianta;
        cin.get();
        switch (varianta) {
        case 1: {
            cout << "Introduceti o ecuatie (exit pentru a iesi): ";
            getline(cin, ecuatie);
            while (ecuatie != "exit")
            {
                e.setEcuatie(ecuatie);
                i.adauga_element_istoric(ecuatie);
                cout << "Pentru '" << ecuatie << "' " << e << endl << endl;
                cout << "Introduceti o ecuatie (exit pentru a iesi): ";
                getline(cin, ecuatie);
            }
            system("cls");
            break;
        }
        case 2: {     
            cout << endl;
            cout << "Afisare in consola sau in fisierul extern 'REZULTATE.TXT' (consola = 'c' si fisier = 'f')?";
            cin >> opt;

            while (f >> ecuatie)
            {
                e.setEcuatie(ecuatie);
                i.adauga_element_istoric(ecuatie);
                if (opt == 'c')
                {
                    cout << "Pentru '" << ecuatie << "' " << e << endl;
                }
                if (opt == 'f')
                {
                    g << "Pentru '" << ecuatie << "' " << e << endl;
                }
            }

            if (opt == 'f')
            {
                cout << "Rezultate scrise in folder-ul 'REZULTATE.txt'!" << endl;
            }
            cout << "Continuati catre meniu?(y/n): ";
            cin >> opt;
            if (opt == 'y')
                system("cls");
            if (opt == 'n')
                varianta = 0;
            break;
        }
        case 3: {
            i.afisare_ecuatii();

            cout << "Continuati catre meniu?(y/n): ";
            cin >> opt;
            if (opt == 'y')
                system("cls");
            if (opt == 'n')
                varianta = 0;
            break;
        }
        case 4: {
            int opt_fct;
            ecuatie = "";
            cout << endl;
            cout << "--- Functii speciale ale calculatorului ---" << endl;
            cout << "1. Teorema lui Pitagora intr-un triunghi dreptunghic, unde stim catetele" << endl;
            cout << "2. Suma primelor n numere folosind Formula lui Gauss" << endl;
            cout << "3. Media geometrica a doua numere" << endl;
            cout << "4. Calculeaza cos." << endl;
            cout << "5. Calculeaza sin." << endl;
            cout << "Alegeti o functie speciala: " << endl;
            cin >> opt_fct;

            if (opt_fct == 1)
            {
                double b, c;
                cout << "Introduceti valoare pentru prima cateta: ";
                cin >> b;
                cout << "Introduceti valoare pentru a doua cateta: ";
                cin >> c;
                ecuatie = "("+to_string(b) + "*" + to_string(b) + "+" + to_string(c) + "*" + to_string(c)+")#2";
                i.adauga_element_istoric(ecuatie);
                cout << "Ipotenuza este: " << sqrt(b * b + c * c) << endl;
            }
            if (opt_fct == 2)
            {
                int n;
                cout << "Introduceti valoare pentru n: ";
                cin >> n;
                ecuatie = to_string(n) + "*(" + to_string(n) + "+1)/2";
                i.adauga_element_istoric(ecuatie);
                cout << "Rezultatul este: " << n * (n + 1) / 2 << endl;
            }
            if (opt_fct == 3)
            {
                int a, b;
                cout << "Introduceti valoarea pentru primul numar: ";
                cin >> a;
                cout << "Introduceti valoarea pentru al doilea numar: ";
                cin >> b;
                ecuatie = "(" + to_string(a) + "*" + to_string(b) + ")#2";
                i.adauga_element_istoric(ecuatie);
                cout << "Rezultatul este " << sqrt(a * b) << endl;
            }
            if (opt_fct == 4)
            {
                double u;
                cout << "Introduceti valoarea unghiului: ";
                cin >> u;
                cout << "Rezultatul este " << cos(u) << endl;
            }
            if (opt_fct == 5)
            {
                double u;
                cout << "Introduceti valoarea unghiului: ";
                cin >> u;
                cout << "Rezultatul este " << sin(u) << endl;
            }

            cout << "Continuati catre meniu?(y/n): ";
            cin >> opt;
            if (opt == 'y')
                system("cls");
            if (opt == 'n')
                varianta = 0;
            break;
        }
        case 5: {
            string a, b;
            double rez_a, rez_b;
            cout << "Introduceti prima ecuatie: ";
            getline(cin, a);
            e.setEcuatie(a);
            i.adauga_element_istoric(a);
            rez_a = e.rezultat_final();
            cout << "Introduceti a doua ecuatie: ";
            getline(cin, b);
            e.setEcuatie(b);
            i.adauga_element_istoric(b);
            rez_b = e.rezultat_final();

            cout << "Rezultatul primei ecuatii este " << rez_a << ", iar celei de-a doua este " << rez_b << endl;
            cout << "Deci, ";
            if (rez_a > rez_b)
            {
                cout << "prima ecuatie este mai mare." << endl;
            }
            if (rez_a < rez_b)
            {
                cout << "prima ecuatie este mai mica." << endl;
            }
            if (rez_a == rez_b)
            {
                cout << "ecuatiile sunt egale." << endl;
            }
            cout << "Continuati catre meniu?(y/n): ";
            cin >> opt;
            if (opt == 'y')
                system("cls");
            if (opt == 'n')
                varianta = 0;
            break;
        }
        }
    }
    
}

int main()
{
    meniu();

    return 0;
}