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

<?php
	//Make sure that a variable $problemid is defined before this in the calling file

	$problemid = htmlentities($problemid);

	$good = false;
	for($i=1 ; $i<=count($points) ; $i++)
		if($problemid == $i)
			$good = true;
	if($good == false)
		$problemid = 1;

	$cn = mysql_connect('localhost', $DBUSER, $DBPASS);
	mysql_select_db($DBNAME, $cn);

	$status = 0;

	$query = "select problemid, status from submissions where userid=$userid and problemid=$problemid order by time desc";
	$result = mysql_query($query);
	$result = mysql_fetch_array($result);

	if(isset($result['status']))
		$status = $result['status'];
	else
		$status = -1;
	
	$status++;
	
	$statString = array('-', 'Accepted', 'Compile Error', 'Wrong Answer', 'Time Limit', 'Invalid File');

	mysql_close($cn);

	print "<table style='margin-top: 20px; border: 0;'><tr>";

	if($statString[$status] != 'Accepted') 
	{
		print "<td id='upload$problemid' class='submitform'>";

		print "<form id='upload$problemid' class='uploadform' action='processfile.php' method='post' enctype='multipart/form-data'>
		<input type='file' name='$problemid'/><input type='submit' value='Submit Solution'/>
		<input type='hidden' name='redirectFile' value='$redirectFile'/></form>"; 

		print "</td>";
	}

	print "<td id='status$problemid' class=";
	switch($status)
	{
		case 0: print '"none"'; break;
		case 1: print '"accepted"'; break;
		case 2: print '"compile"'; break;
		case 3: print '"wrong"'; break;
		case 4: print '"time"'; break;
		case 5: print '"invalid"'; break;
	}
	print '>';
	print "<strong>$statString[$status]</strong></td>";

	print "</tr></table>";
?>
