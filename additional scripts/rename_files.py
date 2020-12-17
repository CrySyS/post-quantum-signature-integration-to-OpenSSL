import os
import re
import fileinput
from tempfile import mkstemp
from shutil import move, copymode
from os import fdopen, remove


path = '/home/marci/Desktop/script/luov-7-57-197-chacha/'
f_out = open("list.txt", "w")
db=0
for files in os.listdir(path):
    x = re.search(".c$", files)
    y = re.search(".h$", files)
    if files != "debug" and files != "release" and x or y:
        os.rename(path + files, path + 'luov_' + files)
        #f_out.write(files + " \\" + "\n")
