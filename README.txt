To build, from this directory:

  $ export AVR_FIND_ROOT_PATH=/usr/local/Cellar/avr-gcc/8.2.0/avr
  $ mkdir ../build
  $ cd build
  $ cmake ../
  $ make atmega1284p_test
  $ make upload_atmega1284p_test

To build in CLion

  Preferences > Build, Execution, Deployment > CMake > Environment

  Add,

       AVR_FIND_ROOT_PATH=/usr/local/Cellar/avr-gcc/8.2.0/avr

  or similar.

