### Nimda
A Linux command line utility used to speed up and simplify the process of a Linux system administrator.

*Nowhere near complete.*

To install, just run: 
```bash
sudo ./configure 
```

Manual install:
```bash
g++ nimda-files/NimdaMain.cpp nimda-files/nimda_cmd.cpp
mv a.out nimda
sudo ln -s /path/to/nimda /usr/bin/nimda
```
