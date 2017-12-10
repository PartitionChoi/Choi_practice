<?php
	require_once("dbconfig.php");

	if(isset($_POST['bno'])) {
		$bNo = $_POST['bno'];
	}

	$bPassword = $_POST['bPassword'];

if(isset($bNo)) {
	$sql = 'select count(b_password) as cnt from board_free where b_password=password("' . $bPassword . '") and b_no = ' . $bNo;
	$result = $db->query($sql);
	$row = $result->fetch_assoc();
	
	if($row['cnt']) {
		$sql = 'delete from board_free where b_no = ' . $bNo;
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
}

	$result = $db->query($sql);

if($result) {
	$msg = '정상적으로 글이 삭제되었습니다.';
	$replaceURL = './';
} else {
	$msg = '글을 삭제하지 못했습니다.';
?>
	<script>
		alert("<?php echo $msg?>");
		history.back();
	</script>
<?php
	exit;
}


?>
<script>
	alert("<?php echo $msg?>");
	location.replace("<?php echo $replaceURL?>");
</script>