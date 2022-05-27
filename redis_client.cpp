#include "redis_client.h"
#include <stdexcept>


RedisClient::RedisClient(std::string const & ip, int port)
  : m_redis_context(redisConnect(ip.c_str(), port))
{
    if (!m_redis_context)
    {
        throw std::runtime_error("connection error: could not allocate Redis context");
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
