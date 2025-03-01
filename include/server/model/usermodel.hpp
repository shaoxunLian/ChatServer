//专门操作model的类，提供相应的数据库操作方法，讲义中那张表的数据操作类
#ifndef USERMODEL_H
#define USERMODEL_H

#include "user.hpp"

//model结尾的代码都是用来操作我们在mysql建立好的相应的表的方法

//User表的数据操作类
class UserModel
{
public:
    // User表的插入方法
    bool insert(User &user);

    // 根据用户号码查询用户信息
    User query(int id);

    // 更新用户的状态信息
    bool updateState(User user);

    // 重置用户的状态信息
    void resetState();
};

#endif // USERMODEL_H