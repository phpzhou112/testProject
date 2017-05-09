<?php

/**
 * Date: 2017/5/4
 * Time: 11:08
 */
class SendMail
{
    const HOST = 'smtp.163.com';
    const USER_NAME = 'xxxxxx';
    const PASSWD = 'xxxxxx';
    const PORT = 25;
    public $mail;

    public function __construct()
    {
        require './phpmailer/class.phpmailer.php';
        $this->mail = new PHPMailer(true);
        $this->mail->CharSet = "UTF-8";//设置信息的编码类型
        $this->mail->Host = SendMail::HOST; //使用163邮箱服务器
        $this->mail->IsSMTP();
        $this->mail->SMTPAuth = true; // 启用SMTP验证功能
        $this->mail->Username = SendMail::USER_NAME; //你的163服务器邮箱账号
        $this->mail->Password = SendMail::PASSWD; // 163邮箱密码
        $this->mail->Port = SendMail::PORT;//邮箱服务器端口号
    }

    public function send($toAddress, $from, $fromName, $subject, $body, $sendType = 'to', $ccAddress = '')
    {
        $this->mail->AddAddress($toAddress);
        if ('cc' == $sendType) {
            $this->mail->AddCC($ccAddress);
        }
        $this->mail->IsHTML(true);
        $this->mail->From = $from;
        $this->mail->FromName = $fromName;
        $this->mail->Subject = $subject;
        $this->mail->Body = $body;
        return $this->mail->Send();
    }
}


