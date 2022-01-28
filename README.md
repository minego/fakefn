# fakefn

Make the bottom left control key act like an function key on a laptop

## Why?!

Many thinkpads have an "fn" key in the bottom left corner, and also have an
option in the bios to swap that and the ctrl key next to it.

The real "fn" key (or the ctrl key when swapped) has very limited functionality
because all you can really do is use it to toggle the behavior of the F keys.

To achieve parity between this keyboard and others I like and use regularly I
want to be able to be able to use this bottom left key as my own customizable
fn key. Specifically I want fn+<num> to act as the matching F key because the
real F keys are strange shapes that I can't find without looking.

This is meant to run along with the caps2esc plugin, and should run BEFORE it so
that this doesn't act on an event sent by that.


Execution
```
fakefn - Simple tool to allow 'fn' on a thinkpad to be used for other things

usage fakefn [-h]

options:
	-h			Show this message and exit
```

## Dependencies

[Interception Tools](https://gitlab.com/interception/linux/tools)


