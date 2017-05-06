<?php
//连接数据库
function getInfo( $id){
    $link = mysqli_connect('192.168.1.33','zhou','root') or die('mysql connect error');
    mysqli_query($link,'set names utf8');
    mysqli_select_db($link,'test2');
    try
    {
        $sql = 'select flag from test2 where id='.$id;

        $result = mysqli_query($link, $sql);
        var_dump($result);
        if($result)
        {
            $info = mysqli_fetch_assoc($result);
            //var_dump($info);
            if($info){
                return $info['flag'];
            }
        }

        return 0;
    }catch (Exception $e)
    {
        echo $e->getMessage();
    }

}

$serv = new Swoole\Websocket\Server("0.0.0.0", 9502);

$serv->on('Open', function($server, $req) {
    echo "connection open: ".$req->fd;
});

$serv->on('Message', function($server, $frame) {

    $jsonInfo = json_decode($frame->data, true);
    var_dump($jsonInfo);

    $results = getInfo($jsonInfo['id']);
    if( $results == 1){
        $server->push($frame->fd, json_encode(["out" => 1]));
    }else{
        $server->push($frame->fd, json_encode(["out" => 2]));
    }

});

$serv->on('Close', function($server, $fd) {
    echo "connection close: ".$fd;
});

$serv->start();