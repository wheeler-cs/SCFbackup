# SCFbackup
**S**erver-**C**lient **F**ile Backup tool.
## About
SCFbackup is a program designed to maintain file parity between multiple clients and a single
central server. Changes occurring on a single client are sent to the server, which then propagates
them to other relevant clients. Think of it like how git changes are made by a client, pushed to a
repo, and the other clients pull the changes. In this case, however, changes made by the client are
automatically sent to the server, and clients automatically receive incoming changes. This isn't a
direct comparison, but it should get the idea across.

SCFbackup is intended to be used by those who prefer to manage their own file servers rather than
use an external service (Google Drive, Dropbox, etc.). It's also intended to handle smaller files
too, so performance of the tool may vary depending on the file size.
