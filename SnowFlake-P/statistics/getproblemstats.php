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
	
	$query = 'select problemid, status from submissions';
	$result = mysql_query($query);

	for($i=1 ; $i<=count($points) ; $i++)
	{
		$cor[$i] = 0;
		$tot[$i] = 0;
	}

	while($row = mysql_fetch_array($result))
	{
		if($row['status'] == 0)
			$cor[ $row['problemid'] ]++;
		$tot[ $row['problemid'] ]++;
	}

	print '<table style="margin-top: 10px;">';
	print '<tr><th>Problem</th><th>Correct</th><th>Total</th></tr>';
	$class = 'row-a';
	for($i=1 ; $i<=count($points) ; $i++)
	{
		print "<tr class='$class'><td><strong>$i</strong></td><td>$cor[$i]</td><td>$tot[$i]</td></tr>";

		if($class == "row-a") $class = "row-b";
		else $class = "row-a";
	}
	print '</table>';

	mysql_close($cn);
?>
