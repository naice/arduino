#define JWifiSetup_HTML_FORM_CSS \
"html, body {" \
    "font-family: Verdana,sans-serif;" \
    "font-size: 20pt;" \
    "line-height: 1.5;" \
"}" \
"h2 {" \
    "display: block;" \
    "font-size: 30pt;" \
    "margin-block-start: 0.83em;" \
    "margin-block-end: 0.83em;" \
    "margin-inline-start: 0px;" \
    "margin-inline-end: 0px;" \
    "font-weight: bold;" \
"}" \
"p {" \
    "margin-top: 1.2em;" \
    "margin-bottom: 1.2em;" \
    "font-size: 20pt;" \
    "display: block;" \
    "margin-block-start: 1em;" \
    "margin-block-end: 1em;" \
    "margin-inline-start: 0px;" \
    "margin-inline-end: 0px;" \
"}" \
"input[type=text], select, textarea{" \
  "width: 100%;" \
  "padding: 12px;" \
  "font-size: 20pt;" \
  "border: 1px solid #ccc;" \
  "border-radius: 4px;" \
  "box-sizing: border-box;" \
  "resize: vertical;" \
"}" \
"label {" \
  "padding: 12px 12px 12px 0;" \
  "display: inline-block;" \
"}" \
"input[type=submit] {" \
  "font-size: 20pt;" \
  "-webkit-appearance: none;" \
  "background-color: #4CAF50;" \
  "color: white;" \
  "padding: 12px 20px;" \
  "border: none;" \
  "border-radius: 4px;" \
  "cursor: pointer;" \
  "float: right;" \
"}" \
".container_inv {" \
  "padding: 20px;" \
"}" \
".container {" \
  "border-radius: 5px;" \
  "background-color: #f2f2f2;" \
  "padding: 20px;" \
"}" \
".col-25 {" \
  "float: left;" \
  "width: 25%;" \
  "margin-top: 6px;" \
"}" \
".col-75 {" \
  "float: left;" \
  "width: 75%;" \
  "margin-top: 6px;" \
"}" \
".row:after {" \
  "content: \"\";" \
  "display: table;" \
  "clear: both;" \
"}" \
"@media screen and (max-width: 600px) {" \
  ".col-25, .col-75, input[type=submit] {" \
    "width: 100%;" \
    "margin-top: 0;" \
  "}" \
"}" 

#define JWifiSetup_HTML_FORM  \
"<!DOCTYPE html>" \
"<html>" \
"<head>" \
"<title>Wifi Setup</title>" \
"<style type=\"text/css\">" \
JWifiSetup_HTML_FORM_CSS  \ 
"</style>" \
"</head>" \
"<body>" \
"<div class=\"container_inv\">" \
  "<h2>Wifi Setup</h2>" \
  "<p> Please enter your Wifi credentials. </p>" \
"</div>" \
"<div class=\"container\">" \
  "<form action=\"/submit_wifi_data\">" \
    "<div class=\"row\">" \
      "<div class=\"col-25\">" \
        "<label for=\"ssid\">SSID</label>" \
      "</div>" \
      "<div class=\"col-75\">" \
        "<input type=\"text\" id=\"ssid\" name=\"ssid\" placeholder=\"SSID\">" \
      "</div>" \
    "</div>" \
    "<div class=\"row\">" \
      "<div class=\"col-25\">" \
        "<label for=\"password\">Password</label>" \
      "</div>" \
      "<div class=\"col-75\">" \
        "<input type=\"text\" id=\"password\" name=\"password\" placeholder=\"Password\">" \
      "</div>" \
    "</div>" \
    "<div class=\"row\">" \
      "<input type=\"submit\" value=\"Submit\">" \
    "</div>" \
  "</form>" \
"</div>" \
"</body>" \
"</html>" 

#define JWifiSetup_HTML_SUCCESS \
"<!DOCTYPE html>" \
"<html>" \
"<head>" \
"<title>Wifi Setup</title>" \
"<style type=\"text/css\">" \
JWifiSetup_HTML_FORM_CSS  \ 
"</style>" \
"</head>" \
"<body>" \
"<div class=\"container\">" \
  "<h2>Wifi Setup</h2>" \
  "<p> <strong>Success!</strong> </p>" \
"</div>" \
"</body>" \
"</html>" 