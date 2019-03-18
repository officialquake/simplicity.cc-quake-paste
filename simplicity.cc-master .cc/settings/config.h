/*
 *  config.h
 */
#pragma once

#include <vector>
#include <fstream>
#include <sys/stat.h>

using namespace std;

class c_config
{
private:
    
    string folder;
    string current_config;
    const vector<const char*> configs = {"one", "two", "three"};
    
public:
    
    c_config();
    
    void init();
    
    void load();
    void save();
    
    vector<const char*> get_configs() { return this->configs; }
    
public:
    
    int config_no;
    
};

extern c_config* config;

