#include <iostream>
#include <unistd.h>
using namespace std;

#define RESET       "\033[0m"
#define BOLD        "\033[1m"
#define CYAN        "\033[96m"
#define YELLOW      "\033[93m"
#define GREEN       "\033[92m"
#define UNDERLINE   "\033[4m"

void Intro() {
    cout << CYAN << BOLD << UNDERLINE << "\t\t\tEcommerce (Dining Philosophy)\n" << RESET << endl << endl;
    cout << YELLOW << "\t\t\tAbdul Ahad => 23k-0590\n" << RESET;
    cout << GREEN  << "\t\t\tRayyan-Ur-Rehman => 23k-0634\n" << RESET;
    cout << CYAN   << "\t\t\tMuhammad Abdullah Khan => 23k-0607\n" << RESET;

    sleep(4); 
}
