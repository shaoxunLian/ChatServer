#ifndef USER_H
#define USER_H

//把数据库里面读出来的数据合成一个对象，提交给业务方去使用

#include <string>
//User表的ORM类，映射表的字段
class User
{
public:
    //给默认值
    User(int id = -1, std::string name = "", 
        std::string pwd = "", std::string state = "offline")
        : _id(id),
          _name(name),
          _state(state)
    {}

    void setId(const int &id) { _id = id; }
    void setName(const std::string &name) { _name = name; }
    void setPassword(const std::string &paw) { _password = paw; }
    void setState(const std::string &state) { _state = state; }

    int getId() { return _id; }
    std::string getName() { return _name; } 
    std::string getPassword() { return _password; } 
    std::string getState() { return _state; } 

protected:
    int _id;
    std::string _name;
    std::string _password;
    std::string _state;    
};


#endif // USER_H