<?php
	require_once("dbconfig.php");

	if(isset($_POST['bno'])) {
		$bNo = $_POST['bno'];
	}

	if(empty($bNo)) {
		$bID = $_POST['bID'];
		$date = date('Y-m-d H:i:s');
	}

	$bPassword = $_POST['bPassword'];
	$bTitle = $_POST['bTitle'];
	$bContent = $_POST['bContent'];

if(isset($bNo)) {
	$sql = 'select count(b_password) as cnt from board_free where b_password=password("' . $bPassword . '") and b_no = ' . $bNo;
	$result = $db->query($sql);
	$row = $result->fetch_assoc();
	
	if($row['cnt']) {
		$sql = 'update board_free set b_title="' . $bTitle . '", b_content="' . $bContent . '" where b_no = ' . $bNo;
		$msgState = '수정';
	} else {
		$msg = '비밀번호가 맞지 않습니다.';
	?>
		<script>
			alert("<?php echo $msg?>");
			history.back();
		</script>
	<?php
		exit;
	}
	
} else {
	$sql = 'insert into board_free (b_no, b_title, b_content, b_date, b_hit, b_id, b_password) values(null, "' . $bTitle . '", "' . $bContent . '", "' . $date . '", 0, "' . $bID . '", password("' . $bPassword . '"))';
	$msgState = '등록';
}

if(empty($msg)) {
	$result = $db->query($sql);

	if($result) {
		$msg = '정상적으로 글이 ' . $msgState . '되었습니다.';
		if(empty($bNo)) {
			$bNo = $db->insert_id;
		}
		$replaceURL = './view.php?bno=' . $bNo;
	} else {
		$msg = '글을 ' . $msgState . '하지 못했습니다.';
?>
		<script>
			alert("<?php echo $msg?>");
			history.back();
		</script>
<?php
		exit;
	}
}

?>
<script>
	alert("<?php echo $msg?>");
	location.replace("<?php echo $replaceURL?>");
</script>
