/* keyview.cpp
 *
 * Author: Austin Voecks
 */

#include "keyview.h"

int main(int argc, char **argv)
{
  int    num_keys, fd, key_counter = 0;
  struct input_event ev;
  bool   is_modifier_key, shift_state, alt_state, ctrl_state, no_buffer;
  STATE  state;

  std::string key, shift_key;
  std::ofstream output_file;

  shift_state = alt_state = ctrl_state = no_buffer = false;
  num_keys = sizeof(keys) / sizeof(*keys);

  // arguments
  if (argc < 2) {
    std::cerr << "usage: " << argv[0] << " <device> [log_file]" << std::endl;
    return 1;
  }

  // open the /dev/input/event device
  fd = open(argv[1], O_RDONLY);

  if (fd < 0) {
    std::cerr << "could not open device '" << argv[1] << "'" << std::endl;
    return 1;
  }

  if (argc == 3) {
    // open output file in append mode, buffer output
    output_file.open(argv[2], std::ios::out | std::ofstream::app);
    no_buffer = true;
  }

  std::ostream & output = (argc == 3 ? output_file : std::cout);
  output << "done" << std::endl;

  while (true) {

    // read the new key
    read(fd, &ev, sizeof(struct input_event));

    if (ev.type == 1) {
      key = shift_key = "";
      is_modifier_key = false;
      state = S_NONE;

      // get key value
      if (ev.code < num_keys and keys[ev.code] != _U_) {
        key = keys[ev.code];
        shift_key = shift_keys[ev.code];
      }

      // get key state
      switch (ev.value) {
        case 0: state = S_OFF ; break;
        case 1: state = S_ON  ; break;
        case 2: state = S_HOLD; break;
      }

      if (not key.empty() and state != S_NONE) {
        // on, hold
        if (state == S_ON or state == S_HOLD) {
          // shift
          if (key == rsh or key == lsh)
            is_modifier_key = shift_state = true;

          // alt
          else if (key == ral or key == lal)
            is_modifier_key = alt_state = true;

          // ctrl
          else if (key == rct or key == lct)
            is_modifier_key = ctrl_state = true;
        }
        // off
        else {
          // shift
          if (key == rsh or key == lsh)
            shift_state = false;

          // alt
          else if (key == ral or key == lal)
            alt_state = false;

          // ctrl
          else if (key == rct or key == lct)
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

          output << key << " " << std::endl;

          if (key_counter++ % 50 == 0 or no_buffer)
            output.flush();
        }
      }
      else {
        printf("key %i state %i\n", ev.code, ev.value);
      }
    }
  }
}
