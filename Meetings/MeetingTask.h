#ifndef MEETINGTASK_H
#define MEETINGTASK_H

#include <string>
using namespace std;
class MeetingTask {
private:
    string startTime;
    string endTime;
public:
    MeetingTask(string startTime, string endTime);
    string getStartTime();
    string getEndTime();
};
#endif

