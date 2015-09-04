![http://advanced-shell-history.googlecode.com/svn/wiki/ASH%20Schema.png](http://advanced-shell-history.googlecode.com/svn/wiki/ASH%20Schema.png)


# Introduction #

The history database is covered by these two tables - sessions and commands.


# Schema #
### Sessions ###
| **Column** | **Type** | **Size** | **Nullable** | **Default** | **Description** |
|:-----------|:---------|:---------|:-------------|:------------|:----------------|
|id          |integer   |11        | √            |null         |The session ID.  |
|hostname    |varchar   |128       | √            |null         |The hostname where the session began.|
|host\_ip    |varchar   |40        | √            |null         |The host IP addresses (taken from all available network interfaces) - space separated.|
|ppid        |integer   |5         |              |             |The parent process ID of this shell.|
|pid         |integer   |5         |              |             |The process ID of this shell.|
|time\_zone  |varchar   |3         |              |             |The time zone set on this host when the session began.|
|start\_time |integer   |11        |              |             |The start time of this session (in seconds since epoch time) in local time.|
|end\_time   |integer   |11        | √            |null         |The end time of this session (in seconds since epoch time) in local time.|
|duration    |integer   |11        | √            |null         |The measured duration of this session - in seconds.|
|tty         |varchar   |20        |              |             |The controlling tty when this session began.|
|uid         |integer   |16        |              |             |The UID when the session began.|
|euid        |integer   |16        |              |             |The effective UID when the session began.|
|logname     |varchar   |48        | √            |null         |The login name of the user when the session began.|
|shell       |varchar   |50        |              |             |The shell name (bash, zsh, etc) of the session.|
|sudo\_user  |varchar   |48        | √            |null         |If set, this implies that the session began as a sudo su to someone else.  This is possibly set to the previous user (who invoked sudo).|
|sudo\_uid   |integer   |16        | √            |null         |If set, this implies that the session began as a sudo su to someone else.  This is possibly set to the previous user ID.|
|ssh\_client |varchar   |60        | √            |null         |If set, this contains the value of the SSH\_CLIENT shell environment variable.|
|ssh\_connection|varchar   |100       | √            |null         |If set, this contains the value of the SSH\_CONNECTION shell environment variable.|

### Commands ###
| **Column** | **Type** | **Size** | **Nullable** | **Default** | **Description** |
|:-----------|:---------|:---------|:-------------|:------------|:----------------|
|id          |integer   |11        | √            |null         |The row id for this command (populated by a DB sequence).|
|session\_id |integer   |11        |              |             |The session id - see the sessions table.|
|shell\_level|integer   |11        |              |             |The shell variable SHLVL.|
|command\_no |integer   |11        | √            |null         |The shell builtin history command number.|
|tty         |varchar   |20        |              |             |The tty where the command was executed.|
|euid        |integer   |16        |              |             |The effective user ID when the command was entered.|
|cwd         |varchar   |256       |              |             |The current working directory where the command was entered.|
|rval        |integer   |5         |              |             |The exit code of the command - equal to ${?}|
|start\_time |integer   |11        |              |             |The start time (in seconds since epoch) UTC when the command was entered.|
|end\_time   |integer   |11        |              |             |The end time (in seconds since epoch) UTC when the command completed.|
|duration    |integer   |11        |              |             |The time measured between start and stop of the command.|
|pipe\_cnt   |integer   |3         | √            |null         |The number of piped commands entered.|
|pipe\_vals  |varchar   |80        | √            |null         |The exit codes of each individual piped command - separated by underscores.|

### Details ###

Whenever a new session begins, the session-specific data is collected once and inserted into the DB.  A new session ID is created and saved into the shell environment as a variable.

Whenever a command-line prompt is drawn, the previous command is logged into the database before the user can enter the next command.


### Tips ###

Download and install sqlite3 so you can query your history database manually.  Save queries you like in your ~/.ash/queries file and invoke them from the command line with the ash\_query command.