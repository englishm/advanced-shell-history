# Introduction #

If you don't have root-access on a host but would still like to use this program, you can do that, but it requires a bit more configuration.  This guide will cover the basics needed to get you up and running.

This guide assumes that you have already [downloaded and compiled](HOWTO_Install.md) the project from source.

# Steps #

  1. Make a direcrory to keep the required binaries and configuration in your home directory.  Here are some suggestions:
```
  mkdir -p ~/.ash/bin  # For binaries.
  mkdir -p ~/.ash/conf  # For configuration files.
  mkdir -p ~/.ash/lib  # For shell library code.
```
  1. Copy the compiled binaries into the local binary directory.
```
  cp -a /tmp/ash-src/files/usr/local/bin/* ~/.ash/bin
```
  1. Copy the required config files into the local configuration directory.
```
  cp -a /tmp/ash-src/files/etc/ash/* ~/.ash/conf
```
  1. Copy the required shell library code into the local lib directory.
```
  cp -a /tmp/ash-src/files/usr/lib/advanced_shell_history/* ~/.ash/lib
```
  1. Edit your local configuration file `~/.ash/conf/ash.conf` to set this value.
```
  #
  # Setup
  #
  ASH_CFG_LIB='~/.ash/lib'
```
  1. Add the following to your shell resource file:
```
  export ASH_CFG="~/.ash/ash.conf"
  export PATH="${PATH}:~/.ash/bin"
  source ~/.ash/lib/bash
```
  1. Confirm that this works as expected by testing in a new terminal window.  Open a terminal window and execute the following:
```
  cd /
  ls -l
  ash_query -q CWD  # You should see the two commands above.
```
  1. Done!  You can now explore the [advanced configuration options.](HOWTO_Configure.md)

# [Next](HOWTO_Configure.md) #

Explore the [advanced configuration options](HOWTO_Configure.md) and customize what is logged or not logged.