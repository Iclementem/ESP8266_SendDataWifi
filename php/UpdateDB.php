<?php
//Creates new record as per request
    //Connect to database
    $servername = "localhost";		//example = localhost or 192.168.0.0
    $username = "root";		//example = root
    $password = "root";	
    $dbname = "maquina_test2";

    // Create connection
    $conn = new mysqli($servername, $username, $password, $dbname);
    // Check connection
    if ($conn->connect_error) {
        die("Database Connection failed: " . $conn->connect_error);
    }

    if(!empty($_POST['ldrvalue']))
    {
		$ldrvalue = $_POST['ldrvalue'];
        $sql = "UPDATE vidrio SET total = '".$ldrvalue."' WHERE (MAC = '30:83:98:A2:EF:EB')"; 

		if ($conn->query($sql) === TRUE) {
		    echo "OK";
		} else {
		    echo "Error: " . $sql . "<br>" . $conn->error;
		}
	}
	$conn->close();
?>