#include "NumberWithUnits.hpp"
#include <iostream>
#include <fstream>
#include <map>
#include <algorithm>
using namespace std;

namespace ariel
{
    const double CON = 0.001;

    static map<string, map<string, double>> MY_LIST;

    NumberWithUnits::NumberWithUnits(double MY_number, const string &unit)
    {
        if (MY_LIST.count(unit) != 0) 
        {
            this->MY_number = MY_number;
            this->unit = unit;
        }else{
        throw invalid_argument("Error");
        }
    }

    void helpfum(string &F11,string &S1)
    {
        for (auto &i : MY_LIST[F11])
        {
            for (auto &j : MY_LIST[S1])
            {
                double convertRatio = MY_LIST[i.first][F11] * MY_LIST[F11][S1] * MY_LIST[S1][j.first];
                MY_LIST[i.first][j.first] = convertRatio;
                MY_LIST[j.first][i.first] = 1 / MY_LIST[i.first][j.first];
            }
        }
    }

    void NumberWithUnits::read_units(ifstream &FILE)
    {
        string F1;
        string S1;
        string T; 
        double FV = 0;
        double SV = 0;

        while (FILE >> FV >> F1 >> T >> SV >> S1)
        {
            MY_LIST[F1][S1] = SV;
            MY_LIST[F1][F1] = 1;
            MY_LIST[S1][F1] = 1 / SV;
            MY_LIST[S1][S1] = 1;

            helpfum(F1, S1);
        }
    }

    double CHANGU(const string &src, const string &dst, const double &MY_number)
    {
        if (MY_LIST.at(src).count(dst) != 0)
        {
            if (src == dst)
            {
                return MY_number;
            }
            return MY_number * MY_LIST[src][dst];
        }
        else{
        throw invalid_argument("Error");
        }
    }

    NumberWithUnits NumberWithUnits::operator+() const
    {
        NumberWithUnits SUB{this->MY_number, this->unit};
        return SUB;
    }

    NumberWithUnits NumberWithUnits::operator+(const NumberWithUnits &N) const
    {
        double C = CHANGU(N.unit, this->unit, N.MY_number);
        NumberWithUnits SUB{this->MY_number+C, this->unit};
        return SUB;
    }

    NumberWithUnits &NumberWithUnits::operator+=(const NumberWithUnits &N)
    {
        double C = CHANGU(N.unit, this->unit, N.MY_number);
        this->MY_number += C;
        return *this;
    }
    NumberWithUnits NumberWithUnits::operator-() const
    {
        NumberWithUnits SUB(-1*this->MY_number, this->unit);
        return SUB;
    }
    NumberWithUnits NumberWithUnits::operator-(const NumberWithUnits &N) const
    {
        double C = CHANGU(N.unit, this->unit, N.MY_number);
        NumberWithUnits SUB(this->MY_number - C, this->unit);
        return SUB;
    }
    NumberWithUnits &NumberWithUnits::operator-=(const NumberWithUnits &N)
    {
        double C = CHANGU(N.unit, this->unit, N.MY_number);
        this->MY_number -= C;
        return *this;
    }


    bool NumberWithUnits::operator<(const NumberWithUnits &N) const
    {
        double C = CHANGU(N.unit, this->unit, N.MY_number);
        return this->MY_number<C;
    }

    bool NumberWithUnits::operator<=(const NumberWithUnits &N) const
    {
        return !(*this>N);
    }

    bool NumberWithUnits::operator>(const NumberWithUnits &N) const
    {
        double C = CHANGU(N.unit, this->unit, N.MY_number);
        return this->MY_number>C;
    }

    bool NumberWithUnits::operator>=(const NumberWithUnits &N) const
    {
         return !(*this<N);
    }

    bool NumberWithUnits::operator==(const NumberWithUnits &N) const
    {
        double C = CHANGU(N.unit, this->unit, N.MY_number);
        double x=this->MY_number-C;
        return (x>=(-1*CON)&& x<=CON);
    }

    bool NumberWithUnits::operator!=(const NumberWithUnits &N) const
    {
        return !(*this==N);
    }

    NumberWithUnits &NumberWithUnits::operator++()
    {
        this->MY_number++;
        return *this;
    }

    NumberWithUnits NumberWithUnits::operator++(int)
    {
        NumberWithUnits SUB = *this;
        this->MY_number++;
        return SUB;
    }

    NumberWithUnits &NumberWithUnits::operator--()
    {
        this->MY_number--;
        return *this;
    }

    NumberWithUnits NumberWithUnits::operator--(int)
    {
        NumberWithUnits SUB = *this;
        this->MY_number--;
        return SUB;
    }

    NumberWithUnits operator*(const double &O, const NumberWithUnits &N)
    {
        NumberWithUnits SUB{N.MY_number * O, N.unit};
        return SUB;
    }

    NumberWithUnits NumberWithUnits::operator*(const double &N) const
    {
        NumberWithUnits SUB(this->MY_number * N, this->unit);
        return SUB;
    }

    ostream &operator<<(ostream &o, const NumberWithUnits &n)
    {
        return o << n.MY_number << "[" << n.unit << "]";
    }

    istream &operator>>(istream &is, NumberWithUnits &num)
    {
        double V=0;
        std::string UN;
        char c=' ';
        is >> V;
        is >> c ;
        while(c!=']'){
            if(c!='['){
                UN.insert(UN.end(),c);
            }
            is>>c;
        }
       if(MY_LIST[UN].empty()){throw invalid_argument{"ERROR"};};
        num.MY_number=V;
        num.unit=UN;
        return is;
    }
}