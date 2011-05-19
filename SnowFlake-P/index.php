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

<!--[if IE]><script language="javascript" type="text/javascript" src="../excanvas.pack.js"></script><![endif]-->
<script type="text/javascript" src="jquery-1.3.1.js"></script>
<script type="text/javascript" src="flot/jquery.flot.js"></script>
<?php include('timer.php'); ?>
<script type="text/javascript">
<!--

function getTimeline()
{
	$.post("gettimeline.php", {}, function(data){

			$.plot($("#graph"), data,
				{
					lines: { show: true },
					points: { show: true },
					xaxis: { mode: "time" },
					yaxis: { ticks: 10, min: 0, max: 150 },
					grid: { backgroundColor: "#ffffff" },
					legend: { backgroundOpacity: 0.5, backgroundColor: "#fffaff"}
				}
			);

		}, "json");
}

$(document).ready(
	function()
	{ 
		dispTime();
		getLeader();
		getLeaders();
		getDetails();
		getProblemStats();
		getAnnouncements();
		getTimeline();

		setInterval("dispTime()", 1000);  
		setInterval("getLeaders()", getLeaderInterval);  
		setInterval("getDetails()", getLeaderInterval);  
		setInterval("getLeader()", getLeaderInterval);  
		setInterval("getProblemStats()", getLeaderInterval);  
		setInterval("getAnnouncements()", getLeaderInterval);  
		setInterval("getTimeline()", getLeaderInterval);  
	} 
);

-->
</script>
	
</head>

<body class="menu1">
<!-- wrap starts here -->
<div id="wrap">
		
		<!--header -->
		<?php include('header.php'); ?>
		
		<!-- menu -->	
		<?php include('menu.php'); ?>
			
		<!-- content-wrap starts here -->
		<div id="content-wrap">
								
			<div id="main">

				<?php

					if($time < $startTime)	
					{
						echo '<h2>The contest has not yet begun</h2>';
					}
					else
					{
						if($running)
							echo '<h2>The contest is running</h2>';
						else
							echo '<h2>The contest has ended</h2>';
							
						echo <<<EOHTML
						<span id="leader"></span>

						<span id="announcements"></span>

						<h2>Contest timeline</h2>
						<div id="graph" style="width:500px;height:250px;"></div>

						<h2>Submission Statistics</h2>
						<span id="problemstats"></span>
EOHTML;
					}

				?>

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
