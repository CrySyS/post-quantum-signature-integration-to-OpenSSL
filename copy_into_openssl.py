import os
from pathlib import Path
from shutil import copytree, copy, copymode, move, rmtree

# header files directories
luov_headers_path: str = "headers/luov"
falcon_headers_path: str = "headers/falcon"
gemss_headers_path: str = "headers/gemss"

# XKCP dir
xkcp_path: str = "XKCP"

# libkeccak dir
libkeccak_path: str = "libkeccak.a.headers"

# main file directories
luov_path = "luov"
falcon_path = "falcon"
gemss_path = "gemss"

# openssl directory
# Get the input dir from user
print("Enter dir name:")
dir_name = str(input())
target = dir_name + "_modified"
os.rename(dir_name, dir_name + "_modified")
try:
    for files in os.listdir(luov_headers_path):
        copy(luov_headers_path + "/" + files, target + "/include/openssl")
    for files in os.listdir(falcon_headers_path):
        copy(falcon_headers_path + "/" + files, target + "/include/openssl")
    for files in os.listdir(gemss_headers_path):
        copy(gemss_headers_path + "/" + files, target + "/include/openssl")

    if os.path.exists(target + "/crypto/luov"):
        rmtree(target + "/crypto/luov")
    copytree(luov_path, target + "/crypto/luov")

    if os.path.exists(target + "/crypto/falcon"):
        rmtree(target + "/crypto/falcon")
    copytree(falcon_path, target + "/crypto/falcon")

    if os.path.exists(target + "/crypto/gemss"):
        rmtree(target + "/crypto/gemss")
    copytree(gemss_path, target + "/crypto/gemss")

    if os.path.exists(target + "/include/XKCP"):
        rmtree(target + "/include/XKCP")
    copytree(xkcp_path, target + "/include/XKCP")

    if os.path.exists(target + "/include/libkeccak.a.headers"):
        rmtree(target + "/include/llibkeccak.a.headers")
    copytree(libkeccak_path, target + "/include/libkeccak.a.headers")
except OSError:
    print("Wrong name")


