//
//  Schedule.h
//  WgServer
//
//  Created by Windgod-World on 3/22/17.
//  Copyright (c) 2017 Windgod. All rights reserved.
//

#ifndef __WgServer__Schedule__
#define __WgServer__Schedule__

#include <stdio.h>
#include <thread>
#include <mutex>
#include <string>
#include <unordered_map>

#define SCHEDULE_ARGS std::bind

//
// Codeing Demo
//Schedule *timer = new Schedule;
//int sum = 0;
//timer->start("mytest", SCHEDULE_ARGS([=](int command)mutable{
//    sum += 1;
//    if (sum >= 5) {
//        timer->stop("mytest");
//        std::cout<<"Done"<<std::endl;
//    }else{
//        std::cout<<"command:"<<command<<std::endl;
//    }
//    
//},1010), 1000)->
//start("mytest1", SCHEDULE_ARGS([=](int command)mutable{
//    sum += 1;
//    if (sum >= 5) {
//        timer->stop("mytest1");
//        std::cout<<"Done1"<<std::endl;
//    }else{
//        std::cout<<"command:"<<command<<std::endl;
//    }
//    
//},1018), 1100);


//  使用线程实现的定时器.
class ScheduleData {
    
public:
    std::string mName;
    
    std::function<void ()> mRun;
    
    bool miSClose;
    
    long _dt;
};

class Schedule {
    
public:
    
    ~Schedule();
    //  要传递参数请用 SCHEDULE_ARGS(&XXX,you arg)
    Schedule* start(std::string name,std::function<void ()> timerCall,long dt);
    
    void stop(std::string name);
    
    void resume(std::string name);
    
    void remove(std::string name);
    
    void Run(ScheduleData *data);
    
private:
    
    std::unordered_map<std::string, ScheduleData*> _timer;
};

#endif /* defined(__WgServer__Schedule__) */
