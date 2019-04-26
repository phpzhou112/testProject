<?php

/**
 * php使用rsa加密和解密
 *
 * linux端生成密钥文件
 * openssl genrsa -out rsa_private_key.pem 1024   //生成密钥
 * openssl rsa -in rsa_private_key.pem -pubout -out rsa_public_key.pem  //生成公钥
 */

function test()
{
    $privateKeyFilePath = 'rsa_private_key.pem';
    $publicKeyFilePath = 'rsa_public_key.pem';
    extension_loaded('openssl') or die('php需要openssl扩展支持');
    (file_exists($privateKeyFilePath) && file_exists($publicKeyFilePath)) or die('文件路径不正确');
    $privateKey = openssl_pkey_get_private(file_get_contents($privateKeyFilePath));
    $publicKey = openssl_pkey_get_public(file_get_contents($publicKeyFilePath));

    ($privateKey && $publicKey) or die('密钥或者公钥不可用');


// 加密数据
    $originalData = '我的帐号是:toutiao,密码是:123456';
// 加密以后的数据
    $encryptData = '';
    echo '原数据为:', $originalData, PHP_EOL;

///////////////////////////////用私钥加密////////////////////////
    if (openssl_private_encrypt($originalData, $encryptData, $privateKey)) {

// 加密后 可以base64_encode后方便在网址中传输
        echo '加密成功，加密后数据(base64_encode后)为:', base64_encode($encryptData), PHP_EOL;
    } else {
        exit('加密失败');
    }

///////////////////////////////用公钥解密////////////////////////
    echo PHP_EOL;

//解密以后的数据
    $decryptData = '';
    if (openssl_public_decrypt($encryptData, $decryptData, $publicKey)) {
        echo '解密成功，解密后数据为:', $decryptData, PHP_EOL;
    } else {
        exit('解密成功');
    }
}
