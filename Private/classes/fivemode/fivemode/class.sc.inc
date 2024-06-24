<?php

/**
 * Copyright 2021, 2026 5 Mode
 *
 * This file is part of SqueePF.
 *
 * SqueePF is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * SqueePF is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.  
 * 
 * You should have received a copy of the GNU General Public License
 * along with SqueePF. If not, see <https://www.gnu.org/licenses/>.
 *
 * class.sc.inc
 * 
 * SC class.
 *
 * @author Daniele Bonini <my25mb@has.im>
 * @copyrights (c) 2016, 2026, 5 Mode
 */

namespace fivemode\fivemode;

/**
 * Cache
 *
 * SC class
 *
 * @package  SC
 * @author   Daniele Bonini <my25mb@aol.com>
 * @version  1.0
 * @access   public
 */
final class SC
{
  /**
   * The static instance of SC
   *  
   * @access private
   * @var SC
   */
  private static $_instance = null;

  /**
   * Get the static instance of SC
   * 
   * @return SC
   */
  public static function &getInstance(): SC
  {  
    if(!isset(self::$_instance)){
      self::$_instance = new SC();
    }  
    return self::$_instance;  
  }

  /**
   * Check route structure
   * 
   * @param string $route the root to check
   *
   * @return bool
   */
  public static function SC_CHECK_ROUTE_STRU($route) 
  {

  $ret = false; 

  echo_ifdebug(true, "CHECKING_ROUTE_STRU: Start<br>");

  // Check for +DESC
  if (!is_readable(APP_PRIVATE_PATH . "/routes/" . $route . "/+DESC")) {
    return $ret;
  }

  echo_ifdebug(true, "CHECKING_ROUTE_STRU: +DESC: ok<br>");

  // Check for +CONTENT
  if (!is_readable(APP_PRIVATE_PATH . "/routes/" . $route . "/" . APP_SECRETS_FOLDER . "/+CONTENT")) {
    return $ret;
  }

  echo_ifdebug(true, "CHECKING_ROUTE_STRU: +CONTENT: exists<br>");

  // Check file dependencies list
  //  Private/routes/test/test.php
  //  Private/functions/func.various.inc
  //  Public/static/css/style.css
  //  Public/static/res/logot.png

  $af = file(APP_PRIVATE_PATH . "/routes/" . $route . "/" . APP_SECRETS_FOLDER . "/+CONTENT");
  foreach($af as &$line) {
    if (!is_readable(APP_PRIVATE_PATH . "/routes/" . $route . "/" . APP_SECRETS_FOLDER . "/" . trim(basename($line)) . "+scr")) {
      return $ret;
    }
    echo_ifdebug(true, "CHECKING_ROUTE_STRU: " . trim(basename($line)) . "+scr: exists<br>");
    if (left($line,7)==="Private") {
      if (!is_readable(APP_PRIVATE_PATH. trim(substr($line, 7)))) {
        return $ret;
      }
    } else {
      if (!is_readable(APP_PUBLIC_PATH . trim(substr($line, 6)))) {
        return $ret;
      }
    }
  }

  //echo_ifdebug(true, "CHECKING_ROUTE_STRU: +CONTENT: ok<br>");
  
  // Check for +REQUIRING
  if (!is_readable(APP_PRIVATE_PATH . "/routes/" . $route . "/" . APP_SECRETS_FOLDER . "/+REQUIRING")) {
    return $ret;
  }

  // Check route dependencies list
  $af = file(APP_PRIVATE_PATH . "/routes/" . $route . "/" . APP_SECRETS_FOLDER . "/+REQUIRING");
  foreach($af as &$line) {
    if (!is_readable(APP_PRIVATE_PATH . "/routes/" . $line)) {
      return $ret;
    }
  }

  echo_ifdebug(true, "CHECKING_ROUTE_STRU: +REQUIRING: ok<br>");

  return true;
}

 /**
  * Check route dependencies
  * 
  * @param string $route the root to check
  *
  * @return bool
  */
 public static function SC_CHECK_ROUTE_DEP($route) 
 {

  $ret = false; 

  echo_ifdebug(true, "CHECKING_ROUTE_DEP: Start<br>");

  // Check for +CONTENT
  if (!is_readable(APP_PRIVATE_PATH . "/routes/" . $route . "/" . APP_SECRETS_FOLDER . "/+CONTENT")) {
    return $ret;
  }

  // echo_ifdebug(true, "CHECKING_ROUTE_DEP: +CONTENT: exists<br>");

  //
  // Check file dependencies list
  //
  //
  //  index-scrs/:
  //    func.various.inc+scr:
  //	partial path
  //	size
  //	sha
  //    style.css+scr
  //	partial path
  //	size
  //	sha
  //
  //   Private/routes/test/test.php
  //   Private/functions/func.various.inc
  //   Public/static/css/style.css
  //   Public/static/res/logot.png
  //
  
  $af = file(APP_PRIVATE_PATH . "/routes/" . $route . "/" . APP_SECRETS_FOLDER . "/+CONTENT");
  foreach($af as &$line) {
    if (is_readable(APP_PRIVATE_PATH . "/routes/" . $route . "/" . APP_SECRETS_FOLDER . "/" . trim(basename($line)) . "+scr")) {
      $asf = file(APP_PRIVATE_PATH . "/routes/" . $route . "/" . APP_SECRETS_FOLDER . "/" . trim(basename($line)) . "+scr");
      $size = trim($asf[1]);
      $sha = trim($asf[2]);

      if (left($line,7)==="Private") {
        $filePath = APP_PRIVATE_PATH . trim(substr($line, 7));
      } else {
        $filePath = APP_PUBLIC_PATH . trim(substr($line, 6));
      }

      if (filesize($filePath) != $size) {
        return $ret;
      } 
 
      if (hash("sha256", file_get_contents($filePath), false) !== $sha) {
        return $ret;
      } 

      echo_ifdebug(true, "CHECKING_ROUTE_DEP: " . trim(basename($line)) . ": recognized<br>");

    } else {
      return $ret;
    }
  }

  return true;
            
 }

