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

	$cn = mysql_connect('localhost', $DBUSER, $DBPASS);
	mysql_select_db($DBNAME, $cn);

	$query = "select * from scores";
	$result = mysql_query($query);

	print '<ul class="sidemenu">';
	$i = 0;
	while(($rows = mysql_fetch_array($result)) && $i<5)
	{
		//Print only normal users (not admins)
		if($rows[rank] == 0)
		{
			print "<li style='position: relative'><span>$rows[username]</span><span style='position: absolute; right: 0px'>$rows[score]</span></li>";
			$i++;
		}
	}
	if($i == 0) print "<li></li>";
	print "</ul>";

	mysql_close($cn);
?>
