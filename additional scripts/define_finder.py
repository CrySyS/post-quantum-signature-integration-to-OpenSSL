import re
import os

path = '/home/marci/Desktop/script/luov-7-57-197-chacha'
db = 0
defines = []
for files in os.listdir(path):
	print(files)
	x = re.search(".c$", files)
	y = re.search(".h$", files)
	if files != "debug" and files != "release" and x or y:
		f = open(path + "/" + files,"r")
		for line in f:
			x = re.search("#define", line)
			if x:
				#print(line)
				db = db + 1
				y = re.search("_H$", line)
				z = re.search("_h$", line)
				#w = re.search("GEMSS_", line)
				if y or z:
					pass
				else:
					#print(line)
					line = line[line.find("#define"):100]
					#print("---------------------------------")
					#print(line)
					line = line.replace("\t", " ")
					line = line.replace("\n", " ")
					line = line.replace("*/", " ")
					line = line.replace("\\", " ")
					line = line.replace("(", " ")
					#print(line.split(" "))
					splitted = line.split(" ")
					#print(splitted)
					split_tmp = []
					for item in splitted:
						#print(item)
						tmp = re.match("\S", item)
						if tmp:
							split_tmp.append(item)
					print(split_tmp)
					contains = 0
					for d in defines:
							if split_tmp[1] == d:
								contains = 1
					if contains == 0:
						tmp = re.match("LUOV", split_tmp[1], re.IGNORECASE)
						if not tmp:
							defines.append(split_tmp[1])

#print(db)
db2 = 0
f_out = open("config_luov.txt", "w")
for d in defines:
	#print(d)
	f_out.write(d + "\t" + "LUOV_" + d + "\n")
	db2 = db2 + 1
f.close()
#print(db2)
