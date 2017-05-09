<?php
if(empty($argv[1])) {
	die('Specify the name of a job to add. e.g, php queue.php PHP_Job');
}

require __DIR__ . '/init.php';
date_default_timezone_set('GMT');
Resque::setBackend('127.0.0.1:6379');

// You can also use a DSN-style format:
//Resque::setBackend('redis://user:pass@127.0.0.1:6379');
//Resque::setBackend('redis://user:pass@a.host.name:3432/2');

$args = array(
    'toAddress' => '',
    'from'=> 'zpyphp@163.com',
    'fromName'=> 'zhou',
    'subject'=>'这是一个关系邮件',
    'body'=>'身体健康，阖家欢乐！',

);

$jobId = Resque::enqueue('default', 'SendMailJob', $args, true);

echo "Queued job ".$jobId."\n\n";
