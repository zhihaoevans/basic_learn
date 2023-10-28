#!/bin/sh

: << EOF

-a/-e : file exist
-b    : file exist and it's block file
-c    : file exist and it's char file
-d    : file exist and it's directory
-f    : file exist and it's normal file
-L/-h : file exist and it's symbol link
-p    : file exist and it's pipe file
-S    : file exist and it's socket file

-s    : file exist and it's not empty

-g    : file exist and it's "setgid" bit was set
-k    : file exist and it's "sticky" bit was set
-u    : file exist and it's "setuid" bit was set

-G    : file exist and it's owned by effictive group id
-O    : file exist and it's owned by effictive user id

-N    : file was modified after last read

-r    : file exist and it can be read
-w    : file exist and it can be write
-x    : file exist and it can be execute

EOF