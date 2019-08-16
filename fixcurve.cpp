#include <fstream>
#include <iostream>
#include <string>

double x, y, z = 0;
using namespace std;
void scale(double scale_factor)
{
    x = x * scale_factor;
    y = y * scale_factor;
}

void translate(double tr_x, double tr_y)
{
    x = x + tr_x;
    y = y + tr_y;
}

void trailing_edge_point(string name)
{
    double a1, a2, b1, b2, c1, c2;
    double x_trailing, y_trailing;
    double x_old, y_old, x_new, y_new;
    int count = 1;
    x_old = y_old = NULL;
    ifstream infile("1" + name);
    ofstream outfile("2" + name);
    while (infile)
    {
        if (x_old == NULL)
        {
            x_old = x;
            y_old = y;
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
    a2 = (y_old - y_new);
    b2 = (x_new - x_old);
    c2 = (x_new - x_old) * y_old - (y_new - y_old) * x_old;
    double det = a1 * b2 - a2 * b1;
    x_trailing = (b2 * c1 - b1 * c2) / det;
    y_trailing = (a1 * c2 - a2 * c1) / det;
}

int main()
{
    int l, scale_flag = 0, translate_flag = 0;
    double tr_x, tr_y, scale_factor;
    double x_old, y_old, x_new, y_new;
    x_old = y_old = NULL;
    string name, outname;

    cout << "Enter the filename with extension: ";
    cin >> name;
    ifstream infile(name);
    outname = "1_" + name;
    ofstream outfile(outname);
    cout << "Do you want to scale the geometry(0/1)? ";
    cin >> scale_flag;
    if (scale_flag != 0)
    {
        cout << "Enter the scale factor: ";
        cin >> scale_factor;
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
    while (infile)
    {
        infile >> x >> y;
        if (scale_flag != 0)
            scale(scale_factor);
        if (translate_flag != 0)
            translate(tr_x, tr_y);
        outfile << x << "\t" << y << "\n";
        if (x_old == NULL)
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
    if (x_new != x_old || y_new != y_old)
        trailing_edge_point(name);
    return 0;
}