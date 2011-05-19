<?php

/*
* @copyright (c) 2008 Nicolo John Davis
* @license http://opensource.org/licenses/gpl-license.php GNU Public License
*/

session_start();
if(!isset($_SESSION['isloggedin']))
{
	echo "<meta http-equiv='Refresh' content='0; URL=login.php' />";
	exit(0);
}
else
{
	$username = $_SESSION['username'];
	$userid = $_SESSION['userid'];

	if($_SESSION['admin'] != true)
	{
		print "You need to be the administrator to access this file";
		exit(0);
	}
}

include('settings.php');
?>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">

<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>

<meta name="Keywords" content="programming, contest, coding, judge" />
<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1" />
<meta name="Distribution" content="Global" />
<meta name="Robots" content="index,follow" />

<link rel="stylesheet" href="images/Envision.css" type="text/css" />

<title>Programming Contest</title>
<script type="text/javascript" src="jquery-1.3.1.js"></script>
<script type="text/javascript" src="jquery.timers-1.1.2.js"></script>
<?php include('timer.php'); ?>
<script type="text/javascript">
<!--

$(document).ready(
	function()
	{ 
		dispTime();
		getLeaders();
		getDetails();
		setInterval("dispTime()", 1000);  
		setInterval("getLeaders()", getLeaderInterval);  
		setInterval("getDetails()", getLeaderInterval);  

		$(".announcementform").focus();
		$(".announcementform").keypress( function(e) {
			if(e.which == 13)
			{
				var msg = this.value;
				this.value = "";

				if(msg != "") //To prevent empty line announcements
					$.post("admin/submitannouncement.php", { message: msg }, function(){
							messagebox('Announcement posted');
						});
			}
		});

		$("#uname,#problemid").change( function() {
				var uname = $("#uname").val();
				var id = $("#problemid").val();

				$.get("admin/getcode.php", {username: uname, problemid: id, mode: 'getdir'}, function(data) { $("#filename").html(data); });
			});
				
		//Initially populate the filename box with problem 1 of admin
		$.get("admin/getcode.php", {username: 'admin', problemid: '1', mode: 'getdir'}, function(data) { $("#filename").html(data); });

		$("#viewcodebutton").click( function() {
				var uname = $("#uname").val();
				var id = $("#problemid").val();
				var file = $("#filename").val();

				$.get("admin/getcode.php", {username: uname, problemid: id, filename: file}, function(data) { $("#codeplaceholder").html(data).fadeIn("fast"); });
			});
	} 
);

-->
</script>
	
</head>

<body class="menu7">
<!-- wrap starts here -->
<div id="wrap">
		
		<!--header -->
		<?php include('header.php'); ?>
		
		<!-- menu -->	
		<?php include('menu.php'); ?>
			
		<!-- content-wrap starts here -->
		<div id="content-wrap">
				
			<div id="main">

				<div class="messagebox" style="display: none"> </div>

				<h2>Post Announcement</h2>
				<input maxlength="400" class="announcementform" type="text" />

				<h2>View Code</h2>
				<p>
					Username
					<select id="uname">
						<?php
							$cn = mysql_connect('localhost', $DBUSER , $DBPASS);
							mysql_select_db($DBNAME, $cn);

							$result = mysql_query("select username from users");

							while($row = mysql_fetch_array($result))
								print "<option value='$row[0]'> $row[0] </option>";

							mysql_close($cn);
						?>
					</select>

					Problem
					<select id="problemid">
						<?php
							for($i=1 ; $i <= count($points) ; $i++)
								print "<option value='$i'> $i </option>";
						?>
					</select>

					Filename
					<select id="filename">
					</select>

					<button id="viewcodebutton">View</button>
				</p>

				<pre id="codeplaceholder" style="display: none">
				</pre>

			</div>
			
			<div id="sidebar">
				<?php include('sidebar.php'); ?>	
			</div>
		
		<!-- content-wrap ends here -->	
		</div>
					
		<!--footer starts here-->
		<div id="footer">
			<?php include('footer.php'); ?>
		</div>	

<!-- wrap ends here -->
</div>

</body>
</html>
