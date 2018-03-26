#include <iostream>
#include <fstream>

using namespace std;

struct FTEmployee {
    double salary;
    double bonus;
};

struct PTEmployee {
    double hourlyWage;
    double workedHours;
};

struct Payroll {
    int ftNumber;
    int ptNumber;

    FTEmployee* ftEmployees;
    PTEmployee* ptEmployees;
};

Payroll* InitPayroll(int ft, int pt){
    Payroll* payroll = new Payroll();
    payroll->ftNumber = ft;
    payroll->ftEmployees = new FTEmployee[ft];
    payroll->ptNumber = pt;
    payroll->ptEmployees = new PTEmployee[pt];
    return payroll;
}

double CalculatePay(Payroll* payroll){
    double pay = 0;
    for(int i = 0; i < payroll->ftNumber; i++){
        pay += payroll->ftEmployees[i].salary + payroll->ftEmployees[i].bonus;
    }

    for(int i = 0; i < payroll->ptNumber; i++){
        pay += payroll->ptEmployees[i].hourlyWage * payroll->ptEmployees[i].workedHours;
    }
    return pay;
}

double CalculateGains(Payroll* payroll, double income){
    return income - CalculatePay(payroll);
}

void AddPT(Payroll* payroll, double wage, double hours, int index){
    PTEmployee employee;
    employee.hourlyWage = wage;
    employee.workedHours = hours;
    payroll->ptEmployees[index] = employee;
}

void AddFT(Payroll* payroll, double salary, double bonus, int index){
    FTEmployee employee;
    employee.salary = salary;
    employee.bonus = bonus;
    payroll->ftEmployees[index] = employee;
}

void DeletePayroll(Payroll* payroll){
    delete payroll->ftEmployees;
    delete payroll->ptEmployees;
}

int main()
{
    cout << "Number of part time employees? " << endl;
    int ptEmployees = 0;
    cin >> ptEmployees;
    if(ptEmployees <= 0){
        cout << "Error! Part time employees need to be more than 0." << endl;
        return 1;
    }

    cout << "Number of full time employees? ";
    int ftEmployees = 0;
    cin >> ftEmployees;
    if(ftEmployees <= 0){
        cout << "Error! Full time employees need to be more than 0." << endl;
        return 1;
    }

    Payroll* payroll = InitPayroll(ftEmployees, ptEmployees);

    for(int i = 0; i < ptEmployees; i++){
        int hours = 0;
        int wage = 0;
        cout << "Hourly Wage for Employee " << i + 1 << ": " << endl;
        cin >> wage;
        cout << "Hours Worked for Employee " << i + 1 << ": " << endl;
        cin >> hours;
        if(wage < 0 || hours < 0){
            cout << "Error! Negative value given for hours or wage.";
            i--;
            continue;
        }
        AddPT(payroll, wage, hours, i);
    }

    for(int i = 0; i < ftEmployees; i++){
        int salary = 0;
        int bonus = 0;
        cout << "Salary for Employee " << i + 1 << ": " << endl;
        cin >> salary;
        cout << "Bonus for Employee " << i + 1 << ": " << endl;
        cin >> bonus;
        if(salary < 0 || bonus < 0){
            cout << "Error! Negative value given for salary or bonus.";
            i--;
            continue;
        }
        AddFT(payroll, salary, bonus, i);
    }

    double income[12];

    for(int i = 1; i <= 12; i++){
        cout << "Enter income for month " << i << ": " << endl;
        double monthlyIncome = 0;
        cin >> monthlyIncome;
        income[i - 1] = monthlyIncome;
    }

    string fileName;
    cout << "Enter filename to write data." << endl;
    cin >> fileName;

    int year;
    cout << "Enter year:" << endl;
    cin >> year;

    std::ofstream output;
    output.open(fileName.c_str());
    cout << "Writing to file..." << endl;

    output << "ACME Inc. Fiscal Year " << year << endl;

    double netProfit = 0;

    for(int i = 0; i < 12; i++){
        output << "Month " << i + 1 << "$" << income[i] << " - $" << CalculatePay(payroll) << " = $"
            << CalculateGains(payroll, income[i]) << endl;
        netProfit += CalculateGains(payroll, income[i]);
    }

    output << "Net profit " << year << ": " << netProfit << endl;
    cout << "Net profit " << year << ": " << netProfit << endl;

    return 0;
}
