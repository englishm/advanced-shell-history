# Want shell history with more than _just_ your commands? #

![http://advanced-shell-history.googlecode.com/svn/wiki/ash_screenshot.png](http://advanced-shell-history.googlecode.com/svn/wiki/ash_screenshot.png)

**Enhance your shell history by also logging:**
  * **Command details:**
    * current working directory where the command was entered
    * exit code and even pipe states
    * command start and stop times
  * **Session details:**
    * login and logout times
    * controlling tty
    * ssh session details (if any)

**Have you ever thought to yourself...**
  * What were those commands I ran in directory `/foo/bar` about a month ago?
  * What was the error code of that command I just ran?  I forgot to check!
  * What commands was I entering between the hours of `X` and `Y` on `DATE`?
  * How long did that command run for?  It finished while I wasn't watching.

```
 0/ - You can stop grepping through your history file and stop guessing!
<Y
/ \
```

## Features ##
  * **compatable** with popular shells **`bash`** and **`zsh`**
  * **[+25 data points](http://code.google.com/p/advanced-shell-history/wiki/DBSchema#Schema)** that are not available in `bash` and `zsh` builtin history
  * **unobtrusive** - configure once and forget about it
  * saves your data to a **[sqlite3 database](http://www.sqlite.org/about.html)** for **advanced history querying**
  * **convenient** tools for selecting history are included
  * **extensible** - write new queries and save them for easy access later

## Information ##
Please see the guide if you are curious about [how this works](HOW_THIS_WORKS.md), how it affects [zsh](http://code.google.com/p/advanced-shell-history/wiki/Disclaimer#zsh_Users) and [bash](http://code.google.com/p/advanced-shell-history/wiki/Disclaimer#bash_Users) users and [the disclaimer](Disclaimer.md).

If you are ready to start, check out the detailed [HOWTO](HOWTO.md) guides.