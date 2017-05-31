<?php
$client = new swoole_client(SWOOLE_SOCK_TCP);
$flag = $client->connect('192.168.1.114', 9501, -1);
if (!$flag) {
    exit('connected..' . "\r\n");
}
$client->send('hello');
$infos = '';
while (($info = $client->recv(1024)) != '') {
    $infos .= $info;
}
$file = fopen('./3.txt', 'a+');
fwrite($file, $infos);
fclose($file);
//echo $infos;
$client->close();