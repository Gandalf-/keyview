# keyview
Linux Key Logging for Developers

This project is composed of two parts: a keylogger called `keyview` and an
output analyzer called `keyanalyzer`. 

- `keyview` reads keyboard events from `/dev/input/event`, interprets them,
  and writes the interpretations to stdout, which can be redirected to a log
  file.

- `keyanalyzer` reads this output and produces statistics about your typing.
  It finds and counts substrings of the sizes you specify, then shows you the
  top `n` of them.

Future features will hopefully include:
- Richer analysis of keystrokes
- Alerts when you're repeating the same sequence of keys too many times, to
  avoid wrist pain

## complete usage
```
  make
  sudo ./keyview /dev/input/event3 > ~/.keyview.log
  ...
  <some typing>
  ...
  python keyanalyzer.py ~/.keyview.log 40 1-5
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
  python keyanalyzer.py [keyview_log_file] [top_k] [n|n-m]
```

where 
- `n,m`   = substring lengths
- `top_k` = print the top k results


## Example output
```
	user@home ~/g/c/c/keyview> python keyanalyzer.py ~/.keyview.log 25 1-2
	j                                       265              7.91
	k                                       247              7.37
	spc                                     234              6.98
	j j                                     150              4.47
	e                                       146              4.36
	w                                       126              3.76
	t                                       118              3.52
	s                                       116              3.46
	bks                                     110              3.28
	esc                                     106              3.16
	k k                                     105              3.13
	o                                       104              3.10
	i                                       103              3.07
	b                                       101              3.01
	y                                       77               2.30
	r                                       76               2.27
	n                                       74               2.21
	ret                                     73               2.18
	ctl_k                                   69               2.06
	d                                       68               2.03
	a                                       68               2.03
	g                                       60               1.79
	u                                       59               1.76
	K                                       59               1.76
	bks bks                                 51               1.52

	total_keys keys: 3352
```
