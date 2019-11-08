<?php

/**
 * Class RedisLock
 *
 * redis单实例锁
 * 1，使用随机值主要是为了能够安全地释放锁
 * 2，使用嵌套值支持同一个进程（线程，请求）中相同名称锁
 *
 * refer
 * https://redis.io/topics/distlock
 * http://www.oschina.net/translate/redis-distlock
 * https://github.com/ronnylt/redlock-php
 */
class RedisLock
{
    const PRE = 'lock_';
    const SALT = 'API';

    private static $_lock_arr = array();
    private static $_gc = false;
    private static $instance;

    public function __construct(array $server)
    {
        list($host, $port, $timeout) = $server;

        $redis = new Redis();
        $port = $port ?: 6379;
        $timeout = $timeout ?: 10;
        $redis->connect($host, $port, $timeout);
        static::$instance = $redis;
    }

    public static function get($lock, $timeout = 10)
    {
        $lock_key = static::PRE . md5(self::SALT . $lock);
        $redis = static::$instance;
        static::gc();


        if (!isset(static::$_lock_arr[$lock_key])) {
            $lock_value = uniqid();

            /*
                EX seconds -- Set the specified expire time, in seconds.
                PX milliseconds -- Set the specified expire time, in milliseconds.
                NX -- Only set the key if it does not already exist.
                XX -- Only set the key if it already exist.
            */
            $ret = $redis->set($lock_key, $lock_value, array('NX', 'EX' => $timeout));
            if ($ret === true) {
                static::$_lock_arr[$lock_key] = array(
                    'token' => $lock_value,
                    'nest' => 1
                );
            } else {
                $exist_lock_value = $redis->get($lock_key);
                echo "Get Redis Lock Failed" . $lock . $lock_key . 'curr value: ' . $exist_lock_value;
                return false;
            }
        } else {
            $redis->expire($lock_key, $timeout);
            static::$_lock_arr[$lock_key]['nest'] += 1;
            $lock_value = static::$_lock_arr[$lock_key]['token'];
        }
        echo "Get Redis Lock Success" . $lock . $lock_key . $lock_value;
        return true;
    }

    public static function release($lock)
    {
        $lock_key = static::PRE . md5(self::SALT . $lock);
        if (isset(static::$_lock_arr[$lock_key])) {

            static::$_lock_arr[$lock_key]['nest'] -= 1;
            if (static::$_lock_arr[$lock_key]['nest'] == 0) {

                $redis = static::$instance;
                $ret = $redis->get($lock_key);
                if ($ret == static::$_lock_arr[$lock_key]['token']) {
                    $redis->del($lock_key);
                } elseif ($ret) {
                    echo "Redis Lock Has Been Obtained By Others" . $lock . $lock_key . 'curr value: ' . $ret;
                }
                unset(static::$_lock_arr[$lock_key]);
            }
        } else {
            echo "release Redis Lock Wrong" . $lock . $lock_key;
        }
        echo "release Redis Lock Success" . $lock . $lock_key;
        return true;
    }

    private static function gc()
    {
        if (static::$_gc === true) return;
        register_shutdown_function(function () {

            $redis = static::$instance;
            foreach (static::$_lock_arr as $k => $v) {
                if (!$v['nest']) continue;
                $ret = $redis->get($k);
                if ($ret == $v['token']) {
                    $redis->del($k);
                }
            }
            static::$_lock_arr = array();
        });
        static::$_gc = true;
        return;
    }

}


