<?php

function dameon(){
	if(($pid=pcntl_fork())<0)
{
	echo "fork失败!";
	exit;
}else if($pid != 0)
{
	echo "父进程退出!";
	exit;
}
$sid = posix_setsid();
if($sid<0)
{
	echo "sid错误!\n";
	exit;
}
if(!chdir("/"))
{
	echo "更改目录失败!\n";
	exit;
}
umask(0);
fclose(STDIN);
fclose(STDOUT);
fclose(STDERR);
}

dameon();
$i = 0;
while(true)
{
	sleep(1);
    echo "good".$i,PHP_EOL;
    $i++;
}









function daemonize()
{
	$pid = pcntl_fork();
	if ($pid == -1)
	{
	die("fork(1) failed!\n");
	}
	elseif ($pid > 0)
	{
	//让由用户启动的进程退出
	exit(0);
	}
 
	//建立一个有别于终端的新session以脱离终端
	posix_setsid();
	 
	$pid = pcntl_fork();
	if ($pid == -1)
	{
		die("fork(2) failed!\n");
	}
	elseif ($pid > 0)
	{
	//父进程退出, 剩下子进程成为最终的独立进程
		exit(0);
	}
}
 
daemonize();
$i = 0;
$fp = fopen("./test.txt", "a+");
while($i<100)
{
	fwrite($fp, "test");
	$i++;
}
fclose($fp);
