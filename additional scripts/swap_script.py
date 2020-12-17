import os
import re
import fileinput
from tempfile import mkstemp
from shutil import move, copymode
from os import fdopen, remove


def luov_felt_functions_search(line):

    felt_function_names = ["multiply", "add", "addInPlace", "printFELT",
                           "inverse", "log", "antilog", "serialize_FELT",
                           "deserialize_FELT", "xpown", "isEqual"]
    for item in felt_function_names:
        match_obj = re.search(r'\bf\d+' + item + r'\(', line)
        if match_obj:
            print(line)
            return match_obj
    return None


config_path = '/home/marci/Desktop/script/config_luov.txt'
dir_path = '/home/marci/Desktop/luov_new'
f_config = open(config_path, "r")

for line in f_config:
    line = line.replace("\n", " ")
    print(line)
    for files in os.listdir(dir_path):
        #print(files)
        x = re.search(".c$", files)
        y = re.search(".h$", files)
        if files != "debug" and files != "release" and x or y:
            fh, abs_path = mkstemp()
            with fdopen(fh, 'w') as new_file:
                with open(dir_path + "/" + files) as old_file:
                    for lines in old_file:
                        #print(lines)
                        z = lines.find(line.split("\t")[0])
                        #print(line.split("\t")[0])
                        re_obj = re.compile(r'\b' + line.split("\t")[0] + r'\b')
                        iterator = re.finditer(line.split("\t")[0], lines)
                        #print(sum(1 for _ in iterator))
                        replace_flag = 0
                        for match in iterator:
                            #print("halo")
                            if lines[match.start() - 1] != "\_" and lines[match.start()-17:match.start()] != "DEFINE_OPERATION("\
                                    and lines[match.end(): match.end()+5] != "##NUM":
                                # print(lines[match.start()-17:match.start()-1])
                                tmp = re.search('\W', lines[match.start() - 1])
                                if tmp:
                                    # print(tmp.groups())
                                    re_obj = re.compile(r'\b' + line.split("\t")[0] + r'\b')
                                    #lines = lines.replace(line.split("\t")[0], line.split("\t")[1].strip())
                                    lines = re_obj.sub(line.split("\t")[1].strip(), lines)
                                    #new_file.write(re_obj.sub(line.split("\t")[1].strip(), lines))
                                    #print("----------------------------------NEW LINE-----------------------")
                                    #print(re_obj.sub(line.split("\t")[1].strip(), lines))
                                    replace_flag = 1
                                else:
                                    pass
                            else:
                                pass
                        re_obj = re.compile('\\(ADD\\)')
                        if re_obj.search(lines):
                            #print(lines)
                            lines = re_obj.sub("(GEMSS_ADD)", lines)
                            #print(lines)

                        re_obj = re.compile('\\(best_sqr\\)')
                        if re_obj.search(lines):
                            # print(lines)
                            lines = re_obj.sub("(GEMSS_best_sqr)", lines)
                            # print(lines)

                        re_obj = re.compile('\\(best_sqr_nocst_\\)')
                        if re_obj.search(lines):
                            # print(lines)
                            lines = re_obj.sub("(GEMSS_best_sqr_nocst_)", lines)
                            # print(lines)

                        re_obj = re.compile('\\(REM\\)')
                        if re_obj.search(lines):
                            # print(lines)
                            lines = re_obj.sub("(GEMSS_REM)", lines)
                            # print(lines)
                        re_obj = re.compile('\\(CMP_LT\\)')
                        if re_obj.search(lines):
                            # print(lines)
                            lines = re_obj.sub("(GEMSS_CMP_LT)", lines)
                            # print(lines)
                        re_obj = re.compile('\\(ISEQUAL\\)')
                        if re_obj.search(lines):
                            # print(lines)
                            lines = re_obj.sub("(GEMSS_ISEQUAL)", lines)
                            # print(lines)

                        re_obj = re.compile('\\(best_mul\\)')
                        if re_obj.search(lines):
                            # print(lines)
                            lines = re_obj.sub("(GEMSS_best_mul)", lines)
                            # print(lines)

                        re_obj = re.compile('\\(SET0_\\)')
                        if re_obj.search(lines):
                            # print(lines)
                            lines = re_obj.sub("(GEMSS_SET0_)", lines)
                            # print(lines)

                        re_obj = re.compile('\\(SET1_\\)')
                        if re_obj.search(lines):
                            # print(lines)
                            lines = re_obj.sub("(GEMSS_SET1_)", lines)
                            # print(lines)

                        re_obj = re.compile('\\(XORLOADMASK1_\\)')
                        if re_obj.search(lines):
                            # print(lines)
                            lines = re_obj.sub("(GEMSS_XORLOADMASK1_)", lines)
                            # print(lines)

                        re_obj = re.compile('\\(CMP_LT_U\\,')
                        if re_obj.search(lines):
                            # print(lines)
                            lines = re_obj.sub("(GEMSS_CMP_LT_U,", lines)
                            # print(lines)

                        re_obj = re.compile('LUOV_DEFINE_OPERATION\\(LUOV_FELT\\)')
                        if re_obj.search(lines):
                            # print(lines)
                            lines = re_obj.sub("LUOV_DEFINE_OPERATION(FELT)", lines)
                            # print(lines)

                        re_obj = re.compile(r'\bf\d+' + 'FELT' + r'\b')
                        if re_obj.search(lines):
                            # print(lines)
                            matched = re_obj.search(lines)
                            lines = re_obj.sub("LUOV_" + matched.group(), lines)
                            # print(lines)

                        re_obj = re.compile('LUOV_DEFINE_OPERATION\\(LUOV_ZERO\\)')
                        if re_obj.search(lines):
                            # print(lines)
                            lines = re_obj.sub("LUOV_DEFINE_OPERATION(ZERO)", lines)
                            # print(lines)

                        re_obj = re.compile(r'\bf79ONE\b')
                        if re_obj.search(lines):
                            # print(lines)
                            lines = re_obj.sub("LUOV_f79ONE", lines)
                            # print(lines)

                        re_obj = re.compile(r'\b' + 'f79ZERO' + r'\b')
                        if re_obj.search(lines):
                            # print(lines)
                            lines = re_obj.sub("LUOV_f79ZERO", lines)
                            # print(lines)

                        if re.search('^luov_', files):
                            matchedFelt = luov_felt_functions_search(lines)
                            if matchedFelt:
                                print(matchedFelt.group())
                                function_name = matchedFelt.group()
                                lines = lines.replace(matchedFelt.group(), "LUOV_" + matchedFelt.group())
                                print(lines)

                        new_file.write(lines)

            new_file.close()
            old_file.close()
            copymode(dir_path + "/" + files, abs_path)
            remove(dir_path + "/" + files)
            move(abs_path, dir_path + "/" + files)

f_config.close()


