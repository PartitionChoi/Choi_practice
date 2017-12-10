<?php
	require_once("dbconfig.php");
	$bNo = $_GET['bno'];

	if(!empty($bNo) || empty($_COOKIE['board_free_' . $bNo])) {
		$sql = 'update board_free set b_hit = b_hit + 1 where b_no = ' . $bNo;
		$result = $db->query($sql); 
		if(empty($result)) {
			?>
			<script>
				alert('오류가 발생했습니다.');
				history.back();
			</script>
			<?php 
		} else {
			setcookie('board_free_' . $bNo, TRUE, time() + (60 * 60 * 24), '/');
		}
	}
	
	$sql = 'select b_title, b_content, b_date, b_hit, b_id from board_free where b_no = ' . $bNo;
	$result = $db->query($sql);
	$row = $result->fetch_assoc();
?>
<!DOCTYPE html>
<html>
  <head>
    <meta charset="utf-8" />
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
      <meta name="description" content="">
        <meta name="viewport" content="width=device-width, initial-scale=1">
          <title>자유게시판</title>
          <link href='http://fonts.googleapis.com/css?family=Raleway:400,100,300,700,600,500' rel='stylesheet' type='text/css'>
            <link href='http://fonts.googleapis.com/css?family=Droid+Serif:400,400italic,700' rel='stylesheet' type='text/css'>


              <link rel="stylesheet" href="css/slicknav.css">
                <link rel="stylesheet" href="css/owl.theme.css">
                  <link rel="stylesheet" href="css/owl.carousel.css">
                    <link rel="stylesheet" href="css/owl.transitions.css">
                      <link rel="stylesheet" href="css/font-awesome.min.css">
                        <link rel="stylesheet" href="css/bt.min.css">
                          <link rel="stylesheet" href="css/main.css">
                            <link rel="stylesheet" href="css/responsive.css">
                              <script src="js/vendor/modernizr-2.6.2.min.js"></script>
                              <link rel="stylesheet" href="./css/normalize.css" />
                              <link rel="stylesheet" href="./css/board.css" />
                              <script src="./js/jquery-2.1.3.min.js"></script>
                            </head>
  <body>
    <section id="header">
      <div class="container">
        <div class="row">
          <div class="col-md-6">
            <div class="block-left">
              <nav class="navbar navbar-default" role="navigation">
                <div class="container-fluid">
                  <div class="navbar-header">
                    <button type="button" class="navbar-toggle collapsed" data-toggle="collapse" data-target="#bs-example-navbar-collapse-1">
                      <span class="sr-only">Toggle navigation</span>
                      <span class="icon-bar"></span>
                      <span class="icon-bar"></span>
                      <span class="icon-bar"></span>
                    </button>
                    <div class="nav-logo">
                      <a href="http://113.198.236.215">
                        <img src="img/logo.jpg" alt="logo">
                    </a>
                    </div>
                  </div>
                  <div class="collapse navbar-collapse" id="bs-example-navbar-collapse-1">
                    <ul class="nav navbar-nav">
                      <li class="active">
                        <a href="http://113.198.236.215">
                          Home<span class="sr-only">(current)</span>
                        </a>
                      </li>
                      <li>
                        <a href="rasp.html">HIWT</a>
                      </li>
                      <li>
                        <a href="sch.html">Scratch Game</a>
                      </li>
                      <li>
                        <a href="choidg/choidg.html">CHOI DG</a>
                      </li>
                      <li>
                        <a href="kimjs/kimjs.html">KIM JS</a>
                      </li>
                      <li>
                        <a href="kimkw/kimkw.html">KIM KW</a>
                      </li>
                      <li>
                        <a href="kimjh/kimjh.html">KIM JH</a>
                      </li>
                      <li>
                        <a href="list.php">Free board</a>
                      </li>
                    </ul>
                  </div>
                </div>
              </nav>
            </div>
          </div>

          <div class="col-md-6">
            <div class="block-right">
              <div class="contact-area">
                <ul>
                  <li>
                    <i class="fa fa-phone-square"></i>담당자 : 010-2863-1221
                  </li>
                  <li>
                    <i class="fa fa-envelope-o"></i>
                    <a href="#" onclick="window.open('mails.php','메일보내기','width=550,height=300')">donggyu5878@gmail.com</a>
                  </li>
                </ul>
              </div>
            </div>
          </div>
        </div>
      </div>
    </section>
    <article class="boardArticle">
      <h3>자유게시판 글뷰어</h3>
      <div id="boardView">
        <h3 id="boardTitle">
          <?php echo $row['b_title']?>
        </h3>
        <div id="boardInfo">
          <span id="boardID">
            작성자: <?php echo $row['b_id']?>
          </span>
          <span id="boardDate">
            작성일: <?php echo $row['b_date']?>
          </span>
          <span id="boardHit">
            조회: <?php echo $row['b_hit']?>
          </span>
        </div>
        <div id="boardContent">
          <?php echo $row['b_content']?>
        </div>
        <div class="btnSet">
          <a href="./write.php?bno=<?php echo $bNo?>">수정
          </a>
          <a href="./delete.php?bno=<?php echo $bNo?>">삭제
          </a>
          <a href="./list.php">목록</a>
          <p>
            <br/>
            <br/>
          </p>
        </div>
        <div id="boardComment">
          <?php include_once("./comment.php")?>
        </div>
      </div>
    </article>
    <section id="footer">
      <div class="container">
        <div class="row">
          <div class="col-md-12">
            <div class="block">
              <div class="footer-contant">
                <h3>Embeded system , Raspberry Pi</h3>
                <h3>and Scratch</h3>
                <div class="support-link">
                  <ul>
                    <li>
                      <a href="#">Copyright ⓒ Dong-Eui University. Group A-5</a>
                    </li>
                  </ul>
                </div>
              </div>
            </div>
          </div>
        </div>
      </div>
    </section>


    <script src="//ajax.googleapis.com/ajax/libs/jquery/1.10.2/jquery.min.js"></script>
    <script>
      window.jQuery || document.write('<script src="js/vendor/jquery-1.10.2.min.js">
        <\/script>')
      </script>
      <script src="js/owl.carousel.min.js"></script>
      <script src="js/bt.min.js"></script>
      <script src="js/plugins.js"></script>
      <script src="js/main.js"></script>
    </body>
</html>