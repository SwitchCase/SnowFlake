<!--
* @copyright (c) 2008 Nicolo John Davis
* @license http://opensource.org/licenses/gpl-license.php GNU Public License
-->

<div id="menu">
	<ul>
		<?php if(!isset($_SESSION['isloggedin'])) print '<li id="menu1"><a href="login.php">Login</a></li>'; ?>
		<?php if(isset($_SESSION['isloggedin'])) print '<li id="menu1"><a href="index.php">Dashboard</a></li>'; ?>
		<?php if(isset($_SESSION['isloggedin'])) print '<li id="menu2"><a href="problem.php">Problems</a></li>'; ?>
		<?php if(isset($_SESSION['isloggedin'])) print '<li id="menu3"><a href="submissions.php">Submissions</a></li>'; ?>
		<?php if(isset($_SESSION['isloggedin'])) print '<li id="menu4"><a href="scores.php">Scoreboard</a></li>'; ?>
		<li id="menu5"><a href="faq.php">FAQ</a></li>	
		<?php if(isset($_SESSION['isloggedin'])) print '<li id="menu6"><a href="chat.php">Chat</a></li>'; ?>
		<?php if(isset($_SESSION['admin'])) print '<li id="menu7"><a href="admin.php">Admin</a></li>'; ?>
		<?php if(isset($_SESSION['isloggedin'])) print '<li id="menu8"><a href="logout.php">Logout</a></li>'; ?>
	</ul>
</div>					
