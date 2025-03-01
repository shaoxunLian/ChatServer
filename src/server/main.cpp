#include "chatserver.hpp"
#include "chatservice.hpp"
#include <muduo/base/Logging.h>
#include <signal.h>
#include <iostream>
using namespace std;

// 捕获SIGINT的处理函数,处理服务器ctrl+c结束后，重置user的状态信息
void resetHandler(int)
{
    LOG_INFO << "capture the SIGINT, will reset state\n";
    ChatService::instance()->reset();
    exit(0);
}

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        //cerr << "command invalid! example: ./ChatServer 127.0.0.1 6000" << endl;
        cerr << "command invalid! example: ./ChatServer 6000" << endl;
        exit(-1);
    }

    // // 解析通过命令行参数传递的ip和port
    // char *ip = argv[1];
    //uint16_t port = atoi(argv[2]);
    uint16_t port = atoi(argv[1]);

    signal(SIGINT, resetHandler);
    
    EventLoop loop;
    InetAddress addr("192.168.242.128",port);
    ChatServer server(&loop, addr, "ChatServer");

    server.start();
    loop.loop();

    return 0;
}