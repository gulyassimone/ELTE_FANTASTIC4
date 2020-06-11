
#include <iostream>
#include "../library/stringstreamenumerator.hpp"
#include "../library/seqinfileenumerator.hpp"
#include "../library/summation.hpp"
#include "../library/linsearch.hpp"
#include "../library/maxsearch.hpp"
#include "../library/counting.hpp"


 using namespace std;

struct Horgasz
{
    string name;
    bool count;
};
//Ezen keresztül
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
    return inp << "faj: " <<s.faj << "meret: " <<s.meret;
}


//Tétel végrehajtása a köztes struct-on
class CuntHal : public Counting<Szamol>
{
protected:
    void first() override {};
    bool cond(const Szamol &e) const override {cout << e << endl; return true;};

};

//Beolvasás
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

//Progtétel szükség esetén, mainbe
class MaxHal : public MaxSearch<Horgasz,int>
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
    MaxHal p;
    SeqInFileEnumerator<Horgasz> enor(fname);
    p.addEnumerator(&enor);
    p.run();
    cout << p.optElem().name << p.optElem().count << endl;


    return 0;
}

