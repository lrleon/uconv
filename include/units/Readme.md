# Unit definitions directory

You can put in this directory all the units definitions that you
project needs. Then, edit the `include/uconv-list.H` and put there
file inclusions to every unit that you have defined. Finally, go to
the `lib` directory and compile the library.

Eventually, you could put other units definition in any other place,
but in order to build the library, you will reference every header
defining a unit in the `uconv-list.H` header.

This directory already contains some units definitions which are here
for test and demo purposes. Remove every unit from this directory that
you do not need in your project.
