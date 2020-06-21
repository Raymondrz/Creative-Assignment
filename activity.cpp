
#include "activity.h"
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

Activity::Activity() {
    hour = 0 % 24;
    minute = 0 % 60;
}
Activity::Activity(int hr, int min) {
    hour = hr % 24;
    minute = min % 60;
}
Activity add(Activity act) {
    int total;
    int hrs;
    total = act.minute + act.duration;
    
    hrs = total / 60;
    
    
    return Activity(act.hour + hrs, act.minute + act.duration);
}

void Activity::format_heading(const Activity&activity) {
    Activity ans;
    ans = add(activity);
    
    cout << "|" << setfill('0') << setw(2) << hour << ":" << setw(2) << minute << " - ";
    cout << setw(2) << ans.hour << ":" << setw(2) << ans.minute << "| ";
    cout << setfill(' ') << setw(25) << listActivity << " | (";
    if (duration % 60 == 0)
        cout << duration / 60 << " hour)" << setfill(' ') << setw(13) << "|" << endl;
    else if (duration > 60) {
        cout << duration / 60 << " hour " << duration % 60 << " minutes)";
        cout << setfill(' ') << setw(2) << "|" << endl;
    }
    else
        cout << activity.duration << " minutes)" << setfill(' ') << setw(9) << "|" << endl;
    
    ;
    
}
bool Activity::valid() {
    if (hour<0||hour>23||minute<0|| minute>59 || duration<0)
        return false;
    return true;
}


bool conflict_Time ( Activity activities[], int n) {
    
    Activity ans[10];
    
    
    for (int i = 0; i <=n; i++) {
        
        ans[i] = add(activities[i]);
        
        if (activities[n] > activities[i]&&activities[n]<ans[i])
            return false;
        else if (activities[n] == activities[i] && activities[n] == ans[i])
            return false;
        
    }
    
    return true;
    
}
istream&operator>>(istream&ins, Activity&activity) {
    char dummy;
    ins >> activity.hour >> dummy >> activity.minute;
    ins >> activity.duration;
    ins.ignore();
    ins.getline(activity.listActivity, 25);
    return ins;
}
ostream&operator<<(ostream&outs, const Activity&activity) {
    Activity ans;
    ans = add(activity);
    outs << setfill('0') << setw(2) << activity.hour << ":" << setw(2) << activity.minute << " - ";
    outs << setw(2) << ans.hour << ":" << setw(2) << ans.minute << " " << activity.listActivity << " (";
    if (activity.duration % 60 == 0)
        outs << activity.duration / 60 << " hour)" << endl;
    else if (activity.duration > 60)
        outs << activity.duration / 60 << " hour " << activity.duration % 60 << " minutes)" << endl;
    else
        outs << activity.duration << " minutes)" << endl;
    
    return outs;
}



void readFileOfActivities(Activity activities[], int&n, int&wrong) {
    ifstream inFile;
    char inFile_pathname[200];
    n = 0;
    wrong = 0;
    cout << "Type the pathname of the input file: ";
    cin >> inFile_pathname;
    inFile.open(inFile_pathname);
    
    
    while (!inFile.eof()) {
        inFile >> activities[n];
        if (!inFile.fail() && activities[n].valid()) {
            n++;
        }
        else if(!activities[n].valid()){
            
            wrong++;
            if (!inFile.fail()) {
                cout << endl;
                cout << activities[n];
                
            }
            
        }
        
        
    }
    wrong--;
    inFile.close();
}
void swap(int&v1, int&v2) {
    int original_v1;
    original_v1 = v1;
    v1 = v2;
    v2 = original_v1;
}
void header() {
    cout << "===================\n";
    cout << setfill('-') << setw(69) << "-" << endl;
    cout << "|No |    Time     |        Activities" << setfill(' ') << setw(10) << "|";
    cout << "      Duration" << setfill(' ') << setw(8) << "|" << endl;
    cout << setfill('-') << setw(69) << "-" << endl;
}
void insertion_sort(Activity activities[], int n) {
    
    int i;
    for (i = 1; i<n; i++) {
        int j = i;
        while (j>0 && activities[j - 1]>activities[j]) {
            swap(activities[j - 1], activities[j]);
            j--;
        }
    }
    
}
void duration_sort(Activity activities[], int n) {
    int i;
    for (i = 1; i<n; i++) {
        int j = i;
        while (j>0 && activities[j - 1].duration>activities[j].duration) {
            
            j--;
        }
        
    }
}

