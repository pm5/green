<?php

/**
 * @file
 * Token integration for the file_entity module.
 */

/**
 * Implements hook_token_info().
 */
function media_youtube_token_info() {
  // File tokens.
  $info['tokens']['file']['youtube-url'] = array(
    'name' => t('Youtube URL'),
    'description' => t('The URL to view the video directly.'),
    'type' => 'youtube-url',
  );
  $info['tokens']['file']['youtube-thumb'] = array(
    'name' => t('Youtube Thumb'),
    'description' => t('The thumbnail of the video.'),
    'type' => 'youtube-thumb',
  );

  return $info;
}

/**
 * Implements hook_tokens().
 */
function media_youtube_tokens($type, $tokens, array $data = array(), array $options = array()){ $replacements = array(); 
  // File tokens.
  if ($type == 'file' && !empty($data['file'])) {
    $file = $data['file'];

    foreach ($tokens as $name => $original) {
      switch ($name) {
        case 'youtube-url':
          $watchurl = str_replace('youtube://v/', 'https://youtube.googleapis.com/v/', $file->uri);
          $replacements[$original] = $watchurl;
          break;

        case 'youtube-thumb':
          $wrapper = file_stream_wrapper_get_instance_by_uri($file->uri);
          $replacements[$original] = file_create_url($wrapper->getLocalThumbnailPath());
          break;
      }
    }
  }

  return $replacements;
}