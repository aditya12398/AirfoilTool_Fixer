#include<fstream>
#include<iostream>
#include<string>

using namespace std;
int main()
{
    int l;
    string name, outname;
    double x, y;
    cout << "Enter the filename with extension: ";
    cin >> name;
    ifstream infile(name);
    outname = "fixed_" + name;
    ofstream outfile(outname);
    while(infile)
    {
        infile >> x >> y;
        outfile << x << "\t" << y <<"\t 0\n";
    }
    return 0;
}