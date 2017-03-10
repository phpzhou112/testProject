<?php
//// 创建一对cURL资源
//$ch1 = curl_init();
//$ch2 = curl_init();
//
//// 设置URL和相应的选项
//curl_setopt($ch1, CURLOPT_URL, "http://www.baidu.com/");
//curl_setopt($ch1, CURLOPT_HEADER, 0);
//curl_setopt($ch2, CURLOPT_URL, "http://www.php.net/");
//curl_setopt($ch2, CURLOPT_HEADER, 0);
//
//// 创建批处理cURL句柄
//$mh = curl_multi_init();
//
//// 增加2个句柄
//curl_multi_add_handle($mh,$ch1);
//curl_multi_add_handle($mh,$ch2);
//
//$running=null;
//// 执行批处理句柄
//do {
//    usleep(10000);
//    curl_multi_exec($mh,$running);
//} while ($running > 0);
//
//// 关闭全部句柄
//curl_multi_remove_handle($mh, $ch1);
//curl_multi_remove_handle($mh, $ch2);
//curl_multi_close($mh);




$ch_1 = curl_init('http://www.cnblogs.com/phpzhou/p/6516152.html');
$ch_2 = curl_init('http://localhost/test_curl/test2.php');
curl_setopt($ch_1, CURLOPT_RETURNTRANSFER, true);
curl_setopt($ch_2, CURLOPT_RETURNTRANSFER, true);

// build the multi-curl handle, adding both $ch
$mh = curl_multi_init();
curl_multi_add_handle($mh, $ch_1);
curl_multi_add_handle($mh, $ch_2);

//解决并发请求过多，出现页面假死状态,使用curl_multi_select
$active = null;
do {
    $mrc = curl_multi_exec($mh, $active);
} while ($mrc == CURLM_CALL_MULTI_PERFORM);

while ($active && $mrc == CURLM_OK) {
    if (curl_multi_select($mh) == -1) {
        usleep(100);
    }
    do {
        $mrc = curl_multi_exec($mh, $active);
    } while ($mrc == CURLM_CALL_MULTI_PERFORM);
}


//close the handles
curl_multi_remove_handle($mh, $ch_1);
curl_multi_remove_handle($mh, $ch_2);
curl_multi_close($mh);

// all of our requests are done, we can now access the results
$response_1 = curl_multi_getcontent($ch_1);
$response_2 = curl_multi_getcontent($ch_2);
echo "$response_1 $response_2"; // output results
