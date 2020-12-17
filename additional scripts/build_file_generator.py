import os
import re
import fileinput
from tempfile import mkstemp
from shutil import move, copymode
from os import fdopen, remove

# This script is for creating build.info files

# Get the input dir from user
print("Enter dir name:")
dir_name = str(input())

f_out = open(dir_name + "/" + "build.info", "w")

# Write out fix lines to file
f_out.write("LIBS=../../libcrypto\n\n")
f_out.write("SOURCE[../../libcrypto]=")

count_files = 0
try:
    # Counting how many files in target directory
    # count_files: this needs for the last line to write
    for file in os.listdir(dir_name):
        count_files = count_files + 1

    # Writing files into build.info
    # files_in_one_row: This is just for aesthetic reasons
    files_in_one_row = 0
    tmp = 0
    for file in os.listdir(dir_name):
        is_source_file = re.search(".c$", file)
        if is_source_file:
            # Check if we reached the last file, because we don't need "\" at the end of the last line
            if tmp == count_files:
                f_out.write(file)

            # This is just to make the file looking good
            # If there are not 3 files in a row just write out with a plus whitespace
            if files_in_one_row != 3:
                f_out.write(file + " ")
                files_in_one_row = files_in_one_row + 1

            # If there are 3 files in a row print the next one in new line
            else:
                f_out.write(" \\\n\t" + file + " ")
                files_in_one_row = 0

            # Iterate tmp just to know how much file we have been through
        tmp = tmp + 1
except OSError:
    print("Wrong directory name")
f_out.close()