 /**
  * Check route dependencies
  * 
  * @param string $route the root to check
  *
  * @return bool
  */
 public static function SC_CHECK_ROUTE_RES($route) 
 {

  $ret = false; 
  $res = [];
  
  echo_ifdebug(true, "CHECKING_ROUTE_RES: Start<br>");

  // Check for +CONTENT
  if (!is_readable(APP_PRIVATE_PATH . "/routes/" . $route . "/" . APP_SECRETS_FOLDER . "/+CONTENT")) {
    return $ret;
  }

  //echo_ifdebug(true, "CHECKING_ROUTE_RES: +CONTENT: exists<br>");

  $af = file(APP_PRIVATE_PATH . "/routes/" . $route . "/" . APP_SECRETS_FOLDER . "/+CONTENT");
  if (left($af[0],7)==="Private") {
      $routeFilePath = APP_PRIVATE_PATH . trim(substr($af[0], 7));
  } else {
      $routeFilePath = APP_PUBLIC_PATH . trim(substr($af[0], 6));
  }

  $acf = file_get_contents($routeFilePath);
  
  // ANALYZING HEADER..
  preg_match_all("/<head>.*<\/head>/s", $acf, $c, PREG_PATTERN_ORDER);
  
  //print_r($c[0][0]); // html header
  preg_match_all('/\/js\/.+\.js/s', $c[0][0], $res, PREG_PATTERN_ORDER); 
  if (!empty($res[0])) { 
    foreach($res[0] as $item) {
      if (!in_array("Public".$item.PHP_EOL,$af)) {
        return $ret;
      }
     echo_ifdebug(true, "CHECKING_ROUTE_RES: $item in  " . basename($routeFilePath) . ": recognized<br>");      
    }
  }  
  preg_match_all('/\/css\/.+\.css/s', $c[0][0], $res, PREG_PATTERN_ORDER); 
  //print_r($res); 
  if (!empty($res)) {
    foreach($res[0] as $item) {
      //echo("Public".$item);
      if (!in_array("Public".$item.PHP_EOL,$af)) {
        return $ret;
     }
     echo_ifdebug(true, "CHECKING_ROUTE_RES: $item in " . basename($routeFilePath) . ": recognized<br>");
    }
  }
  //print_r($res[0]);

  // ANALYZING BODY..
  preg_match_all("/<body>.*<\/body>/s", $acf, $c, PREG_PATTERN_ORDER);
  
  //print_r($c[0][0]); // html body
  preg_match_all('/\/res\/.+\.png/s', $c[0][0], $res, PREG_PATTERN_ORDER); 
  if (!empty($res[0])) { 
    foreach($res[0] as $item) {
      //echo("Public".$item);
      if (!in_array("Public".$item.PHP_EOL,$af)) {
        return $ret;
      }
     echo_ifdebug(true, "CHECKING_ROUTE_RES: $item in  " . basename($routeFilePath) . ": recognized<br>");      
    }
  }  

  return true;
      
}                  

 /**
  * Route check entry point
  * 
  * @param string $route the root to check
  *
  * @return int
  */
 public static function SC_CHECK_ROUTE_ALL($route) 
 {
 
  $ret = 200;

  if (!is_readable(APP_PRIVATE_PATH . "/routes/" . $route)) {
    $ret = 404;
    return $ret;
  }

  if (!self::SC_CHECK_ROUTE_STRU($route) || !self::SC_CHECK_ROUTE_DEP($route) || !self::SC_CHECK_ROUTE_RES($route)) {
    $ret = 502;
    return $ret;
  }

  return $ret;                   
  
 }                                                       
                                                      
  /**
   * Check if the static instance is set
   * 
   * @return bool
   */
  public static function issetInstance(): bool
  {
    return isset(self::$_instance);
  }
  
  /**
   * Unset the static instance
   * 
   * @return void
   */
  public static function unsetInstance(): void
  {
    if (self::$_instance) {
      self::$_instance = null;
    }  
  }

  /**
   * Default constructor
   * 
   * @return void
   */
  private function __construct()
  {
  }
}
