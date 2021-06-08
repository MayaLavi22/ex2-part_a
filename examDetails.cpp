#include <iostream>
#include "examDetails.h"
#include "sortedList.h"
using std::cout;
using std::endl;
using std::string;
using std::ostream;
namespace mtm
{
    ExamDetails::ExamDetails(int course,int month,int day,double start,unsigned long length,string link)
{
    if(month>12||month<1||day<=0||day>30){
        throw InvalidDateException();
    }
    if(start<0||start>23.5 || length<=0){
        throw InvalidTimeException();
    }
    if(course<=0){
        throw InvalidArgsException();
    }
    this->course=course;
    this->month=month;
    this->day=day;
    this->start=start;
    this->length=length;
    this->link=link;
}

string ExamDetails::getLink() const
{
    return link;
}

void ExamDetails::setLink(string link)
{
    this->link=link;
}

int ExamDetails::operator-(const ExamDetails& exam) const
{   
    return (this->month*30+this->day)-(exam.month*30+exam.day);
}

bool ExamDetails::operator<(const ExamDetails& exam) const
{
if (this->month<exam.month){
        return true;
}
if(this->month>exam.month){
    return false;
}
if(this->day<exam.month){
    return true;
}
if(this->day>exam.day){
    return false;
}
if(this->start<exam.start){
    return true;
}
return false;
}

ostream& operator<<(ostream& os, const ExamDetails& exam)
{
    double hour=(int)exam.start;
    double half_hour=exam.start-hour;
    if(half_hour==0.5){
        half_hour=3;
    }
    return os <<"Course Number: "<<exam.course<<endl<<"Time: "<<exam.day<<"."<<exam.month<<" at "<<hour<<":"
            <<(int)half_hour<<"0"<<endl<<"Duration: "<<exam.length<<":00"<<endl<<"Zoom Link: "<<exam.link<<endl;
}

ExamDetails ExamDetails::makeMatamExam()
{
    return ExamDetails(234124,7,28,13,3,"https://tinyurl.com/59hzps6m");
}

}

