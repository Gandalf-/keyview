/* keyview.cpp
 *
 * Author: Austin Voecks
 */

#include "keyview.h"

int main(int argc, char **argv)
{
  if (argc < 2) {
    std::cerr << "usage: " << argv[0] << " <device>\n";
    return EXIT_FAILURE;
  }

  size_t num_keys = keys.size();

  // open the /dev/input/event device
  int fd = open(argv[1], O_RDONLY);

  while (1) {
    // initialize key strings to empty
    std::string key, shift_key;

    KeyState state = KeyState::None;
    bool ctrl_state = false;
    bool alt_state = false;
    bool shift_state = false;
    bool is_modifier_key = false;

    struct input_event ev;

    // read the new key
    read(fd, &ev, sizeof(struct input_event));

    if (ev.type == 1) {
      shift_key = "";
      key = "";
      is_modifier_key = false;
      state = KeyState::None;

      // get key value
      if (ev.code < num_keys && keys.at(ev.code) != _U_) {
        key = keys.at(ev.code);
        shift_key = shift_keys.at(ev.code);
      }

      // get key state
      switch (ev.value) {
        case 0: state = KeyState::Off ; break;
        case 1: state = KeyState::On  ; break;
        case 2: state = KeyState::Hold; break;
      }

      if (!key.empty() and state != KeyState::None) {
        // on, hold
        if (state == KeyState::On or state == KeyState::Hold) {
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
        if (!is_modifier_key and state == KeyState::On) {

          if (shift_state) {
            if (shift_key != key)
              key = shift_key;
            else
              std::cout << "shf_";
          }

          if (ctrl_state) std::cout << "ctl_";
          if (alt_state)  std::cout << "alt_";

          std::cout << key << " " << "\n";
        }
      }
      else {
        // Instead of printf(), try using the C++11 "std::to_string()":
        // std::cout << "key " << std::to_string(ev.code) << " state " <<
        //   std::to_string(ev.value) << "\n";
        //
        // A fancy way to print before C++11 is:
        // #include <sstream>
        // ...
        // std::stringstream ss;
        // ss << "key " << ev.code << " state " << ev.value << "\n";
        // std::cout << ss.str();
        printf("key %i state %i\n", ev.code, ev.value);
      }
    }
  }
}
