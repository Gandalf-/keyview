# keyview
Linux Key Logging for Developers

This project is composed of two parts: a keylogger called `keyview` and an
output analyzer called `keyanalyzer`. 

- `keyview` reads keyboard events from `/dev/input/event`, interprets them,
  and writes the interpretations to stdout, which can be redirected to a log
  file.

- `keyanalyzer` reads this output and produces statistics about your typing,
  based on queries.

Future features will hopefully include:
- Richer analysis of keystrokes
- Alerts when you're repeating the same sequence of keys too many times, to
  avoid wrist pain

## complete usage
```
  make
  sudo ./keyview /dev/input/event3 ~/.keyview.log
  ...
  <some typing anywhere on the system>
  ...
  python keyanalyzer.py ~/.keyview.log
```

## keyview usage
```
  sudo keyview [keyboard_device]
```

where
- `keyboard_device` = the device your keyboard writes to. This is typically
  something like `/dev/input/event0`. You can figure out which `event#` by
  running `keyview` on them and typing somewhere else. There will be output if
  you found the right one
  

## keyanalyzer usage
```
  python keyanalyzer.py ~/.keyview.log
  keyanalyzer.py
          total_keys : 54716
          type 'h' for help

  ?> h
  h         : help
  q         : quit
  c         : clear
  r int-int : set substring size range
  s int     : set number of results
  d         : default query
  m str ... : query, results must match all provided input
  n str ... : query, results must match any of provided input
  f str ... : query, results must not match provided input
  t str     : query, results must match provided input exactly

                                                                          0.068 ms
```

### example queries

- show top 5 most frequently used keys
```
  ?> s 5
                                                                          0.030 ms

  ?> d
  spc                                               4793             8.76
  bks                                               3663             6.69
  k                                                 3540             6.47
  j                                                 2979             5.44
  e                                                 2034             3.72
```

- order home row keys by frequency of use
```
  ?> n a s d f j k l ;
  k                                                 3540             6.47
  j                                                 2979             5.44
  l                                                 1728             3.16
  s                                                 1606             2.94
  d                                                 1463             2.67
  a                                                 1337             2.44
  f                                                 1271             2.32
  ;                                                 738              1.35
                                                                          0.439 ms
```

- show sequences of keys, length 2 to 5, including escape
```
  ?> r 2-5
                                                                          246.632 ms

  ?> s 10
                                                                          0.030 ms

  ?> m esc
  esc k                                             268              0.49
  esc j                                             167              0.31
  esc spc                                           145              0.27
  spc esc                                           123              0.22
  esc k x2                                          98               0.18
  esc spc k                                         80               0.15
  esc j x2                                          66               0.12
  " esc                                             65               0.12
  ret esc                                           54               0.10
  esc b                                             50               0.09
                                                                          87.346 ms
```
