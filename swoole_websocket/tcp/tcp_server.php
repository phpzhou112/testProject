<?php
/**
 * tcpserver，测试数据传输和接收
 */
$host = '192.168.1.114';
$port = 9501;
$maxSize = 32 * 1024 * 1024;
$serv = new swoole_server($host, $port, SWOOLE_BASE, SWOOLE_SOCK_TCP);
//设置运行参数
$serv->set([
    'worker_num' => 1,
    'daemonize' => false,
    'backlog' => 2,
    //   'open_length_check' => true,
    //'package_max_length' => 81920
    'buffer_output_size' => 32 * 1024 * 1024
]);
//注册回调函数
$serv->on('connect', function ($serv, $fd, $from_id) {
    echo "[#" . posix_getpid() . "]\tClient@[$fd:$from_id]: Connect.\n";
});
$serv->on('receive', function ($serv, $fd, $from_id, $data) {
    require_once 'mysql.php';
    $mysql = new Mysql();
    $info = $mysql->getInfo();
    $result = json_encode($info);

    $serv->send($fd, $result);

    $serv->close($fd);
});
$serv->on('close', function ($serv, $fd, $from_id) {
    echo "[#" . posix_getpid() . "]\tClient@[$fd:$from_id]: Close.\n";
});

$serv->start();
