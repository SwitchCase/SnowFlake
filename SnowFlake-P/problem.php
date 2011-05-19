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
<link rel="stylesheet" href="images/Tabs.css" type="text/css" />

<title>Programming Contest</title>
	
<script type="text/javascript" src="jquery-1.3.1.js"></script>
<script type="text/javascript" src="jquery.form.js"></script>
<script type="text/javascript" src="jquery.timers-1.1.2.js"></script>
<?php include('timer.php'); ?>
<script type="text/javascript">
<!--

function onSucess(data)
{
	if(data.verdict == 0)
	{
		$('#status' + data.problemid).attr('class', 'accepted');
		$('#upload' + data.problemid).hide();
		$('#status' + data.problemid).html('<strong>Accepted</strong>');
		$('#status' + data.problemid).hide();
		$('#status' + data.problemid).fadeIn('slow');

		messagebox('Accepted');

		getDetails();
		getLeaders();
	}
	else if(data.verdict == 1)
	{
		$('#status' + data.problemid).attr('class', 'compile');
		$('#status' + data.problemid).html('<strong>Compile Error</strong>');
		$('#status' + data.problemid).hide();
		$('#status' + data.problemid).fadeIn('slow');

		messagebox('Compile Error');
	}
	else if(data.verdict == 2)
	{
		$('#status' + data.problemid).attr('class', 'wrong');
		$('#status' + data.problemid).html('<strong>Wrong Answer</strong>');
		$('#status' + data.problemid).hide();
		$('#status' + data.problemid).fadeIn('slow');

		messagebox('Wrong Answer');
	}
	else if(data.verdict == 3)
	{
		$('#status' + data.problemid).attr('class', 'time');
		$('#status' + data.problemid).html('<strong>Time Limit</strong>');
		$('#status' + data.problemid).hide();
		$('#status' + data.problemid).fadeIn('slow');

		messagebox('Time Limit Exceeded');
	}
	else if(data.verdict == 5)
	{
		$('#status' + data.problemid).attr('class', 'wrong');
		$('#status' + data.problemid).html('<strong>Run Time Error</strong>');
		$('#status' + data.problemid).hide();
		$('#status' + data.problemid).fadeIn('slow');

		messagebox('Run Time Error');
	}
	else if(data.verdict == 6)
	{
		$('#status' + data.problemid).attr('class', 'wrong');
		$('#status' + data.problemid).html('<strong>Presentation Error</strong>');
		$('#status' + data.problemid).hide();
		$('#status' + data.problemid).fadeIn('slow');

		messagebox('Presentation Error');
	}
}

function onEdit()
{
	$('#editpanel').html( '<button id="save">Save</button> <button id="cancel">Cancel</button>' );
	$('#save').click(onSave);
	$('#cancel').click(onCancel);

	//This will return tabn where n is the problem number
	var problem = $('body').attr('id'); 
	//We extract the number from the above
	problem = problem[3];

	$.get('admin/modifyproblem.php', {problemid: problem, mode: 'get'}, function(data) {
			$('#statementpanel').html( '<textarea id="statement" style="width: 100%"></textarea>' );
			$('#statement').text(data);
		});
}

function onCancel()
{
	$('#editpanel').html( '<button id="edit">Edit</button>' );
	$('#edit').click(onEdit);

	//This will return tabn where n is the problem number
	var problem = $('body').attr('id'); 
	//We extract the number from the above
	problem = problem[3];

	$.get('admin/modifyproblem.php', {problemid: problem, mode: 'get'}, function(data) {
			$('#statementpanel').html( '<code class="statement"></code>' );
			$('code.statement').html(data);
		});
}

function onSave()
{
	$('#editpanel').html( '<button id="edit">Edit</button>' );
	$('#edit').click(onEdit);

	var st = $('#statement').val();

	//This will return tabn where n is the problem number
	var problem = $('body').attr('id'); 
	//We extract the number from the above
	problem = problem[3];

	$.post('admin/modifyproblem.php', {problemid: problem, mode: 'put', statement: st}, function(data) {
			$('#statementpanel').html( '<code class="statement"></code>' );
			$('code.statement').html(data);
		});
}

$(document).ready(function() { 
		dispTime();
		getLeaders();
		getDetails();
		setInterval("dispTime()", 1000);  
		setInterval("getLeaders()", getLeaderInterval);  
		setInterval("getDetails()", getLeaderInterval);  

		$('.uploadform').ajaxForm({
				dataType: 'json',
				success: onSucess
			});

		$('#edit').click(onEdit);
	} );

-->
</script>

</head>

<?php
	$problemid = $_GET['id'];
	$problemid = htmlentities($problemid);

	$good = false;
	for($i=1 ; $i<=count($points) ; $i++)
		if($problemid == $i)
			$good = true;
	if($good == false)
		$problemid = 1;
	
	print '<body class="menu2" id="tab'; print $problemid; print '">';
?>

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
				
				<?php
					
					$time = date_create();

					if($time < $startTime)
						echo '<h2>The contest has not yet begun</h2>';
					else
					{
						print '<ul id="tabnav">';
						for($i=1 ; $i<=count($points) ; $i++)
							print "<li class='tab$i'><a href='problem.php?id=$i'>Problem $i</a></li>\n";
						print '</ul>';

						$value = $points[$problemid-1];

						print "<h2>Problem $problemid</h2>";

						if($running)
						{
							include('uploadform.php');
						}

						print "<p id='statementpanel'><code class='statement'>";
						
						readfile("$PROBLEMDIR/$problemid/statement") or print "Problem is not available at this time";	
						
						print "</code></p>";

						if($_SESSION['admin'])
							print "<p id='editpanel' style='float: right'> <button id='edit'>Edit</button> </p>";
					}

				?> 
				
			</div>
			
			<div id="sidebar">
				
				<?php 
				
				if($time >= $startTime)
				{
					 echo <<<EO
					 <h3>Point Value</h3>				
					 <ul class="sidemenu">
					 <li><strong>$value</strong></li>			 
					 </ul>
EO;

					 if($problemid == 1)
					 {
						/*echo <<<EO
					 <h3>Hints</h3>				
					 <ul class="sidemenu">
					 <li>Be careful when you read the input.</li>			 
					 </ul>
EO;*/
					 }
					 else if($problemid == 2)
					 {
					 }
					 else if($problemid == 3)
					 {
					 }
					 else if($problemid == 4)
					 {
					 }
					 else if($problemid == 5)
					 {
					 }
				}
					echo <<<EOHTML
					</li>
					</ul>
EOHTML;

				include('sidebar.php');
				?>

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
