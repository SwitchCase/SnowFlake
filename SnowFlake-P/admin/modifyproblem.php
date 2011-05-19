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

		if($_SESSION['admin'] != true)
		{
			print "You need to be the administrator to access this file";
			exit(0);
		}
	}

	include('../settings.php');

	$problemid = htmlentities($_REQUEST['problemid']);
	$mode = htmlentities($_REQUEST['mode']);

	$file = "../$PROBLEMDIR/$problemid/statement";

	if($mode == 'get')
	{
		readfile($file);
	}
	else if($mode == 'put')
	{
		$statement = $_REQUEST['statement'];
		
		$f = fopen($file, "w");
		fwrite($f, $statement);
		fclose($f);

		readfile($file);
	}
?>				
