<?php
$city="Eureka";
$country="US"; //Two digit country code
$url="http://api.openweathermap.org/data/2.5/weather?q=".$city.",".$country."&units=metric&cnt=7&lang=en";
$json=file_get_contents($url);
$data=json_decode($json,true);
$icon=$data['weather'][0]['icon'];
echo "<" . $icon . ">";
// Return icon to Arduino
?>