#pragma once
#include <stdio.h>
#include <string>
using namespace std;

struct UDP_CONFIG {
    string ip_address;
    int port;
};

struct DISPLAY_CONFIG {
    string FS_config_path;
    UDP_CONFIG UDP_config;

};