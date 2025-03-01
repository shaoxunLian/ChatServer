#ifndef __GROUP_MODEL_H
#define __GROUP_MODEL_H

#include "group.hpp"
#include <string>
#include <vector>

//model结尾的代码都是用来操作我们在mysql建立好的相应的表的方法

class GroupModel
{
public:
    // 创建群组
    bool createGroup(Group &group);
    // 加入群组
    void addGroup(int userid, int groupid, std::string role);
    // 查询用户所在群组信息,所在的群，以及群组成员信息
    std::vector<Group> queryGroups(int userid);
    // 根据指定的groupid查询群组用户id列表，除userid自己，主要用户群聊业务给群组其它成员群发消息
    std::vector<int> queryGroupUsers(int userid, int groupid);

};

#endif // __GROUP_MODEL_H