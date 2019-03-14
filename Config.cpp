#include "Config.h"
#include "StringUtils.h"

Config::Config()
{
    m_split = '=';
    m_comment = '#';
}

Config::~Config()
{
}

void Config::configIn(string fileName)
{
    ifstream fin(fileName);
    if(!fin)
    {
        cout<<"config in file open wrong"<<endl;
        return;
    }
    
    string line;
    while(getline(fin, line))
    {
        StringUtils::deleteAllMark(line, " ");
        StringUtils::deleteAllMark(line, "\t");
        StringUtils::removeComment(line, m_comment);
        vector<string> data;
        StringUtils::split2vec(line, data, m_split);
        if(data.size() == 0)
            continue;
        if(data.size() != 2)
        {
            cout<<"config line split size = "<<data.size()<<endl;
            break;
        }
        m_datas[data[0]] = data[1];
    }
    fin.close();
}

void Config::configOut(string fileName)
{
    ofstream fout;
    fout.open(fileName);
    if(!fout)
    {
        cout<<"config out file open wrong"<<endl;
        return;
    }
    
    for(auto it = m_datas.begin();it != m_datas.end();it++)
    {
        fout<<it->first<<m_split<<it->second<<'\n';
    }
    fout.close();
}

int Config::getInt(string key, int def)
{
    if(m_datas.find(key) != m_datas.end())
    {
        stringstream ss("");
        int ret = 0;
        ss<<m_datas[key];
        ss>>ret;
        return ret;
    }
    return def;
}

string Config::getStr(string key, string def)
{
    if(m_datas.find(key) != m_datas.end())
        return m_datas[key];
    return def;
}

/*
char line[100];
while(fin.getline(line, 100))
{
    
}

string data;
while(fin>>data)//space split
{
    
}
 */
