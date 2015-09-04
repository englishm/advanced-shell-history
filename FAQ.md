# Introduction #


**If you would like to ask a question that you don't see here, [please do.](http://code.google.com/p/advanced-shell-history/issues/entry?template=Defect%20report%20from%20user)**

## FAQ ##
  * **Why an SQLite database per host instead of a central SQL database for all hosts?**
> This is a pretty easy extension to make - if you have a situation where there are many servers you are managing and you want to consolidate all history into a central repository.  The DB schema is actually already designed to hold data from several hosts.

> One approach would be to write a new `_ash_collect` binary for the servers that makes an RPC to the central server, passing along all its arguments and any bits of information that need to be collected from the host.  This would result in one RPC per command, and there could be some complexity to manage to avoid hanging your system when the central server is not reachable or unresponsive.

> Another approach is to periodically push the new entries in the local DB file to a central server.  Since the same DB schema can be used on the central repository and on the individual servers, the collection and aggregation task is trivial.  In this design, if the central server is gone, the user prompts are not blocked and the central history will eventually become up-to-date when it is again available.  The downside is that this is not as 'real-time' as the first approach.

> These solutions may eventually manifest here in the codebase since I've been wanting to do it from the get-go.  Stay tuned!  :-)


I will fill this out as the questions come in.

In the meantime, you can [subscribe to the feed](http://code.google.com/p/advanced-shell-history/feeds) if you are interested in following this project.


### Troubleshooting ###

If you are having problems, please see the [troubleshooting guide.](HOWTO_Troubleshoot.md)