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

	$query = "select * from users U join chat C where U.id = C.userid order by C.id";

	$result = mysql_query($query);

	$already = 0;
	if(isset($_GET['already']))
		$already = $_GET['already'];

	$i = 0;
	$records = mysql_num_rows($result);
	while($row = mysql_fetch_array($result))
	{
		if($i >= $already)
		{
			print '<span';
			if($row[rank] == 1) print ' id="admin"';
			else print ' id="name"';
			print '>';
			print $row[username];
			print '</span> : ';
			print $row[msg];
			print '<br/>';
		}

		$i++;
	}

	mysql_close($cn);
?>
