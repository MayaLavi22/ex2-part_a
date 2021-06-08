#ifndef EXAMDETAILS_H
#define EXAMDETAILS_H
#include <iostream>
namespace mtm
{
    class ExamDetails
    {
        int course,month,day;
        double start;
        unsigned long length;
        std::string link;
    public:
        ExamDetails(int course,int month,int day,double start,unsigned long length,std::string link="");
        ~ExamDetails() = default;
        ExamDetails(const ExamDetails& exam) = default;
        ExamDetails& operator=(const ExamDetails& exam) = default;
        std::string getLink() const;
        void setLink(std::string link);
        int operator-(const ExamDetails& exam) const;
        bool operator<(const ExamDetails& exam) const;
        friend std::ostream& operator<<(std::ostream& os, const ExamDetails& exam); 
        static ExamDetails makeMatamExam();
        class InvalidDateException {};
        class InvalidTimeException {};
        class InvalidArgsException {};
    };
   
}

 #endif // EXAMDETAILS_H
