#ifndef PUBLIC_H
#define PUBLIC_H

// server和client的公共头文件,当int X == EnMsgType.LOGIN_MSG 时 说明要处理登录事件
enum EnMsgType
{
    LOGIN_MSG = 1,  // 登录消息
    LOGIN_MSG_ACK,//登录响应消息2
    LOGINOUT_MSG,      // 注销消息3
    REGISTER_MSG ,     // 注册消息.4
    REGISTER_MSG_ACK, //注册相应消息5
    ONE_CHAT_MSG,   // 聊天消息6
    ADD_FRIEND_MSG ,   // 添加好友消息7

    CREATE_GROUP_MSG,  // 创建群组8
    ADD_GROUP_MSG,     // 加入群组9
    GROUP_CHAT_MSG,    // 群聊天10

};



#endif // PUBLIC_H