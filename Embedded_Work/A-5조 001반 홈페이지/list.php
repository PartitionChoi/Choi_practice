<?php

	require_once("dbconfig.php");
	


	if(isset($_GET['page'])) {
		$page = $_GET['page'];
	} else {
		$page = 1;
	}
	
	
	if(isset($_GET['searchColumn'])) {
		$searchColumn = $_GET['searchColumn'];
		$subString .= '&amp;searchColumn=' . $searchColumn;
	}
	if(isset($_GET['searchText'])) {
		$searchText = $_GET['searchText'];
		$subString .= '&amp;searchText=' . $searchText;
	}
	
	if(isset($searchColumn) && isset($searchText)) {
		$searchSql = ' where ' . $searchColumn . ' like "%' . $searchText . '%"';
	} else {
		$searchSql = '';
	}
	
	
	$sql = 'select count(*) as cnt from board_free' . $searchSql;
	$result = $db->query($sql);
	$row = $result->fetch_assoc();
	
	$allPost = $row['cnt']; 
	
	if(empty($allPost)) {
		$emptyData = '<tr><td class="textCenter" colspan="5">글이 존재하지 않습니다.</td></tr>';
	} else {

		$onePage = 15; 
		$allPage = ceil($allPost / $onePage); 
		
		if($page < 1 && $page > $allPage) {
?>
<script>
  alert("존재하지 않는 페이지입니다.");
  history.back();
</script>
<?php
			exit;
		}
	
		$oneSection = 10; 
		$currentSection = ceil($page / $oneSection); 
		$allSection = ceil($allPage / $oneSection); 
		
		$firstPage = ($currentSection * $oneSection) - ($oneSection - 1); 
		
		if($currentSection == $allSection) {
			$lastPage = $allPage; 
		} else {
			$lastPage = $currentSection * $oneSection; 
		}
		
		$prevPage = (($currentSection - 1) * $oneSection); 
		$nextPage = (($currentSection + 1) * $oneSection) - ($oneSection - 1); 
		
		$paging = '<ul>'; 
		

		if($page != 1) { 
			$paging .= '<li class="page page_start"><a href="./list.php?page=1' . $subString . '">처음</a></li>';
		}
		if($currentSection != 1) { 
			$paging .= '<li class="page page_prev"><a href="./list.php?page=' . $prevPage . $subString . '">이전</a></li>';
		}
		
		for($i = $firstPage; $i <= $lastPage; $i++) {
			if($i == $page) {
				$paging .= '<li class="page current">' . $i . '</li>';
			} else {
				$paging .= '<li class="page"><a href="./list.php?page=' . $i . $subString . '">' . $i . '</a></li>';
			}
		}
		
		if($currentSection != $allSection) { 
			$paging .= '<li class="page page_next"><a href="./list.php?page=' . $nextPage . $subString . '">다음</a></li>';
		}
		
		if($page != $allPage) { 
			$paging .= '<li class="page page_end"><a href="./list.php?page=' . $allPage . $subString . '">끝</a></li>';
		}
		$paging .= '</ul>';

		
		
		$currentLimit = ($onePage * $page) - $onePage; 
		$sqlLimit = ' limit ' . $currentLimit . ', ' . $onePage; 
		
		$sql = 'select * from board_free' . $searchSql . ' order by b_no desc' . $sqlLimit; 
		$result = $db->query($sql);
	}
?>
<!DOCTYPE html>
<html>
  <head>
    <meta charset="utf-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
      <title>SAMKIM</title>
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
      <div id="boardList">
        <table>
          <thead>
            <tr>
              <th scope="col" class="no">번호</th>
              <th scope="col" class="title">제목</th>
              <th scope="col" class="author">작성자</th>
              <th scope="col" class="date">작성일</th>
              <th scope="col" class="hit">조회</th>
            </tr>
          </thead>
         <tbody>
          <?php
						if(isset($emptyData)) {
							echo $emptyData;
						} else {
							while($row = $result->fetch_assoc())
							{
								$datetime = explode(' ', $row['b_date']);
								$date = $datetime[0];
								$time = $datetime[1];
								if($date == Date('Y-m-d'))
									$row['b_date'] = $time;
								else
									$row['b_date'] = $date;
						?>
            <tr>
              <td class="no">
                <?php echo $row['b_no']?>
              </td>
              <td class="title">
                <a href="./view.php?bno=<?php echo $row['b_no']?>"><?php echo $row['b_title']?>
                </a>
              </td>
              <td class="author">
                <?php echo $row['b_id']?>
              </td>
              <td class="date">
                <?php echo $row['b_date']?>
              </td>
              <td class="hit">
                <?php echo $row['b_hit']?>
              </td>
            </tr>
            <?php
							}
						}
						?>
          </tbody>
        </table>
        <div class="btnSet">
          <a href="./write.php" class="btnWrite btn">글쓰기</a>
        </div>
        <div class="paging">
          <?php echo $paging ?>
        </div>
        <div class="searchBox">
          <form action="./list.php" method="get">
            <select name="searchColumn">
              <option
                <?php echo $searchColumn=='b_title'?'selected="selected"':null?> value="b_title">제목
              </option>
              <option
                <?php echo $searchColumn=='b_content'?'selected="selected"':null?> value="b_content">내용
              </option>
              <option
                <?php echo $searchColumn=='b_id'?'selected="selected"':null?> value="b_id">작성자
              </option>
            </select>
            <input type="text" name="searchText" value=""<?php echo isset($searchText)?$searchText:null?>">
            <button type="submit">검색</button>
            <p>
              <br/>
            </p>
          </form>
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