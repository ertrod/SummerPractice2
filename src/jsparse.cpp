#include "practice.h"

namespace practice
{
    std::string start_prop(bool is_more, std::string prop, std::map<std::string, std::string>& values, int lvl ) // начало элемента json
    {
        std::string obj;
        std::string tabs = "";
        std::string itabs = "";
        
        for (int i = 0; i < lvl; i++)
            tabs += "\t";
        
        obj += tabs + "\"" + prop + "\" : {\n";
        itabs += tabs + "\t";

        int pos = 0;

        if (values.size())
        {
            for (std::map<std::string, std::string>::iterator val = values.begin(); val != values.end(); val++)
            {
                if (pos == 0)
                    obj += itabs + "\"" + val->first + "\"" + " : " + "\"" + val->second + "\"";
                else
                    obj += ",\n" + itabs + "\"" + val->first + "\"" + " : " + "\"" + val->second + "\"";
            }
            if (is_more)
                obj += ",\n";
            else
                obj += "\n";
        }
        
        return obj;
    }

    std::string obj_to_json(std::string prop, std::map<std::string, std::string>& values, int lvl) 
    {
        std::string obj;
        std::string tabs = "";
        std::string itabs = "";
        
        for (int i = 0; i < lvl; i++)
            tabs += "\t";
        
        obj += tabs + "\"" + prop + "\" : {\n";
        itabs += tabs + "\t";

        int pos = values.size() - 1;

        for (std::map<std::string, std::string>::iterator val = values.begin(); val != values.end(); val++)
        {
            if (pos)
                obj += itabs + "\"" + val->first + "\"" + " : " + "\"" + val->second + "\",";
            else
                obj += itabs + "\"" + val->first + "\"" + " : " + "\"" + val->second + "\"";
            obj += "\n";
            pos--;
        }
        obj += tabs + "}";
        
        return obj;
    }

    std::string close_prop(std::string prop, std::map<std::string, std::string>& values, int lvl) // закрытие объекта json
    {
        std::string obj;
        std::string tabs;
        
        for (int i = 0; i < lvl; i++)
            tabs += "\t";
        
        obj += tabs + "}";
        
        return obj;
    }

    std::string get_prop(std::ifstream& file) // получение атрибута
    {
        char c;
        std::string prop = "";

        while(!file.eof() && file.get(c) && c != '\"');
        while(!file.eof() && file.get(c) && c != '\"')
            prop += c;

        return prop;
    }

    std::map<std::string, std::string> next_pair(std::ifstream& file) // получение пары атрибут-значение
    {
        std::map<std::string, std::string> m;
        std::string first;
        std::string second;

        first = get_prop(file);
        second = get_prop(file);
        m[first] = second;
        
        return m;
    }
}