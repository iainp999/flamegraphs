<?php

/**
 * Credit for the code in this include goes to Mark Sonnabaum; I've butchered it a little bit to encapsulate in
 * functions and make it fit what I want.
 *
 * Mark's original code can be found on github :-
 *
 *  - https://github.com/msonnabaum/xhprof-flamegraphs
 *
 */

/**
 * @param array $files
 * @return string
 */
function flamegraphs_generate_from_files($files = array()) {
  $data = '';

  foreach ($files as $file) {
    if (!file_exists($file)) {
      throw new RuntimeException("$file doesn't exist!");
    }
    $file = strpos($file, 'gz') === (strlen($file) - 2) ? "compress.zlib://$file" : $file;
    $raw_xhprof = @unserialize(file_get_contents($file));

    $data = flamegraphs_get_stack_data($raw_xhprof);
  }

  return $data;
}

/**
 * @param $dir
 * @return string
 */
function flamegraphs_generate_from_directory($dir) {
  $files = array();

  if (is_dir($dir)) {
    $files = glob("{$dir}/*.sample_xhprof") + glob("{$dir}/*.sample_xhprof.gz");
  }

  return flamegraphs_generate_from_files($files);
}

/**
 * Generate stacks from raw xhprof data.
 *
 * @param $raw_xhprof
 * @return string
 */
function flamegraphs_get_stack_data($raw_xhprof) {
  $stacks = array();

  foreach ($raw_xhprof as $stack) {
    $stack_key = implode(";", explode("==>", $stack));
    if (!isset($stacks[$stack_key])) {
      $stacks[$stack_key] = 0;
    }
    $stacks[$stack_key]++;
  }

  $stackData = '';

  foreach ($stacks as $stack => $count) {
    $stackData .= "$stack $count" . PHP_EOL;
  }

  return $stackData;
}