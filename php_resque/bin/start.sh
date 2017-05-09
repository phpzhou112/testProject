#!/bin/bash
nohup QUEUE=notification php resque.php >> /var/log//phpreq.log 2>&1 &
