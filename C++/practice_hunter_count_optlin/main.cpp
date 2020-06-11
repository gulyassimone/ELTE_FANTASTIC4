#include <iostream>
#include "../library/stringstreamenumerator.hpp"
#include "../library/seqinfileenumerator.hpp"
#include "../library/summation.hpp"
#include "../library/linsearch.hpp"
#include "../library/maxsearch.hpp"
#include "../library/counting.hpp"

using namespace std;

//Ide j�n a v�geredm�ny
struct Vadasz
{
    string _name;
    bool _hunted;
};

//Ezen kereszt�l
struct Vad
{
    string _faj;
    double _meret;
};

//EXTRA
istream& operator>>(istream& inp, Vad &s)
{
    return inp>>s._faj>>s._meret;
}

//T�tel v�grehajt�sa a k�ztes struct-on - BEOLVAS�SN�L
//LinSearch
class Renszarvas : public LinSearch<Vad, true>
{
protected:
    bool cond(const Vad& e)const override
    {
        return e._faj=="r�nszarvas";
    }
};

//Beolvas�s
istream& operator>>(istream& inp, Vadasz &s)
{
    string line;
    getline(inp, line);
    stringstream is(line);
    is >> s._name;
    Renszarvas pr;
    StringStreamEnumerator<Vad> enor(is);
    pr.addEnumerator(&enor);
    pr.run();
    s._hunted=pr.found();



    return inp;
}

class List : public Counting<Vadasz>
{
protected:
    void first() override {};
    bool cond(const Vadasz &e) const override {
        //cout << e._hunted<<endl;
        return e._hunted==true;};
};

int main(int argc, char* argv[])
{
    string fname = argc>1 ? argv[1] : "input.txt";
    List p;
    SeqInFileEnumerator<Vadasz> enor(fname);
    p.addEnumerator(&enor);
    p.run();
    if(p.result()>0)
    {
        cout << p.result()<<endl;
    }
    else
    {
        cout << "NINCS"<<endl;
    }
    return 0;
}
