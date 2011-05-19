<?php

/*
* @copyright (c) 2008 Nicolo John Davis
* @license http://opensource.org/licenses/gpl-license.php GNU Public License
*/

	session_start();
	if(!isset($_SESSION['isloggedin']))
	{
		echo "<meta http-equiv='Refresh' content='0; URL=../login.php' />";
		exit(0);
	}
	else
	{
		$username = $_SESSION['username'];
		$userid = $_SESSION['userid'];
	}

	include('../settings.php');
?>

<?php
	$cn = mysql_connect('localhost', $DBUSER, $DBPASS);
	mysql_select_db($DBNAME, $cn);
	
	$query = 'select * from scores LIMIT 0,1';
	$result = mysql_query($query);

	$row = mysql_fetch_array($result);

	$leader = $row[username];
	$score = $row[score];

	if($score > 0)
	{
		if($time > $endTime)
		{
			print "<h2>Winner</h2>";
			print "<h1>$leader</h1>";
		}
	}

	mysql_close($cn);
?>
