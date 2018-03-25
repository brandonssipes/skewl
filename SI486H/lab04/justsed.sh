#!/bin/bash

#invoke sed to edit the log file and reduce the lines to just the size value.

sed -e 's/.*size=//' size.log | sed -e 's/,.*//'
