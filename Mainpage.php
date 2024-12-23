<?php
$conn=new mysqli("localhost:3307","root","Asdfg#143","ecs1002");
if($conn->connect_error){
  die("Failed to connect ".$conn->connect_error);
}
$innu = 1;//id
$cnt=0;
#Check Count variable and get a notification or an alert message in website
$sqlcount = "select * from food_dispense_table where ID=1";
$result_to_sql_count = $conn->query($sqlcount);
$valuetocount = mysqli_fetch_assoc($result_to_sql_count);
$cnt=$valuetocount['Count'];
$cnterr="";
if ($cnt===0){
  $cnterr = "Your device is empty, Please fill the food";
}
$value_for_button="fill";
if (isset($_POST['fillfood'])){
  $update_query_to_count="update food_dispense_table set Count=6 where ID=1";
  $result_query_to_count = $conn->query($update_query_to_count);
  $value_for_button = "Filled";
}
?>
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Main Page</title>
  <style>
    body{
      background-color: white;
    }
    h1{
      margin-left: 20em;
      text-decoration: underline;
      color: black;
    }
    #header{
      display: flex;
      justify-content: space-between;
    }
    #h{
      margin-left: 18em;
      text-align: center;
      font-size: 2em;
      font-weight: bolder;
      text-decoration: underline;
    }
    #userid{
      font-weight: bold;
      font-size: 1.4em;
      margin-top: 1em;
      margin-right: 5em;
    }
    h2{
      margin-left: 2em;
      margin-top: 5em;
      text-decoration: underline;
    }
    table,th,td{
      border: 3px solid black;
    }
    table{
      width: 100%;
      border-collapse: collapse;
    }
    td{
      text-align: center;
    }
   th{
      font-weight: bold;
      font-size: 1.5em;
    }
    p{
      font-size: large;
    }
    .button_for_filling{
      font-size: larger;
      border: none;
      border-radius: 5px;
      background-color: red;
      color: white;
    }
    .button_for_filling:hover{
      background-color: green;
    }
  </style>
</head>
<body>
  <form method="post" action="">
  <div id="header">
  <div id="h">Pet Food Dispenser</div>
  <div id="userid">User ID: 1</div>
</div>
<h2>Your Product Details:</h2>
<p>Count: <b><?php echo $cnt;?></b></p>
<?php
if ($cnt===0){
echo "<input class='button_for_filling' type='submit' value=<?php echo $value_for_button;?> name='fillfood'>";
}
?>
<br>
<span><?php echo $cnterr;?></span>
<br>
<table>
  <tr >
    <th>Time</th>
    <th>Status</th>
    
  </tr>
  <tr>
    <td>B</td>
    <td>C</td>
  </tr>
</table>
</form>
</body>
<script>
  function FillFood(){

  }
</script>
</html>