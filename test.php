<?php 
$hostname = "localhost"; 
$username = "root"; 
$password = ""; 
$database = "mfrc522"; 

$conn = mysqli_connect($hostname, $username, $password, $database);

if (!$conn) { 
	die("Connection failed: " . mysqli_connect_error()); 
} else{
	echo "Database connection is OK<br>"; 
}

if(isset($_POST["idcard"]) && isset($_POST["akses"])) {

	$t = $_POST["idcard"];
	$h = $_POST["akses"];

	$sql = "INSERT INTO rfid (idcard, akses) VALUES ('".$t."', '".$h."')"; 

	if (mysqli_query($conn, $sql)) { 
		echo "New record created successfully"; 
	} else { 
		echo "Error: " . $sql . "<br>" . mysqli_error($conn); 
	}
}

?>