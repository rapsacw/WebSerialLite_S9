#ifndef _webserial_webpage_h
#define _webserial_webpage_h
char WEBSERIAL_HTML[] = R"=====(
<!doctype html>
<html>
<head>
<style>
table, th {
  border: 1px solid #ddd;
  border-radius: 10px;
}

th {
	background-color: #ddd;
}

#aProgress {
  width: 110px;
  background-color: #ddd;
}

#aBar {
  width: 110px;
  height: 8px;
  background-color: #04AA6D;
  text-align: right;
  line-height: 30px;
  color: black;
}
</style>
<meta charset=utf-8>
<meta content="IE=edge" http-equiv=X-UA-Compatible>
<title id="Title">aSiNine ESP Miner</title>
<meta content="width=device-width,initial-scale=1" name=viewport>
<body>
<div class="section main text-center">
<h2><div id="Name" style="display: inline">Log</div></h2>

<div class="shadow grid gap-2 pannel">
<table id="stattable">
<tr>
  <th colspan="6">Hashrate (GH/s)</th>
</tr>
<tr>
  <td style="width:16.66%">1 week</td>
  <td style="width:16.66%">1 day</td>
  <td style="width:16.66%">1 hour</td>
  <td style="width:16.66%">5 minutes</td>
  <td style="width:16.66%">1 minute</td>
  <td><div >5s</div><div id="aProgress"><div id="aBar""></div></div></div></td>
</tr>
<tr>
  <td id = "Hash0">0</td>
  <td id = "Hash1">0</td>
  <td id = "Hash2">0</td>
  <td id = "Hash3">0</td>
  <td id = "Hash4">0</td>
  <td id = "Hash5">0</td>
</tr>
<tr>
  <th id = "Pool0" colspan="6">Pool</th>
</tr>
<tr>
  <td></td>
  <td>#connects</td>
  <td>difficulty</td>
  <td>Accepted</td>
  <td>Rejected</td>
  <td>best share</td>
</tr>
<tr>
  <td></td>
  <td id = "Pool1">1</td>
  <td id = "Pool2">1000</td>
  <td id = "Pool3">0</td>
  <td id = "Pool4">0</td>
  <td id = "Pool5">0</td>
</tr>
<tr>
  <th colspan="6">Asic settings</th>
</tr>
<tr>
  <td colspan="2">setting file</td>
  <td>frequency</td>
  <td>Vcore set</td>
  <td>Vcore actual</td>
  <td>job interval</td>
</tr>
<tr>
  <td id = "Asic0" colspan="2">default.cfg</td>
  <td id = "Asic1">100</td>
  <td id = "Asic2">1.000</td>
  <td id = "Asic3">1.000</td>
  <td id = "Asic4">5</td>
</tr>

</table>
</div>
<br>
<div class="shadow grid gap-2 pannel">
  <div id=control-button>
  <button class="rounded shadow" onclick=terminalClean()><svg aria-hidden=true data-icon=delete fill=currentColor height=1em viewBox="64 64 896 896" width=1em><path d="M864 256H736v-80c0-35.3-28.7-64-64-64H352c-35.3 0-64 28.7-64 64v80H160c-17.7 0-32 14.3-32 32v32c0 4.4 3.6 8 8 8h60.4l24.7 523c1.6 34.1 29.8 61 63.9 61h454c34.2 0 62.3-26.8 63.9-61l24.7-523H888c4.4 0 8-3.6 8-8v-32c0-17.7-14.3-32-32-32zm-200 0H360v-72h304v72z"></path></svg></button>
  <button class="rounded shadow" onclick="enableFlowLock=!enableFlowLock"><svg aria-hidden=true data-icon=lock fill=currentColor height=1em viewBox="64 64 896 896" width=1em><path d="M832 464h-68V240c0-70.7-57.3-128-128-128H388c-70.7 0-128 57.3-128 128v224h-68c-17.7 0-32 14.3-32 32v384c0 17.7 14.3 32 32 32h640c17.7 0 32-14.3 32-32V496c0-17.7-14.3-32-32-32zM332 240c0-30.9 25.1-56 56-56h248c30.9 0 56 25.1 56 56v224H332V240zm460 600H232V536h560v304zM484 701v53c0 4.4 3.6 8 8 8h40c4.4 0 8-3.6 8-8v-53a48.01 48.01 0 10-56 0z"></path></svg></button>
  <button class="rounded shadow" onclick="enableTimestamp=!enableTimestamp"><svg aria-hidden=true data-icon=clock-circle fill=currentColor height=1em viewBox="64 64 896 896" width=1em><path d="M512 64C264.6 64 64 264.6 64 512s200.6 448 448 448 448-200.6 448-448S759.4 64 512 64zm0 820c-205.4 0-372-166.6-372-372s166.6-372 372-372 372 166.6 372 372-166.6 372-372 372z"></path><path d="M686.7 638.6L544.1 535.5V288c0-4.4-3.6-8-8-8H488c-4.4 0-8 3.6-8 8v275.4c0 2.6 1.2 5 3.3 6.5l165.4 120.6c3.6 2.6 8.6 1.8 11.2-1.7l28.6-39c2.6-3.7 1.8-8.7-1.8-11.2z"></path></svg></button>
  </div>
  <textarea class="rounded w-full" cols=30 disabled=disabled id=log rows=10 title=log></textarea>
  <div class="gap-2 grid flex w-full" id=terminal><input class="rounded grow" id=command-text name=cmd><button class="rounded shadow grid justify-items-end" id=command-button>SEND</button>
  </div>
