# EveryoneIsHere
A reverse-engineering tool used to look for size values in an array of data structures in a binary file

# Usage (Linux):
```
./EveryoneIsHere -f <frequency in bytes of value> -o <starting offset of values> -n <number of values> -s <size in bytes of value: 1-8> filename
```

# Usage (Windows):
```
EveryoneIsHere.exe -f <frequency in bytes of value> -o <starting offset of values> -n <number of values> -s <size in bytes of value: 1-8> filename
```

# Why the name?
This tool was initially developed for reverse-engineering a format found in Switch games that should be like SSBU but aren't (Pokémon games on Switch).

# When would this be most useful?
Consider a proprietary archive format.  You want to find the size value for the files contained within.  this program can be used to poke around the file until you find the size values.

# What does the console output mean and how does it help?
The output is all values matching the params added up.  If you get something slightly smaller than the file size, that is a candidate for being what you want.

# Known issues:
Entire file is loaded into RAM at once.  A block size feature is planned tho.
