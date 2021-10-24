const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <title>KELCIE</title>
  <link rel="stylesheet" href="https://cdn.jsdelivr.net/npm/bootstrap@4.6.0/dist/css/bootstrap.min.css" integrity="sha384-B0vP5xmATw1+K9KRQjQERJvTumQW0nPEzvF6L/Z6nronJ3oUOFUFpCjEUQouq2+l" crossorigin="anonymous">
  <!--<meta http-equiv="refresh" content="15">-->
   
  <script>
  %BUTTONPLACEHOLDER%     
  </script>
  <link rel="icon" href="data:,">
</head>
<body>
<div class = "container">
 <h1 class="display-3">
 Hi, I am Kelcie
 </h1>
 <hr class="mt-2 mb-3"/> 
<table class="table"><thead><tr><th scope="col">Variable</th><th scope="col">Read</th></tr></thead><tbody>
<tr><th scope="row"><script></script></th></tr>
<script>
for (i=0; i < kelcieData.length; i++) {
   document.write("<tr><th scope=\"row\">"+ kelcieData[i][0] + "</th><td>"+ kelcieData[i][1] + "</td></tr>");
}
</script>
 </tbody></table> 
 </div>

</body>
</html>
)rawliteral";
/*
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <title>KELCIE</title>
  <link rel="stylesheet" href="https://cdn.jsdelivr.net/npm/bootstrap@4.6.0/dist/css/bootstrap.min.css" integrity="sha384-B0vP5xmATw1+K9KRQjQERJvTumQW0nPEzvF6L/Z6nronJ3oUOFUFpCjEUQouq2+l" crossorigin="anonymous">
  <meta http-equiv="refresh" content="15">
  <link rel="icon" href="data:,">
</head>
<body>
<div class = "container">
 <h1 class="display-3">
 Hi, I am Kelcie
 </h1>
 <hr class="mt-2 mb-3"/>
 %BUTTONPLACEHOLDER% 
 </div>

</body>
</html>
)rawliteral";*/
///**************************************************************************************
///**************************************************************************************
///**************************************************************************************

const char token_setup_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html><head><title>KELCIE</title><link rel="stylesheet" href="https://cdn.jsdelivr.net/npm/bootstrap@4.6.0/dist/css/bootstrap.min.css" integrity="sha384-B0vP5xmATw1+K9KRQjQERJvTumQW0nPEzvF6L/Z6nronJ3oUOFUFpCjEUQouq2+l" crossorigin="anonymous"><link rel="icon" href="data:,"></head><body><div class = "container"> %TOKEN_VARIABLE%</div></body></html>
)rawliteral";
/*
const char token_setup_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <title>KELCIE</title>
  <link rel="stylesheet" href="https://cdn.jsdelivr.net/npm/bootstrap@4.6.0/dist/css/bootstrap.min.css" integrity="sha384-B0vP5xmATw1+K9KRQjQERJvTumQW0nPEzvF6L/Z6nronJ3oUOFUFpCjEUQouq2+l" crossorigin="anonymous">
  <link rel="icon" href="data:,">
</head>
<body>
<div class = "container">
 %TOKEN_VARIABLE% 
 </div>
</body>
</html>
)rawliteral";*/
