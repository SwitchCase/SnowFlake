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
<?php include('timer.php'); ?>
<script type="text/javascript">
<!--

function getChat()
{
	var chatCount = $("#chat > span").length;

	$.get("getchat.php", {already: chatCount}, function(data){
		  $("#chat").append(data);

		  if(data != '')
		  {
			  var objDiv = document.getElementById("chat");
			  objDiv.scrollTop = objDiv.scrollHeight;
		  }
	  });
}

$(document).ready(
	function()
	{ 
		dispTime();
		getLeaders();
		getDetails();
		getChat();
		setInterval("dispTime()", 1000);  
		setInterval("getLeaders()", getLeaderInterval);  
		setInterval("getDetails()", getLeaderInterval);  
		setInterval("getChat()", getChatInterval);  

		$(".chatform").focus();
		$(".chatform").keypress( function(e) {
			if(e.which == 13)
			{
				var msg = this.value;
				this.value = "";

				//$.post("submitchat.php", { message: msg }, function(data){ getChat(); }); This was causing duplication

				if(msg != "") //To prevent empty line messages
					$.post("submitchat.php", { message: msg });
			}
		});
	} 
);

-->
</script>
	
</head>

<body class="menu6">
<!-- wrap starts here -->
<div id="wrap">
		
		<!--header -->
		<?php include('header.php'); ?>
		
		<!-- menu -->	
		<?php include('menu.php'); ?>
			
		<!-- content-wrap starts here -->
		<div id="content-wrap">
				
			<div id="main">
				
				<div id="chat"> </div>

				<input maxlength="60" class="chatform" type="text" />

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
