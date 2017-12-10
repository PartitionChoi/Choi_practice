<?php
	require_once("dbconfig.php");

	if(isset($_GET["bno"])) {
		$bNo = $_GET["bno"];
	}
?>
<!DOCTYPE html>
<html>
<head>
	<meta charset="utf-8" />
	<meta http-equiv="X-UA-Compatible" content="IE=edge">
        <title>SAMKIM</title>
        <meta name="description" content="">
        <meta name="viewport" content="width=device-width, initial-scale=1">
	<title>자유게시판 글삭제</title>
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
                         <a href="http://113.198.236.215"><img src="img/logo.jpg" alt="logo"></a>
								  </div>
								</div>

								<div class="collapse navbar-collapse" id="bs-example-navbar-collapse-1">
								  <ul class="nav navbar-nav">
									<li class="active"><a href="http://113.198.236.215">Home<span class="sr-only">(current)</span></a></li>
                                    <li><a href="rasp.html">HIWT</a></li>
                                    <li><a href="sch.html">Scratch Game</a></li>
									<li><a href="choidg/choidg.html">CHOI DG</a></li>
									<li><a href="kimjs/kimjs.html">KIM JS</a></li>
									<li><a href="kimkw/kimkw.html">KIM KW</a></li>
                                    <li><a href="kimjh/kimjh.html">KIM JH</a></li>
                                    <li><a href="list.php">Free board</a></li>
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
                                    <li><i class="fa fa-phone-square"></i>담당자 : 010-2863-1221</li>
                                    <li><i class="fa fa-envelope-o"></i><a href="#" onclick="window.open('mails.php','메일보내기','width=550,height=300')">donggyu5878@gmail.com</a></li>
                                </ul>
                            </div>
                        </div>
                    </div>
                </div>
            </div>
        </section>
	<article class="boardArticle">
		<?php
			if(isset($bNo)) {
				$sql = 'select count(b_no) as cnt from board_free where b_no = ' . $bNo;
				$result = $db->query($sql);
				$row = $result->fetch_assoc();
				if(empty($row['cnt'])) {
		?>
		<script>
			alert('글이 존재하지 않습니다.');
			history.back();
		</script>
		<?php
			exit;
				}
				
				$sql = 'select b_title from board_free where b_no = ' . $bNo;
				$result = $db->query($sql);
				$row = $result->fetch_assoc();
		?>
		<div id="boardDelete">
			<form action="./delete_update.php" method="post">
				<input type="hidden" name="bno" value="<?php echo $bNo?>">
				<table>
					<caption class="readHide">자유게시판 글삭제</caption>
					<thead>
						<tr>

						</tr>
					</thead>
					<tbody>
						<tr>
							<th scope="row">글 제목</th>
							<td><?php echo $row['b_title']?></td>
						</tr>
						<tr>
							<th scope="row"><label for="bPassword">비밀번호<br/></label></th>
							<td><input type="password" name="bPassword" id="bPassword"></td>
						</tr>
					</tbody>
				</table>

				<div class="btnSet">
					<button type="submit" class="btnSubmit btn">삭제</button>
					<a href="./list.php" class="btnList btn">목록</a>
					<p><br/><br/></p>
				</div>
			</form>
		</div>
	<?php
		} else {
	?>
		<script>
			alert('정상적인 경로를 이용해주세요.');
			history.back();
		</script>
	<?php
			exit;
		}
	?>
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
                                        <li><a href="#">Copyright ⓒ Dong-Eui University. Group A-5</a></li>
                                    </ul>
                                </div>
                            </div>
                        </div>
                    </div>
                </div>
            </div>
        </section>


        <script src="//ajax.googleapis.com/ajax/libs/jquery/1.10.2/jquery.min.js"></script>
        <script>window.jQuery || document.write('<script src="js/vendor/jquery-1.10.2.min.js"><\/script>')</script>
        <script src="js/owl.carousel.min.js"></script>
        <script src="js/bt.min.js"></script>
        <script src="js/plugins.js"></script>
        <script src="js/main.js"></script>
</body>
</html>