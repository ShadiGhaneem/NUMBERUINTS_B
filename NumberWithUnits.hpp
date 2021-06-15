#include <string>
#include <map>
using namespace std;

namespace ariel
{
    class NumberWithUnits
    {
    string unit;
    double MY_number;

    public:
        NumberWithUnits(double, const string&);
        static void read_units(ifstream&);

        NumberWithUnits operator-() const; 
        NumberWithUnits operator-(const NumberWithUnits& N) const; 
        NumberWithUnits &operator-=(const NumberWithUnits& N);
        NumberWithUnits operator+() const; 
        NumberWithUnits operator+(const NumberWithUnits& N) const;
        NumberWithUnits &operator+=(const NumberWithUnits& N);

        friend int compare(const NumberWithUnits&, double);
        bool operator<(const NumberWithUnits& N) const;
        bool operator<=(const NumberWithUnits& N) const;
        bool operator>(const NumberWithUnits& N) const;
        bool operator>=(const NumberWithUnits& N) const;
        bool operator==(const NumberWithUnits& N) const;
        bool operator!=(const NumberWithUnits& N) const;

        NumberWithUnits &operator++();
        NumberWithUnits operator++(int); 
        NumberWithUnits &operator--();
        NumberWithUnits operator--(int); 

        friend NumberWithUnits operator*(const double& O, const NumberWithUnits& N);
        NumberWithUnits operator*(const double&) const;
        
        friend ostream &operator<<(ostream& o, const NumberWithUnits& N);
        friend istream &operator>>(istream& o, NumberWithUnits& N);
    };
}