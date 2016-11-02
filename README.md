A Linux command line utility used to speed up and simplify the process of a Linux system administrator.

Nowhere near complete.
The symbolic link creation in the install is not working. that was mostly for convenience, it will be fixed soon.

to install, just run "sudo ./configure". 

Manual install:
g++ nimda-files/NimdaMain.cpp nimda-files/nimda_cmd.cpp
mv a.out nimda
sudo ln -s /path/to/nimda /usr/bin/nimda
