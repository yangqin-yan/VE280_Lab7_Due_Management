//
// VE280 Lab 7, SU2020
// Created by cyx on 20-5-22.
//

#include <iostream>
#include "course.h"

typedef struct task{
    std::string type;
    int index; // Task index of type
    int due_month;
    int due_day;
} Task;
/*
 * Task is used to represent tasks in a course.
 * type could be "Lab", "Project" and etc., which specifies the type of the task,
 * index is the number of task of this type,
 * due_month and due_day specifies its due date
 */

const int MAXTASKS = 4; // default maximum number of tasks in a course at a time
class TechnicalCourse : public Course {
protected:
    Task *tasks;
    int numTasks;
    int sizeTasks;
    std::string course_code;
public:
    // TODO: implement the constructor
    TechnicalCourse(const std::string &course_code, int size = MAXTASKS);

    // TODO: declare and implement the destructor
    ~TechnicalCourse();

    // TODO: declare updateTask method
    void updateTask(const std::string &type, int index, int due_month, int due_day);

    void finishTask(const std::string &type, int index, int finish_month, int finish_day);
    void print();
};

TechnicalCourse::TechnicalCourse(const std::string &course_code, int size):
tasks(new Task[size]), numTasks(0),  sizeTasks(size), course_code(course_code){}

TechnicalCourse::~TechnicalCourse(){
    delete[] tasks;
}

void TechnicalCourse::updateTask(const std::string &type, int index, int due_month, int due_day)
// REQUIRES: due_month and due_day are in normal range.
// MODIFIES: this
// EFFECTS: if Task index of type already exists in tasks, updates its due_month & due_day ;
//          otherwise, adds Task i of type at the end of tasks if tasks is not full,
//          throw an exception if tasks is full
{
    // TODO: implement this function
    for(int i = 0; i < numTasks; i++){
        if(type == tasks[i].type && index == tasks[i].index){
            tasks[i].due_month = due_month;
            tasks[i].due_day = due_day;
            return;
        }
    }

    // Cases of adding a new task
    // Check overflow
    if(numTasks == sizeTasks){
        throw tooManyTasks{};
    }

    // normal Cases
    tasks[numTasks].type = type;
    tasks[numTasks].index = index;
    tasks[numTasks].due_month = due_month;
    tasks[numTasks].due_day = due_day;
    if(type == "Lab" || type == "Project"){
        std::cout << course_code << " " << type << " "
        << index << " is released! Submit it via oj!" << std::endl;
    }
    else{
        std::cout << course_code << " " << type << " "
        << index << " is released! Submit it via canvas!" << std::endl;
    }
}

void TechnicalCourse::finishTask(const std::string &type, int index, int finish_month, int finish_day)
// REQUIRES: Task index of type is in tasks. finish_month and finish_day are in normal range.
// MODIFIES: this
// EFFECTS: removes Task index of type
{
    // TODO: implement this function
    for(int i = 0; i < numTasks; i++){
        if(type == tasks[i].type && index == tasks[i].index){
            // overdue due_month
            if(finish_month > tasks[i].due_month){
                std::cout << course_code << " " << type << " "
                << index << " is overdue!" << std::endl;
            }
            // overdue date
            else if(finish_month == tasks[i].due_month && finish_day > tasks[i].due_day){
                std::cout << course_code << " " << type << " "
                << index << " is overdue!" << std::endl;
            }
            else{
                // finished
                std::cout << course_code << " " << type << " "
                << index << " is finished!" << std::endl;
            }

            // will be removed.
            if(i < numTasks - 1){
                for(int j = i; j < numTasks; j++){
                    tasks[j] = tasks[j + 1];
                }
                numTasks--;
                break;
            }
            else{
                numTasks--;
                break;
            }
        }
    }
}

void TechnicalCourse::print()
{
    std::cout << course_code << std::endl;
    for(int i = 0; i < numTasks; ++i){
        std::cout << tasks[i].type << " " << tasks[i].index << ": "
                  << tasks[i].due_month << "/" << tasks[i].due_day << std::endl;
    }
}

class UpperlevelTechnicalCourse : public TechnicalCourse {
public:
    // TODO: implement the constructor
    UpperlevelTechnicalCourse(const std::string &course_code, int size = MAXTASKS);

    // TODO: declare and implement the destructor
    ~UpperlevelTechnicalCourse();

    void updateTask(const std::string &type, int index, int due_month, int due_day) override;
};

UpperlevelTechnicalCourse::UpperlevelTechnicalCourse(const std::string &course_code, int size):
TechnicalCourse(course_code, size)
{}

UpperlevelTechnicalCourse::~UpperlevelTechnicalCourse(){
    delete[] tasks;
}

void UpperlevelTechnicalCourse::updateTask(const std::string &type, int index, int due_month, int due_day)
// REQUIRES: due_month and due_day are in normal range.
// MODIFIES: this
// EFFECTS: If Task index of type does not exist in tasks,
//          adds Task i of type according to its due date if tasks is not full, throw an exception if tasks is full.
//          If Task index of type already exists in tasks,
//          updates its position in tasks & due_month & due_day if its due_month/due_day is changed,
//          do nothing if its due_month/due_day is unchanged.
{
    // TODO: implement this function
    for(int i = 0; i < numTasks; i++){
        if(type == "Team Project"){
            std::cout << course_code << " " << type << " "
            << index << " is released! Submit it via github!" << std::endl;
            return;
        }
    }
    TechnicalCourse::updateTask(type, index, due_month, due_day);
}

Course *create(const std::string &class_type, const std::string &course_code, bool assign_size, int tasks_size)
{
    if(class_type == "Technical"){
        if(assign_size){
            return new TechnicalCourse(course_code, tasks_size);
        }
        else{
            return new TechnicalCourse(course_code);
        }
    }
    else if(class_type == "Upper Level Technical"){
        if(assign_size){
            return new UpperlevelTechnicalCourse(course_code, tasks_size);
        }
        else{
            return new UpperlevelTechnicalCourse(course_code);
        }
    }
    else{
        return nullptr;
    }
}
