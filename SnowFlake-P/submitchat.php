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
	
	$msg = $_POST['message'];
	
	$cn = mysql_connect('localhost', $DBUSER, $DBPASS);
	mysql_select_db($DBNAME, $cn);

	$t = time();
	$query = "insert into chat(userid, time, msg) values($userid, $t, '$msg')";
	$query = htmlentities($query);

	mysql_query($query);
	mysql_close($cn);
?>
