<!--
* @copyright (c) 2008 Nicolo John Davis
* @license http://opensource.org/licenses/gpl-license.php GNU Public License
-->

<script type="text/javascript">
<!--

<?php
	echo 'var currentTime = new Date("'. date_format(date_create(), "F d, Y H:i:s") . '");';	
	echo 'var startTime = new Date("'. date_format($startTime, "F d, Y H:i:s") . '");';	
	echo 'var endTime = new Date("'. date_format($endTime, "F d, Y H:i:s") . '");';	
?>

var getLeaderInterval = <?php echo $getLeaderInterval; ?>;
var getChatInterval = <?php echo $getChatInterval; ?>;

var diff1 = startTime - currentTime;
var diff2 = endTime - currentTime;
var diff = 0;

function getLeaders()
{
	$.get("getleaders.php", function(data){
	  $("#leaders").html(data);
	  });
}

function getDetails()
{
	$.get("getdetails.php", function(data){
	  $("#details").html(data);
	  });
}

function getScores()
{
	$.get("getscores.php", function(data){
	  $("#scores").html(data);
	  });
}

function getSubmissions()
{
	$.get("getsubmissions.php", function(data){
	  $("#submissions").html(data);
	  });
}

function getAnnouncements()
{
	$.get("getannouncements.php", function(data){
	  $("#announcements").html(data);
	  });
}

function getProblemStats()
{
	$.get("statistics/getproblemstats.php", function(data){
	  $("#problemstats").html(data);
	  });
}

function getLeader()
{
	$.get("statistics/getleader.php", function(data){
	  $("#leader").html(data);
	  });
}

function dispTime() 
{
	if(diff1>0)
	{
		$("#timeheading").text('Contest starts in');			
		diff = diff1;
	}
	else if(diff2>0)
	{
		$("#timeheading").text('Contest ends in');			
		diff = diff2;
	}
	else
	{
		$("#timeheading").text('Contest over');			
		diff = 0;
	}

	diff = Math.floor(diff/1000);

	var d = Math.floor(diff/(3600*24));
	diff = diff - d * 3600 *24;
	var h = Math.floor(diff/3600);
	var m = Math.floor((diff/60)%60);
	var s = Math.floor(diff%60);

	var hh = h;
	var mm = m;
	var ss = s;
	if(h<10) hh = '0' + h;
	if(m<10) mm = '0' + m;
	if(s<10) ss = '0' + s;

	var str = "<strong>"+hh+":"+mm+":"+ss+"</strong>";

	if(d > 1)
		str = "<strong>" + d + " days</strong>";
	else if(d == 1)
		str = "<strong>" + d + " day</strong>";

	$("#time").html(str);

	if(diff1 > 0)
	{
		diff1 = diff1-1000;
		if(diff1 <= 0)
		{
			alert('Contest has started');
			window.location.reload();
		}
	}

	if(diff2 > 0)
	{
		diff2 = diff2-1000;
		if(diff2 <= 0)
		{
			alert('Contest has ended');
			setTimeout("reloadPage()", 2000);
		}
	}
}

function reloadPage() {
	window.location.reload();
}

function messagebox(text)
{
	$(".messagebox").text(text);
	$(".messagebox").hide();
	$(".messagebox").slideDown("slow").oneTime("5s", function() { $(this).slideUp("fast") });
	$(".messagebox").click( function() { $(this).slideUp("fast"); } );
}

-->
</script>
