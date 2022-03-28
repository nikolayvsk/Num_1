// Mykola Vasyclhuk Lab 1;
// Variant 1
#include <iostream> 
#include <cmath>
#include <vector>
#include <string>
#include <iomanip>
#include <stdlib.h>
using namespace std;


double evaluate_relaxation(double x) { // x^3 + 2x^2 - x - 2 = 0
    return pow(x,3) + 2 * pow(x,2) - x -2;
}

void relaxation() {
    double eps;
    cout << "You can enter precision (10^-3 = 1e-3):\n";
    cin >> eps;
    double tau = 0.1481;
    double x1 = 0.5;
    double x_prev = 0;

    vector <int> iter = {};
    int i = 1;
    vector <double> x_res = {};
    vector <double> fX_res = {};

    while ((abs((x1 - x_prev)) >= eps) && abs(evaluate_relaxation(x1)) >= eps) {
        x_prev = x1;
        x1 = x1 - tau * evaluate_relaxation(x1); // f'(x) > 0

        iter.push_back(i++);
        x_res.push_back(x1);
        fX_res.push_back(evaluate_relaxation(x1));
    }

    cout << "Starting point x = 0,5; root = 1\n";
    cout << left << setw(10) << "Iter: " << setw(20) << "x:" << setw(20) << "f(x):" << endl;
    for (int i = 0; i <= iter.size() - 1; i++)
    {
        cout << left << setw(10) << iter[i];
        cout.precision(15);
        cout << setw(20) << x_res[i] << setw(20) << fX_res[i] << endl;
    }
}

///
/// 
///
/// 
double evaluate_modNew(double x) { // x^3 - 2x^2 - x + 2 = 0
    return pow(x, 3) - 2 * pow(x, 2) - x + 2;
}

double evaluate_der_modNew(double x) {
    return 3 * pow(x, 2) - 4 * x - 1;
}

double evaluate_secDer_modNew(double x) {
    return 6 * x - 4;
}

void modifiedNewton() {
    double eps;
    cout << "You can enter precision (10^-3 = 1e-3):\n";
    cin >> eps;
    double curr_P = -2;
    double P_prev = 0;
    double start_P = curr_P;

    vector <int> iter = {};
    int i = 1;
    vector <double> x_res = {};
    vector <double> fX_res = {};

    if ((evaluate_modNew(curr_P) * evaluate_secDer_modNew(curr_P)) < 0) { cout << "Error\n"; exit(1); } // думаю, что можно выкинуть

    while ((abs((curr_P - P_prev)) >= eps) && (abs(evaluate_modNew(curr_P)) >= eps)) {
        P_prev = curr_P;
        curr_P = curr_P - (evaluate_modNew(curr_P) / evaluate_der_modNew(start_P));

        iter.push_back(i++);
        x_res.push_back(curr_P);
        fX_res.push_back(evaluate_modNew(curr_P));
    }
    cout << "Starting point x = -2; root = -1\n";
    cout << left << setw(10) << "Iter: " << setw(20) << "x:" << setw(20) << "f(x):" << endl;
    for (int i = 0; i <= iter.size() - 1; i++)
    {
        cout << left << setw(10) << iter[i];
        cout.precision(15);
        cout << setw(20) << x_res[i] << setw(20) << fX_res[i] << endl;
    }
}

///
/// 
///
/// 
/// 
double evaluate_phi(double x) { // x^3 - 4x^2 + x + 6 = 0
    double s = pow((abs((6 * x * x) / (-x * x + 4 * x - 1))), 1.0 / 3.0);
    if ((6 * x * x) / (-x * x + 4 * x - 1) < 0)
        return s * (-1);
    else
        return s;
}

double evaluate_fx(double x) {
    return pow(x, 3) + 2 * pow(x, 2) - x - 2;
}
void simpleIteration() {
    double eps;
    cout << "You can enter precision (10^-3 = 1e-3):\n";
    cin >> eps;

    double q = 0.1; // calculated on paper
    double x_0 = -2.5;
    double x;
    x = evaluate_phi(x_0);
    double x_prev = x_0;
    vector <int> iter = {};
    int i = 1;
    vector <double> x_res = {};
    vector <double> fX_res = {};

    while(abs(x - x_prev) >= (1 - q) * eps / q) {
        x_prev = x;
        x = evaluate_phi(x);

        iter.push_back(i++);
        x_res.push_back(x);
        fX_res.push_back(evaluate_fx(x));
    }

    cout << "Starting point x = -2,5; root = -1\n";
    cout << left << setw(10) << "Iter: " << setw(20) << "x:" << setw(20) << "f(x):" << endl;
    for (int i = 0; i <= iter.size() - 1; i++)
    {
            cout << left << setw(10) << iter[i];
        cout.precision(15);
        cout << setw(20) << x_res[i] << setw(20) << fX_res[i] << endl;
    }
}
///
/// 
///
/// 
/// 



void iterationProcess()
{
    while (true) {
        cout << "Choose (undefined symbol = exit):\n(1) Relaxation method (max for x^2+2x^2-x-2=0)\n(2) Modified Newton method (min for x^3-2x^2-x+2=0)\n(3) Simple iteration method (min for x^3-4x^2+x+6=0)\n";
        int i;
        cin >> i;
        if (i == 1) {
            relaxation();
            iterationProcess();
            break;
        }
        else if (i == 2) {
            modifiedNewton();
            iterationProcess();
            break;
        }
        else if (i == 3) {
            simpleIteration();
            iterationProcess();
            break;
        }
        else { break; };
    }
}

int main()
{
    iterationProcess();
    return 0;
}
