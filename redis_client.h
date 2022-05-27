#pragma once

#include <string>
#include <hiredis/hiredis.h>


class RedisClient
{
    public:
        RedisClient(std::string const & ip, int port);
        ~RedisClient();

        std::string send_command(std::string const & command);

    private:
        RedisClient(RedisClient const &) = delete;
        RedisClient & operator=(RedisClient const &) = delete;

    private:
        redisContext * m_redis_context;
};
