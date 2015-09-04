## Disclaimer ##

Since this is a brand new project, both the FAQ and the troubleshooting guides are a bit green.  If you find them lacking in some way, don't hesitate to [raise an issue](http://code.google.com/p/advanced-shell-history/issues/entry) with your suggestions.
```
\0/
 Y
/ \
```

## Debugging ##

It may be worth your time to [turn on more verbose debugging output](HOWTO_Debug.md) to help narrow down the issue.

# Common Problems #

## Compilation Errors ##
  * There is a known C++ issue preventing users on some platforms from using the program.  The code may not compile or it may segfault when invoked.
    * If Python is available, you can install the Python version with:
```
  make install_python
```

## Slowness ##

#### There is noticeable delay before each prompt is redrawn. ####

This can be caused by a few things.
  * Your DB file exists on an NFS mount and it can't be reached quickly.
  * You are connected to a remote host and the connection to the remote host is flaky.

You can _immediately disable_ history logging by exporting an environment variable.
```
  $ export ASH_DISABLE='please'  # Any non-empty value will work, actually.
```
You can later undo the disable like this:
```
  $ unset ASH_DISABLE
```
If you see the problem immediately go away after disabling logging, it's likely that the database is the culprit.  Perhaps the file exists on an NFS mounted filesystem or maybe the filesystem is full.  It's possible that the DB is simply getting large and indexes should be created.  In that case, please [raise an issue with your specifics](http://code.google.com/p/advanced-shell-history/issues/entry) (if they may be divulged).

If the problem does _**not**_ go away after disabling logging, it's likely a separate problem with the host or possibly your connection to it (are you connecting through ssh?).