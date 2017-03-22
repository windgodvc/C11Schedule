//
//  Schedule.cpp
//  WgServer
//
//  Created by Windgod-World on 3/22/17.
//  Copyright (c) 2017 Windgod. All rights reserved.
//

#include "Schedule.h"

Schedule::~Schedule(){
    for (auto &itor:_timer) {
        delete itor.second;
        itor.second = NULL;
    }
    std::unordered_map<std::string, ScheduleData*>().swap(_timer);
}

Schedule* Schedule::start(std::string name,std::function<void ()> timerCall,long dt){
    auto time = new ScheduleData();
    time->mName = name;
    time->mRun = timerCall;
    time->miSClose = false;
    time->_dt = dt;
    auto thread = std::thread(&Schedule::Run,this,time);
    thread.detach();
    _timer[name] = time;
    return this;
}

void Schedule::stop(std::string name){
    auto itor = _timer.find(name);
    if (itor != _timer.end()) {
        itor->second->miSClose = true;
    }
}

void Schedule::resume(std::string name){
    auto itor = _timer.find(name);
    if (itor != _timer.end()) {
        itor->second->miSClose = false;
    }
}

void Schedule::remove(std::string name){
    stop(name);
    auto itor = _timer.find(name);
    if (itor != _timer.end()) {
        _timer.erase(itor);
        delete itor->second;
        itor->second = NULL;
    }
}

void  Schedule::Run(ScheduleData *data){
    std::mutex signalMutex;
    std::condition_variable _sleepCondition;
    std::unique_lock<std::mutex> signal(signalMutex);
    while (true) {
        if (data->miSClose) {
            break;
        }else{
            _sleepCondition.wait_for(signal, std::chrono::milliseconds(data->_dt));
            data->mRun();
        }
    }
}