</div>
</div>
</body>
<script>
let websocket,gateway=`ws://${window.location.host+window.location.pathname}ws`,textArea=document.getElementById("log"),enableFlowLock=!1,enableTimestamp=!1;
function initWebPage()
{
  document.getElementById("command-button").disabled=!0,
  document.getElementById("command-text").disabled=!0,
  terminalWrite("[WebSerial] Connecting...\n"),
  initWebSocket(),
  initButton(),
  trapEnterKeyPress()
}
function initWebSocket()
{
  console.log("Trying to open a WebSocket connection..."),
  websocket=new WebSocket(gateway),
  websocket.onopen=onOpen,
  websocket.onclose=onClose,
  websocket.onmessage=onMessage
}
function initButton()
{
  document.getElementById("command-button").addEventListener("click",sendCommand)
}
function trapEnterKeyPress()
{
  document.getElementById("command-text").addEventListener("keypress",enterPressed)
}
function enterPressed(e)
{
  "Enter"===e.key&&(e.preventDefault(),document.getElementById("command-button").click())
}
function onOpen(e)
{
  console.log("Connection opened"),
  terminalWrite("[WebSerial] Connected...\n"),
  document.getElementById("command-button").disabled=!1,
  document.getElementById("command-text").disabled=!1
}
function onClose(e)
{
  console.log("Connection closed"),
  setTimeout(initWebSocket,2e3)
}
function onMessage(e)
{
  console.log("Data Received:")
  console.log(e.data)
  if(e.data.charAt(0) != '!')
    terminalWrite(e.data)
  else if (e.data.charAt(1) == 'n')
	namewrite(e.data.substr(2))
  else if (e.data.charAt(1) == 'h')
	hashwrite(e.data.substr(2))
  else if (e.data.charAt(1) == 'p')
	poolwrite(e.data.substr(2))
  else if (e.data.charAt(1) == 'a')
	asicwrite(e.data.substr(2))
  else if (e.data.charAt(1) == 't')
	titlewrite(e.data.substr(2))

}

function terminalWrite(e)
{
  if(console.log(enableTimestamp),enableTimestamp)
  {
    e="["+(new Date).toLocaleTimeString()+"] "+e
  }
  textArea.value+=e,enableFlowLock||(textArea.scrollTop=textArea.scrollHeight)
}

function namewrite(e)
{
	document.getElementById("Name").innerHTML = e;
}

function titlewrite(e)
{
	document.getElementById("Title").innerHTML = e;
}

