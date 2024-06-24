<?php

  require("config.inc");

  if (!empty($cachedScript)) {
    if (!is_readable(__DIR__.DIRECTORY_SEPARATOR.$cachedScript)) {
      echo("Wrong &lt;source&gt; parameter: ".$cachedScript."<br>");
      exit(1);  
    }
  } 

  $cmdstr = $phpExecName." source.php -- ".$cachedScript;
  //__DIR__.DIRECTORY_SEPARATOR.$cachedScript;

  passthru($cmdstr);
 
