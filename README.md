# wikilead
Tool for getting the lead sentence of Wikipedia artiles from command line.

# Dependencies
## libcurl 
```
sudo apt install libcurl4-gnutls-dev
```

## rapidxml
Download rapidxml and put `rapidxml.hpp" in /include directory.

# Build
```
make
```

# Usage
./wikilead [Options] word
  
|Option         | Description    |
|---------------|----------------|
|-j  --japanese |use japanese api|


# Example
```Shell
$ ./wikilead Linux
Linux is a family of open source Unix-like operating systems based on the Linux kernel, an operating system kernel first released on September 17, 1991 by Linus Torvalds. Linux is typically packaged in a Linux distribution.
```

```Shell
$ ./wikilead -j Linux
Linux（リナックス、他の読みは後述）とは、Unix系オペレーティングシステムカーネルであるLinuxカーネル、およびそれをカーネルとして周辺を整備したシステムである（GNU/Linuxシステムも参照）。
```
