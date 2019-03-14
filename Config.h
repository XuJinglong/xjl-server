#ifndef _Config_h
#define _Config_h

#include <map>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

class Config
{
public:
    Config();
    virtual ~Config();
    
    void configIn(string fileName);
    void configOut(string fileName);
    int getInt(string key, int def = 0);
    string getStr(string key, string def = "");
    
    template<class T>
    void addRecord(string key, T value)
    {
        stringstream ss("");
        string valueStr;
        ss<<value;
        m_datas[key] = ss.str();
    }
public:
    char m_split;
    char m_comment;
private:
    map<string, string> m_datas;
};

#endif
