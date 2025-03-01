#ifndef CHATSERVICE_H
#define CHATSERVICE_H

#include <muduo/net/TcpConnection.h>
#include <unordered_map>
#include <functional>
#include <mutex>
#include "json.hpp"
#include "user.hpp"
#include "usermodel.hpp"
#include "offlinemessagemodel.hpp"
#include "friendmodel.hpp"
#include "group_model.hpp"
#include "redis.hpp"


using json = nlohmann::json;
using namespace muduo;
using namespace muduo::net;

// 处理消息事件的回调函数类型
using MsgHandler = std::function<void(const TcpConnectionPtr&, json&, Timestamp)>;

// 聊天服务器业务类
class ChatService
{
public:
    // ChatService 单例模式,获取单例对象的接口函数
    // thread safe
    static ChatService* instance()
    {
        static ChatService service;
        return &service;
    }

    // 登录业务
    void loginHandler(const TcpConnectionPtr &conn, json &js, Timestamp time);
    // 注册业务
    void registerHandler(const TcpConnectionPtr &conn, json &js, Timestamp time);
    //处理注销业务
    void loginoutHandler(const TcpConnectionPtr &conn, json &js, Timestamp time);

    // 一对一聊天业务
    void oneChatHandler(const TcpConnectionPtr &conn, json &js, Timestamp time);

    // 处理客户端异常退出
    void clientCloseExceptionHandler(const TcpConnectionPtr &conn);

    // 获取对应消息的处理器
    MsgHandler getHandler(int msgId);

    // 创建群组业务
    void createGroup(const TcpConnectionPtr &conn, json &js, Timestamp time);
    // 加入群组业务
    void addGroup(const TcpConnectionPtr &conn, json &js, Timestamp time);
    // 群组聊天业务
    void groupChat(const TcpConnectionPtr &conn, json &js, Timestamp time);

    // 服务端异常终止之后的操作
    void reset();

     // 添加好友业务
    void addFriendHandler(const TcpConnectionPtr &conn, json &js, Timestamp time);

    //redis订阅消息触发的回调函数
    void redis_subscribe_message_handler(int channel, string message);



private:
    //单例类的构造函数是私有的,要用单例来设计，首先要将构造函数私有化
    //单例模式（单例类）： 即该类只有一个实例化对象，不管外部声明调用多少次，其本质也都是访问同一块内存。
    //单例模式的核心是构造方法的私有化（即在入口处限制了对象的实例化），之后在类的内部实例化对象，并通过静态方法返回实例化对象的引用。
    ChatService();

    // 存储消息id和其对应的业务处理方法,这个表要存的事件处理方法 运行的时候就存好了 是确定的 不会随着程序执行而要存越来越多
    //的数据，所以不存在线程安全问题
    std::unordered_map<int, MsgHandler> _msgHandlerMap;

    //存储在线用户的通信连接，随着服务器的运行 会有很多客户连接 访问并添加数据到表中的次数会很多 也就是表被访问并且
    //数据是不断被改变的 是不确定的 所以有线程安全问题；共享数据被多线程访问后的结果和单线程访问的结果是一致的就是线程安全
    std::unordered_map<int,TcpConnectionPtr> _userConnMap;

    //定义互斥锁，保证_userConnMap的线程安全
    std::mutex _connMutex;

    // 数据操作类对象
    UserModel _userModel;
    OfflineMsgModel _offlineMsgModel;
    FriendModel _friendModel;
    GroupModel _groupModel;

    //redis操作对象
    Redis _redis;

};

#endif // CHATSERVICE_H