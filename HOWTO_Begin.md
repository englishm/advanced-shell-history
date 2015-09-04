# Introduction #

Once you have [compiled and installed](HOWTO_Install.md) the program, you need to configure it to automatically collect command history data.  This guide will walk you through the basic options to get you started.


# Steps #
  1. If you are using the Python version, do this first:
```
  export ASH_LOG_BIN=/usr/local/bin/_ash_log.py
```
  1. To begin, you need to source the correct shell code library into your shell session.  Start by manually sourcing the appropriate library in `/usr/lib/advanced_shell_history` - later you will see how to make this automatic.
```
  source /usr/lib/advanced_shell_history/bash  # for bash users
```
  1. Confirm that a history database has been created by looking for it in the default location.
```
  ls ~/.ash  # you should see (at least) a history.db file.
```
  1. Confirm that you are able to query the database using the `ash_query` utility.
```
  ash_query -Q  # to print the existing saved queries.

  ash_query -q CWD  # to print history of commands entered inside the current working directory.
```
  1. Source the shell library code automatically by adding the `source` command to your shell resource file.  Add the following to your `~/.bashrc` file (for bash users).
```
  # Enable Advanced Shell History:
  export ASH_LOG_BIN=/usr/local/bin/_ash_log.py  # For Python users.
  source /usr/lib/advanced_shell_history/bash
```
  1. Confirm this works by opening a new terminal window and changing to a new directory and viewing history for that particular directory.  For example:
```
  # In a new terminal window.
  cd /
  ls -l
  ash_query -q CWD  # You should see (at least) the previous ls command.
```
  1. Done!  You may now proceed to the [advanced configuration](HOWTO_Configure.md) guide if you wish.  Also, feel free to browse the man pages for `ash_query`.
```
  man ash_query
```
# [Next](HOWTO_Configure.md) #

Look at [this guide](HOWTO_Configure.md) for more configuration options.