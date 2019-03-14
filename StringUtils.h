#ifndef _StringUtils_h
#define _StringUtils_h

#include <vector>
#include <string>

using namespace std;

namespace StringUtils
{
    void deleteAllMark(string& str, const string& mark)
    {
        auto size = mark.size();
        while(1)
        {
            auto pos = str.find(mark);
            if(pos == string::npos)
                return;
            str.erase(pos, size);//str.replace(pos, mark.size(), "");
        }
    }
    
    void removeComment(string& str, const char comment)
    {
        auto pos = str.find(comment);
        if(pos != string::npos)
            str = str.substr(0, pos);
    }
    
    void split2vec(string& str, vector<string> data, const char split = '=')
    {
        size_t start = 0;
        size_t end = 0;
        while(start < str.size())
        {
            end = str.find(split, start);
            if(end == string::npos)
                return;
            string temp = str.substr(start, end-start);
            data.push_back(temp);
            start = end+1;
        }
    }
}

#endif
