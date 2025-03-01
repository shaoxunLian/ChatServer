#ifndef FRIENDMODEL_H
#define FRIENDMODEL_H
#include "user.hpp"
#include <vector>

//model结尾的代码都是用来操作我们在mysql建立好的相应的表的方法

// 维护好友信息的操作接口方法
class FriendModel
{
public:
    // 添加好友关系
    void insert(int userId, int friendId);

    // 返回用户好友列表
    std::vector<User> query(int userId);
};

#endif // FRIENDMODEL_H