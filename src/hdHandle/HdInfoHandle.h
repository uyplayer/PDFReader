//
// Created by uyplayer on 2024-06-23.
//

#ifndef HDINFOHANDLE_H
#define HDINFOHANDLE_H

#include <iostream>
#include <string>
#include <QSysInfo>



#ifdef _WIN32
#include <windows.h>
#include <iphlpapi.h>
#pragma comment(lib, "iphlpapi.lib")
#elif __linux__
#include <fstream>
#elif __APPLE__
#include <sys/socket.h>
#include <sys/sysctl.h>
#include <net/if_dl.h>
#include <ifaddrs.h>
#endif

class HdInfoHandle {
public:
    HdInfoHandle() = default;

    static void generate();

private:
    static std::string getMacAddress();


    static std::string systemName;
    static std::string systemVersion;
    static std::string systemKernel;
    static std::string systemArch;
    static std::string systemHostname;
    static std::string macAddress;
    static std::string key_info;
};

#endif //HDINFOHANDLE_H
