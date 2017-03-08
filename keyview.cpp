/* keyview.cpp
 *
 * Author: Austin Voecks
 */

#include "keyview.h"

using namespace std;

int main(int argc, char **argv)
{
  int    num_keys, fd;
  struct input_event ev;
  bool   is_modifier_key, shift_state, alt_state, ctrl_state;
  string key, shift_key;
  STATE  state;

  shift_state = alt_state = ctrl_state = false;
  num_keys = sizeof(keys) / sizeof(*keys);

  if(argc < 2) {
    printf("usage: %s <device>\n", argv[0]);
    return 1;
  }

  // open the /dev/input/event device
  fd = open(argv[1], O_RDONLY);

  while (1) {

    // read the new key
    read(fd, &ev, sizeof(struct input_event));

    if(ev.type == 1) {
      key = shift_key = "";
      is_modifier_key = false;
      state = S_NONE;

      // get key value
      if (ev.code < num_keys && keys[ev.code] != _U_) {
        key = keys[ev.code];
        shift_key = shift_keys[ev.code];
      }

      // get key state
      switch (ev.value) {
        case 0: state = S_OFF ; break;
        case 1: state = S_ON  ; break;
        case 2: state = S_HOLD; break;
      }

      if (key != "" and state != S_NONE) {
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
        if (! is_modifier_key and state == S_ON) {

          if (shift_state) {
            if (shift_key != key)
              key = shift_key;
            else
              cout << "shf_";
          }

          if (ctrl_state) cout << "ctl_";
          if (alt_state)  cout << "alt_";

          cout << key << " " << endl;
        }
      }
      else {
        printf("key %i state %i\n", ev.code, ev.value);
      }
    }
  }
}
