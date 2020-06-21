
#ifndef Activity_h
#define Activity_h
#include <iostream>
#include <fstream>
using namespace std;

class Activity {
public:
    Activity();
    Activity(int hr, int min);
    
    
    friend Activity add(Activity act);
    friend bool operator>(const Activity&activity1, const Activity&activity2);
    friend bool operator<(const Activity&activity1, const Activity&activity2);
    friend bool operator==(const Activity&activity1, const Activity&activity2);
    friend bool binary_search(const Activity activities[], int n, int search_h, int search_m, int&idFound);
    void add_Dur(int x, int howLong);
    friend void show_Stat(const Activity activities[], int n);
    friend void add_Activity(Activity activities[], int&n);
    void format_heading(const Activity&activity);
    friend ostream &operator<<(ostream&outs, const Activity &activity);
    friend istream &operator >>(istream&ins, Activity &activity);
    friend void activities_sort(Activity activities[], int n);
    friend void duration_sort(Activity activities[], int n);
    bool valid() ;
    friend bool valid_Add( Activity activities[], int x,int howlong);
    friend bool conflict_Time(Activity activities[],int n);
    
private:
    int hour, minute;// for start time
    int duration;
    char listActivity[25];
    
};


void readFileOfActivities(Activity activities[], int&n, int&wrong);
void swap(int&v1, int&v2);
void insertion_sort(Activity activities[], int n);
char getUserChoice();
void header();

#endif /* Activity_h */
