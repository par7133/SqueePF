<?php

  ob_start();

  require("test.php");

  $output = ob_get_clean();

  echo($output) . "<br>" . PHP_EOL;

  echo(hash("sha256", $output, false));