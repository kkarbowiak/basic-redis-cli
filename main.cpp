#include "argparse.h"
#include "redis_client.h"
#include <stdexcept>


void send_command(RedisClient & client, std::string const & command)
{
    auto result = client.send_command(command);
    std::cout << result << "\n";
}

void set_value(RedisClient & client, std::string const & key, std::string const & value)
{
    send_command(client, "SET " + key + " " + value);
}

void get_value(RedisClient & client, std::string const & key)
{
    send_command(client, "GET " + key);
}

int main(int argc, char * argv[])
{
    try
    {
        auto parser = argparse::ArgumentParser();
        parser.add_argument("address").help("Redis server address");
        parser.add_argument("-p", "--port").type<int>().default_(6379).help("Redis server port number (default: 6379)");
        auto group = parser.add_mutually_exclusive_group();
        group.add_argument("-s", "--set").nargs(2).help("sets key to value");
        group.add_argument("-g", "--get").help("gets value for key");

        auto parsed = parser.parse_args(argc, argv);

        auto client = RedisClient(parsed.get_value("address"), parsed.get_value<int>("port"));

        if (parsed.get("set"))
        {
            auto const set_data = parsed.get_value<std::vector<std::string>>("set");
            set_value(client, set_data[0], set_data[1]);
        }

        if (parsed.get("get"))
        {
            get_value(client, parsed.get_value("get"));
        }
    }
    catch (std::exception const & e)
    {
        std::cout << "Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
