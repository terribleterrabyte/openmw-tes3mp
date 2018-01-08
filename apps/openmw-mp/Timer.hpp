//
// Created by koncord on 12.08.17.
//

#pragma once

#include <sol.hpp>

class LuaState;

class Timer
{
    friend class TimerController;
public:
    static void Init(LuaState &lua);
public:
    bool isElapsed();
    void stop();
    void start();
    void restart(long msec);

    Timer() = delete;
    ~Timer();
protected:
    Timer(sol::environment &env, sol::function &callback, long msec, sol::table &args);
    void tick();
    void kill();
    bool isMarkedToDelete() const { return markedToDelete; }
private:
    double startTime, targetMsec;
    sol::function callback;
    sol::table data;
    sol::environment env;
    bool end;
    bool markedToDelete;
};

class TimerController
{
public:
    static void Init(LuaState &lua);
public:
    std::shared_ptr<Timer> create(sol::environment env, sol::function callback, long msec, sol::table args);
    void kill(const std::shared_ptr<Timer> &timer);

    void terminate();
    void tick();
private:
    std::vector<std::shared_ptr<Timer>> timers;
    std::vector<std::shared_ptr<Timer>> newTimersQueue;
    bool haveMarkedToDeletion;
};

