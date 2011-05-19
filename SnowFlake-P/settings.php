<?php

/*
* @copyright (c) 2008 Nicolo John Davis
* @license http://opensource.org/licenses/gpl-license.php GNU Public License
*/

	//The user name of your database
	$DBUSER = '';
	//The password of your database
	$DBPASS = '';
	//The name of the database
	$DBNAME = 'onj';

	//The point values of the problems
	//Set it to the values you wish to use
	//The number of elements in this array determines the number of problems
	$points = array(75,100,50,50,150,150,100);
	
	$time_limit = array(5,1,1,1,5,2,4);

	//Start time of the contest in the format 'YYYY-MM-DD HH:MM:SS'
	$startTime = date_create('2010-09-24 18:30:25');               //Capital starttime

	//End time of the contest in the format 'YYYY-MM-DD HH:MM:SS'
	$endTime = date_create('2011-09-24 23:00:25');                   //Capital endtime

	//Interval between refreshes of the leaderboard (milliseconds)
	$getLeaderInterval = 10000;

	//Interval between refreshes of the chat room (milliseconds)
	$getChatInterval = 1000;

	//This is used to disable PHP error messages
	ini_set('display_errors', false);

	//You can use the variable $running to determine if the contest is running or not
	$time = date_create();
	$running = false;
	if($time >= $startTime && $time <= $endTime)
		$running = true;

	//The following variables hold values of the code and problem directories. These directories are renamed with random strings for security purposes.
	$CODEDIR = 'code';
	$PROBLEMDIR = 'problems';
?>
