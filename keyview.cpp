/* keyview.cpp
 *
 * Author: Austin Voecks
 *
 * Usage:
 *    sudo keyview (input_device_name) [output_log_file]
 */

#include "keyview.h"

int
main(int argc, char **argv) {

  // variables
  int    num_keys, fd;
  struct input_event ev;
  bool   is_modifier_key, shift_state, alt_state, ctrl_state;
  char  *program_name, *device_name, *output_name;
  STATE  state;

  std::string key, shift_key;
  std::ofstream output_file;

  // initialize
  shift_state  = false;
  alt_state    = false;
  ctrl_state   = false;
  program_name = argv[0];
  device_name  = argv[1];
  output_name  = argv[2];
  num_keys     = sizeof(keys) / sizeof(*keys);

  // arguments
  if (argc < 2) {
    std::cerr << "usage: " << program_name
              << " (device) [log_file]" << std::endl;
    return EXIT_FAILURE;
  }

  // open the /dev/input/event device
  fd = open(device_name, O_RDONLY);

  if (fd < 0) {
    std::cerr << "could not open device '"
              << device_name << "'" << std::endl;
    return EXIT_FAILURE;
  }

  // open output file in append mode
  if (argc == 3) {
    output_file.open(output_name, std::ios::out | std::ofstream::app);
  }

  // set output to stdout or log file
  std::ostream & output = (argc == 3 ? output_file : std::cout);

  while (true) {

    // read the new key
    read(fd, &ev, sizeof(struct input_event));

    if (ev.type == 1) {
      key             = "";
      shift_key       = "";
      state           = S_NONE;
      is_modifier_key = false;

      // get key value
      if (ev.code < num_keys and keys[ev.code] != _U_) {
        key       = keys[ev.code];
        shift_key = shift_keys[ev.code];
      }

      // get key state
      switch (ev.value) {
        case 0: state = S_OFF ; break;
        case 1: state = S_ON  ; break;
        case 2: state = S_HOLD; break;
      }

      if (not key.empty() and state != S_NONE) {

        if (state == S_ON or state == S_HOLD) {     // on, hold

          if (key == rsh or key == lsh)               // shift
            is_modifier_key = shift_state = true;

          else if (key == ral or key == lal)          // alt
            is_modifier_key = alt_state = true;

          else if (key == rct or key == lct)          // ctrl
            is_modifier_key = ctrl_state = true;
        }
        else {                                      // off

          if (key == rsh or key == lsh)               // shift
            shift_state = false;

          else if (key == ral or key == lal)          // alt
            alt_state = false;

          else if (key == rct or key == lct)          // ctrl
            ctrl_state = false;
        }

        // output
        if (not is_modifier_key and state == S_ON) {

          if (shift_state) {

            if (shift_key != key)
              key = shift_key;
            else
              output << "shf_";
          }

          if (ctrl_state) output << "ctl_";
          if (alt_state)  output << "alt_";

          output << key << std::endl;
        }
      }
      else {
        printf("key %i state %i\n", ev.code, ev.value);
      }
    }
  }

  return EXIT_SUCCESS;
}
