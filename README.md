# median_filter
author: miroslav.karpis@gmail.com

About: - this was a just an excercise, so use it only on your own risk. It can be used as a reference only.

Input Data: 16Bytes md5 Hash | 32bit int header reacord (num of records) | Each record 2xfloat32 values

Program
 * Reads input data files
 * Initializes window of 100,000 zeros
 * Runs an online median filter
 * Write the output of the filter to a text file

Use: <input-file> <output-file> <(optional) window-size (default 100 000)>
