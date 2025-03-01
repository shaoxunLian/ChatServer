#ifndef OFFLINEMESSAGEMODEL_H
#define OFFLINEMESSAGEMODEL_H
#include <string>
#include <vector>
using namespace std;

//model结尾的代码都是用来操作我们在mysql建立好的相应的表的方法

// 提供离线消息表的操作接口方法
class OfflineMsgModel
{
public:
    // 存储用户的离线消息
    void insert(int userId, std::string msg);

    // 删除用户的离线消息
    void remove(int userId);

    // 查询用户的离线消息
    std::vector<std::string> query(int userId);
};
#endif