function hashwrite(e)
{
	move()
	clr = e.charAt(0)
	f = e.substr(1)
	hsh = f.split(" ")
	console.log(hsh)
	document.getElementById("Hash0").innerHTML = hsh[0];
	document.getElementById("Hash1").innerHTML = hsh[1];
	document.getElementById("Hash2").innerHTML = hsh[2];
	document.getElementById("Hash3").innerHTML = hsh[3];
	document.getElementById("Hash4").innerHTML = hsh[4];
	document.getElementById("Hash5").innerHTML = hsh[5];
	document.getElementById("Hash4").style.color = "green";
	if(clr != 'g')
	{
		if(clr == 'o') document.getElementById("Hash4").style.color = "orange";
		else document.getElementById("Hash4").style.color = "red";
	}
}

function poolwrite(e)
{
	pl = e.split(" ")
	console.log(pl)
	document.getElementById("Pool0").innerHTML = pl[0];
	document.getElementById("Pool1").innerHTML = pl[1];
	document.getElementById("Pool2").innerHTML = pl[2];
	document.getElementById("Pool3").innerHTML = pl[3];
	document.getElementById("Pool4").innerHTML = pl[4];
	document.getElementById("Pool5").innerHTML = pl[5];
}

function asicwrite(e)
{
	as = e.split(" ")
	console.log(as)
	document.getElementById("Asic0").innerHTML = as[0];
	document.getElementById("Asic1").innerHTML = as[1];
	document.getElementById("Asic2").innerHTML = as[2];
	document.getElementById("Asic3").innerHTML = as[3];
	document.getElementById("Asic4").innerHTML = as[4];
}

function terminalClean()
{
  textArea.value="",textArea.scrollTop=textArea.scrollHeight
}

function sendCommand()
{
  websocket.send(document.getElementById("command-text").value)
}

var i = 0;
var tid = 0;
function move()
{
  if (tid)
  {
      clearInterval(tid);
  }
  i = 1;
  var elem = document.getElementById("aBar");
  var width = 1;
  tid = setInterval(frame, 60);
  
  
  function frame()
  {
    if (width >= 100)
	{
      clearInterval(tid);
	  tid = 0;
      i = 0;
    }
	else
	{
      width++;
      elem.style.width = width + "%";
	  if(width<86)
	  {
        elem.style.backgroundColor = "lightgreen";
	  }
	  else if(width < 90)
	  {
        elem.style.backgroundColor = "orange";
	  }
	  else
	  {
        elem.style.backgroundColor = "red";
	  }
    }
  }
}

initWebPage()
</script>
<style>
div{display:block}a{margin:.4rem;text-decoration:none}*,::after,::before{-webkit-box-sizing:inherit;box-sizing:inherit}p{margin:0 0 1rem}body{overscroll-behavior:none;height:100%;width:100%;margin:0;padding:0;font-family:-apple-system,system-ui,BlinkMacSystemFont,"Segoe UI",Roboto,"Helvetica Neue",sans-serif}.text-center{text-align:center}.gray{color:#667189}.shadow{filter:drop-shadow(0 4px 3px rgb(0 0 0 / .07)) drop-shadow(0 2px 2px rgb(0 0 0 / .06))}.w-full{width:100%}.grid{display:grid}.gap-2{gap:.5rem}.flex{display:flex}.grow{flex-grow:1}.justify-items-end{justify-items:end}.rounded{border-radius:.5rem}.section{box-sizing:border-box;background-color:#f8f9fa}.main{display:flex;flex-direction:column;justify-content:center;align-items:center;height:100dvh}.main .pannel{position:relative;border:#fff;border-style:solid;border-width:.5rem;border-radius:1rem;background-color:#fff;max-width:45rem;width:calc(100% - 1rem);font-size:medium}.pannel button{cursor:pointer;padding:8px 10px 8px;font-size:medium;outline-style:none;border:0;color:#fff;background-color:#0067f4}.pannel button:disabled{background-color:#5a6169}.pannel #log{min-height:3.25rem;padding:.5rem;resize:vertical;overscroll-behavior:none}#control-button{position:absolute;top:.5rem;right:1.5rem}#control-button button{background-color:#5a6169}.alert span{user-select:none;background:#ffe14d;padding:2px 10px;display:block;color:#000}.footer{padding:1rem .5rem;background-color:#fff}.copyright{padding-bottom:1rem}.float-left{float:left}.float-right{float:right}</style>
</head>
</html>
)=====";
#endif
