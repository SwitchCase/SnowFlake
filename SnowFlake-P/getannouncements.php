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

	$cn = mysql_connect('localhost', $DBUSER , $DBPASS);
	mysql_select_db($DBNAME, $cn);

	$result = mysql_query("select * from announcements order by time asc");

	if(mysql_num_rows($result) >= 1)
	{
		print '<h2>Announcements</h2>';

		print '<code>';
		while($row = mysql_fetch_array($result))
		{
			$t = strftime('%H:%M:%S',$row[time]);
			print "<strong>($t) </strong>$row[msg]<br/>";
		}
		print '</code>';
	}

	mysql_close($cn);

?>				
