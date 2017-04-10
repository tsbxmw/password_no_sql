---
layout: post
title: C++ Thread in Class at windows
categories: C++
description: bookmark
keywords: c++,thread,class,windows
---

C++ Thread in Class at windows

## 链接

* nothing here

##  摘要
    
    Write a thread function in class at windows 10


----------

## 内容    
    
### Header.h
----------

```c

    #pragma once
    /*
        * Header.h
        * Tools of test 
        * version 0.1 edit by wei.meng @ 20170405
    */

    #include <iostream>
    #include <string>
    #include <Windows.h>
    #include <fstream>
    #include <time.h> 
    #include <process.h>
    #include <rpos\robot_platforms\slamware_core_platform.h>
    #include<rpos\features\sweep_motion_planner.h>
    #include<rpos\robot_platforms\objects\composite_map_reader.h>
    #include<rpos\robot_platforms\objects\composite_map_writer.h>
    #include<rpos\robot_platforms\objects\line_map_layer.h>
    using namespace rpos::robot_platforms;
    using namespace std;
    using namespace rpos::core;
    using namespace rpos::features;
    using namespace rpos::actions;
    using namespace rpos::features::detail;
    using namespace rpos::features::system_resource;

    class Tools {

    private:

    public:
        int argc;
        char **args;
        float xy_v[2][2];
        SlamwareCorePlatform platform;

        

        Tools() {}
        ~Tools(){}
        Tools(int argc, char *args[]);

        void execArgs();
        void ExecOne();
        void ExecTwo();
        void HelpInfo();
        void RunTest();
        void BatteryHoldTimeTest();
        void GetVxy();
        void BatteryChargeTest();
        friend unsigned int __stdcall Moveto_vecxy(PVOID pParam); // this is the thread function at windows as friend function
        void MoveAndGoHome();
        void TurnLRTest();
        void TurnLeft(int time);
        void TurnRight(int time);
        void getPT();

        void logTest(string test,string logstr);
        string Word2String(WORD w);
        string Int2String(int value);

    };
```
### Tools.cpp