void activities_sort(Activity activities[], int n) {
    int i;
    for (i = 1; i<n; i++) {
        int j = i;
        while (j>0 && activities[j - 1].listActivity[0]>activities[j].listActivity[0]) {
            if (activities[j - 1].listActivity[0] == activities[j].listActivity[0]&& activities[j - 1].listActivity[1] > activities[j].listActivity[0]) {
                
                swap(activities[j - 1], activities[j]);
            }
            else
                swap(activities[j - 1], activities[j]);
            
            j--;
        }
        
    }
}
bool operator>(const Activity&activity1, const Activity&activity2) {
    
    if (activity1.hour>activity2.hour)
        return true;
    else if (activity1.hour == activity2.hour&&activity1.minute>activity2.minute)
        return true;
    else
        return false;
    
    
}
bool operator<(const Activity&activity1, const Activity&activity2) {
    
    if (activity1.hour<activity2.hour)
        return true;
    else if (activity1.hour == activity2.hour&&activity1.minute<activity2.minute)
        return true;
    else
        return false;
    
    
}
bool operator==(const Activity&activity1, const Activity&activity2) {
    
    if (activity1.hour==activity2.hour&&activity1.minute==activity2.minute)
        return true;
    else
        return false;
    
    
}
bool binary_search(const Activity activities[], int n, int search_h, int search_m, int&idFound) {
    
    int low = 0; int high = n - 1;
    
    while (low <= high)
    {
        int mid = (low + high) / 2;
        
        if (activities[mid].hour == search_h && activities[mid].minute == search_m) {
            idFound = mid;
            return true;
        }
        if (activities[mid].hour<search_h)
            low = mid + 1;
        else
            high = mid - 1;
        
    }
    return false;
}
char getUserChoice() {
    char c;
    do {
        cout << " Choices: [E]xtend duration,[A]dd Activities or [Q]uit: ";
        cin >> c;
        cout << endl;
    } while (c != 'E'&&c != 'A'&&c != 'Q');
    
    return c;
    
}

void Activity::add_Dur(int x, int howLong) {
    
    duration += howLong;
    
}
void add_Activity(Activity activities[], int&n) {
    
    cout << "Input new activities[time, duration, the activity]: ";
    cin >>  activities[n];
    
    if (conflict_Time(activities, n)) {
        cout << "A new activities is added succesfully " << endl;
        cout << activities[n];
        n++;
    }
    else if (!conflict_Time(activities, n)) {
        cout << "Cannot add activities. Refer to your schedule. " << endl;
    }
    
    
}
void show_Stat(const Activity activities[], int n) {
    
    int longest = 0;
    int total = 0;
    int shortest = 60;
    int mean = 0;
    for (int i = 0; i < n; i++) {
        if (activities[i].duration > longest)
            longest = activities[i].duration;
    }
    cout << "Longest activity duration : " << longest <<" minutes."<< endl;
    
    for (int i = 0; i < n; i++) {
        if (activities[i].duration < shortest)
            shortest = activities[i].duration;
    }
    cout << "Shortest activity duration : " << shortest << " minutes." << endl;
    
    for (int i = 0; i < n; i++) {
        total += activities[i].duration;
    }
    
    cout << "The total time of activities : " << total << " minutes." << endl;
    
    for (int i = 0; i < n; i++) {
        mean += activities[i].duration;
    }
    mean = mean / n;
    
    cout << "The mean time of all activities : " << mean << " minutes." << endl;
    
}

bool valid_Add( Activity activities[], int x, int howlong) {
    activities[x - 1].add_Dur(x, howlong);
    Activity ans;
    ans = add(activities[x - 1]);
    
    if (ans > activities[x] || ans == activities[x])
    {
        activities[x - 1].duration -= howlong;
        return false;
    }
    else
        return true;
    
    
    
}
