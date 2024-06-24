<?php

  require("config.inc");

  chdir(APP_PRIVATE_PATH . DIRECTORY_SEPARATOR . "routes" . DIRECTORY_SEPARATOR . "cachedcrc"); 

  $source = $cachedScript;

  $cachedSource = "cachedsource.php -- " . $source;

  //$phpcmdopts = "--php-ini $APP_PUBLIC_PATH/php.ini";

  //if (!exec("$phpExecName $source $phpcmdopts", $out)) {
  if (!exec("$phpExecName $source", $out1)) {
    echo "An hanexpected error happened!".PHP_EOL;
    exit(1);  
  } 

  //$cachedres = system("$phpExecName $cachedSource");
  $cachedres = exec("$phpExecName $cachedSource", $out2);

  foreach($out1 as $line) {
    echo($line)."<br>";
  }

  if (hash("sha256", trim($out1[count($out1)-1]), false) === trim($cachedres)) {
    echo(trim($cachedres)."<br>");
    echo(PHP_EOL . "good: php cache result verified." . PHP_EOL);   
  } else {
    echo("<br>" . PHP_EOL . "attention, php cache result is uncoherent!" . PHP_EOL);   
  }