```c

    #include "Header.h"

    void Tools::execArgs()
    {
        if (argc == 1)
        {
            cout << "[error] wrong with args" << endl;
            cout << "[error] using -h to show help info" << endl;
        }
        else
        {
            switch (argc) {
            case 2:
                ExecOne();
                break;
            case 3:
            case 4:
            case 5:
            case 6:
            case 7:
            case 8:
            case 9:
            case 10:
            case 11:
            case 12:
            case 13:
                ExecTwo();
                break;
            }
        }
    }

    Tools::Tools(int argc, char *args[]) {
        this->argc = argc;
        this->args = args;
    }


    void Tools::ExecOne()
    {
        char cmd = strtok(args[1], "-")[0];
        switch (cmd)
        {
        case 'h':
            HelpInfo();
            break;
        default:
            cout << "[error] wrong -" << endl;
            HelpInfo();
            break;
        }
    }

    void Tools::ExecTwo()
    {
        char cmd = strtok(args[1], "-")[0];
        switch (cmd)
        {
        case 't':
            RunTest();
            break;
        default:
            cout << "[error] wrong with argc - " << cmd << endl;
            HelpInfo();
            break;
        }
    }

    void Tools::RunTest()
    {
        cout << "RunTest ..." << endl;
        string cmd = args[3];
        if (cmd == "test1")
        {
            BatteryHoldTimeTest();
        }else if (cmd == "test2")
        {
            BatteryChargeTest();
        }
        else if (cmd == "test3")
        {
            MoveAndGoHome();
        }
        else {
            cout << "[error] wrong with args" << endl;
        }
    }


    void Tools::BatteryHoldTimeTest()
    {
    #ifndef test1
    #define test1 "BatteryHoldTimeTest"
    #endif // !
        logTest(test1, "[Battery Hold Time Test] ---- Start ...\n");
        int time;
        SYSTEMTIME sys;
        bool runthread = false;

        if (argc > 4)
        {
            time = (atoi)(args[4]);
        }
        else {
            logTest(test1, " 参数输入错误 \n");
        }
        if (argc >= 10)
        {
            GetVxy();
            runthread = true;
        }

        getPT();

        while (platform.getBatteryIsCharging())
        {
            logTest(test1, " 请断开充电设备 \n");
            Sleep(5000);
        }

        if (platform)
        {
            GetLocalTime(&sys);
            logTest(test1, " --------------------------------------------------\n");
            logTest(test1, " BEGIN time : " + Word2String(sys.wYear) + "/" + Word2String(sys.wMonth) + "/" + Word2String(sys.wDay) + " - " 
                + Word2String(sys.wHour) + ":" + Word2String(sys.wMinute) + ":" + Word2String(sys.wSecond) + "\n");
            logTest(test1, " battery life  : " + Int2String(platform.getBatteryPercentage()) + "\n");
            logTest(test1, " --------------------------------------------------\n");
            logTest(test1, " ----- > every [ " + (string)args[4] + " ] seconds check once \n");
            if(runthread)
                _beginthreadex(NULL, 0, Moveto_vecxy, this, 0, NULL);
            while (true)
            {
                GetLocalTime(&sys);
                logTest(test1, Word2String(sys.wYear) + "/" + Word2String(sys.wMonth) + "/" + Word2String(sys.wDay) + " - " + 
                    Word2String(sys.wHour) + ":" + Word2String(sys.wMinute) + ":" + Word2String(sys.wSecond) + "--" + Int2String(platform.getBatteryPercentage()) + "\n" );
                Sleep(time * 1000);
            }
        }
    }

    void Tools::GetVxy()
    {
        SYSTEMTIME sys;
        double x[100], y[100];
        int power = 100;
        int count,time;
        if (argc > 5)
        {
            time = (atoi)(args[4]);
            count = (atoi)(args[5]);
        }
        if (argc > (2 * count + 5))
        {
            int jx = 0, jy = 0;
            for (int i = 6; i <= 2 * count + 5; i++)
            {
                if (i % 2 == 0)
                {
                    x[jx] = (atof)(args[i]);
                    jx++;
                }
                else
                {
                    y[jy] = (atof)(args[i]);
                    jy++;

                }
            }
        }
        else {
            cout << "[error] wrong with the argc " << endl;
        }

            for (int i = 0; i < count; i++)
            {
                xy_v[i][0] = x[i];
                xy_v[i][1] = y[i];
            }
           
            
    }

    unsigned int __stdcall  Moveto_vecxy(PVOID pParam)
    {

        
        try {
            
            vector<Location> vxy;
            for (int i = 0; i < 2; i++)
            {
                vxy.push_back(Location(((Tools*)pParam)->xy_v[i][0], ((Tools*)pParam)->xy_v[i][1]));
            }
            while (true)
            {
                for (vector<Location>::const_iterator it = vxy.begin(); it != vxy.end(); it++)
                {
                    MoveAction ma = ((Tools*)pParam)->platform.moveTo(*it, true, true);
                    while (ma.getStatus() != ActionStatusFinished)
                        if (ma.getStatus() == ActionStatusError)
                            break;
                }
            }
        }
        catch (rpos::system::detail::ExceptionBase &e)
        {
            SYSTEMTIME sys;
            GetLocalTime(&sys);
            cout << " END time : " << sys.wYear << "/" << sys.wMonth << "/" << sys.wDay << " - " << sys.wHour << ":" << sys.wMinute << ":" << sys.wSecond << endl;
            cout << " battery life  : " << ((Tools*)pParam)->platform.getBatteryPercentage() << endl;
            cout << " connection fail " << e.what() << endl;
            exit(1);
        }
        return 0;
    }

    void Tools::MoveAndGoHome()
    {
    #ifndef test3
    #define test3 "MoveAndGoHome"
    #endif // !test3
        logTest(test3, "[MoveAndGoHome] ---- Start ...\n");
        SYSTEMTIME sys;
        int life, count;
        if (argc > 9)
        {
            life = (atoi)(args[4]);
            count = (atoi)(args[5]);
        }
        else
            logTest(test3, "[error] wrong with - argc");
        GetVxy();
        getPT();

        GetLocalTime(&sys);
        logTest(test3, " --------------------------------------------------\n");
        logTest(test3, " BEGIN time : " + Word2String(sys.wYear) + "/" + Word2String(sys.wMonth) + "/" + Word2String(sys.wDay) + " - "
            + Word2String(sys.wHour) + ":" + Word2String(sys.wMinute) + ":" + Word2String(sys.wSecond) + "\n");
        logTest(test3, " battery life  : " + Int2String(platform.getBatteryPercentage()) + "\n");
        logTest(test3, " --------------------------------------------------\n");
        try {

            vector<Location> vxy;
            for (int i = 0; i < 2; i++)
            {
                vxy.push_back(Location(xy_v[i][0],xy_v[i][1]));
            }

            while (true)
            {
                if (platform.getBatteryPercentage() >= life)
                {
                    for (vector<Location>::const_iterator it = vxy.begin(); it != vxy.end(); it++)
                    {
                        MoveAction ma = platform.moveTo(*it, true, true);
                        while (ma.getStatus() != ActionStatusFinished)
                        {
                            if (ma.getStatus() == ActionStatusError)
                                break;
                        }
                    }
                    Sleep(1000);
                }
                else {

                    GetLocalTime(&sys);
                    logTest(test3,Word2String(sys.wYear) + "/" + Word2String(sys.wMonth) + "/" + Word2String(sys.wDay) + " - "
                        + Word2String(sys.wHour) + ":" + Word2String(sys.wMinute) + ":" + Word2String(sys.wSecond) + " [gohome] Battery is low " + "\n");
                    int i = 0;
                    while(!platform.getBatteryIsCharging())
                    {
                        logTest(test3, " [gohome] try go home" + Int2String(i) + "\n");
                        MoveAction gohome = platform.goHome();
                        while (gohome.getStatus() != ActionStatusFinished)
                        {
                            if (gohome.getStatus() == ActionStatusError)
                            {
                                break;
                            }
                        }
                        Sleep(5000);
                        i++;
                    }

                    GetLocalTime(&sys);
                    logTest(test3, Word2String(sys.wYear) + "/" + Word2String(sys.wMonth) + "/" + Word2String(sys.wDay) + " - "
                        + Word2String(sys.wHour) + ":" + Word2String(sys.wMinute) + ":" + Word2String(sys.wSecond) + " [charge] at home and charge...");
                    while (true)
                    {
                        if (platform.getBatteryPercentage() >= 98)
                        {
                            break;
                        }
                        else
                            Sleep(5000);
                    }
                    GetLocalTime(&sys);
                    logTest(test3, Word2String(sys.wYear) + "/" + Word2String(sys.wMonth) + "/" + Word2String(sys.wDay) + " - "
                        + Word2String(sys.wHour) + ":" + Word2String(sys.wMinute) + ":" + Word2String(sys.wSecond) + " [charge] ok ...");

                }
            }
        }
        catch (rpos::system::detail::ExceptionBase &e)
        {
            SYSTEMTIME sys;
            GetLocalTime(&sys);
            cout << " END time : " << sys.wYear << "/" << sys.wMonth << "/" << sys.wDay << " - " << sys.wHour << ":" << sys.wMinute << ":" << sys.wSecond << endl;
            cout << " battery life  : " << platform.getBatteryPercentage() << endl;
            cout << " connection fail " << e.what() << endl;
            exit(1);
        }
    }

    void Tools::BatteryChargeTest()
    {
    #ifndef test2
    #define test2 "BatteryChargeTest"
    #endif
        int count;
        int life = 0;
        int time;
        SYSTEMTIME sys;
        DWORD start;
        double x1, y1, x2, y2;
        if (argc > 5)
        {
            time = (atoi)(args[4]);
            life = (atoi)(args[5]);
        }
        try {

            getPT();
            GetLocalTime(&sys);
            logTest(test2, " --------------------------------------------------\n");
            logTest(test2, " BEGIN time : " + Word2String(sys.wYear) + "/" + Word2String(sys.wMonth) + "/" + Word2String(sys.wDay) + " - "
                + Word2String(sys.wHour) + ":" + Word2String(sys.wMinute) + ":" + Word2String(sys.wSecond) + "\n");
            logTest(test2, " battery life  : " + Int2String(platform.getBatteryPercentage()) + "\n");
            logTest(test2, " battery life check line : " + Int2String(life) + "\n");
            logTest(test2, " --------------------------------------------------\n");
            logTest(test2, " ----- > every [ " + Int2String(time) + " ] seconds check once \n");
            while (true)
            {
                if (!platform.getBatteryIsCharging())
                {
                    logTest(test2, " fail on battery is not charging ");
                    break;
                }
                if (platform.getBatteryPercentage() >= life)
                {
                    logTest(test2, " percentage is higher than " + Int2String(life) + "%" );
                    break;
                }
                GetLocalTime(&sys);
                logTest(test2, Word2String(sys.wYear) + "/" + Word2String(sys.wMonth) + "/" + Word2String(sys.wDay) + " - " +
                    Word2String(sys.wHour) + ":" + Word2String(sys.wMinute) + ":" + Word2String(sys.wSecond) + "--" + Int2String(platform.getBatteryPercentage()) + "\n");
                Sleep(time * 1000);
            }
            GetLocalTime(&sys);
            logTest(test2, " --------------------------------------------------\n");
            logTest(test2, " END time : " + Word2String(sys.wYear) + "/" + Word2String(sys.wMonth) + "/" + Word2String(sys.wDay) + " - "
                + Word2String(sys.wHour) + ":" + Word2String(sys.wMinute) + ":" + Word2String(sys.wSecond) + "\n");
            logTest(test2, " battery life  : " + Int2String(platform.getBatteryPercentage()) + "\n");
            logTest(test2, " --------------------------------------------------\n");

        }
        catch (rpos::robot_platforms::ConnectionFailException &e)
        {
            GetLocalTime(&sys);
            cout << " END time : " << sys.wYear << "/" << sys.wMonth << "/" << sys.wDay << " - " << sys.wHour << ":" << sys.wMinute << ":" << sys.wSecond << endl;
            cout << " connection fail " << e.what() << endl;
        }
        catch (rpos::system::detail::ExceptionBase & e) {
            GetLocalTime(&sys);
            cout << " END time : " << sys.wYear << "/" << sys.wMonth << "/" << sys.wDay << " - " << sys.wHour << ":" << sys.wMinute << ":" << sys.wSecond << endl;
            cout << " fail on " << e.what() << endl;
        }
    }

    void Tools::TurnLRTest()
    {
    #ifndef test4
    #define test4 "TurnLRTest"
    #endif
        int time;
        if (argc > 4)
        {
            time = atoi(args[4]);
        }
        else {
            logTest(test4,"[error] - wrong with - argc\n");
        }
        TurnLeft(time / 2);
        TurnRight(time / 2);
        platform.rotate(Rotation(0, 0, 0));
    }

    void Tools::TurnLeft(int time)
    {

        try {
            SYSTEMTIME sys;
            DWORD start;
            float www = 1.129;
            GetLocalTime(&sys);
            logTest(test4, " --------------------------------------------------\n");
            logTest(test4, "-------------------------------- \n");
            logTest(test4, " 逆时针转动 : " + Int2String(time) + " s\n");
            logTest(test4, " Begin time : " + Word2String(sys.wYear) + "/" + Word2String(sys.wMonth) + "/" + Word2String(sys.wDay) + " - "
                + Word2String(sys.wHour) + ":" + Word2String(sys.wMinute) + ":" + Word2String(sys.wSecond) + "\n");
            logTest(test4, "  ------- 运行中 (s) : 0 -> " + Int2String(time) + "\n");
            start = GetTickCount();

            MoveAction ma = platform.rotate(Rotation(www * time, 0, 0));

            while (ma.getStatus() != ActionStatusFinished)
            {
                if (GetTickCount() - start > 1000 * time)
                {
                    platform.rotate(Rotation(0, 0, 0));
                    break;
                }

            }
            GetLocalTime(&sys);
            logTest(test4, " End time : " + Word2String(sys.wYear) + "/" + Word2String(sys.wMonth) + "/" + Word2String(sys.wDay) + " - "
                + Word2String(sys.wHour) + ":" + Word2String(sys.wMinute) + ":" + Word2String(sys.wSecond) + "\n");
        }
        catch (rpos::system::detail::ExceptionBase &e)
        {
            logTest(test4, " fail on " + e.toString() + "\n");
        }
    }

    void Tools::TurnRight(int time)
    {

        try {
            SYSTEMTIME sys;
            DWORD start;
            float www = 1.129;
            GetLocalTime(&sys);
            logTest(test4, " --------------------------------------------------\n");
            logTest(test4, "-------------------------------- \n");
            logTest(test4, " 顺时针转动 : " + Int2String(time) + " s\n");
            logTest(test4, " Begin time : " + Word2String(sys.wYear) + "/" + Word2String(sys.wMonth) + "/" + Word2String(sys.wDay) + " - "
                + Word2String(sys.wHour) + ":" + Word2String(sys.wMinute) + ":" + Word2String(sys.wSecond) + "\n");
            logTest(test4, "  ------- 运行中 (s) : 0 -> " + Int2String(time) + "\n");
            start = GetTickCount();

            MoveAction ma = platform.rotate(Rotation(www * time, 0, 0));

            while (ma.getStatus() != ActionStatusFinished)
            {
                if (GetTickCount() - start > 1000 * time)
                {
                    platform.rotate(Rotation(0, 0, 0));
                    break;
                }
            }
            GetLocalTime(&sys);
            logTest(test4, " End time : " + Word2String(sys.wYear) + "/" + Word2String(sys.wMonth) + "/" + Word2String(sys.wDay) + " - "
                + Word2String(sys.wHour) + ":" + Word2String(sys.wMinute) + ":" + Word2String(sys.wSecond) + "\n");
        }
        catch (rpos::system::detail::ExceptionBase &e)
        {
            logTest(test4, " fail on " + e.toString() + "\n");
        }
    }



    void Tools::HelpInfo()
    {
        cout << "[ help info ] --------------------------------" << endl;
        cout << " usage : " << endl
            << " -h     :   show help info " << endl
            << " -t  [test[1/2/3/4]] [args]     :   run test1 with args " << endl
            << " test1  : battery host test " << endl
            << " test2  : battery charge time test " << endl
            << " test3  : move and go home test  " << endl
            << " test4  : turn left and right test " << endl
            << " [test1] ------------------------------> " << endl
            << " [test1] example: " << endl
            << " exe -t ipaddress    test1 time [moveoption]" << endl
            << " exe -t 192.168.11.1 test1 5" << endl
            << " exe -t ipaddress    test1 time count=2 p1x p1y p2x p2y" << endl
            << " exe -t 192.168.11.1 test1 5     2       0   0   1   1  " << endl
            << " [test2] ------------------------------> " << endl
            << " exe -t ipaddress    test2 time battery_life " << endl
            << " exe -t 192.168.11.1 test2 5    98 " << endl
            << " [test3] ------------------------------> " << endl
            << " exe -t ipaddress    test3 life count=2 p1x p1y p2x p2y" << endl
            << " exe -t 192.168.11.1 test3 30    2      0   1    0   2 " << endl
            << " [test4] ------------------------------> " << endl
            << " exe -t ipaddress    test4 time " << endl
            << " exe -t 192.168.11.1 test4 100 " << endl
            << " ---------------------------------------------" << endl;

    }


    void Tools::logTest(string test,string logstr)
    {
        cout << logstr << endl;
        string logname = "log\\" + test + ".log";
        FILE *fp;
        fp = fopen( logname.c_str(), "a");
        fprintf(fp,logstr.c_str());
        fclose(fp);

    }

    string Tools::Word2String(WORD w)
    {
        char tmpbuff[16];
        sprintf(tmpbuff, "%d", w);
        string str = tmpbuff;
        return str;
    }

    string Tools::Int2String(int value)
    {
        stringstream ss;
        string str;
        ss << value;
        ss >> str;
        return str;
    }


    void Tools::getPT()
    {
    try {
        string ip = args[2];
        platform = SlamwareCorePlatform::connect(ip, 1445, 10000);
        
    }
    catch (ConnectionTimeOutException e)
    {
        std::cout << e.what() << endl;
    }
    catch (ConnectionFailException e)
    {
        std::cout << e.what() << endl;
        exit(1);
    }
}
```

### Source.cpp

```c

    #include"Header.h"
    int main(int argc,char *args[])
    {
        Tools tool = Tools(argc, args);
        tool.execArgs();
        return 0;
    }
```

> #### LINK

* nothing to show
