<?php

  require("_config.inc");

  chdir(APP_PRIVATE_PATH . DIRECTORY_SEPARATOR . "routes" . DIRECTORY_SEPARATOR . "cachedcrc"); 

  $source = $cachedScript;

  $cachedSource = "_cachedsource.php -- " . $source;

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
    echo_ifdebug(true, trim($cachedres)."<br>");
    echo_ifdebug(true, PHP_EOL . "CHECKING_CACHE_VALIDITY: ok!" . PHP_EOL);
  } else {
    echo_ifdebug(true, "<br>" . PHP_EOL . "CHECKING_CACHE_VALIDITY: uncoherent!" . PHP_EOL);
  }
