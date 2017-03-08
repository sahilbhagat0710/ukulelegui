#include <iostream>
using namespace std;

int main()
{
    /* variable definition and initialization */
    char stringArray[100];
    
    /* Take user input and assign to variable */
    cout << "Please write something:" << endl; //cin >> stringArray;
    cin.getline(stringArray,80);
    
    /* Print */
    cout << "You enter the string:" << stringArray << endl;
    return 0; 
}
