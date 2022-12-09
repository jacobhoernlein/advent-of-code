#ifndef GETLINES_H_
#define GETLINES_H_

#include <string>
#include <vector>

/** Get the lines of the file named in argv[1] as a vector.
 * @param argc The size of argv.
 * @param argv An array of character pointers.
 * @returns A vector of strings representing the lines of the file.
 * @exception std::argument_error if argc < 2.
 * @exception std::ifstream::failure if the file doesn't exist.
*/
std::vector<std::string> getlines(int argc, char** argv);

#endif
