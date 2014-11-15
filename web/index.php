<html>
	<head>
		<!-- �� Bootstrap ���� CSS �ļ� -->
		<link rel="stylesheet" href="http://cdn.bootcss.com/bootstrap/3.3.0/css/bootstrap.min.css">
		
		<!-- ��ѡ��Bootstrap�����ļ���һ�㲻�����룩 -->
		<link rel="stylesheet" href="http://cdn.bootcss.com/bootstrap/3.3.0/css/bootstrap-theme.min.css">
		
		<!-- jQuery�ļ��������bootstrap.min.js ֮ǰ���� -->
		<script src="http://cdn.bootcss.com/jquery/1.11.1/jquery.min.js"></script>
		
		<!-- ���µ� Bootstrap ���� JavaScript �ļ� -->
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
		    <h3 class="panel-title">����˵��</h3>
		  </div>
		  <div class="panel-body">
		    ��ɫ�Ǻţ�<b>w</b>:��ɫ&nbsp;<b>y</b>:��ɫ&nbsp;<b>g</b>:��ɫ&nbsp;<b>b</b>:��ɫ&nbsp;<b>r</b>:��ɫ&nbsp;<b>o</b>:��ɫ<br />
		    ��������˳��������ѡ��һ����Ϊǰ�棬֮���� <b>�� �� �� �� ǰ ��</b> ˳������������ɫ<br />
		    ��������˳�򣺵�<b>1</b>�е�<b>1</b>�� ��<b>1</b>�е�<b>2</b>�� ��<b>1</b>�е�<b>3</b>�� ��<b>2</b>�е�<b>1</b>��...<br />
		    ����orobbwbbygobbggyybgrryyybwrrwoowbyyywgworrgrgwgwoowogr
		  </div>
		</div>
		<div class="panel panel-default">
		  <div class="panel-heading">
		    <h3 class="panel-title">���˵��</h3>
		  </div>
		  <div class="panel-body">
		    ����������<br />
		    <b>F</b>:ǰ��˳ʱ�� <b>B</b>:����˳ʱ�� <b>L</b>:����˳ʱ�� <b>R</b>:����˳ʱ�� <b>U</b>:����˳ʱ�� <b>D</b>:����˳ʱ�� <b>rxy</b>:�����м��˳ʱ��(�����濴) <b>rxz</b>:ǰ���м��˳ʱ��(��ǰ�濴) <b>ryz</b>:�����м��˳ʱ��(�����濴) <br />
		    <b>Fi</b>:ǰ����ʱ�� <b>Bi</b>:������ʱ�� <b>Li</b>:������ʱ�� <b>Ri</b>:������ʱ�� <b>Ui</b>:������ʱ�� <b>Di</b>:������ʱ�� <b>rxyi</b>:�����м����ʱ��(�����濴) <b>rxzi</b>:ǰ���м����ʱ��(��ǰ�濴) <b>ryzi</b>:�����м����ʱ��(�����濴) 
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
	echo '<h3 class="panel-title">��������</h3>';
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