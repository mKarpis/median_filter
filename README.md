# median_filter
Author: miroslav.karpis@gmail.com
* md5 filter converted to C++ class by Frank Thilo (thilo@unix-ag.org) for bzflag (http://www.bzflag.org) based on: md5.h and md5.c reference implementation of RFC 1321 Copyright (C) 1991-2, RSA Data Security, Inc. Created 1991. All rights reserved.

About: - this was a just an excercise, so use it only on your own risk. It can be used as a reference only.

Input Data: 16Bytes md5 Hash | 32bit int header reacord (num of records) | Each record 2xfloat32 values

Program
 * Reads input data files
 * Initializes window of 100,000 zeros
 * Runs an online median filter
 * Write the output of the filter to a text file

Use: <input-file> <output-file> <(optional) window-size (default 100 000)>
