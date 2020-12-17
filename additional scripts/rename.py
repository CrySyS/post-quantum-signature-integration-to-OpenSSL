import os
import re
import fileinput
from tempfile import mkstemp
from shutil import move, copymode
from os import fdopen, remove

path = '/home/marci/Desktop/luov_new/'
f_out = open("list.txt", "w")
db=0
for files in os.listdir(path):
    x = re.search(".c$", files)
    y = re.search(".h$", files)
    if files != "debug" and files != "release" and x or y:
        # os.rename(path + files, path + 'luov_' + files)
        # f_out.write(files + " \\" + "\n")

        fh, abs_path = mkstemp()
        with fdopen(fh, 'w') as new_file:
            with open(path + files) as old_file:
                for line in old_file:
                    # print(line)
                    x = re.search("#include", line)
                    if x:
                        # print(line)
                        y = re.search("\"", line)
                        if y and files != "luov_local.h" and line[10:14] != "luov":
                            z = line.split(" ")
                            z = z[1].split("\n")
                            # print(z[0])
                            tmp = z[0][1:len(z[0])]
                            print(tmp)
                            if tmp == "LUOV.h\"" or tmp == "parameters.h\"":
                                tmp = "local.h\""
                                print(tmp)
                            new_line = "#include " + "\"" + "luov_" + tmp + "\n"
                            # new_line = line
                            new_file.write(new_line)
                            if files == "luov.c" :
                                new_file.write("#include \"luov_Column.h\"\n")
                                new_file.write("#include \"luov_LinearAlgebra.h\"\n")
                                new_file.write("#include \"luov_rng.h\"\n")
                                new_file.write("#include \"luov_intermediateValues.h\"\n")
                            # print(tmp)
                        else:
                            new_file.write(line)
                    else:
                        new_file.write(line)
        copymode(path + "/" + files, abs_path)
        remove(path + "/" + files)
        move(abs_path, path + "/" + files)
