# post-quantum-signature-integration-to-OpenSSL
***
## Table of Contents
1. [General Info](#general-info)
2. [Technologies](#technologies)
3. [Installation](#installation)
4. [How to use](#howtouse)
### General Info
***
This is an open source student project at the Budapest University of Technology and Economics, Hungary and is free to use for everyone. This project integrates post-quantum algorithms into the OpenSSL library. Tested on 1.1.1-stable and 3.0.0-dev OpenSSL. This project currently integrates three algorithms:
* Falcon
* LUOV
* GeMSS
## Technologies
***
A list of technologies used within the project:
* Qt Creator: Version 4.11.0
* PyCharm Community Edition: Version  2020.2.4
* OpenSSL: Version 1.1.1 and 3.0.0
## Installation
***
The Installation requires a python package and an OpenSSL library. First run the python script and give the path to the OpenSSL
```
$ python3 copy_into_openssl.py
```
Then some files must be patched in the OpenSSL library. This can be done with the given patch files, for example:
```
$ patch openssl-master_modified/util/libcrypto.num < patch_files/openssl_3.0.0_dev/libcrypto_patch
$ patch openssl-master_modified/crypto/build.info < patch_files/openssl_3.0.0_dev/build_info_patch
```
Next step is to install OpenSSL, enter into OpenSSL library and issue the commands for example:
```
$ ./config
$ make
$ make install
```
After these steps only needs to import this modified OpenSSL library and import the desired algorithm into your code and then it is ready to use for example:
```
#include <openssl/falcon.h>
```
Side information: There are side scripts that are for help the integration and further development. These also free to use and modify.
## How to use
***
The use of these algorithms are similar to RSA implementation in OpenSSL library, they use those conventions. For example:
```
FALCON_new(...)
FALCON_generate_key(...)
FALCON_sign(...)
FALCON_verify(...)
etc.
```
