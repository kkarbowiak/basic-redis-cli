#include "redis_client.h"
#include <stdexcept>


namespace
{
    class RedisReply
    {
        public:
            explicit RedisReply(void * reply)
              : m_redis_reply(static_cast<redisReply *>(reply))
            {
            }

            ~RedisReply()
            {
                freeReplyObject(m_redis_reply);
            }

            redisReply * get() const
            {
                return m_redis_reply;
            }

        private:
            RedisReply(RedisReply const &) = delete;
            RedisReply & operator=(RedisReply const &) = delete;

        private:
            redisReply * m_redis_reply;
    };
}

RedisClient::RedisClient(std::string const & ip, int port)
  : m_redis_context(redisConnect(ip.c_str(), port))
{
    if (!m_redis_context)
    {
        throw std::runtime_error("Connection error: could not allocate Redis context");
    }
    if (m_redis_context->err)
    {
        redisFree(m_redis_context);
        throw std::runtime_error("Conneection error: " + std::string(m_redis_context->errstr));
    }
}

RedisClient::~RedisClient()
{
    redisFree(m_redis_context);
}

std::string RedisClient::send_command(std::string const & command)
{
    auto reply = RedisReply(redisCommand(m_redis_context, command.c_str()));
    if (!reply.get())
    {
        throw std::runtime_error("Command error: sending command failed");
    }
    if (reply.get()->type == REDIS_REPLY_ERROR)
    {
        throw std::runtime_error("Command error: " + std::string(reply.get()->str));
    }
    return std::string(reply.get()->str);
}
