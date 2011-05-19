<?php

/*
* @copyright (c) 2008 Nicolo John Davis
* @license http://opensource.org/licenses/gpl-license.php GNU Public License
*/

session_start();
if(isset($_SESSION['isloggedin'])) 
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

$(document).ready(function(){ 
		dispTime();
		getLeaders();
		getDetails();
		setInterval("dispTime()", 1000);  
		setInterval("getLeaders()", getLeaderInterval);  
		setInterval("getDetails()", getLeaderInterval);  
	} );

-->
</script>
	
</head>

<body class="menu5">
<!-- wrap starts here -->
<div id="wrap">
		
		<!--header -->
		<?php include('header.php'); ?>
		
		<!-- menu -->	
		<?php include('menu.php'); ?>
			
		<!-- content-wrap starts here -->
		<div id="content-wrap">
				
			<div id="main">
				
				<a name="TemplateInfo"></a>
				<h2>Rules</h2>
				
				<ul>
					<li>All programs will be compiled using the GNU compiler collection.</li>
					<li>You are required to solve all the problems.</li>
					<li>For each problem, you are required to submit only your source file (C or C++).</li>
					<li>The name of your source file does not matter. Only the extension does.</li>
					<li>Each correct submission fetches you the number of points indicated in the problem.</li>
					<li>A submission is deemed correct if it compiles, and passes all system test cases.</li>
					<li>You may submit multiple times. It will not hurt your score. The last submission is the only one that counts.</li>
					<li>Ties will be resolved by ranking the person who submitted earlier higher.</li>
					<li>Any program that takes longer than 2 seconds to execute will be flagged 'Time Limit'</li>
					<li><strong>WARNING</strong> : You may not use any system calls in your programs.</li>
					<li><strong>WARNING</strong> : Do not use non-standard functions like getch(), strrev(), gets() etc.</li>
					<li><strong>WARNING</strong> : Any attempt to hack into the system will lead to an automatic disqualification.</li>
					<li><strong>WARNING</strong> : Adhere to the output format strictly! Even a single stray character not asked for will result in an incorrect submission.</li>
				</ul>	

				<h2>How to submit a solution</h2>
				
				<ul>
					<li>Upload your source file on the page of the corresponding problem.</li>
					<li>The file will be compiled, automatically tested by the system and the verdict will be displayed.</li> 
<li>This may take a while when the server is loaded, so please be patient.</li>
					
				</ul>

				<h2>What happens when you submit</h2>
				
				<ul>
					<li>Your file is compiled.</li>
					<li>The executable produced is run, with an input file being fed to its standard input (when you use scanf or cin, you are reading from the standard input).</li>
					<li>The output produced is saved.</li>
					<li>The output is compared with the expected output. If they match, the solution is accepted</li>
				</ul>

				<h2>Verdicts</h2>
				
				<ul>
					<li><strong>Accepted</strong> : Your code compiled correctly, passed all system tests and was awarded the points indicated in the problem.</li>
					<li><strong>Wrong Answer</strong> : Your code compiled correctly, but failed one or more system tests.</li>
					<li><strong>Time Limit</strong> : Your code took longer than 2 seconds to execute.</li>
					<li><strong>Compile Error</strong> : Your code did not compile correctly, or had system calls in it.</li>
					<li><strong>Invalid File</strong> : The file you uploaded was not a valid C or C++ source file.</li>
				</ul>

				<h2>About the interface</h2>
				
				<ul>
					<li>All tables and charts are auto-refreshed, so you never have to refresh the page.</li>
					<li>The Dashboard displays announcements and various statistics.</li>
					<li>The Submissions page allows you to see which users have submitted solutions, and what the verdict was.</li>
					<li>The Scoreboard displays the current standings.</li>
					<li>The Chat allows you to ask questions, and have them answered in real time.</li>
				</ul>

				<p class="post-footer align-right"></p>
				
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
