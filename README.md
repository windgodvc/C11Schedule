# C11Schedule
C11 Schedule Timer.
使用线程实现的跨平台定时器.


```c++
//Codeing Demo
Schedule *timer = new Schedule;
int sum = 0;
timer->start("mytest", SCHEDULE_ARGS([=](int command)mutable{
    sum += 1;
    if (sum >= 5) {
        timer->stop("mytest");
        std::cout<<"Done"<<std::endl;
    }else{
        std::cout<<"command:"<<command<<std::endl;
    }
    
},1010), 1000)->
start("mytest1", SCHEDULE_ARGS([=](int command)mutable{
    sum += 1;
    if (sum >= 5) {
        timer->stop("mytest1");
        std::cout<<"Done1"<<std::endl;
    }else{
        std::cout<<"command:"<<command<<std::endl;
    }
    
},1018), 1100);
```
