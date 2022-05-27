#include "argparse.h"
#include <hiredis/hiredis.h>


void send_command(std::string const & command)
{
    auto redis_context = redisConnect("127.0.0.1", 6379);
    auto redis_reply = redisCommand(redis_context, command.c_str());
    freeReplyObject(redis_reply);
}

void set_value(std::string const & key, std::string const & value)
{
    send_command("SET " + key + " " + value);
}

void get_value(std::string const & key)
{
    send_command("GET " + key);
}

int main(int argc, char * argv[])
{
    try
    {
        auto parser = argparse::ArgumentParser();
        auto group = parser.add_mutually_exclusive_group();
        group.add_argument("-s", "--set").nargs(2).help("sets key to value");
        group.add_argument("-g", "--get").help("gets value for key");

        auto parsed = parser.parse_args(argc, argv);

        if (parsed.get("set"))
        {
            auto const set_data = parsed.get_value<std::vector<std::string>>("set");
            set_value(set_data[0], set_data[1]);
        }

        if (parsed.get("get"))
        {
            get_value(parsed.get_value("get"));
        }
    }
    catch (std::exception const & e)
    {
        std::cout << "Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
