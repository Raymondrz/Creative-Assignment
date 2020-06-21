#include "activity.h"

#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
    //The activities array and count of activities (n)
    Activity activities[20];
    int n;
    int wrong;//for wrong
    //For part D
    int id_found;
    int search_hh, search_mm;
    char dummy; //colon between search_hh and search_mm
    char choice = ' ';
    char finalchoice = ' ';
    int x, howlong;
    char ans;
    cout << "[A] Input activities from file\n";
    cout << "==============================\n";
    readFileOfActivities(activities, n, wrong);
    cout << endl;
    if (wrong > 0)
        cout << wrong << " activities are wrong and discarded." << endl << endl;
    
    cout << n << " activities are extracted. ";
    
    cout << "\n\n\n";
    
    cout << "[B] Display list of activities\n";
    cout << "==============================\n";
    
    for (int i = 0; i < n; i++) {
        
        cout << activities[i] << endl;
        
        
    }
    cout << endl << endl;
    do {
        cout << "Sorting using [S]tart time, [D]uration,[A]lphabetical order of activities: " ;
        cin >> ans;
    } while (ans != 'S'&&ans!='D'&&ans!='A');
    cout << endl;
    
    cout << "[C] Sort activities\n";
    header();
    if (ans == 'S') {
        insertion_sort(activities, n);
        for (int i = 0; i < n; i++) {
            
            cout << "| " << i + 1 << " ";
            activities[i].format_heading(activities[i]);
        }
    }
    else if (ans == 'D') {
        duration_sort(activities, n);
        for (int i = 0; i < n; i++) {
            cout << "| " << i + 1 << " ";
            activities[i].format_heading(activities[i]);
        }
        
    }
    else if (ans == 'A') {
        activities_sort(activities, n);
        for (int i = 0; i < n; i++) {
            cout << "| " << i + 1 << " ";
            activities[i].format_heading(activities[i]);
        }
        
    }
    
    cout << setfill('-') << setw(69) << "-";
    cout << endl << endl;
    
    cout << "[D] Search activities\n";
    cout << "=====================\n";
    cout << "Type a start time to search: ";
    cin >> search_hh >> dummy >> search_mm;
    if (binary_search(activities, n, search_hh, search_mm, id_found))
    {
        cout << "\n";
        cout << activities[id_found] << "\n\n";
    }
    else
        cout << "\n No activity is found.\n\n";
    
    
    cout << "[E] Customize some activities\n";
    cout << "=============================\n";
    
    do {
        choice = getUserChoice();
        
        if (choice == 'E') {
            cout << " Please input the activity number which you want to edit: ";
            cin >> x;
            cout << " Extend duration(in minutes) by: ";
            cin >> howlong;
            
            if (valid_Add(activities,x, howlong)) {
                
                cout << "Change successful : ";
                cout << activities[x - 1];
                cout << endl;
            }
            else
                cout << "Change unsuccessful. Coincided with another activities. " << endl;
            
            finalchoice = 'E';
        }
        
        else if (choice == 'A') {
            add_Activity(activities,n);
            
            finalchoice = 'A';
            
        }
        else if (choice == 'Q')
            finalchoice = 'Q';
        
    } while (finalchoice != 'Q');
    
    cout << "Last updated: " << endl;
    insertion_sort(activities, n);
    for (int i = 0; i<n; i++)
        cout << activities[i] << endl;
    cout << endl << endl;
    
    cout << "[F] Statistics\n";
    cout << "================\n";
    show_Stat(activities, n);
    cout << endl << endl;
    
    cout << "Thank you for using this program.\n\n";
    
    return 0;
}

