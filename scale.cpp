#include <fstream>
#include <iostream>

int main()
{
    double x, y, z;
    int k;
    double scale_factor = 0.001;
    std::ifstream infile("naca0012_1.dat");
    std::ofstream outfile("naca0012_scaled.dat");
    infile >> k;
    outfile << k << "\n";
    for (int i = 1; i <= k; i++)
    {
        infile >> x >> y >> z;
        outfile << x * scale_factor << "\t" << y * scale_factor << "\t" << z * scale_factor << "\n";
    }
    infile.close();
    outfile.close();
    return 0;
}
