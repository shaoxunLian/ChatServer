#include "usermodel.hpp"
#include "db.h"
#include <iostream>

//将用户传输过来的数据合成一个user对象，插入到我们在mysql创建的user表中
bool UserModel::insert(User &user)
{
    // 1、组装用户传进来的sql语句
    char sql[1024] = {0};
    //格式化输出字符串，并将结果写入到指定的缓冲区，将insert into user(name, password, state) values(这里为Name, 这里为password, '这里为state')
    //写到字符串sql中
    snprintf(sql, sizeof(sql), "insert into user(name, password, state) values('%s', '%s', '%s')",
        user.getName().c_str(), user.getPassword().c_str(), user.getState().c_str());

    MySQL mysql;
    if (mysql.connect())
    {
        if (mysql.update(sql))//数据库连接成功以后将用户数据存入数据库中
        {
            //获取插入成功的用户数据生成的主键ID，ID由数据库自动生成
            user.setId(mysql_insert_id(mysql.getConnection()));
            return true;
        } 
    }

    return false;
}

// 根据用户号码查询用户信息
User UserModel::query(int id)
{
    char sql[1024] = {0};
    snprintf(sql, sizeof(sql), "select * from user where id = %d", id);

    MySQL mysql;
    if (mysql.connect())
    {
        MYSQL_RES *res = mysql.query(sql);
        if (res != nullptr)
        {
            MYSQL_ROW row = mysql_fetch_row(res);
            if (row != nullptr)
            {
                // 生成一个User对象，填入信息
                User user;
                user.setId(atoi(row[0]));
                user.setName(row[1]);
                user.setPassword(row[2]);
                user.setState(row[3]);
                mysql_free_result(res);
                return user;
            }
        }

    }

    // 返回空User
    return User();
}

bool UserModel::updateState(User user)
{
    char sql[1024] = {0};
    snprintf(sql, sizeof(sql), "update user set state = '%s' where id =%d", user.getState().c_str(), user.getId());

    MySQL mysql;
    if (mysql.connect())
    {
        if (mysql.update(sql))
        {
            return true;
        }
    }
    return false;
}

// 重置用户的状态信息
void UserModel::resetState()
{
    // 1.组装sql语句
    char sql[1024] = "update user set state = 'offline' where state = 'online'";

    MySQL mysql;
    if (mysql.connect())
    {
        mysql.update(sql);
    }
}