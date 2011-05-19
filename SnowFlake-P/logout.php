<?php

/*
* @copyright (c) 2008 Nicolo John Davis
* @license http://opensource.org/licenses/gpl-license.php GNU Public License
*/

	session_start(); 
	
	unset($_SESSION['username']);
	unset($_SESSION['password']);
	unset($_SESSION['userid']);
	unset($_SESSION['admin']);
	unset($_SESSION['isloggedin']);
	
	echo "<meta http-equiv='Refresh' content='0; URL=login.php'/>";
?>
