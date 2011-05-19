<!--
* @copyright (c) 2008 Nicolo John Davis
* @license http://opensource.org/licenses/gpl-license.php GNU Public License
-->

<h3 id="timeheading"></h3>
<ul class="sidemenu">
	<li id="time"></li>
</ul>

<?php 
if(isset($_SESSION['isloggedin'])) 
{
	print <<<EOHTML

	<h3>Details</h3>
	<span id="details"> </span>

	<h3>Leaderboard</h3>
	<span id="leaders"> </span>

EOHTML;
}

?>
