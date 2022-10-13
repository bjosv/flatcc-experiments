#include <stdio.h>

#include "example_builder.h"
#include "example_json_printer.h"

int main(int argc, char *argv[]) {
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

  char json_buffer[1000];
  flatcc_json_printer_t printer;
  flatcc_json_printer_init_buffer(&printer, json_buffer, sizeof(json_buffer));

  /* Results in:
   * warning: use of a signed integer operand with a binary bitwise operator
   * [hicpp-signed-bitwise]
   */
  flatcc_json_printer_set_flags(&printer, flatcc_json_printer_f_unquote |
                                              flatcc_json_printer_f_noenum);

  example_print_json(&printer, (char *)buffer, size);
  size_t printed_size = flatcc_json_printer_flush(&printer);

  printf("%.*s\n", (int)printed_size, json_buffer);
  flatcc_builder_clear(&builder);
}
