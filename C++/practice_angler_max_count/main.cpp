#include <iostream>
#include "../library/stringstreamenumerator.hpp"
#include "../library/seqinfileenumerator.hpp"
#include "../library/summation.hpp"
#include "../library/linsearch.hpp"
#include "../library/maxsearch.hpp"
#include "../library/counting.hpp"

using namespace std;

//Ide j�n a v�geredm�ny
struct Horgasz
{
    string name;
    int count;
};

//Ezen kereszt�l
struct Szamol
{
    string faj;
    int meret;
};

//EXTRA
istream& operator>>(istream& inp, Szamol &s)
{
    return inp>>s.faj>>s.meret;
}
ostream& operator<<(ostream& inp, const Szamol &s)
{
    cout << "faj: "<< s.faj << " meret: "<< s.meret <<endl;
    return inp;
}
//T�tel v�grehajt�sa a k�ztes struct-on
class CuntHal : public Counting<Szamol>
{
protected:
    bool cond(const Szamol &e) const override
    {
//        cout << e << endl;
        return true;
    };
};

//Beolvas�s
istream& operator>>(istream& inp, Horgasz &s)
{
    string line;
    getline(inp, line);
    stringstream is(line);
    is >> s.name;

    CuntHal pr;
    StringStreamEnumerator<Szamol> enor(is);
    pr.addEnumerator(&enor);
    pr.run();
    s.count = pr.result();
    return inp;
}

//Progt�tel sz�ks�g eset�n, mainbe
class List : public MaxSearch<Horgasz, int, Greater<int>>
{
protected:
    int func(const Horgasz& e) const override
    {
        return e.count;
    }
};


int main(int argc, char* argv[])
{
    string fname = argc>1 ? argv[1] : "input.txt";
    List p;
    SeqInFileEnumerator<Horgasz> enor(fname);
    p.addEnumerator(&enor);
    p.run();
    cout << p.optElem().name << " " << p.optElem().count << endl;



    return 0;
}
