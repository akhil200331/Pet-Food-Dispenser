<?php
$conn=new mysqli("localhost:3307","root","Asdfg#143","ecs1002");
if($conn->connect_error){
  die("Failed to connect ".$conn->connect_error);
}
$sqlcount = "select * from food_dispense_table where ID=1";
$result_to_sql_count = $conn->query($sqlcount);
$valuetocount = mysqli_fetch_assoc($result_to_sql_count);
// echo "Count";
// echo $valuetocount['Count'];
if ($valuetocount['Count']==0){
  $st1 = "update food_dispense_table set STATUS='UNACTIVATED' where ID=1";
  $result_to_sql_count = $conn->query($st1);
  // echo "result=";
  // echo $result_to_sql_count;
}
$sqlstoget="select * from food_dispense_table where STATUS='ACTIVATED'";
$resulttoget=$conn->query($sqlstoget);
//$rowtoget=mysqli_fetch_assoc($resulttoget);
$timesArray = array();
if ($resulttoget->num_rows > 0) {
    // echo "<h2>List of Times:</h2>";
    // echo "<ul>";
    // Output data of each row
    while ($rowtoget = $resulttoget->fetch_assoc()) {
        // Assuming 'Time' is the column name in your table
        $time = $rowtoget['Time'];
        // echo "<li>$time</li>";
    $timesArray[] = $time;
    }
    // echo "</ul>";
} else {
    // echo "No results found.";
}

//time zone set for INDIA
date_default_timezone_set('Asia/Kolkata');
//getting hour converting it into string
$hh = strval(date('H'));
//getting Minute converting it into string
$mm = strval(date('i'));
//manipulating time HH:MM in 24-hour format as same format time stored in database
$time = $hh . ":" . $mm;
//echo $time;
$status = 9;
if (in_array($time, $timesArray)) {
    // echo "present";
  $status = 1;
  $st2 = "update food_dispense_table set Count='". $valuetocount['Count']-1 ."' where ID=1";
  $result_update_to_sql_count = $conn->query($st2);
  // echo "result=";
  // echo $result_update_to_sql_count;
}
echo $status;
?>