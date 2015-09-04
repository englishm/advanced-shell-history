# Introduction #

Configuration options are kept (by default) in `/etc/ash/ash.conf`

There are two components to keep in mind when looking at the configuration.  There is the collector `_ash_log` and the querier `ash_query`.  Many of the configuation options are specific to one or the other, but in some cases both.

Each option has a brief description of the option in a comment above the value.  The default value is also listed in a comment trailing the actual value.
```
# File: /etc/ash/ash.conf


#
# Setup
#

# ASH_CFG_FOO - An example variable description.
ASH_CFG_FOO='an example value'  # Default: 'an example value'
...
```


# Settings #

The default location for the settings listed below is `/etc/ash/ash.conf`.  This file is effectively sourced once into your shell environment when you source the shell code in `/usr/lib/advanced_shell_history/`.  This allows the history logger to avoid reading and parsing the config file every time you enter a new command.  This also means that you can modify your configuration directly in your shell.

These are not things you will want to change every day, it's just good to be aware of your options early on.  If all this seems overwhelming, you can [skip to the next section](HOWTO_Query.md) (the defaults are reasonable for most users).

### Customize ###
If you find that you want to modify one or more of these variables, please add your own custom values in your shell resource file (`~/.bashrc` or `~/.zshrc`) _after_ you have sourced the shell code in `/usr/lib/advanced_shell_history`.

For example:
```
  # File: ~/.bashrc
...
  # Enable Advanced Shell History:
  source /usr/lib/advanced_shell_history/bash
  export ASH_CFG_DB_FAIL_TIMEOUT='0'
  export ASH_CFG_LOG_LEVEL='DEBUG'
...
```

#### Custom Installation Options ####
| **Environment Variable Name** | **Default Value** | **Description** |
|:------------------------------|:------------------|:----------------|
|ASH\_CFG\_LIB                  |`/usr/lib/advanced_shell_history`|The location of the sourced shell code.  This is only changed when doing [custom installations.](HOWTO_Custom.md)|
|ASH\_LOG\_BIN                  |`/usr/local/bin/_ash_log`|The binary used to log commands.  This can be changed to select the Python version of the logger: `/usr/local/bin/_ash_log.py`.|

#### General Options ####
| **Environment Variable Name** | **Default Value** | **Description** |
|:------------------------------|:------------------|:----------------|
|ASH\_DISABLED                  |_unset_            |If set, history collection is disabled.  See the [troubleshooting guide](HOWTO_Troubleshoot.md) for details on when this is useful.|
|ASH\_SESSION\_ID               |_unset_            |The session id number created for the current session.  If unset, a new session ID will be automatically created and this variable set by the sourced shell code.|

#### `ash_query` Options ####
| **Environment Variable Name** | **Default Value** | **Description** |
|:------------------------------|:------------------|:----------------|
|ASH\_CFG\_DEFAULT\_FORMAT      |auto               |The default value for the --format flag in `ash_query`.|
|ASH\_CFG\_DEFAULT\_QUERY       |session            |The default value for the --query flag in `ash_query`.|
|ASH\_CFG\_HIDE\_USAGE\_FOR\_NO\_ARGS|false              |Normally, if you invoke `ash_query` with no arguments, the `--help` output is displayed.  With this variable set to a non-empty value, the `--help` output is suppressed in this case.|
|ASH\_CFG\_IGNORE\_UNKNOWN\_FLAGS|false              |Normally `ash_query` complains when it sees unknown flags.  With this variable set to a non-empty value, unknown flags are ignored.|

#### Debug Logging Options ####
| **Environment Variable Name** | **Default Value** | **Description** |
|:------------------------------|:------------------|:----------------|
|ASH\_CFG\_LOG\_DATE\_FMT       |`'%Y-%m-%d %H:%M:%S %Z: '`|If logging is in use, this format string can be set to customize the date string.|
|ASH\_CFG\_LOG\_FILE            |`~/.ash/ash.log`   |The file destination of logged messages, if logging is in use.|
|ASH\_CFG\_LOG\_LEVEL           |`WARNING`          |The lowest level of logging to make visible.  Levels (in increasing order) are DEBUG, INFO, WARNING, ERROR and FATAL.|

#### Database Options ####
| **Environment Variable Name** | **Default Value** | **Description** |
|:------------------------------|:------------------|:----------------|
|ASH\_CFG\_DB\_FAIL\_RANDOM\_TIMEOUT|4                  |After a failed insert, sleep a random number of milliseconds before retrying.  This is intended to add some noise to the retry mechanism.|
|ASH\_CFG\_DB\_FAIL\_TIMEOUT    |3                  |After a failed insert, sleep this many milliseconds before retrying.|
|ASH\_CFG\_DB\_MAX\_RETRIES     |5                  |Quit db retries after this many failed attempts.|
|ASH\_CFG\_HISTORY\_DB          |`~/.ash/history.db`|The default database to query.  This signifies the location of the database where commands are logged.|

#### History Logging Options ####
| **Environment Variable Name** | **Default Value** | **Description** |
|:------------------------------|:------------------|:----------------|
|ASH\_CFG\_LOG\_IPV4            |true               |Can be used to skip logging ipv4 host IP addresses.|
|ASH\_CFG\_LOG\_IPV6            |true               |Can be used to skip logging ipv6 host IP addresses.|
|ASH\_CFG\_SKIP\_LOOPBACK       |true               |Skip logging IP addresses for loopback devices (both ipv4 and ipv6).|

# [Next](HOWTO_Query.md) #

Now that you can configure the program, you should look at [how to query the database](HOWTO_Query.md) using the `ash_query` command.