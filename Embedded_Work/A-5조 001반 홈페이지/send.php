<?php

$mail_from = trim($_POST['form_user']); // 보내는 사람메일주소 
$mail_to = trim($_POST['form_user']); // 받는사람 메일주소 

$mailheaders.= "Return-Path : ". trim($_POST['form_user'])." \r\n";	//리턴되는 메일을 받는 주소
$mailheaders.= "From : SendMailTest \r\n";
$Headers .= "from: raspberry <formmail> \r\n";
$Headers .= "Content-Type: text/html; charset=utf-8 \r\n";

$subject =  trim($_POST['subject']);
$contents = $_POST['content'];

mail($mail_to,$subject,$contents,$Headers);
echo "메일을 보냈습니다.";
?>