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
 * func.file.inc
 * 
 * String related functions.
 *
 * @author Daniele Bonini <my25mb@has.im>
 * @copyrights (c) 2016, 2026 5 Mode
 */

/**
 * Copy a source file
 * 
 * @param string $sourceFilePath the file to copy
 * @param string $destFilePath the destination file
 * @return void
 */
function cp(string $sourceFilePath, string $destFilePath): void 
{
  $dataLength = 300000;
  $hsfile = fopen($sourceFilePath, "r");
  $hdfile = fopen($destFilePath, "w");
  while ($data = fread($hsfile, $dataLength)) {
    fwrite($hdfile, $data);
  }
  fclose($hsfile);
  fclose($hdfile);
}

/**
 * Store FileSystem data version of an XML snip field 
 * 
 * @param string $details the SimpleXML base details collection
 * @param string $filename the basedir
 * @param string $field the field to save
 * @return void
 */
function storeFSData($details, $filename, $field) {

  $datapath = APP_DATA_PATH . PHP_SLASH . $filename . PHP_SLASH . "data" . PHP_SLASH . $field;
  chdir($datapath);
  $pattern = "*";
  $apath = glob($pattern);
  foreach($apath as $path) {
    unlink($path);
  }  
  switch($field) {
    case "title":
      file_put_contents($details->detail[0]->title, PHP_STR);
      break;
    case "desc":
      file_put_contents($details->detail[0]->desc, PHP_STR);
      break;
    case "code":
      file_put_contents("code.txt", $details->detail[0]->code);
      break;
    case "tags":
      $tags = trim($details->detail[0]->tags);
      $a = explode(" ", $tags);
      foreach($a as $f) {
        file_put_contents($f, PHP_STR);
      }  
      break;
    case "cats":
      $cats = trim($details->detail[0]->cats);
      $a = explode(" ", $cats);
      foreach($a as $f) {
        file_put_contents($f, PHP_STR);
      }  
      break;
    case "label":
      file_put_contents($details->detail[1]->label, PHP_STR);
      break;
    case "link":
      file_put_contents($details->detail[1]->link, PHP_STR);
      break;
    case "email":
      file_put_contents($details->detail[1]->email, PHP_STR);
      break;
    case "guid":
      file_put_contents($details->detail[2]->guid, PHP_STR);
      break;
    case "password":
      file_put_contents($details->detail[3]->password, PHP_STR);
      break;
  }
  
}
