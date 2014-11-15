<html>
	<head>
		<!-- 新 Bootstrap 核心 CSS 文件 -->
		<link rel="stylesheet" href="http://cdn.bootcss.com/bootstrap/3.3.0/css/bootstrap.min.css">
		
		<!-- 可选的Bootstrap主题文件（一般不用引入） -->
		<link rel="stylesheet" href="http://cdn.bootcss.com/bootstrap/3.3.0/css/bootstrap-theme.min.css">
		
		<!-- jQuery文件。务必在bootstrap.min.js 之前引入 -->
		<script src="http://cdn.bootcss.com/jquery/1.11.1/jquery.min.js"></script>
		
		<!-- 最新的 Bootstrap 核心 JavaScript 文件 -->
		<script src="http://cdn.bootcss.com/bootstrap/3.3.0/js/bootstrap.min.js"></script>
		<meta http-equiv="content-type" content="text/html; charset=UTF-8" />
	</head>
	<body>
		<div class="container-fluid">
			<div class="page-header">
		  	<h1>Rubik's Cube Solver <small>beta</small></h1>
			</div>
			<div class="panel panel-default">
		  <div class="panel-heading">
		    <h3 class="panel-title">输入说明</h3>
		  </div>
		  <div class="panel-body">
		    颜色记号：<b>w</b>:白色&nbsp;<b>y</b>:黄色&nbsp;<b>g</b>:绿色&nbsp;<b>b</b>:蓝色&nbsp;<b>r</b>:红色&nbsp;<b>o</b>:橙色<br />
		    六面输入顺序：先任意选定一面作为前面，之后按照 <b>左 右 上 下 前 后</b> 顺序输入六面颜色<br />
		    面内输入顺序：第<b>1</b>行第<b>1</b>个 第<b>1</b>行第<b>2</b>个 第<b>1</b>行第<b>3</b>个 第<b>2</b>行第<b>1</b>个...<br />
		    例：orobbwbbygobbggyybgrryyybwrrwoowbyyywgworrgrgwgwoowogr
		  </div>
		</div>
		<div class="panel panel-default">
		  <div class="panel-heading">
		    <h3 class="panel-title">输出说明</h3>
		  </div>
		  <div class="panel-body">
		    基本操作：<br />
		    <b>F</b>:前面顺时针 <b>B</b>:后面顺时针 <b>L</b>:左面顺时针 <b>R</b>:右面顺时针 <b>U</b>:上面顺时针 <b>D</b>:下面顺时针 <b>rxy</b>:上下中间层顺时针(从下面看) <b>rxz</b>:前后中间层顺时针(从前面看) <b>ryz</b>:左右中间层顺时针(从右面看) <br />
		    <b>Fi</b>:前面逆时针 <b>Bi</b>:后面逆时针 <b>Li</b>:左面逆时针 <b>Ri</b>:右面逆时针 <b>Ui</b>:上面逆时针 <b>Di</b>:下面逆时针 <b>rxyi</b>:上下中间层逆时针(从下面看) <b>rxzi</b>:前后中间层逆时针(从前面看) <b>ryzi</b>:左右中间层逆时针(从右面看) 
		  </div>
		</div>
			<form role="form" action="" method="GET" id="input">
				<div class="form-group">
					<div id="slug_group">
						<div class="input-group">
					  	<span class="input-group-addon input-lg">cube</span>
					  	<input class="form-control input-lg" type="text" id="slug" name="cube" placeholder="" value="<?php echo $_GET['cube']; ?>">
					  	<span class="input-group-btn">
      					<button class="btn btn-default btn-lg" type="button" onclick="document.getElementById('input').submit();">Solve!</button>
   						</span>
						</div>
				  </div>
			  </div>
		  </form>
		

<?php
$cube=$_GET['cube'];
if($cube!="")
{
	echo '<div class="panel panel-default">';
	echo '<div class="panel-heading">';
	echo '<h3 class="panel-title">操作步骤</h3>';
	echo '</div>';
	echo '<div class="panel-body">';
	exec("/var/www/bin/server ".escapeshellcmd($cube),$output);
	for ($i=0;$i<count($output);$i++)
	{
		echo '<span class="label label-default" style="display: inline-block;">'.$output[$i].'</span>';
		if ($i%4==3)
		{
			echo '	';
		}
	}
	echo '</div>';
	echo '</div>';
}
?>

		</div>
	</body>
</html>