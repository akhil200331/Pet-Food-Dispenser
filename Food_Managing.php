<?php
$conn=new mysqli("localhost:3307","root","Asdfg#143","ecs1002");
if($conn->connect_error){
  die("Failed to connect ".$conn->connect_error);
}?>
<!DOCTYPE html>
<html lang="en">
<head>
  <style>
    form{
      margin: 10em 0 0 34em;
      height: 180px;
      width: 400px;
      background-color: skyblue;
    }
    label{
      font-size: large;
      font-weight: bolder;
    }
    label,#time{
      margin: 20px;
    }
    .sub{
margin-left: 150px;
border: none;
border-radius: 5px;
height: 30px;
width: 70px;
background-color: red;
color: white;
    }
    .sub:hover{
      background-color: green;
    }
    h2{
      margin-left: 5em;
    }
  </style>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Document</title>
</head>
<body>
    <form method="post" action="">
      <h2>Food Time:</h2>
        <label for="time">Time:</label>
        <input type="time" id="time" name="timee" pattern="(?:[01]\d|2[0-3]):(?:[0-5]\d)" required><br><br>
        <input type="submit" class="sub" name="submit" value="Add">
    </form>
    <a href="Mainpage.php">Click Here to go MainPage</a>
</body>
</html>
<?php
$time_adding_through_form;
if ($_SERVER["REQUEST_METHOD"] == "POST") {
    $time_adding_through_form = $_POST['timee'];
  echo $time_adding_through_form;
  $innu = 1;
$sqlstoget="select * from food_dispense_table where ID='" . $innu . "'";
$resulttoget=$conn->query($sqlstoget);
$timesArray = array();
$count=0;
if ($resulttoget->num_rows > 0) {
    echo "<h2>List of Times:</h2>";
    echo "<ul>";
    // Output data of each row
    while ($rowtoget = $resulttoget->fetch_assoc()) {
        // Assuming 'Time' is the column name in your table
        $time = $rowtoget['Time'];
        $count=$rowtoget['Count'];
        echo "<li>$time $count</li>";
    $timesArray[] = $time;
    }
    echo "</ul>";
} else {
    echo "No results found.";
}
//check it time present
if (in_array($time_adding_through_form, $timesArray)) {
    echo "present so Not adding check status for the medicine";
}
else{
    $i = 1;
    $q = "insert into food_dispense_table(ID,Time,Status,Count,NAME) values('" . $i . "','" . $time_adding_through_form . "','UNACTIVATED','" . $count . "','VIT-AP')";
    $res = $conn->query($q);
    echo $res;
    if ($res===TRUE){
      echo "Inserted Succesfully";
    }
    else{
      echo "Error";
    }
}
}

?>