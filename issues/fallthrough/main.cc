#include "example_builder.h"
#include "flatcc/support/hexdump.h"

#include <algorithm>
#include <boost/lambda/lambda.hpp>
#include <iostream>

int main(int argc, char *argv[]) {
    (void) argc;
    (void) argv;

    flatcc_builder_t builder;
    flatcc_builder_init(&builder);
    Example_Obj_start_as_root(&builder);
    Example_Obj_value_add(&builder, 40);
    Example_Obj_name_create_str(&builder, "Bob");
    Example_Obj_end_as_root(&builder);

    void *buffer;
    size_t size;
    buffer = flatcc_builder_get_direct_buffer(&builder, &size);
    assert(buffer);

    hexdump("example", buffer, size, stdout);
    flatcc_builder_clear(&builder);

    // Use boost
    typedef std::istream_iterator<int> in;
    std::cout << "Type in any number: ";
    std::for_each(in(std::cin), in(),
                  std::cout << (boost::lambda::_1 * 10)
                  << "\nType in another number: ");
    return 0;
}
