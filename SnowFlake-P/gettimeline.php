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

	$s = mysql_query("select * from scores where rank=0");

	$numberOfLines = 5;

	for($i=0 ; $i<$numberOfLines && $i<mysql_num_rows($s) ; $i++)
	{
		$row = mysql_fetch_array($s);
		$pos[$i] = $row[username];
	}

	$result = mysql_query("select time, username, problemid, status from users, submissions where users.id = submissions.userid and status = 0 order by time asc");

	if($result)
	{
		$scores = array();
		$data = array();
		for($i=0 ; $i<count($pos) ; $i++)
		{
			array_push($scores,0);
			array_push($data,array('label'=>$pos[$i], 'data'=>array()));

			$diff = ((int)strtotime($startTime->format(DATE_ATOM))*1000);
			$tuple = array(0,0);	
			$tuple[0] = (int)$diff;
			array_push($data[$i]['data'], $tuple);
		}

		while($row = mysql_fetch_array($result))
		{
			$index = 0;
			while($index < count($pos))
			{
				if($pos[$index] == $row[username])
					break;
				$index++;
			}

			if($index < count($pos))
			{
				$tuple = array(0,0);	
				$diff = ((int)($row[time])*1000);
				$tuple[0] = (int)$diff;
				$scores[$index] += $points[ $row[problemid]-1 ];
				$tuple[1] = $scores[$index];

				array_push($data[$index]['data'], $tuple);
			}
		}
	}

	print json_encode($data);

	mysql_close($cn);
?>				
