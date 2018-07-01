# PreventFromDataTransmisionErrorsProject

Application, which allows to check parity bit, CRC sum or add some errors to given file. It was written in C++.

::::DEFINITIONS::::
#define INPUT_NAME "test.png" // Name of file, with which we would like to work.
#define OUTPUT_NAME "output.png" // Name of file, where should be saved changes after adding some errors to file.
#define NUMBER_OF_ERRORS 0.0001 //  1 responds to 1% of errors
#define WITH_REPEATS true // do we want to check, if bit has been changed already
