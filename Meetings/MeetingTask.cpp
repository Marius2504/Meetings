#include "MeetingTask.h"

MeetingTask::MeetingTask(string startTime, string endTime)
{
    this->startTime = startTime;
    this->endTime = endTime;
}
string MeetingTask::getStartTime() { return this->startTime; }
string MeetingTask::getEndTime() { return this->endTime; }
