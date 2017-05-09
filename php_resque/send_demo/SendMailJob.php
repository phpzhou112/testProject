<?php

/**
 * Created by PhpStorm.
 * User: zhou
 * Date: 2017/5/4
 * Time: 16:00
 */
class SendMailJob
{
    public function setUp()
    {
        //开始工作
        require_once 'sendMail.php';
    }
    //job实体
    public function perform()
    {
        $mail = new SendMail();
        if($this->args){
            $toAddress = $this->args['toAddress'];
            $from = $this->args['from'];
            $fromName = $this->args['fromName'];
            $subject = $this->args['subject'];
            $body = $this->args['body'];
            //发送邮件
            $mail->send($toAddress, $from, $fromName, $subject, $body);
        }

    }
}