//
// Created by  on 2024-06-23.
//

#include "HdInfoHandle.h"
#include "KeyInfoDialog.h"
#include <QSysInfo>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <QString>



std::string HdInfoHandle::key_info;
std::string HdInfoHandle::systemName;
std::string HdInfoHandle::systemVersion;
std::string HdInfoHandle::systemKernel;
std::string HdInfoHandle::systemArch;
std::string HdInfoHandle::systemHostname;
std::string HdInfoHandle::macAddress;



void HdInfoHandle::generate() {
    systemName = QSysInfo::prettyProductName().toStdString();
    systemVersion = QSysInfo::productVersion().toStdString();
    systemKernel = QSysInfo::kernelType().toStdString();
    systemArch = QSysInfo::currentCpuArchitecture().toStdString();
    systemHostname = QSysInfo::machineHostName().toStdString();
    macAddress = getMacAddress();
    key_info = systemName + systemVersion + systemKernel + systemArch + systemHostname + macAddress;
    key_info.erase(std::remove(key_info.begin(), key_info.end(), ' '), key_info.end());
    KeyInfoDialog dialog(key_info);
    dialog.exec();
}

std::string HdInfoHandle::getMacAddress() {
    std::string macAddress;

#ifdef _WIN32
    // Windows specific code
    IP_ADAPTER_INFO AdapterInfo[16];
    DWORD dwBufLen = sizeof(AdapterInfo);

    DWORD dwStatus = GetAdaptersInfo(AdapterInfo, &dwBufLen);

    if (dwStatus == ERROR_SUCCESS) {
        PIP_ADAPTER_INFO pAdapterInfo = AdapterInfo;
        macAddress.reserve(18);

        for (UINT i = 0; i < pAdapterInfo->AddressLength; i++) {
            if (i > 0)
                macAddress += ':';
            char buf[3];
            sprintf_s(buf, "%02X", static_cast<int>(pAdapterInfo->Address[i]));
            macAddress += buf;
        }
    }
#elif __linux__
    // Linux specific code
    std::ifstream file("/sys/class/net/eth0/address");
    if (file.is_open()) {
        std::getline(file, macAddress);
        file.close();
    }
#elif __APPLE__
    // macOS specific code
    struct ifaddrs *ifAddrStruct = nullptr;
    struct ifaddrs *ifa = nullptr;
    void *addrPtr = nullptr;

    int result = getifaddrs(&ifAddrStruct);
    if (result == 0) {
        for (ifa = ifAddrStruct; ifa != nullptr; ifa = ifa->ifa_next) {
            if (ifa->ifa_addr->sa_family == AF_LINK) {
                struct sockaddr_dl* sdl = (struct sockaddr_dl*)ifa->ifa_addr;
                if (sdl->sdl_type == IFT_ETHER && (strcmp(ifa->ifa_name, "en0") == 0)) {
                    unsigned char *ptr = (unsigned char*)LLADDR(sdl);
                    std::ostringstream oss;
                    oss << std::hex << std::uppercase << std::setfill('0');
                    for (int i = 0; i < sdl->sdl_alen; i++) {
                        if (i > 0) oss << ":";
                        oss << std::setw(2) << static_cast<int>(ptr[i]);
                    }
                    macAddress = oss.str();
                    break;
                }
            }
        }
        freeifaddrs(ifAddrStruct);
    }
#endif

    return macAddress;
}




std::string HdInfoHandle::get_key_info() {
    systemName = QSysInfo::prettyProductName().toStdString();
    systemVersion = QSysInfo::productVersion().toStdString();
    systemKernel = QSysInfo::kernelType().toStdString();
    systemArch = QSysInfo::currentCpuArchitecture().toStdString();
    systemHostname = QSysInfo::machineHostName().toStdString();
    macAddress = getMacAddress();
    key_info = systemName + systemVersion + systemKernel + systemArch + systemHostname + macAddress;
    key_info.erase(std::remove(key_info.begin(), key_info.end(), ' '), key_info.end());
    return key_info;
}