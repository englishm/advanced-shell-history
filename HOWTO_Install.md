# Introduction #

To compile and install this program from source you will need a basic linux toolchain (g++, gcc, libc and make) and the ability to sudo on the target system.  This guide will walk you through compiling and installing everything from source.

If you are running Mac OSX, you may need to perform an extra step.


# Steps #

  1. If you are running OSX - please refer to the [OSX Notes](HOWTO_Install_In_OSX.md).
  1. Open a new terminal window.  The following steps will be performed within the shell.
  1. Download and unpack the source tarball (or minimal source tarball). Alternatively, you can [checkout the repository](http://code.google.com/p/advanced-shell-history/source/checkout) and continue building from the next step.
```
  curl -s http://advanced-shell-history.googlecode.com/files/ash-0.5.r155.tar.gz -o /tmp/ash-src.tar.gz
  cd /tmp
  tar -xvzpf ash-*.tar.gz

# Alternatively, you can check out the source with svn:

  svn checkout http://advanced-shell-history.googlecode.com/svn/branches/rb-0.5 /tmp/ash-src
```
  1. Compile the code.
```
  cd /tmp/ash-src
  make build
```
    * NOTE: If there are problems compiling the C++ source on your system, you can build a Python-only version instead.
```
  make build_python
```
  1. If you wish to install the package system-wide, you can use the included makefile target to do so.  If you do NOT want to install the package system-wide, see the guide for [custom installations.](HOWTO_Custom.md)
```
  make install
```
    * You can also install the Python-only version if there are problems with the C++ version.
```
  make install_python
```
  1. Cleanup (Optional).
```
  cd /tmp
  rm -rf ash-src ash-*.tar.gz
```
  1. Congratulations!  The code compiled and is installed, but you are not quite done yet.  You still need to enable automatic logging for your account.

# [Next](HOWTO_Begin.md) #

To learn about how to begin using the program, look at [this guide.](HOWTO_Begin.md)