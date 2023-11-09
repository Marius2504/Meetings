#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <fstream>
#include "MeetingTask.h"

using namespace std;

#define initialTime "08:00"
#define finalTime "20:00"

ifstream mon("monday.txt");
ifstream tue("tuesday.txt");
ifstream wed("wednesday.txt");
ifstream thu("thursday.txt");
ifstream fri("friday.txt");

// GLOBAL VARIABLES
vector<MeetingTask*> meetings;

char* removeSpaces(char* str)
{
    int i = 0, j = 0;
    while (str[i])
    {
        if (str[i] != ' ')
            str[j++] = str[i];
        i++;
    }
    str[j] = '\0';
    return str;
}
void correctHour(string& hour)
{
    //Corrects the hour. Eg from 9:00 to 09:00
    if (hour[0] != '0' && hour[0] != '1' && hour[0] != '2')
        hour = "0" + hour;
}

void readFile(ifstream &in)
{
    char line[100], * p;
    string aux="";
    string startTime, endTime;
    while (!in.eof())
    {
        in.get(line, 100);
        in.get();

        p = strtok(line, "-");
        if (p == NULL)
            break;
        startTime = removeSpaces(p);
        correctHour(startTime);

        p = strtok(NULL, "-");
        endTime = removeSpaces(p);
        correctHour(endTime);
        

        MeetingTask* m = new MeetingTask(startTime, endTime);
        meetings.push_back(m);
    }
}
bool compareInterval(MeetingTask *i1, MeetingTask *i2)
{
    return (i1->getStartTime() < i2->getStartTime());
}
string findMeeting()
{
    sort(meetings.begin(), meetings.end(),compareInterval); // O(N^2)
    string end = meetings[0]->getEndTime();
    string res = "";
    if (initialTime < meetings[0]->getStartTime())
    {
        res = res + "[ " + initialTime + " - " + meetings[0]->getStartTime() + " ]";
    }

    for (auto& meeting : meetings)
    {
        if (end < meeting->getStartTime())
            res = res + "[ " +  end + " - " + meeting->getStartTime() + " ]";
       
        end = max(end,meeting->getEndTime());
    }

    if(meetings[meetings.size()-1]->getEndTime() < finalTime)
    {
        res = res + "[ " + meetings[meetings.size() - 1]->getEndTime() + " - " + finalTime + " ]";
    }
    meetings.clear();
    return res + "";
}

void showResults(vector<string> results)
{
    int i = 0;
    vector<const char*> days = {"Monday","Tuesday","Wednesday","Thursday","Friday"};
    for (auto& res : results)
    {
        cout << "--------------------------------------------------------------------" << endl;
        cout << days[i++] << " : " << res << endl;
    }
    cout << endl << endl << "============= AVALIABLE TIME " << initialTime << " - " << finalTime<<" ========================="<<endl<<endl;
}


int main()
{
    vector<string> results;
    readFile(mon);
    results.push_back(findMeeting());

    readFile(tue);
    results.push_back(findMeeting());

    readFile(wed);
    results.push_back(findMeeting());

    readFile(thu);
    results.push_back(findMeeting());

    readFile(fri);
    results.push_back(findMeeting());

    showResults(results);
    return 0;
}


