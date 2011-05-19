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

	print <<<EOHTML
	<ul class="sidemenu">				
		<li>
		<div style='position: relative'><span>$username</span>
EOHTML;

		$cn = mysql_connect('localhost', $DBUSER, $DBPASS);
		mysql_select_db($DBNAME, $cn);

		$query = "select score from users where id = $userid";
		$result = mysql_query($query);
		if($result)
		{
			$result = mysql_fetch_array($result);
			$score = $result['score'];						
			print "<span style='position: absolute; right: 0px'>$score</span></div>";
		} 
		mysql_close($cn);

	print <<<EOHTML
		</li>						
	</ul>	
EOHTML;

?>
