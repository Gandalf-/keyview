# keyview
Linux Key Logging for Developers

This project is composed of two parts: a keylogger called `keyview` and an
output analyzer called `keyanalyzer`. 

- `keyview` reads keyboard events from `/dev/input/event`, interprets them,
  and writes the interpretations to stdout.

- `keyanalyzer` reads this log file and produces statistics about your typing.
  It finds and counts substrings of the sizes you specify, then shows you the
  top `n` of them.

Future features will hopefully include:
- Richer analysis of keystrokes
- Alerts when you're repeating the same sequence of keys too many times, to
  avoid wrist pain

## Complete usage:
```
  make
  sudo ./keyview /dev/input/event3 > ~/.keyview.log
  ...
  <some typing>
  ...
  python keyanalyzer.py ~/.keyview.log 1-5 40
```

## keyview usage
```
  sudo keyview [keyboard_device]
```

where
- keyboard_device = the device your keyboard writes to. This is typically
  something like `/dev/input/event0`. You can figure out which `event#` by
  running `keyview` on them and typing somewhere else. There will be output if
  you found the right one
  

## keyanalyzer usage
```
  python keyanalyzer.py [keyview_log_file] [n|n-m] [top_k]
```

where 
- n,m   = substring lengths
- top_k = print the top k results

