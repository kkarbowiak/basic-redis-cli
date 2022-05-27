#include "argparse.h"


int main(int argc, char * argv[])
{
    auto parser = argparse::ArgumentParser();
    auto group = parser.add_mutually_exclusive_group();
    group.add_argument("-s", "--set").nargs(2).help("sets key to value");
    group.add_argument("-g", "--get").nargs(1).help("gets value for key");

    auto parsed = parser.parse_args(argc, argv);

    return 0;
}
