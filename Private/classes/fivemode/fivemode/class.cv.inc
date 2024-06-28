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
 * class.cv.inc
 * 
 * Caching validation class.
 *
 * @author Daniele Bonini <my25mb@has.im>
 * @copyrights (c) 2016, 2026, 5 Mode
 */

namespace fivemode\fivemode;

/**
 * Caching validation
 *
 * CV class
 *
 * @package  CV
 * @author   Daniele Bonini <my25mb@aol.com>
 * @version  1.0
 * @access   public
 */
final class CV
{
  /**
   * The static instance of CV
   *  
   * @access private
   * @var CV
   */
  private static $_instance = null;

  /**
   * Get the static instance of CV
   * 
   * @return CV
   */
  public static function &getInstance(): CV
  {  
    if(!isset(self::$_instance)){
      self::$_instance = new CV();
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
  public static function CV_CHECK_CACHE($route, $curPath, $echo) 
  {

  $cachedScript = $route . ".php";
  $source = $cachedScript;
  
  if (!exec(PHP_EXE_NAME." '".$curPath.DIRECTORY_SEPARATOR.$source."'", $out1)) {
    echo "An hanexpected error happened!".PHP_EOL;
    exit(1);  
  } 

  $sha1 = hash("sha256", implode("", $out1), false);

  ob_start(); 

  require($curPath.DIRECTORY_SEPARATOR.$source);

  $output = ob_get_clean();

  $sha2 = hash("sha256", $output, false);

  if ($echo) {
    foreach($out1 as $line) {
      echo($line)."<br>";
    }
  }
  
  if ($sha1 === $sha2) {
    echo_ifdebug($echo, $sha2."<br>");
    echo_ifdebug($echo, PHP_EOL . "CHECKING_CACHE_VALIDITY: ok!" . PHP_EOL);
    
    return true;
  } else {
    echo_ifdebug($echo, "<br>" . PHP_EOL . "CHECKING_CACHE_VALIDITY: uncoherent!" . PHP_EOL);
    
    return false;
  }
  
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
