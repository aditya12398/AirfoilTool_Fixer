#include <fstream>
#include <iostream>
#include <string>
#include <cmath>

double x, y, z = 0;
using namespace std;

double trailing_edge_point(string name, int line)
{
    double a1, a2, b1, b2, c1, c2;
    double x_trailing, y_trailing;
    double x_old, y_old, x_new, y_new;
    int count = 1;
    x_old = y_old = -10000;
    ifstream infile(name);
    for (int i = 1; i <= line; i++)
    {
        infile >> x >> y;
        if (x_old == -10000)
        {
            x_new = x_old = x;
            y_new = y_old = y;
        }
        else
        {
            x_old = x_new;
            y_old = y_new;
            x_new = x;
            y_new = y;
        }
        if (count == 2)
        {
            a1 = (y_old - y_new);
            b1 = (x_new - x_old);
            c1 = (x_new - x_old) * y_old - (y_new - y_old) * x_old;
        }
        count++;
    }
    infile.close();
    ifstream infile2(name);
    ofstream outfile("pw_origin_" + name);
    outfile.precision(20);
    a2 = (y_old - y_new);
    b2 = (x_new - x_old);
    c2 = (x_new - x_old) * y_old - (y_new - y_old) * x_old;
    double det = a1 * b2 - a2 * b1;
    x_trailing = (b2 * c1 - b1 * c2) / det;
    y_trailing = (a1 * c2 - a2 * c1) / det;
    if (fabs(x_trailing) <= 1E-12)
        x_trailing = 0;
    else if (fabs(y_trailing) <= 1E-12)
        y_trailing = 0;
    outfile << line + 2 << endl;
    outfile << x_trailing << "\t" << y_trailing << "\t" << z << "\n";
    for (int i = 1; i <= line; i++)
    {
        infile2 >> x >> y;
        outfile << x << "\t" << y << "\t" << z << "\n";
    }
    outfile << x_trailing << "\t" << y_trailing << "\t" << z;
    infile2.close();
    outfile.close();
    return sqrt(x_trailing * x_trailing + y_trailing * y_trailing);
}

int main()
{
    int line = 0, scale_flag = 0, translate_flag = 0;
    double tr_x = 0, tr_y = 0, scale_factor = 1.0, chord_length = 1.0;
    double x_old, y_old, x_new, y_new, length;
    x_old = y_old = -10000;
    string name, outname;

    cout << "Enter the filename with extension: ";
    cin >> name;
    ifstream infile(name);
    cout << "Do you want to change the chord length of the airfoil(0/1)? ";
    cin >> scale_flag;
    if (scale_flag != 0)
    {
        cout << "Enter the chord length: ";
        cin >> chord_length;
    }
    cout << "Do you want to translate the geometry from origin(0/1)? ";
    cin >> translate_flag;
    if (translate_flag != 0)
    {
        cout << "Enter x translate value: ";
        cin >> tr_x;
        cout << "Enter y translate value: ";
        cin >> tr_y;
    }
    while (!infile.eof())
    {
        line++;
        infile >> x >> y;
        if (x_old == -10000)
        {
            x_old = x;
            y_old = y;
        }
        else
        {
            x_new = x;
            y_new = y;
        }
    }
    infile.close();
    if (x_new != x_old || y_new != y_old)
        length = trailing_edge_point(name, line);
    else
        length = sqrt(x_new * x_new + y_new * y_new);
    cout.precision(20);
    scale_factor = chord_length / length;
    cout << length << "\t" << scale_factor << endl;
    ifstream infile2("pw_origin_" + name);
    ofstream outfile("scaled_pw_" + name);
    outfile.precision(20);
    infile2 >> line;
    outfile << line << endl;
    for (int i = 1; i <= line; i++)
    {
        infile2 >> x >> y >> z;
        outfile << (x * scale_factor + tr_x) << "\t" << (y * scale_factor + tr_y) << "\t" << (z) << endl;
    }
    infile2.close();
    outfile.close();
    return 0;
}