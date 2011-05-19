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

	$username = htmlentities($_GET['username']);
	$problemid = htmlentities($_GET['problemid']);
	$mode = htmlentities($_GET['mode']);

	$path = "../$CODEDIR/$username/$problemid/";
	$dir = dir($path) or print "Empty directory";

	if($mode == 'getdir')
	{
		while(($entry = $dir->read()) != false)
		{
			list($filename, $ext) = explode(".", $entry);

			if($ext=="cpp" || $ext=="c" || $ext=="java" || $ext=="py" || $ext=="cs")
				print "<option value='$entry'> $entry </option>";
			else if($entry == "op")
				print "<option value='$entry'> Output </option>";
		}
	}
	else
	{
		$filerequested = htmlentities($_GET['filename']);

		$filePresent = false;

		while(($entry = $dir->read()) != false)
		{
			if($entry == $filerequested)
			{
				$f = fopen($path.$entry, "r");

				print "Username: <strong>$username</strong> | Problem: <strong>$problemid</strong> | Filename: <strong>$entry</strong> <br/><br/>";

				while(!feof($f))
					print htmlentities(fgets($f));
				fclose($f);

				$filePresent = true;
				break;
			}
		}

		if($filePresent == false)
			print "File not available";
	}
?>				
